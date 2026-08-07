#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include <QObject>
#include <QAudioSource>
#include <QMediaDevices>
#include <QIODevice>

class AudioInput : public QObject
{
    Q_OBJECT

public:
    explicit AudioInput(QObject *parent = nullptr);
    void start();
    void stop();

signals:
    void samplesReady(const QByteArray &data);

private slots:
    void readMore();

private:
    QAudioSource *m_audio = nullptr;
    QIODevice *m_device = nullptr;
};

#endif // AUDIOINPUT_H
