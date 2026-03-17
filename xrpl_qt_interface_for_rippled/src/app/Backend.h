#pragma once

// Backend.h
// -----------------------------------------------------------------------------
// Declares the Backend class responsible for managing the rippled process,
// relaying logs and status to the QML UI, and executing shell or rippled
// commands entered by the user.
// -----------------------------------------------------------------------------

#include <QObject>
#include <QStringList>
#include <QProcess>
#include <QTimer>
#include <QVariantMap>
#include <functional>


#include "RippledCommands.h"
#include "QWebSocketClient.h"

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QObject *parent = nullptr);

public slots:
    void onStartServerRequested();
    void onStopServerRequested();
    void onCommandEntered(const QString &command);
    Q_INVOKABLE bool saveWalletConfig(const QString &walletName,
                                      const QString &address,
                                      const QString &pubkey,
                                      const QString &seed);
    Q_INVOKABLE QVariantMap loadWalletConfig();

public:
    void leswitch(RippledCommand command);

signals:
    void serverStateChanged(int state);
    void latestOutputChanged(const QString &text);
    void logLineArrived(const QString &line);
    void ledgersValidatedChanged(int v);
    void completedLedgersChanged(int v);
    void logHighlightChanged(double v);
    void outputHighlightChanged(double v);
    void commandLogOut(const QString &text);
    void walletGenerated(const QString address,const QString pubkey,const QString seed);

private slots:
    void handleRippledStdout();
    void handleRippledStderr();
    void handleRippledFinished(int exitCode, QProcess::ExitStatus status);
    void pollServerInfo();
    void handleWebSocketConnected();
    void handleWebSocketDisconnected();
    void handleWebSocketError(const QString &message);
    void handleWebSocketMessage(const QString &message);

private:
    std::string exec(const char* cmd);
    void appendLog(const QString &line);
    void appendLogLine(const QString &line);
    void commandLog(const QString &line);
    void setLedgerStats(int validated, int completed);
    void WsBuffer();
private:
    QProcess* m_rippledProcess;
    QTimer*   m_pollTimer;
    QStringList m_logLines;
    QWebSocketClient m_wsClient;
    std::function<void(QString)> m_nextCallback = nullptr;
};

