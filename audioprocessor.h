#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <QObject>
#include <QVector>
#include "ringbuffer.h"

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


private:
    float calculateRMS(const qint16* samples, int count);

    RingBuffer m_buffer;
};

#endif // AUDIOPROCESSOR_H
