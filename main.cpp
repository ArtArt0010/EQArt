#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "AudioInput.h"
#include "audioprocessor.h"
#include "waveformview.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    qmlRegisterType<WaveformView>(
        "EQ",
        1,
        0,
        "WaveformView"
        );


    QQmlApplicationEngine engine;


    AudioProcessor processor;
    AudioInput audio;


    engine.rootContext()->setContextProperty(
        "audioProcessor",
        &processor
        );


    // Загружаем QML
    engine.loadFromModule("EQ_Art", "Main");


    if (engine.rootObjects().isEmpty())
        return -1;


    QObject *root = engine.rootObjects().first();


    WaveformView *waveform =
        root->findChild<WaveformView*>("waveform");


    if(!waveform)
    {
        qDebug() << "WaveformView не найден";
        return -1;
    }


    QObject::connect(
        &processor,
        &AudioProcessor::samplesReady,
        waveform,
        &WaveformView::setSamples
        );


    QObject::connect(
        &audio,
        &AudioInput::samplesReady,
        &processor,
        &AudioProcessor::process
        );


    audio.start();


    return app.exec();
}
