#include "audioprocessor.h"
#include <QDebug>

AudioProcessor::AudioProcessor(QObject *parent)
{

}

void AudioProcessor::process(const QByteArray &data)
{
    if (data.isEmpty())
        return;


    // QByteArray -> массив сэмплов
    const qint16* samples =
        reinterpret_cast<const qint16*>(data.constData());


    // Количество сэмплов
    int count = data.size() / sizeof(qint16);

    for(int i = 0; i<count; i++){
        float sample =  samples[i] / 32768.0f;
        m_buffer.push(sample);
    }

    emit samplesReady(m_buffer.qData());


    float volume = calculateRMS(samples, count);

    volume *= 5.0f;

    volume = std::clamp(volume, 0.0f, 1.0f);

    emit volumeChanged(volume);


    /*qDebug() << "Громкость:" << volume;
    qDebug() << "Размер буфера:"
             << m_buffer.size();
    auto values = m_buffer.data();

    if(!values.empty())
    {
        qDebug()
        << "Первый:"
        << values.front()
        << "Последний:"
        << values.back();
    }
*/
}

float AudioProcessor::calculateRMS(const qint16 *samples, int count)
{
    double sum = 0;


    for (int i = 0; i < count; i++)
    {
        // переводим Int16 в диапазон -1.0 ... 1.0
        float sample = samples[i] / 32768.0f;


        // квадрат амплитуды
        sum += sample * sample;
    }


    // среднее значение
    double mean = sum / count;


    // корень
    return sqrt(mean);
}
