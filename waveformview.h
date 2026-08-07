#ifndef WAVEFORMVIEW_H
#define WAVEFORMVIEW_H


#include <QQuickPaintedItem>
#include <QVector>

class WaveformView : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int smoothing READ smoothing WRITE setSmoothing NOTIFY smoothingChanged)

public:
    explicit WaveformView(QQuickItem *parent = nullptr);

    int smoothing() const;

    void setSmoothing(int value);


    void paint(QPainter *painter) override;

signals:
     void smoothingChanged();

public slots:
    void setSamples(const QVector<float>& samples);

private:
    QVector<float> m_samples;
    QVector<float> m_smoothSamples;
    float m_scale = 1.5f;
    int m_smoothing = 1;

    QVector<float> smoothSamples(const QVector<float>& input);

protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // WAVEFORMVIEW_H
