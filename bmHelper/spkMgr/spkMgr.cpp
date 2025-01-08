#include "spkMgr.h"
#include <windows.h>
#include <iostream>
#include <thread>


SpkMgr::SpkMgr()
{
    this->speed = 20;
    this->volume = 70;
    speaker = std::make_shared<QTextToSpeech>();

    

    speaker->setLocale(QLocale::English);
    speaker->setRate((float)this->speed / 100.0f);
    speaker->setRate((float)this->volume / 100.0f);
    
    QObject::connect(&textblockTimer, &QTimer::timeout, [this]() {
        this->processQueue();
    });
    textblockTimer.start(50);
}



void SpkMgr::processQueue() {
    if (!textQueue.empty() && speaker->state() == QTextToSpeech::Ready) {
        currentText = textQueue.front();
        textQueue.pop();
        QMetaObject::invokeMethod(speaker.get(), "say", Qt::QueuedConnection, Q_ARG(QString, currentText));
    }
}

void SpkMgr::playThreadFunc(const wchar_t* targetText)
{
    
    

}

void SpkMgr::playInternal(QString targetText)
{
    
    QMetaObject::invokeMethod(speaker.get(),
        "say",
        Qt::QueuedConnection,
        Q_ARG(QString, targetText));
}

void SpkMgr::playTextBlock(QString targetText)
{
    if (speaker->state() == QTextToSpeech::Speaking) {
        if (targetText != currentText) {
            textQueue.push(targetText);
        }
        return;
    }
    currentText = targetText;
    QMetaObject::invokeMethod(speaker.get(),
        "say",
        Qt::QueuedConnection,
        Q_ARG(QString, targetText));

}



void SpkMgr::play(QString targetText)
{
    /*speaker->say(targetText);*/
    if (speaker->state() == QTextToSpeech::Speaking)
        return;
    QMetaObject::invokeMethod(speaker.get(),
        "say",
        Qt::QueuedConnection,
        Q_ARG(QString, targetText));
}


void SpkMgr::setSpeed(bool direction)
{
    this->setSpeed(direction ? ((this->speed + 10) >= 100 ? 100 : (this->speed + 10)) : \
        ((this->speed - 10) <= 0 ? 0 : (this->speed - 10)));
}

void SpkMgr::setSpeed(int speed)
{
    QString tip;
    this->speed = speed;
    speaker->setRate((float)speed / 100.0f);
    if (speaker->locale() == QLocale::Chinese) {
        tip = QString("当前语速: %1").arg(speed);
    }
    else if (speaker->locale() == QLocale::English) {
        tip = QString("speed: %1").arg(speed);
    }
    else {
        tip = QString("speed: %1").arg(speed);
    }
    this->playInternal(tip);
}

void SpkMgr::setVolume(bool direction)
{
    this->setVolume(direction ? ((this->volume + 10) > 100 ? 100 : (this->volume + 10)) : \
        ((this->volume - 10) <= 0 ? 5 : (this->volume - 10)));
}

void SpkMgr::setVolume(int volume)
{
    QString tip;
    this->volume = volume;
    this->speaker->setVolume((float)volume / 100.0f);
    
    if (speaker->locale() == QLocale::Chinese) {
        tip = QString("当前音量: %1").arg(volume);
    }
    else if (speaker->locale() == QLocale::English) {
        tip = QString("volume: %1").arg(volume);
    }
    else {
        tip = QString("volume: %1").arg(volume);
    }
    this->playInternal(tip);
}
