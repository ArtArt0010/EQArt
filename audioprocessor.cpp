#include "audioprocessor.h"
#include <QDebug>

AudioProcessor::AudioProcessor(QObject *parent): QObject(parent)
{
    m_window = WindowFunction::hanning(FFT_SIZE);
}

void AudioProcessor::process(const QByteArray &data)
{
    if (data.isEmpty())
        return;


    // QByteArray -> массив сэмплов
    const qint16* samples = reinterpret_cast<const qint16*>(data.constData());


    // Количество сэмплов
    int count = data.size() / sizeof(qint16);

    for(int i = 0; i<count; i++){
        float sample =  samples[i] / 32768.0f;
        m_buffer.push(sample);
    }
    m_fftCounter += count;

    emit samplesReady(m_buffer.qData());


    float volume = calculateRMS(samples, count);

    volume *= 5.0f;

    volume = std::clamp(volume, 0.0f, 1.0f);

    emit volumeChanged(volume);

    if (m_buffer.size() >= FFT_SIZE  && m_fftCounter >= HOP_SIZE){
        // начинаем новый отсчёт
        m_fftCounter = 0;


        // Получаем последние 4096 семплов
        auto fftSamples = m_buffer.data();

      /*  auto allData = m_buffer.data();
        std::vector<float> fftSamples;
        fftSamples.reserve(FFT_SIZE);

        if(allData.size() >= FFT_SIZE){

            int start_id = allData.size()-FFT_SIZE;

            for(int i = start_id; i < allData.size(); i++){

                fftSamples.push_back(allData[i]);

            }
        }

*/
        // =====================================================
        // 7. FFT
        // =====================================================



        auto spectrum = FFT::calculate(fftSamples, &m_window);



        if (!spectrum.empty())
        {
            emit spectrumChanged(
                QVector<float>(
                    spectrum.begin(),
                    spectrum.end()
                    )
                );
        }


        if (!spectrum.empty())
        {
            // =================================================
            // 8. Ищем максимальную частоту
            // =================================================

            int maxIndex = 0;

            // Для реального сигнала используем
            // только первую половину спектра.
            int spectrumSize = spectrum.size() / 2;


            for (int i = 1; i < spectrumSize;i++)
            {
                if (spectrum[i] >
                    spectrum[maxIndex])
                {
                    maxIndex = i;
                }
            }


            // =================================================
            // 9. Индекс FFT -> частота
            // =================================================

            constexpr float sampleRate = 44100.0f;
            constexpr float fftSize = 4096.0f;

            float frequency =
                maxIndex *
                sampleRate /
                fftSize;


            //qDebug()<< "Главная частота:"<< frequency<< "Hz";
        }
      /*  if(m_buffer.size() > HOP_SIZE){
            int remove_count = m_buffer.size() - HOP_SIZE;
            m_buffer.removeFirst(remove_count);
        }
*/
    }



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
