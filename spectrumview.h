#ifndef SPECTRUMVIEW_H
#define SPECTRUMVIEW_H


#include <QQuickPaintedItem>
#include <QVector>

class SpectrumView : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit SpectrumView(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

public slots:
    void setSpectrum(const QVector<float> &spectrum);

private:
    QVector<float> m_spectrum;
};

#endif // SPECTRUMVIEW_H
