#include "spkMgr.h"
#include <windows.h>
#include <iostream>
#include <thread>


spkMgr::spkMgr()
{
    this->speed = 20;
    this->volume = 70;
    speaker = new QTextToSpeech();
    speaker->setLocale(QLocale::Chinese);
    speaker->setRate((float)this->speed / 100.0f);
    speaker->setRate((float)this->volume / 100.0f);
    
    QObject::connect(&textblockTimer, &QTimer::timeout, [this]() {
        this->processQueue();
    });
    textblockTimer.start(50);
}


spkMgr::~spkMgr() {
    delete speaker;
}

void spkMgr::processQueue() {
    if (!textQueue.empty() && speaker->state() == QTextToSpeech::Ready) {
        currentText = textQueue.front();
        textQueue.pop();
        QMetaObject::invokeMethod(speaker, "say", Qt::QueuedConnection, Q_ARG(QString, currentText));
    }
}

void spkMgr::playThreadFunc(const wchar_t* targetText)
{
    
    

}

void spkMgr::playInternal(QString& targetText)
{
    
    QMetaObject::invokeMethod(speaker,
        "say",
        Qt::QueuedConnection,
        Q_ARG(QString, targetText));
}

void spkMgr::playTextBlock(QString& targetText)
{
    if (speaker->state() == QTextToSpeech::Speaking) {
        if (targetText != currentText) {
            textQueue.push(targetText);
        }
        return;
    }
    currentText = targetText;
    QMetaObject::invokeMethod(speaker,
        "say",
        Qt::QueuedConnection,
        Q_ARG(QString, targetText));

}

void spkMgr::playInternal(const char* targetText)
{
    QMetaObject::invokeMethod(speaker,
        "say",
        Qt::QueuedConnection,
        Q_ARG(QString, targetText));
}

void spkMgr::play(QString &targetText)
{
    /*speaker->say(targetText);*/
    if (speaker->state() == QTextToSpeech::Speaking)
        return;
    QMetaObject::invokeMethod(speaker,
        "say",
        Qt::QueuedConnection,
        Q_ARG(QString, targetText));
}

void spkMgr::play(const char *targetText)
{
    /*speaker->say(targetText);*/
    if (speaker->state() == QTextToSpeech::Speaking)
        return;
    QMetaObject::invokeMethod(speaker,
        "say",
        Qt::QueuedConnection,
        Q_ARG(QString, targetText));
}

void spkMgr::setSpeed(bool direction)
{
    this->setSpeed(direction ? ((this->speed + 10) >= 100 ? 100 : (this->speed + 10)) : \
        ((this->speed - 10) <= 0 ? 0 : (this->speed - 10)));
}

void spkMgr::setSpeed(int speed)
{
    this->speed = speed;
    speaker->setRate((float)speed / 100.0f);
    QString tip = QString("当前语速: %1").arg(speed);
    this->playInternal(tip);
}

void spkMgr::setVolume(bool direction)
{
    this->setVolume(direction ? ((this->volume + 10) > 100 ? 100 : (this->volume + 10)) : \
        ((this->volume - 10) <= 0 ? 5 : (this->volume - 10)));
}

void spkMgr::setVolume(int volume)
{
    this->volume = volume;
    this->speaker->setVolume((float)volume / 100.0f);
    QString tip = QString("当前音量: %1").arg(volume);
    this->playInternal(tip);
}
