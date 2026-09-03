#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <QObject>
#include <QVector>
#include "ringbuffer.h"
#include "fft.h"
#include "windowfunction.h"

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
    std::vector<float> m_window;

    static constexpr int FFT_SIZE = 4096;
    static constexpr int HOP_SIZE = 3072;   // 50% от FFT_SIZE
    static constexpr int OVERLAP = FFT_SIZE - HOP_SIZE;  // 3072 (75%)
};

#endif // AUDIOPROCESSOR_H
