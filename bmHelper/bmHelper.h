#pragma once

#include <QtWidgets/QWidget>
#include "ui_bmHelper.h"
#include <QSystemTrayIcon>
#include "SpkMgr/SpkMgr.h"
#include "KeyMgr/KeyMgr.h"
#include "MapMgr/MapMgr.h"
#include "KVMgr/KVMgr.h"
#include "mocIPC.h"
#include "mGameAudio/mGameAudio.h"

/* gif icon */
namespace mPet {
namespace mPetConfig {
constexpr int mMaxScaleWidth = 800;
constexpr int mMaxScaleHeight = 600;

constexpr int mMinScaleWidth = 128;
constexpr int mMinScaleHeight = 256;

constexpr int mDefaultScaleSize = 256;

} /* mPetConfig */

} /* mPet */


class bmHelper : public QWidget
{
    Q_OBJECT

public:
    bmHelper(QWidget *parent = nullptr);
    ~bmHelper()
    {

    }
    inline static std::shared_ptr<BmMapMgr> mapMgr;
    inline static std::shared_ptr<SpkMgr> speaker;
    std::shared_ptr<KeyMgr> keyMgr;
    std::shared_ptr<MocIPC::IPCServer> server;
    std::shared_ptr<KVMgr> kvMgr;
    
    std::vector<std::string> languageSupport;
    std::string language;

    std::shared_ptr<QSystemTrayIcon> trayIcon;
    std::shared_ptr<QMenu> trayIconMenu;
    std::shared_ptr<QAction> quitAction;
   

    bool injected;
    bool autoAttention;
    int autoAttentionPeriod;
    int attentionMode;
    bool quitAll;
    std::thread injectHelper;
    void injectThread(HANDLE &&hProcess);
    void initHelperThread();
    void autoInfoAttentionThread();
    void importantInfoThread();
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
private:
    std::shared_ptr<QMovie> mPetMovie;

    bool mDragging;
    QPoint mObjetCurrentPos;
    QPoint mDraggingStartPos;
    float mPetWidthFactor;
    float mPetHeightFactor;
    Ui::bmHelperClass ui;

    
    std::thread initHelper;
    std::thread autoAttentionHelper;

    std::thread importantInfoHelper;
};
