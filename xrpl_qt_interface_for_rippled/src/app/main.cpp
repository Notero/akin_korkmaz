// main.cpp
// -----------------------------------------------------------------------------
// Application entry point. Sets up the Qt application, instantiates the Backend
// that manages the rippled process, and wires C++ signals/slots to the QML UI.
// -----------------------------------------------------------------------------

#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringList>
#include <QUrl>

#include "Backend.h"

namespace {
// Limits rolling text buffers to a maximum number of lines to prevent the UI
// from accumulating unbounded log data.
void trimRollingBuffer(QObject* root, const char* propertyName, int maxLines = 100)
{
    QString current = root->property(propertyName).toString();
    QStringList lines = current.split('\n');
    if (lines.size() > maxLines) {
        lines = lines.mid(lines.size() - maxLines);
        current = lines.join('\n');
        root->setProperty(propertyName, current);
    }
}
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Backend backend;
    engine.rootContext()->setContextProperty("backend", &backend);

    const QUrl url(QStringLiteral("qrc:/qt/qml/xrpl/qml/Main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *root = engine.rootObjects().first();

    QObject::connect(root, SIGNAL(startServerRequested()),
                     &backend, SLOT(onStartServerRequested()));
    QObject::connect(root, SIGNAL(stopServerRequested()),
                     &backend, SLOT(onStopServerRequested()));
    QObject::connect(root, SIGNAL(commandEntered(QString)),
                     &backend, SLOT(onCommandEntered(QString)));

    QObject::connect(&backend, &Backend::serverStateChanged,
                     root, [root](int state) {
                         root->setProperty("serverState", state);
                     });

    QObject::connect(&backend, &Backend::latestOutputChanged,
                     root, [root](const QString &line) {
                         QString current = root->property("latestOutput").toString();
                         current += line + "\n";
                         root->setProperty("latestOutput", current);
                         trimRollingBuffer(root, "latestOutput");
                         root->setProperty("outputHighlight", 1.0);
                     });

    QObject::connect(&backend, &Backend::logLineArrived,
                     root, [root](const QString &line) {
                         QString current = root->property("logStream").toString();
                         current += line + "\n";
                         root->setProperty("logStream", current);
                         trimRollingBuffer(root, "logStream");
                         root->setProperty("logHighlight", 1.0);
                     });

    QObject::connect(&backend, &Backend::commandLogOut,
                     root, [root](const QString &line) {
                         QString current = root->property("commandout").toString();
                         current += line;
                         root->setProperty("commandout", current);
                         trimRollingBuffer(root, "commandout");
                         root->setProperty("logHighlight", 1.0);
                     });

    QObject::connect(&backend, &Backend::ledgersValidatedChanged,
                     root, [root](int v) {
                         root->setProperty("ledgersValidated", v);
                     });

    QObject::connect(&backend, &Backend::completedLedgersChanged,
                     root, [root](int v) {
                         root->setProperty("completedLedgers", v);
                     });

    QObject::connect(&backend, &Backend::logHighlightChanged,
                     root, [root](double val) {
                         root->setProperty("logHighlight", val);
                     });

    QObject::connect(&backend, &Backend::outputHighlightChanged,
                     root, [root](double val) {
                         root->setProperty("outputHighlight", val);
                     });

    return app.exec();
}
