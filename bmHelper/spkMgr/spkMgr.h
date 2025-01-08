#pragma once
#include <future>
#include <QTextToSpeech>
#include <queue>
#include <QTimer>
#include <QList>
#include <QVoice>
class SpkMgr {
public:
	SpkMgr();
	~SpkMgr() {}

	void play(QString targetText);
	void play(const char* targetText) { play(QString(targetText)); }
	void play(std::string targetText) { play(QString(targetText.c_str())); }
	void playInternal(std::string targetText) { playInternal(QString(targetText.c_str())); }
	void playInternal(const char* targetText) { playInternal(QString(targetText)); }
	void playInternal(QString targetText);
	void playTextBlock(QString targetText);
	void playThreadFunc(const wchar_t* targetText);
	void setSpeed(int speed);
	void setVolume(int volume);
	void processQueue();
	void setSpeed(bool direction);
	void setVolume(bool direction);

	void setLanguage(std::string src)
	{
		if (speaker) {
			if(src == "Chinese")
				speaker->setLocale(QLocale::Chinese);
			else if (src == "English") {
				speaker->setLocale(QLocale::English);
			}
			else {
				speaker->setLocale(QLocale::English);
			}
		}
		
	}
protected:
	std::shared_ptr<QTextToSpeech> speaker;

	QString currentText;
	std::queue<QString> textQueue;
	QTimer textblockTimer;
	std::thread playThread;
	int speed;
	int volume;
};