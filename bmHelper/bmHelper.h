#pragma once

#include <QtWidgets/QWidget>
#include "ui_bmHelper.h"
#include <QSystemTrayIcon>
#include "spkMgr.h"
#include "keyMgr.h"
#include "mocIPC.h"
class bmHelper : public QWidget
{
    Q_OBJECT

public:
    bmHelper(QWidget *parent = nullptr);
    ~bmHelper()
    {
        delete mPetMovie;
        delete trayIcon;
        delete speaker;
        delete key;
        delete server;

    }

    spkMgr *speaker;
    keyMgr* key;
    MocIPC::IPCServer* server;
    QSystemTrayIcon* trayIcon;
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
    QMovie* mPetMovie;
    
    bool mDragging;
    QPoint mObjetCurrentPos;
    QPoint mDraggingStartPos;
    float mPetWidthFactor;
    float mPetHeightFactor;
    Ui::bmHelperClass ui;

    
    std::thread initHelper;
    std::thread autoAttentionHelper;

    std::thread importantInfoHelper;
    static void playReadme(void* arg);


};
