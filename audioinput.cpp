#include "audioinput.h"
#include <QDebug>

AudioInput::AudioInput(QObject *parent)
{
    QAudioFormat format;

    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    auto device = QMediaDevices::defaultAudioInput();

    qDebug() << "Устройство:" << device.description();

    m_audio = new QAudioSource(device, format, this);
    qDebug() << m_audio->format();
}

void AudioInput::start()
{
    m_device = m_audio->start();

    connect(m_device,
            &QIODevice::readyRead,
            this,
            &AudioInput::readMore);
}

void AudioInput::stop()
{
    if (m_audio)
        m_audio->stop();
}

void AudioInput::readMore()
{
    QByteArray data = m_device->readAll();

    //qDebug() << "Получено байт:" << data.size();

    emit samplesReady(data);

/*    const qint16 *samples =
        reinterpret_cast<const qint16*>(data.constData());

    int count = data.size() / sizeof(qint16);

    for (int i = 0; i < 10 && i < count; ++i)
    {
        qDebug() << samples[i];
    }
*/
}
