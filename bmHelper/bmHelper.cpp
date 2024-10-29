#include "bmHelper.h"
#include "common.h"
#include <stdio.h>
#include "tlhelp32.h"
#include <QMovie>
#include <QMouseEvent>
#include <QResource>
#include <QFileInfo>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>
#include <Windows.h>
HANDLE findProcess(WCHAR* processName)
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("[---] Could not create snapshot.\n");
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32)) {

        CloseHandle(hProcessSnap);
        return FALSE;
    }

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do {

        if (!wcscmp(pe32.szExeFile, processName)) {
            wprintf(L"[+] The process %s was found in memory.\n", pe32.szExeFile);

            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
            if (hProcess != NULL) {
                return hProcess;
            }
            else {
                wprintf(L"[---] Failed to open process %s.\n", pe32.szExeFile);
                return NULL;

            }
        }

    } while (Process32Next(hProcessSnap, &pe32));

    wprintf(L"[---] %s has not been loaded into memory, aborting.\n", processName);
    return NULL;
}

/* Load DLL into remote process
* Gets LoadLibraryA address from current process, which is guaranteed to be same for single boot session across processes
* Allocated memory in remote process for DLL path name
* CreateRemoteThread to run LoadLibraryA in remote process. Address of DLL path in remote memory as argument
*/
BOOL loadRemoteDLL(HANDLE hProcess, const char* dllPath)
{
    printf("Enter any key to attempt DLL injection.");

    // Allocate memory for DLL's path name to remote process
    LPVOID dllPathAddressInRemoteMemory = VirtualAllocEx(hProcess, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (dllPathAddressInRemoteMemory == NULL) {
        printf("[---] VirtualAllocEx unsuccessful.\n");

        getchar();
        return FALSE;
    }

    // Write DLL's path name to remote process
    BOOL succeededWriting = WriteProcessMemory(hProcess, dllPathAddressInRemoteMemory, dllPath, strlen(dllPath), NULL);

    if (!succeededWriting) {
        printf("[---] WriteProcessMemory unsuccessful.\n");

        getchar();
        return FALSE;
    }
    else {
        // Returns a pointer to the LoadLibrary address. This will be the same on the remote process as in our current process.
        LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
        if (loadLibraryAddress == NULL) {
            printf("[---] LoadLibrary not found in process.\n");

            getchar();
            return FALSE;
        }
        else {
            HANDLE remoteThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryAddress, dllPathAddressInRemoteMemory, NULL, NULL);
            if (remoteThread == NULL) {
                printf("[---] CreateRemoteThread unsuccessful.\n");

                return FALSE;
            }
        }
    }

    CloseHandle(hProcess);
    return TRUE;
}


struct bind_playerInfo_param_t {
    void* obj;
    int number;
};
bind_playerInfo_param_t bind_playerInfo_param[3] = {0};

static void *globalSpeaker = nullptr;
void savePositionCallback(void* arg)
{
    bmHelper* obj = (bmHelper*)arg;
    obj->speaker->playInternal("已保存当前位置");
    CommonData::config.targetPlayerLocation = CommonData::locationBuffer.playerLocation;
    printf("event: %d, received: %.05f, %.05f, %.05f\n", static_cast<int>(CommonData::locationBuffer.event), CommonData::locationBuffer.playerLocation.X, CommonData::locationBuffer.playerLocation.Y, CommonData::locationBuffer.playerLocation.Z);
    printf("save position pressed!");
    /* obj->server->write((void*)&a, sizeof(int)); */

}
void setPositionCallback(void* arg)
{
    bmHelper* obj = (bmHelper*)arg;
    HANDLE hProcess = nullptr;

    hProcess = findProcess((LPWSTR)L"b1-Win64-Shipping.exe");
    if (hProcess && obj->injected && CommonData::gameStatus.gameInited) {
        CommonData::gameInfo_t send(CommonData::event_t::EVENT_PLAYER_LOCATION_SET);
        send.targetPlayerLocation = CommonData::config.targetPlayerLocation;

        obj->server->write((void*)&send, sizeof(CommonData::gameInfo_t));

        obj->speaker->playInternal("已传送至保存的位置");
        printf("set position pressed!");
    }
    else {
        if (!CommonData::gameStatus.gameInited && hProcess) {
            obj->speaker->playInternal("未进入游戏世界，无法传送");
        }
        else {
            obj->speaker->playInternal("未检测到游戏, 毛都获取不到啊");
        }
        
    }
    

}
static void playInfoNotify(void* arg)
{
    QString tip;
    bind_playerInfo_param_t* obj = (bind_playerInfo_param_t*)arg;
    bmHelper *owner = (bmHelper *)obj->obj;
    int number = obj->number;
    if (number == 0) {
        tip = QString("血量: %1, 血瓶: %2") \
            .arg(CommonData::infoBuffer.playerInfo.playerHp).arg(CommonData::infoBuffer.playerInfo.playerBloodButton);
    }
    else if (number == 1) {
        tip = QString("灵力: %1, 蓝条: %2") \
            .arg(CommonData::infoBuffer.playerInfo.playerStamina).arg(CommonData::infoBuffer.playerInfo.playerMp);
    }
    else if (number == 2) {
        QString buffer;
        if (CommonData::infoBuffer.playerInfo.playerBurn)
            buffer = "烧伤";
        else if (CommonData::infoBuffer.playerInfo.playerFreeze)
            buffer = "冻结";
        else if (CommonData::infoBuffer.playerInfo.playerPoison)
            buffer = "中毒";
        else if (CommonData::infoBuffer.playerInfo.playerThunder)
            buffer = "麻痹";
        else {
            buffer = "没异常啊卧槽";
        }
        tip = QString("能量: %1, 异常: %2") \
            .arg(CommonData::infoBuffer.playerInfo.playerEnergy).arg(buffer);
    }


    owner->speaker->playInternal(tip);

}
void increaseVolume(void* arg)
{
    bmHelper* obj = (bmHelper*)arg;
    obj->speaker->setVolume(true);
}
void decreaseVolume(void* arg)
{
    bmHelper* obj = (bmHelper*)arg;
    obj->speaker->setVolume(false);
}
void increaseSpeed(void* arg)
{
    bmHelper* obj = (bmHelper*)arg;
    obj->speaker->setSpeed(true);
}
void decreaseSpeed(void* arg)
{
    bmHelper* obj = (bmHelper*)arg;
    obj->speaker->setSpeed(false);
}

int my_wprintf(const wchar_t* format, ...)
{
    int n;
    va_list list;
    wchar_t str[1024];
    DWORD ret;
    HANDLE console;

    va_start(list, format);
    n = _vsnwprintf_s(str, _countof(str), _countof(str) - 1, format, list);
    va_end(list);

    console = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleW(console, str, (DWORD)wcslen(str), &ret, NULL);
    return n;
}
std::string wcharToString(const std::wstring& wstr)
{
    // 获取所需缓冲区大小，以存储转换后的字符串，包括空终止字符。
    size_t len = 0;
    errno_t err = wcstombs_s(&len, nullptr, 0, wstr.c_str(), _TRUNCATE);
    if (err != 0) {
        throw std::runtime_error("wcstombs_s failed to calculate size");
    }

    std::vector<char> buffer(len);
    err = wcstombs_s(&len, buffer.data(), buffer.size(), wstr.c_str(), _TRUNCATE);
    if (err != 0) {
        throw std::runtime_error("wcstombs_s failed to convert");
    }

    return std::string(buffer.data());
}

std::string charArrayToString(const char* data, size_t length)
{
    if (length % 2 != 0) {
        throw std::invalid_argument("The length must be even.");
    }

    std::wstring wstr;
    wstr.reserve(length / 2); // 提前分配空间

    // 反转每两个字节并转换为 wchar_t
    for (size_t i = 0; i < length; i += 2) {
        wchar_t wc = (static_cast<unsigned char>(data[i + 1]) << 8) | static_cast<unsigned char>(data[i]);
        wstr.push_back(wc);
    }

    return wcharToString(wstr);
}
void testRecv(void* arg)
{
    
    if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_PLAYER_INFO) {
        printf("received player info\n");
        memcpy(&CommonData::infoBuffer, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_PLAYER_LOCATION) {
        printf("received location info\n");
        memcpy(&CommonData::locationBuffer, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_ENEMY_MAP) {
        printf("received enemy info\n");
        memcpy(&CommonData::enemyInfo, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        if(CommonData::enemyInfo.enemyInfo.playerHp)
        printf("enemy: %.5f", CommonData::enemyInfo.enemyInfo.playerHp);
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_GAMESTATUS) {
        memcpy(&CommonData::gameStatus, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        printf("gameStatus: %d\n", CommonData::gameStatus.gameInited);
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_SPEAKERINFO) {
        memcpy(&CommonData::speakerInfo, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        printf("received speaker info, length: %d\n", CommonData::speakerInfo.speakerInfo.length);
        
        
        /*for (int i = 0; i < CommonData::speakerInfo.speakerInfo.length / 2 - 1; i++) {
            char tmp;
            tmp = ((char *)CommonData::speakerInfo.speakerInfo.label)[i];
            ((char*)CommonData::speakerInfo.speakerInfo.label)[i] = ((char*)CommonData::speakerInfo.speakerInfo.label)[i+1];
            ((char*)CommonData::speakerInfo.speakerInfo.label)[i + 1] = tmp;
        }*/
        /*printf("TEXT: ");
        const wchar_t* labelPtr = CommonData::speakerInfo.speakerInfo.label;
        size_t length_in_bytes = CommonData::speakerInfo.speakerInfo.length;

        const char* byteLabelPtr = reinterpret_cast<const char*>(labelPtr);
        for (size_t i = 0; i < length_in_bytes; ++i) {
            printf("%02x ", static_cast<unsigned char>(byteLabelPtr[i]));
        }
        printf("\n");*/
        /*my_wprintf(L"[接收到的数据] %s\n", CommonData::speakerInfo.speakerInfo.label);*/
        std::wstring ws(CommonData::speakerInfo.speakerInfo.label);
        QString tip = QString::fromStdWString(ws);
        if(globalSpeaker)
            ((spkMgr *)globalSpeaker)->playInternal(tip);
        /*std::string result = charArrayToString(CommonData::speakerInfo.speakerInfo.label, CommonData::speakerInfo.speakerInfo.length);
        printf("char data is %s", result.c_str());*/
    }
    
    /*printf("[post]event: %d, received: %.05f, %.05f, %.05f\n", static_cast<int>(CommonData::buffer.event), CommonData::buffer.playerLocation.X, CommonData::buffer.playerLocation.Y, CommonData::buffer.playerLocation.Z);
    if(CommonData::buffer.event & CommonData::event_t::EVENT_PLAYER_INFO) {
        printf("event: %d, received: %.05f, %.05f, %.05f\n", static_cast<int>(CommonData::buffer.event), CommonData::buffer.playerLocation.X, CommonData::buffer.playerLocation.Y, CommonData::buffer.playerLocation.Z);
    }
    if(CommonData::buffer.event & CommonData::event_t::EVENT_PLAYER_LOCATION_SET) {
        printf("event: %d, received: %.05f, %.05f, %.05f\n", static_cast<int>(CommonData::buffer.event), CommonData::buffer.playerLocation.X, CommonData::buffer.playerLocation.Y, CommonData::buffer.playerLocation.Z);
    }*/

}

void bmHelper::playReadme(void *arg)
{
    bmHelper* obj = (bmHelper*)arg;
    QString tip = QString("退出程序请按ctrl+t, ctrl加方向键控制音量和语速, 大小写切换键播报敌人信息, F1,开启自动提醒,F2,切换提醒模式,F3,缩短提醒间隔,F4增加提醒间隔, ctrl加 西,保存角色位置, ctrl加V,传送到保存的位置, Z,血量信息,X,蓝量信息,西,异常状态信息, 退出程序请按ctrl+t");
    obj->speaker->playInternal(tip);

}

void getEnemyDelta(void* arg)
{
    bmHelper* obj = (bmHelper*)arg;
    QString tip = "";

    tip = QString("距离: %1, 血量: %2").arg((int)(CommonData::enemyInfo.enemyInfo.enemyDelta)).arg(CommonData::enemyInfo.enemyInfo.playerHp);
    obj->speaker->playInternal(tip);

}


void bmHelper::injectThread(HANDLE &&hProcess)
{

    if (!hProcess) {
        if(this->quitAll)
            return;
        hProcess = findProcess((LPWSTR)L"b1-Win64-Shipping.exe");
        Sleep(1000);
    }
    
    

    Sleep(17000);
    QString relativePath = ".\\bmDLL.dll";
    QString absolutePath = QFileInfo(relativePath).absoluteFilePath();
    BOOL injectSuccessful = loadRemoteDLL(hProcess, absolutePath.toStdString().c_str());

    printf("[+] DLL injection successful! \n");
    

    this->speaker->playInternal("正在加载游戏信息");
    


}

void bmHelper::initHelperThread()
{
    while (1) {
        
        HANDLE hProcess = nullptr;

        hProcess = findProcess((LPWSTR)L"b1-Win64-Shipping.exe");
        if (!hProcess) {
            this->injected = false; 
        }
        else {
            if (!this->injected) {
                this->injected = true;
                this->injectHelper = std::thread(&bmHelper::injectThread, this, std::move(hProcess));
                this->injectHelper.join();
            }
            
        }
        Sleep(5000);

    }

}

namespace mPet {
namespace mPetConfig {
    constexpr int mMaxScaleWidth = 800;
    constexpr int mMaxScaleHeight = 600;

    constexpr int mMinScaleWidth = 128;
    constexpr int mMinScaleHeight = 256;

    constexpr int mDefaultScaleSize = 256;

} /* mPetConfig */

} /* mPet */

static void quit(void* arg) {
    bmHelper* obj = (bmHelper*)arg;
    obj->speaker->playInternal("已退出程序");
    
    QTimer::singleShot(1000, [obj]() {
        obj->trayIcon->setVisible(false);
        obj->quitAll = true;
        QApplication::quit();
        std::exit(0);
    });
    
   
    
    
}

static void autoAttentionSwitch(void* arg) {
    bmHelper* obj = (bmHelper*)arg;
    obj->autoAttention = !obj->autoAttention;
    if(obj->autoAttention)
        obj->speaker->playInternal("开启提醒");
    else {
        obj->speaker->playInternal("关闭提醒");
    }
}




void bmHelper::autoInfoAttentionThread()
{
    QString tip;
    while (1) {
        if (this->autoAttention) {
            if (this->attentionMode == 0) {
                tip = QString("距离 %1 ,血量 %2") \
                    .arg(CommonData::enemyInfo.enemyInfo.enemyDelta).arg(CommonData::enemyInfo.enemyInfo.playerHp);
                this->speaker->play(tip);
            }
            else if (this->attentionMode == 1) {
                tip = QString("血量 %1 ,灵力 %2") \
                    .arg(CommonData::infoBuffer.playerInfo.playerHp).arg(CommonData::infoBuffer.playerInfo.playerStamina);
                this->speaker->play(tip);
            }
            else if (this->attentionMode == 2) {
                tip = QString("敌方 %1, 自身 %2") \
                    .arg(CommonData::enemyInfo.enemyInfo.playerHp).arg(CommonData::infoBuffer.playerInfo.playerHp);
                this->speaker->play(tip);
            }
        }
        Sleep(this->autoAttentionPeriod);
    }
}
void bmHelper::importantInfoThread()
{
    QString tip;
    static int notifyCount = 0;
    static bool normal = true;
    while (1) {
        if (notifyCount < 3) {
            if (CommonData::infoBuffer.playerInfo.playerBurn) {
                notifyCount++;
                normal = false;
                tip = QString("注意,角色烧伤");
                this->speaker->playInternal(tip);
            }
            else if (CommonData::infoBuffer.playerInfo.playerFreeze) {
                notifyCount++;
                normal = false;
                tip = QString("注意,角色冻结");
                this->speaker->playInternal(tip);
            }
            else if (CommonData::infoBuffer.playerInfo.playerPoison) {
                notifyCount++;
                normal = false;
                tip = QString("注意,角色中毒");
                this->speaker->playInternal(tip);
            }
            else if (CommonData::infoBuffer.playerInfo.playerThunder) {
                notifyCount++;
                normal = false;
                tip = QString("注意,角色麻痹");
                this->speaker->playInternal(tip);
            }
            else {
                normal = true;
            }
        }
        
        if(normal)
            notifyCount = 0;
        

        Sleep(2000);
    }

}

static void autoAttentionModeSwitch(void* arg)
{
    bmHelper* obj = (bmHelper*)arg;
    QString tip;
    if (obj->attentionMode + 1 > 2) {
        obj->attentionMode = 0;
    }
    else {
        obj->attentionMode++;
    }
    if (obj->attentionMode == 0) {
        tip = QString("敌方提醒");
    }
    else if (obj->attentionMode == 1) {
        tip = QString("自身提醒");
    }
    else if (obj->attentionMode == 2) {
        tip = QString("双方提醒");
    }
    obj->speaker->playInternal(tip);
}

static void autoAttentionIncrease(void* arg) {
    bmHelper* obj = (bmHelper*)arg;
    QString tip;

    if (obj->autoAttentionPeriod + 1000 >= 20000)
        obj->autoAttentionPeriod = 20000;
    else
        obj->autoAttentionPeriod += 1000;

    tip = QString("提醒间隔: %1 秒").arg(obj->autoAttentionPeriod / 1000);
    obj->speaker->playInternal(tip);

}

static void autoAttentionDecrease(void* arg) {
    bmHelper* obj = (bmHelper*)arg;
    QString tip;

    if (obj->autoAttentionPeriod - 1000 <= 0)
        obj->autoAttentionPeriod = 1000;
    else
        obj->autoAttentionPeriod -= 1000;

    tip = QString("提醒间隔: %1 秒").arg(obj->autoAttentionPeriod / 1000);
    obj->speaker->playInternal(tip);

    
        
    
}
bmHelper::bmHelper(QWidget *parent)
    : QWidget(parent)
{
    SetConsoleOutputCP(CP_UTF8);

    QResource::registerResource("bmHelper.rcc");
    ui.setupUi(this);
    spdlog::info("fucktest!");
    trayIcon = new QSystemTrayIcon(this);

    trayIcon->setIcon(QIcon(":/res/bm.png"));

    QMenu* trayIconMenu = new QMenu(this);

    QAction* quitAction = new QAction("退出", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    trayIconMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayIconMenu);

    trayIcon->show();
    /*Q_INIT_RESOURCE(bmHelper);*/
    /*bool result = QResource::registerResource("bmHelper.rcc");
    std::cout << result << std::endl;*/
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);

    this->mDragging = false;
    QString resourcePath = ".\\bm.gif";
    this->mPetMovie = new QMovie(resourcePath);
    if (!this->mPetMovie->isValid()) {
        std::cout << "GIF file is invalid!" << std::endl;
        resourcePath = ".\\bm.png";
        this->mPetMovie = new QMovie(resourcePath);
        if (!this->mPetMovie->isValid()) {
            resourcePath = ".\\bm.jpg";
            this->mPetMovie = new QMovie(resourcePath);


        }

        
    }
    this->mPetMovie->setParent(this);

    ui.mPetLabel->setMovie(mPetMovie);

    ui.mPetLabel->setScaledContents(true);
    this->mPetMovie->start();

    QRect rect = mPetMovie->frameRect();
    float width = rect.width();
    float height = rect.height();

    this->mPetWidthFactor = width / (height + width);
    this->mPetHeightFactor = height / (height + width);

    qDebug() << "GIF Width:" << this->mPetWidthFactor << ", Height:" << this->mPetHeightFactor;


    ui.mPetLabel->resize(mPet::mPetConfig::mDefaultScaleSize * this->mPetWidthFactor, mPet::mPetConfig::mDefaultScaleSize * this->mPetHeightFactor);
    ui.mPetLabel->setAlignment(Qt::AlignCenter);
    ui.mPetLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui.mPetLabel->setMinimumSize(1, 1);


    this->quitAll = false;
    this->injected = false;
    this->autoAttention = false;
    this->autoAttentionPeriod = 2000;
    QString tip;
    key = new keyMgr();
    speaker = new spkMgr();
    server = new MocIPC::IPCServer();
    globalSpeaker = speaker;
    server->registerRecvHOOK(testRecv);

    key->bindKeys({ VK_CONTROL, 'C' }, savePositionCallback, this);
    key->bindKeys({ VK_CONTROL, 'V' }, setPositionCallback, this);
    key->bindKeys({ VK_CONTROL, VK_SHIFT, 'D' }, &bmHelper::playReadme, this);

    key->bindKeys({ VK_CONTROL, VK_LEFT }, &decreaseVolume, this);
    key->bindKeys({ VK_CONTROL, VK_RIGHT }, &increaseVolume, this);
    key->bindKeys({ VK_CONTROL, VK_DOWN }, &decreaseSpeed, this);
    key->bindKeys({ VK_CONTROL, VK_UP }, &increaseSpeed, this);

    key->bindKeys({ VK_CONTROL, 'T' }, &quit, this);
    
    key->bindKeys({ VK_F1 }, &autoAttentionSwitch, this);
    key->bindKeys({ VK_F2 }, &autoAttentionModeSwitch, this);
    key->bindKeys({ VK_F3 }, &autoAttentionDecrease, this);
    key->bindKeys({ VK_F4 }, &autoAttentionIncrease, this);
    
    bind_playerInfo_param[0].obj = this;
    bind_playerInfo_param[1].obj = this;
    bind_playerInfo_param[2].obj = this;
    bind_playerInfo_param[0].number = 0;
    bind_playerInfo_param[1].number = 1;
    bind_playerInfo_param[2].number = 2;
    key->bindKeys({ 'Z' }, playInfoNotify, &bind_playerInfo_param[0]);
    key->bindKeys({ 'X' }, playInfoNotify, &bind_playerInfo_param[1]);
    key->bindKeys({ 'C' }, playInfoNotify, &bind_playerInfo_param[2]);

    key->bindKeys({ VK_CAPITAL }, getEnemyDelta, this);

    this->speaker->setSpeed(20);
    tip = QString("初始化环境成功, 按下 %1 + %2 + %3 阅读使用说明, control + T退出程序") \
            .arg("control").arg("shift").arg("D");
    speaker->playInternal(tip);

 
     /*notifyThread(this);*/
    /*RemoteThreadInject32((LPWSTR)L"b1-Win64-Shipping.exe", (LPWSTR)L"D:\\WORK\\blackmyth\\dlltest\\x64\\Debug\\bmdll.dll");*/

    initHelper = std::thread(&bmHelper::initHelperThread, this);
    initHelper.detach();
    

    autoAttentionHelper = std::thread(&bmHelper::autoInfoAttentionThread, this);
    autoAttentionHelper.detach();

    
    importantInfoHelper = std::thread(&bmHelper::importantInfoThread, this);
    importantInfoHelper.detach();
}



void bmHelper::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (mDragging) {
            move(mObjetCurrentPos + event->globalPosition().toPoint() - mDraggingStartPos);
            event->accept();
        }
    }

}

void bmHelper::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        mDragging = true;
        mDraggingStartPos = event->globalPosition().toPoint();
        mObjetCurrentPos = this->frameGeometry().topLeft();
        event->accept();
    }

}

void bmHelper::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        mDragging = false;
        event->accept();
    }

}
