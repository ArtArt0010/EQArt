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

    painter->fillRect(
        0,
        0,
        w,
        h,
        Qt::black
        );

    float maxValue = 0.0f;

    for (float value : m_spectrum)
    {
        if (value > maxValue)
            maxValue = value;
    }

    if (maxValue <= 0.0f)
        return;

    int count = m_spectrum.size() / 2;

    for (int i = 0; i < count; ++i)
    {
        if (m_spectrum[i] > maxValue){
            maxValue = m_spectrum[i];
        }

        float value = m_spectrum[i] / maxValue;

        float barHeight = value * h;

        float x = static_cast<float>(i) / count * w;

        float barWidth = w / count;

        painter->fillRect(
            QRectF(
                x,
                h - barHeight,
                barWidth,
                barHeight
                ),
            Qt::green
            );
    }
}

void SpectrumView::setSpectrum(const QVector<float> &spectrum)
{
    m_spectrum = spectrum;
    update();
}
