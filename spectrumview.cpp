#include "spectrumview.h"
#include <QPainter>
#include <QPainterPath>
#include <QtMath>

SpectrumView::SpectrumView(QQuickItem *parent): QQuickPaintedItem(parent)
{

}

void SpectrumView::paint(QPainter *painter)
{
    if (m_spectrum.isEmpty())
        return;

    const float w = width();
    const float h = height();

    const float leftMargin = 50.0f;
    const float bottomMargin = 30.0f;

    const float graphWidth = w - leftMargin;

    const float graphHeight = h - bottomMargin;

    constexpr float minDb = -80.0f;
    constexpr float maxDb = 0.0f;

    constexpr float minFreq = 20.0f;
    constexpr float maxFreq = 22050.0f;


    painter->fillRect(0, 0, w, h, Qt::black);


    // dB GRID


    painter->setPen(QPen(QColor(60, 60, 60),1));

    QFont font;
    font.setPointSize(9);

    painter->setFont(font);


    for (int db = 0; db >= -80; db -= 20)
    {
        float normalized =(db - minDb)/(maxDb - minDb);

        float y =graphHeight-normalized * graphHeight;

        painter->drawLine(leftMargin, y, w, y);

        painter->setPen(Qt::white);

        painter->drawText(5, y + 4, QString::number(db) + " dB");

        painter->setPen(QPen(QColor(60, 60, 60), 1));
    }



    // SPECTRUM


    int count = m_spectrum.size() / 2;

    for (int i = 0; i < count; ++i)
    {
        float amplitude = m_spectrum[i];

        amplitude = qMax(amplitude, 0.000001f);

        float db = 20.0f *qLn(amplitude)/qLn(10.0f);

        db = qBound(minDb, db, maxDb);

        float normalized =(db - minDb)/(maxDb - minDb);

        float barHeight = normalized * graphHeight;


        // Частота этого FFT bin
        float frequency = static_cast<float>(i) *44100.0f/4096.0f;


        // ЛОГАРИФМИЧЕСКОЕ ПОЛОЖЕНИЕ


        if (frequency < minFreq)
            continue;

        float xNormalized = qLn(frequency / minFreq)/qLn(maxFreq / minFreq);

        float x = leftMargin + xNormalized * graphWidth;


        // ширина столбика
        float barWidth = 2.0f;

        painter->fillRect(
            QRectF(
                x,
                graphHeight - barHeight,
                barWidth,
                barHeight
                ),
            Qt::green
            );
    }




    QVector<float> frequencies =
        {
            20,
            50,
            100,
            200,
            500,
            1000,
            2000,
            5000,
            10000,
            20000
        };


    painter->setPen(Qt::white);


    for (float frequency : frequencies)
    {
        float xNormalized = qLn(frequency / minFreq) / qLn(maxFreq / minFreq);

        float x = leftMargin + xNormalized * graphWidth;


        // вертикальная отметка

        painter->drawLine(x, graphHeight, x, graphHeight + 5);


        // подпись

        QString text;

        if (frequency >= 1000)
        {
            text =QString::number(frequency / 1000.0f, 'g',3)+ "k";
        }
        else
        {
            text = QString::number(frequency);
        }


        painter->drawText(x - 15, h - 8, text);
    }
}

void SpectrumView::setSpectrum(const QVector<float> &spectrum)
{
    m_spectrum = spectrum;
    update();
}
