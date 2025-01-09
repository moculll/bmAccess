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

HANDLE findProcess(WCHAR* processName)
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        spdlog::info("[---] Could not create snapshot.");
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

            spdlog::info("[+] The process {} was found in memory.", wcharToString(std::wstring(pe32.szExeFile)));

            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
            if (hProcess != NULL) {
                return hProcess;
            }
            else {
                spdlog::info("[---] Failed to open process {}.", wcharToString(std::wstring(pe32.szExeFile)));
                return NULL;

            }
        }

    } while (Process32Next(hProcessSnap, &pe32));

    spdlog::info("[---] {} has not been loaded into memory, aborting.", wcharToString(std::wstring(processName)));
    return NULL;
}

/* Load DLL into remote process
* Gets LoadLibraryA address from current process, which is guaranteed to be same for single boot session across processes
* Allocated memory in remote process for DLL path name
* CreateRemoteThread to run LoadLibraryA in remote process. Address of DLL path in remote memory as argument
*/
BOOL loadRemoteDLL(HANDLE hProcess, const char* dllPath)
{
    spdlog::info("Enter any key to attempt DLL injection.");

    // Allocate memory for DLL's path name to remote process
    LPVOID dllPathAddressInRemoteMemory = VirtualAllocEx(hProcess, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (dllPathAddressInRemoteMemory == NULL) {
        spdlog::info("[---] VirtualAllocEx unsuccessful.");

        getchar();
        return FALSE;
    }

    // Write DLL's path name to remote process
    BOOL succeededWriting = WriteProcessMemory(hProcess, dllPathAddressInRemoteMemory, dllPath, strlen(dllPath), NULL);

    if (!succeededWriting) {
        spdlog::info("[---] WriteProcessMemory unsuccessful.");

        getchar();
        return FALSE;
    }
    else {
        // Returns a pointer to the LoadLibrary address. This will be the same on the remote process as in our current process.
        LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
        if (loadLibraryAddress == NULL) {
            spdlog::info("[---] LoadLibrary not found in process.");

            getchar();
            return FALSE;
        }
        else {
            HANDLE remoteThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryAddress, dllPathAddressInRemoteMemory, NULL, NULL);
            if (remoteThread == NULL) {
                spdlog::info("[---] CreateRemoteThread unsuccessful.");

                return FALSE;
            }
        }
    }

    CloseHandle(hProcess);
    return TRUE;
}

std::array<DirectX::XMFLOAT3, 3> getPlayerAudioInfo()
{
    DirectX::XMFLOAT3 newLocation = { static_cast<float>(CommonData::locationBuffer.playerLocationInfo.Location.X * 8), static_cast<float>(CommonData::locationBuffer.playerLocationInfo.Location.Y * 8), static_cast<float>(CommonData::locationBuffer.playerLocationInfo.Location.Z * 8) };

    auto locationMin = bmHelper::mapMgr->getCurrentMapRange()[0];
    auto locationMax = bmHelper::mapMgr->getCurrentMapRange()[1];
    DirectX::XMFLOAT3 mapMinRange = { static_cast<float>(locationMin.X), static_cast<float>(locationMin.Y), static_cast<float>(locationMin.Z) };
    DirectX::XMFLOAT3 mapMaxRange = { static_cast<float>(locationMax.X), static_cast<float>(locationMax.Y), static_cast<float>(locationMax.Z) };
    auto newLocationForAudio = MGameAudio::posGame2Audio<DirectX::XMFLOAT3>(newLocation, mapMinRange, mapMaxRange);
    auto rotatorNormalized = CommonData::locationBuffer.playerLocationInfo.Rotator.GetNormalized();
    auto orientTopNormalized = CommonData::locationBuffer.playerLocationInfo.OrientTop.GetNormalized();
    DirectX::XMFLOAT3 newOrientFront = { static_cast<float>(rotatorNormalized.X), static_cast<float>(rotatorNormalized.Y), static_cast<float>(rotatorNormalized.Z) };
    DirectX::XMFLOAT3 newOrientTop = { static_cast<float>(orientTopNormalized.X), static_cast<float>(orientTopNormalized.Y), static_cast<float>(orientTopNormalized.Z) };
    return { newLocationForAudio, newOrientFront, newOrientTop };
}

std::array<DirectX::XMFLOAT3, 3> getEnemyAudioInfo()
{
    DirectX::XMFLOAT3 newLocation = { static_cast<float>(CommonData::enemyInfo.enemyInfo.Location.X * 8), static_cast<float>(CommonData::enemyInfo.enemyInfo.Location.Y * 8), static_cast<float>(CommonData::enemyInfo.enemyInfo.Location.Z * 8) };

    auto locationMin = bmHelper::mapMgr->getCurrentMapRange()[0];
    auto locationMax = bmHelper::mapMgr->getCurrentMapRange()[1];
    DirectX::XMFLOAT3 mapMinRange = { static_cast<float>(locationMin.X), static_cast<float>(locationMin.Y), static_cast<float>(locationMin.Z) };
    DirectX::XMFLOAT3 mapMaxRange = { static_cast<float>(locationMax.X), static_cast<float>(locationMax.Y), static_cast<float>(locationMax.Z) };
    auto newLocationForAudio = MGameAudio::posGame2Audio<DirectX::XMFLOAT3>(newLocation, mapMinRange, mapMaxRange);
    auto rotatorNormalized = CommonData::enemyInfo.enemyInfo.Rotator.GetNormalized();
    auto orientTopNormalized = CommonData::enemyInfo.enemyInfo.OrientTop.GetNormalized();
    DirectX::XMFLOAT3 newOrientFront = { static_cast<float>(rotatorNormalized.X), static_cast<float>(rotatorNormalized.Y), static_cast<float>(rotatorNormalized.Z) };
    DirectX::XMFLOAT3 newOrientTop = { static_cast<float>(orientTopNormalized.X), static_cast<float>(orientTopNormalized.Y), static_cast<float>(orientTopNormalized.Z) };
    return { newLocationForAudio, newOrientFront, newOrientTop };
}

DirectX::XMFLOAT3 CalculateFacingOrientFront(
    const DirectX::XMFLOAT3& characterPosition,
    const DirectX::XMFLOAT3& targetPosition)
{
    DirectX::XMFLOAT3 direction = {
        targetPosition.x - characterPosition.x,
        targetPosition.y - characterPosition.y,
        targetPosition.z - characterPosition.z
    };

    DirectX::XMVECTOR dirVector = DirectX::XMLoadFloat3(&direction);
    dirVector = DirectX::XMVector3Normalize(dirVector);

    DirectX::XMFLOAT3 orientFront;
    DirectX::XMStoreFloat3(&orientFront, dirVector);
    return orientFront;
}
std::array<DirectX::XMFLOAT3, 3> getMapAudioInfo()
{
    auto unit = bmHelper::mapMgr->getUnit<BmMapMgr::PointDirection::CUR>();
    auto playerInfo = getPlayerAudioInfo();

    DirectX::XMFLOAT3 newLocation = { static_cast<float>(unit->point.X * 8), static_cast<float>(unit->point.Y * 8), static_cast<float>(unit->point.Z * 8) };

    auto locationMin = bmHelper::mapMgr->getCurrentMapRange()[0];
    auto locationMax = bmHelper::mapMgr->getCurrentMapRange()[1];
    DirectX::XMFLOAT3 mapMinRange = { static_cast<float>(locationMin.X), static_cast<float>(locationMin.Y), static_cast<float>(locationMin.Z) };
    DirectX::XMFLOAT3 mapMaxRange = { static_cast<float>(locationMax.X), static_cast<float>(locationMax.Y), static_cast<float>(locationMax.Z) };
    DirectX::XMFLOAT3 newLocationForAudio = MGameAudio::posGame2Audio<DirectX::XMFLOAT3>(newLocation, mapMinRange, mapMaxRange);
    DirectX::XMFLOAT3 newOrientFront = CalculateFacingOrientFront(playerInfo[0], newLocationForAudio);

    return { newLocationForAudio, newOrientFront, playerInfo[2] };
}

void testRecv(void* arg)
{
    
    if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_PLAYER_INFO) {
        
        memcpy(&CommonData::infoBuffer, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_PLAYER_LOCATION) {
        
        memcpy(&CommonData::locationBuffer, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        if((bmHelper::mapMgr->getCurrentMapRange().empty()))
            return;
        auto audioInfo = getPlayerAudioInfo();
        spdlog::info("[Listener]: X: {}, Y: {}, Z: {}", audioInfo[0].x, audioInfo[0].y, audioInfo[0].z);
        MGameAudio::updatePosition<MGameAudio::UpdatePositionParam::LISTENER>("closestEnemy", audioInfo[0], audioInfo[1], audioInfo[2]);
        MGameAudio::updatePosition<MGameAudio::UpdatePositionParam::LISTENER>("mapTarget", audioInfo[0], audioInfo[1], audioInfo[2]);
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_ENEMY_MAP) {
        
        memcpy(&CommonData::enemyInfo, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        if(CommonData::enemyInfo.enemyInfo.playerHp)
            spdlog::info("enemy: {:.5f}", CommonData::enemyInfo.enemyInfo.playerHp);
        if(bmHelper::mapMgr->getCurrentMapRange().empty())
            return;
        auto audioInfo = getEnemyAudioInfo();
        spdlog::info("[Emitter]: X: {}, Y: {}, Z: {}", audioInfo[0].x, audioInfo[0].y, audioInfo[0].z);
        MGameAudio::updatePosition<MGameAudio::UpdatePositionParam::EMITTER>("closestEnemy", audioInfo[0], audioInfo[1], audioInfo[2]);
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_GAMEINITED_RESULT) {
        memcpy(&CommonData::gameStatus, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        spdlog::info("gameStatus: {}", CommonData::gameStatus.gameInited);
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_SPEAKERINFO) {
        memcpy(&CommonData::speakerInfo, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        spdlog::info("received speaker info, length: {}", CommonData::speakerInfo.speakerInfo.length);
        
        
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
        if(bmHelper::speaker)
            bmHelper::speaker->playInternal(tip);
        /*std::string result = charArrayToString(CommonData::speakerInfo.speakerInfo.label, CommonData::speakerInfo.speakerInfo.length);
        printf("char data is %s", result.c_str());*/
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_LEVELINFO) {
        static bool result;
        memcpy(&CommonData::levelInfoBuffer, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        if(bmHelper::mapMgr->getCurrentMap() != CommonData::levelInfoBuffer.levelInfo.levelId) {
            result = bmHelper::mapMgr->updateCurrentMap(CommonData::levelInfoBuffer.levelInfo.levelId, CommonData::locationBuffer.playerLocationInfo.Location.X, CommonData::locationBuffer.playerLocationInfo.Location.Y, CommonData::locationBuffer.playerLocationInfo.Location.Z);
            
            spdlog::info("update map[{}] result: {}", CommonData::levelInfoBuffer.levelInfo.levelId, result ? 1 : 0);
        }
        
    }
    else if (MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_DLL_EXIT_REQ) {
        memcpy(&CommonData::gameStatus, MocIPC::getArg<CommonData::gameInfo_t*>(arg), sizeof(CommonData::gameInfo_t));
        if (CommonData::gameStatus.dllExitReq) {
            bmHelper::injected = false;
        }

    }
    /*printf("[post]event: %d, received: %.05f, %.05f, %.05f\n", static_cast<int>(CommonData::buffer.event), CommonData::buffer.playerLocation.X, CommonData::buffer.playerLocation.Y, CommonData::buffer.playerLocation.Z);
    if(CommonData::buffer.event & CommonData::event_t::EVENT_PLAYER_INFO) {
        printf("event: %d, received: %.05f, %.05f, %.05f\n", static_cast<int>(CommonData::buffer.event), CommonData::buffer.playerLocation.X, CommonData::buffer.playerLocation.Y, CommonData::buffer.playerLocation.Z);
    }
    if(CommonData::buffer.event & CommonData::event_t::EVENT_PLAYER_LOCATION_SET) {
        printf("event: %d, received: %.05f, %.05f, %.05f\n", static_cast<int>(CommonData::buffer.event), CommonData::buffer.playerLocation.X, CommonData::buffer.playerLocation.Y, CommonData::buffer.playerLocation.Z);
    }*/

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

    spdlog::info("[+] DLL injection successful!");
    
    speaker->playInternal(kvMgr->getKV(language, "gameDetectedTips"));

}

void bmHelper::initHelperThread()
{
    while (1) {
        
        HANDLE hProcess = nullptr;

        hProcess = findProcess((LPWSTR)L"b1-Win64-Shipping.exe");
        if (!hProcess) {
            injected = false; 
        }
        else {
            if (!injected) {
                injected = true;
                this->injectHelper = std::thread(&bmHelper::injectThread, this, std::move(hProcess));
                this->injectHelper.join();
            }
            
        }
        Sleep(5000);

    }

}

void bmHelper::autoInfoAttentionThread()
{
    QString tip;
    while (1) {
        if (this->autoAttention) {
            if (this->attentionMode == 0) {
                speaker->play(kvMgr->transfer(kvMgr->getKV(language, "autoAttentionMode0Tips"), { std::to_string((int)(CommonData::enemyInfo.enemyInfo.enemyDelta)), std::to_string((int)(CommonData::enemyInfo.enemyInfo.playerHp)) }));

            }
            else if (this->attentionMode == 1) {
                speaker->play(kvMgr->transfer(kvMgr->getKV(language, "autoAttentionMode1Tips"), { std::to_string((int)(CommonData::infoBuffer.playerInfo.playerHp)), std::to_string((int)(CommonData::infoBuffer.playerInfo.playerStamina)) }));

            }
            else if (this->attentionMode == 2) {
                speaker->play(kvMgr->transfer(kvMgr->getKV(language, "autoAttentionMode2Tips"), { std::to_string((int)(CommonData::enemyInfo.enemyInfo.playerHp)), std::to_string((int)(CommonData::infoBuffer.playerInfo.playerHp)) }));

            }
        }
        Sleep(this->autoAttentionPeriod);
    }
}
void bmHelper::importantInfoThread()
{
    static int notifyCount = 0;
    static bool normal = true;
    while (1) {
        if (notifyCount < 3) {
            if (CommonData::infoBuffer.playerInfo.playerBurn) {
                notifyCount++;
                normal = false;

                speaker->playInternal(kvMgr->getKV(language, "burnDebuffTips"));
            }
            else if (CommonData::infoBuffer.playerInfo.playerFreeze) {
                notifyCount++;
                normal = false;
                speaker->playInternal(kvMgr->getKV(language, "freezeDebuffTips"));
            }
            else if (CommonData::infoBuffer.playerInfo.playerPoison) {
                notifyCount++;
                normal = false;
                speaker->playInternal(kvMgr->getKV(language, "poisonDebuffTips"));
            }
            else if (CommonData::infoBuffer.playerInfo.playerThunder) {
                notifyCount++;
                normal = false;
                speaker->playInternal(kvMgr->getKV(language, "thunderDebuffTips"));
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



bmHelper::bmHelper(QWidget *parent)
    : QWidget(parent), attentionMode(0)
{
    SetConsoleOutputCP(CP_UTF8);

    QResource::registerResource("bmHelper.rcc");
    ui.setupUi(this);
    spdlog::info("BMHelper initialized.");
    trayIcon = std::make_shared<QSystemTrayIcon>(this);

    trayIcon->setIcon(QIcon(":/res/bm.png"));

    trayIconMenu = std::make_shared<QMenu>(this);

    quitAction = std::make_shared<QAction>("退出", this);
    connect(quitAction.get(), &QAction::triggered, qApp, &QApplication::quit);
    trayIconMenu->addAction(quitAction.get());

    trayIcon->setContextMenu(trayIconMenu.get());

    trayIcon->show();
    /*Q_INIT_RESOURCE(bmHelper);*/
    /*bool result = QResource::registerResource("bmHelper.rcc");
    std::cout << result << std::endl;*/
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);

    this->mDragging = false;
    QString resourcePath = ".\\bm.gif";
    this->mPetMovie = std::make_shared<QMovie>(resourcePath);
    if (!this->mPetMovie->isValid()) {
        spdlog::info("GIF file is invalid!");
        resourcePath = ".\\bm.png";
        this->mPetMovie = std::make_shared<QMovie>(resourcePath);
        if (!this->mPetMovie->isValid()) {
            resourcePath = ".\\bm.jpg";
            this->mPetMovie = std::make_shared<QMovie>(resourcePath);


        }

        
    }
    this->mPetMovie->setParent(this);

    ui.mPetLabel->setMovie(mPetMovie.get());

    ui.mPetLabel->setScaledContents(true);
    this->mPetMovie->start();

    QRect rect = mPetMovie->frameRect();
    float width = rect.width();
    float height = rect.height();

    this->mPetWidthFactor = width / (height + width);
    this->mPetHeightFactor = height / (height + width);
    spdlog::info("GIF Width: {}, Height: {}", this->mPetWidthFactor, this->mPetHeightFactor);

    ui.mPetLabel->resize(mPet::mPetConfig::mDefaultScaleSize * this->mPetWidthFactor, mPet::mPetConfig::mDefaultScaleSize * this->mPetHeightFactor);
    ui.mPetLabel->setAlignment(Qt::AlignCenter);
    ui.mPetLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui.mPetLabel->setMinimumSize(1, 1);


    this->quitAll = false;
    injected = false;
    this->autoAttention = false;
    this->autoAttentionPeriod = 2000;

    keyMgr = std::make_shared<KeyMgr>();
    speaker = std::make_shared<SpkMgr>();
    

    server = std::make_shared<MocIPC::IPCServer>();
    kvMgr = std::make_shared<KVMgr>();
    kvMgr->init("language.json");
    languageSupport = kvMgr->getOuterKeys();
    if(!languageSupport.empty())
        language = languageSupport[0];
    else {
        language = "Chinese";
    }
    
    speaker->setLanguage(language);

    server->registerRecvHOOK(testRecv);
    

    keyMgr->bindKeys({ VK_CONTROL, 'C' }, std::function<void()>([&]() {
        if (!speaker)
            return;

        speaker->playInternal(kvMgr->getKV(language, "savePosTips"));
        CommonData::config.targetPlayerLocation = CommonData::locationBuffer.playerLocationInfo.Location;
        spdlog::info("event: {}, received: {:.5f}, {:.5f}, {:.5f}", static_cast<int>(CommonData::locationBuffer.event), CommonData::locationBuffer.playerLocationInfo.Location.X, CommonData::locationBuffer.playerLocationInfo.Location.Y, CommonData::locationBuffer.playerLocationInfo.Location.Z);
        spdlog::info("save position pressed!");
    }));


    keyMgr->bindKeys({ VK_CONTROL, 'V' }, std::function([&]() {

        HANDLE hProcess = nullptr;
        if (!speaker || !server)
            return;
        hProcess = findProcess((LPWSTR)L"b1-Win64-Shipping.exe");
        if (hProcess && CommonData::gameStatus.gameInited) {
            CommonData::gameInfo_t send(CommonData::event_t::EVENT_PLAYER_LOCATION_SET);
            send.targetPlayerLocation = CommonData::config.targetPlayerLocation;

            server->write((void*)&send, sizeof(CommonData::gameInfo_t));

            speaker->playInternal(kvMgr->getKV(language, "teleportTips"));
            spdlog::info("set position pressed!");
        }
        else {
            if (!CommonData::gameStatus.gameInited && hProcess) {
                speaker->playInternal(kvMgr->getKV(language, "tpNotInGameTips"));
            }
            else {
                speaker->playInternal(kvMgr->getKV(language, "tpGameProcessNotExistTips"));
            }

        }

    }));

    keyMgr->bindKeys({ VK_CONTROL, VK_SHIFT, 'D' }, std::function([&]() {
        if (!speaker || !kvMgr)
            return;
        speaker->playInternal(kvMgr->transfer(kvMgr->getKV(language, "helperTips"), { "control", "T", "control", "方向键", "大小写切换键", "F1", "F2", "F3", "F4", "control", "西", "control", "V", "Z", "X", "西", "control", "T" }));
    }));

    
    keyMgr->bindKeys({ VK_CONTROL, VK_LEFT }, std::function<void()>([&]() {
        if(speaker)
            speaker->setVolume(false);
    }));
    
    keyMgr->bindKeys({ VK_CONTROL, VK_RIGHT }, std::function<void()>([&]() {
        if (speaker)
            speaker->setVolume(true);
    }));
    
    keyMgr->bindKeys({ VK_CONTROL, VK_DOWN }, std::function<void()>([&]() {
        if (speaker)
            speaker->setSpeed(false);
    }));
    
    keyMgr->bindKeys({ VK_CONTROL, VK_UP }, std::function<void()>([&]() {
        if (speaker)
            speaker->setSpeed(true);
    }));

    


    keyMgr->bindKeys({ VK_CONTROL, 'T' }, std::function<void()>([&]() {
        if(speaker)
            speaker->playInternal(kvMgr->getKV(language, "exitTips"));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        trayIcon->setVisible(false);
        quitAll = true;
        QApplication::quit();
    }));
    
    


    keyMgr->bindKeys({ VK_F1 }, std::function<void()>([&]() {
        autoAttention ^= 1;
        if (!speaker)
            return;
        if (autoAttention)
            speaker->playInternal(kvMgr->getKV(language, "openAutoAttentionTips"));
        else {
            speaker->playInternal(kvMgr->getKV(language, "closeAutoAttentionTips"));
        }
    }));

   



    keyMgr->bindKeys({ VK_F2 }, std::function<void()>([&]() {
        if (attentionMode + 1 > 2) {
            attentionMode = 0;
        }
        else {
            attentionMode++;
        }
        if (attentionMode == 0) {
            speaker->playInternal(kvMgr->getKV(language, "autoAttentionMode0TitleTips"));
        }
        else if (attentionMode == 1) {
            speaker->playInternal(kvMgr->getKV(language, "autoAttentionMode1TitleTips"));
        }
        else if (attentionMode == 2) {
            speaker->playInternal(kvMgr->getKV(language, "autoAttentionMode2TitleTips"));
        }
    }));

    


    keyMgr->bindKeys({ VK_F3 }, std::function<void()>([&]() {

        if (autoAttentionPeriod - 1000 <= 0)
            autoAttentionPeriod = 1000;
        else
            autoAttentionPeriod -= 1000;

        std::string tips = kvMgr->transfer(kvMgr->getKV(language, "autoAttentionPeriodTips"), { std::to_string(autoAttentionPeriod / 1000) });
        /* cut 1 second(s) */
        speaker->playInternal(tips.substr(0, language == "English" ? (autoAttentionPeriod == 1000 ? tips.size() - 1 : tips.size()) : tips.size()));

    }));


    


    keyMgr->bindKeys({ VK_F4 }, std::function<void()>([&]() {

        if (autoAttentionPeriod + 1000 >= 20000)
            autoAttentionPeriod = 20000;
        else
            autoAttentionPeriod += 1000;

        speaker->playInternal(kvMgr->transfer(kvMgr->getKV(language, "autoAttentionPeriodTips"), { std::to_string(autoAttentionPeriod / 1000) }));
    }));
    
    
    std::function infoFunc = std::function<void(int)>([&](int number) {
        if (number == 0) {
            speaker->playInternal(kvMgr->transfer(kvMgr->getKV(language, "manuallyGetInfo0Tips"), { std::to_string((int)(CommonData::infoBuffer.playerInfo.playerHp)), std::to_string((int)(CommonData::infoBuffer.playerInfo.playerBloodButton)) }));
        }
        else if (number == 1) {
            speaker->playInternal(kvMgr->transfer(kvMgr->getKV(language, "manuallyGetInfo1Tips"), { std::to_string((int)(CommonData::infoBuffer.playerInfo.playerStamina)), std::to_string((int)(CommonData::infoBuffer.playerInfo.playerMp)) }));

        }
        else if (number == 2) {
            std::vector<std::string> ret;
            ret.emplace_back(std::to_string(int(CommonData::infoBuffer.playerInfo.playerEnergy)));

            if (CommonData::infoBuffer.playerInfo.playerBurn)
                ret.emplace_back(kvMgr->getKV(language, "burnDebuffTips"));
            else if (CommonData::infoBuffer.playerInfo.playerFreeze)
                ret.emplace_back(kvMgr->getKV(language, "freezeDebuffTips"));
            else if (CommonData::infoBuffer.playerInfo.playerPoison)
                ret.emplace_back(kvMgr->getKV(language, "poisonDebuffTips"));
            else if (CommonData::infoBuffer.playerInfo.playerThunder)
                ret.emplace_back(kvMgr->getKV(language, "thunderDebuffTips"));
            else {
                ret.emplace_back(kvMgr->getKV(language, "manuallyGetInfoNoDebuffTips"));
            }

            speaker->playInternal(kvMgr->transfer(kvMgr->getKV(language, "manuallyGetInfo2Tips"), ret));

        }

    });
    keyMgr->bindKeys({ 'Z' }, infoFunc, 0);
    keyMgr->bindKeys({ 'X' }, infoFunc, 1);
    keyMgr->bindKeys({ 'C' }, infoFunc, 2);
   

    keyMgr->bindKeys({ VK_CAPITAL }, std::function<void()>([&]() {
        speaker->playInternal(kvMgr->transfer(kvMgr->getKV(language, "manuallyGetClosestEnemyInfoTips"), { std::to_string((int)(CommonData::enemyInfo.enemyInfo.enemyDelta)), std::to_string((int)(CommonData::enemyInfo.enemyInfo.playerHp)) }));

    }));
    keyMgr->bindKeys({ 'L' }, std::function<void()>([&]() {
        for (auto it : languageSupport) {
            if (language != it) {
                speaker->setLanguage(it);
                language = it;
                break;
            }
                
        }
        
        speaker->playInternal(kvMgr->transfer(kvMgr->getKV(language, "switchLanguageTips"), { language }));
        spdlog::info(kvMgr->transfer(kvMgr->getKV(language, "switchLanguageTips"), { language }));

    }));
    

    this->speaker->setSpeed(20);
    speaker->playInternal(kvMgr->transfer(kvMgr->getKV(language, "initTips"), { "control", "shift", "D", "control", "T", "L"}));
    
 
    /*notifyThread(this);*/
    /*RemoteThreadInject32((LPWSTR)L"b1-Win64-Shipping.exe", (LPWSTR)L"D:\\WORK\\blackmyth\\dlltest\\x64\\Debug\\bmdll.dll");*/

    initHelper = std::thread(&bmHelper::initHelperThread, this);
    initHelper.detach();
    

    autoAttentionHelper = std::thread(&bmHelper::autoInfoAttentionThread, this);
    autoAttentionHelper.detach();

    
    importantInfoHelper = std::thread(&bmHelper::importantInfoThread, this);
    importantInfoHelper.detach();


    mapMgr = std::make_shared<BmMapMgr>();
    mapMgr->init("bmmap.json");
    bool result = mapMgr->updateCurrentMap(30, 75001, 48001, -40000);
    spdlog::info("update map result: {}", result ? 1 : 0);
    /* MGameAudio Initialization can't be called from qt thread */
    auto mGameAudioInitWork = std::async(std::launch::async, []() {
        MGameAudio::init();
        MGameAudio::createNewVoice("closestEnemy", "cloestEnemy_01.wav");
        MGameAudio::createNewVoice("mapTarget", "cloestEnemy_01.wav");
    });
    mGameAudioInitWork.get();
    

    keyMgr->bindKeys({ '0' }, std::function<void()>([&]() {
        MGameAudio::playAudio("closestEnemy", true);
    }));

    keyMgr->bindKeys({ '9' }, std::function<void()>([&]() {
        MGameAudio::playAudio("mapTarget", true);
    }));

    keyMgr->bindKeys({ '6' }, std::function<void()>([&]() {
        auto unit = mapMgr->getUnit<BmMapMgr::PointDirection::NEXT>();
        auto mapAudioInfo = getPlayerAudioInfo();
        spdlog::info("[0] {} {} {}, [1] {} {} {}, [2] {} {} {}", mapAudioInfo[0].x, mapAudioInfo[0].y, mapAudioInfo[0].z, mapAudioInfo[1].x, mapAudioInfo[1].y, mapAudioInfo[1].z, mapAudioInfo[2].x, mapAudioInfo[2].y, mapAudioInfo[2].z);
        MGameAudio::updatePosition<MGameAudio::UpdatePositionParam::EMITTER>("mapTarget", mapAudioInfo[0], mapAudioInfo[1], mapAudioInfo[2]);
        speaker->playInternal(QString("target: %1").arg(unit->pointName.c_str()));
    }));

    keyMgr->bindKeys({ '7' }, std::function<void()>([&]() {
        auto unit = mapMgr->getUnit<BmMapMgr::PointDirection::PREV>();
        auto mapAudioInfo = getMapAudioInfo();
        MGameAudio::updatePosition<MGameAudio::UpdatePositionParam::EMITTER>("mapTarget", mapAudioInfo[0], mapAudioInfo[1], mapAudioInfo[2]);
        speaker->playInternal(QString("target: %1").arg(unit->pointName.c_str()));
    }));
    /*bool result = mapMgr->updateCurrentMap(30, 75001, 48001, -40000);
    spdlog::info("update map result: %d", result ? 1 : 0);

    for (int i = 0; i < 1000; i++) {
        BmMapMgr::levelUnit_t* unit = mapMgr->getUnit<BmMapMgr::PointDirection::NEXT>();
        if (unit) {
            spdlog::info("get unit name: %s, location: [%d] [%d] [%d]\r\n", unit->pointName.c_str(), unit->point.X, unit->point.Y, unit->point.Z);
        }
    }
    
    std::thread newthread = std::thread([] () {
        MGameAudio::runTestCase();
    });
    newthread.detach();*/
    
    
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
