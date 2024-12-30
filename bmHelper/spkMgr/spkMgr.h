#pragma once
#include <future>
#include <QTextToSpeech>
#include <queue>
#include <QTimer>
class SpkMgr {
public:
	SpkMgr();
	~SpkMgr();

	void play(QString &targetText);
	void play(const char* targetText);
	void playInternal(const char* targetText);
	void playInternal(QString& targetText);
	void playTextBlock(QString& targetText);
	void playThreadFunc(const wchar_t* targetText);
	void setSpeed(int speed);
	void setVolume(int volume);
	void processQueue();
	void setSpeed(bool direction);
	void setVolume(bool direction);
protected:
	QTextToSpeech *speaker;
	QString currentText;
	std::queue<QString> textQueue;
	QTimer textblockTimer;
	std::thread playThread;
	int speed;
	int volume;
};