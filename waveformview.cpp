#include "waveformview.h"
#include <QPainter>
#include <QPainterPath>
#include <QPen>
WaveformView::WaveformView(QQuickItem *parent) : QQuickPaintedItem(parent)
{

}

int WaveformView::smoothing() const
{
    return m_smoothing;
}

void WaveformView::setSmoothing(int value)
{
    if(value < 1)
        value = 1;


    if(value == m_smoothing)
        return;


    m_smoothing = value;


    emit smoothingChanged();


    update();
}

void WaveformView::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if (m_samples.isEmpty()){return; }

    float w = width();
    float h = height();



    painter->setPen(QPen(Qt::yellow, 1));

    painter->drawLine(0,h/2,w,h/2);

    painter->setPen(QPen(Qt::green, 2));



    QPainterPath path;
    int points = width();


    for(int x = 0; x < points; x++)
    {

        // выбираем семпл под этот пиксель

        int index = x * m_samples.size() / points;

        float sample = m_smoothSamples[index];


        // масштабируем

        sample *= m_scale;


        // ограничиваем

        sample = qBound(-1.0f, sample, 1.0f);

        float y = h/2 - sample * h/2;

        if(x == 0){
            path.moveTo(x,y);
        }
        else{
            path.lineTo(x,y);
        }

    }
    painter->drawPath(path);
}

void WaveformView::setSamples(const QVector<float> &samples)
{
    m_samples = samples;


    m_smoothSamples = smoothSamples(m_samples);


    update();
}

QVector<float> WaveformView::smoothSamples(const QVector<float> &input)
{
    QVector<float> res;
    res.resize(input.size());

    for(int i = 0; i<input.size(); i++){
        float sum = 0;
        int count = 0;

        for(int j = -m_smoothing; j<= m_smoothing; j++){
            int id = i+j;

            if(id >= 0 && id < input.size()){
                sum += input[id];
                count++;
            }
        }

        res[i] = sum/count;
    }
    return res;
}

void WaveformView::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();

    if(delta > 0){m_scale *= 1.1f;}
    else{m_scale *= 0.9f;}

    if(m_scale < 0.1f){m_scale = 0.1f;}
    if(m_scale > 10.0f){m_scale = 10.0f;}

    //qDebug() << "Scale:" << m_scale;


    update();


    event->accept();
}
