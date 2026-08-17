#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <QObject>
#include <QVector>
#include "ringbuffer.h"
#include "fft.h"

class AudioProcessor : public QObject
{

    Q_OBJECT

public:
   explicit AudioProcessor(QObject *parent = nullptr);


public slots:
    void process(const QByteArray &data);


signals:
    void volumeChanged(float volum);
    void samplesReady(const QVector<float>& samples);
    void spectrumChanged(const QVector<float>& spectrum);


private:
    float calculateRMS(const qint16* samples, int count);

    RingBuffer m_buffer;
    int m_fftCounter = 0;
};

#endif // AUDIOPROCESSOR_H
