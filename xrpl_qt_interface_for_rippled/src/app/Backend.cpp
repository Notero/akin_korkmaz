// Backend.cpp
// -----------------------------------------------------------------------------
// Implements the Backend class. The backend manages the rippled process
// lifecycle, polls node status, and bridges data between C++ and the QML UI.
// -----------------------------------------------------------------------------

#include "Backend.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include <QVariantMap>

#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

#include "walletconfig.h"

Backend::Backend(QObject *parent)
    : QObject(parent)
    , m_rippledProcess(new QProcess(this))
    , m_pollTimer(new QTimer(this))
{
    connect(m_rippledProcess, &QProcess::readyReadStandardOutput,
            this, &Backend::handleRippledStdout);
    connect(m_rippledProcess, &QProcess::readyReadStandardError,
            this, &Backend::handleRippledStderr);
    connect(m_rippledProcess,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &Backend::handleRippledFinished);

    m_pollTimer->setInterval(3000);
    connect(m_pollTimer, &QTimer::timeout, this, &Backend::pollServerInfo);

    connect(&m_wsClient, &QWebSocketClient::connected,
            this, &Backend::handleWebSocketConnected);
    connect(&m_wsClient, &QWebSocketClient::disconnected,
            this, &Backend::handleWebSocketDisconnected);
    connect(&m_wsClient, &QWebSocketClient::errorOccurred,
            this, &Backend::handleWebSocketError);
    connect(&m_wsClient, &QWebSocketClient::textMessageReceived,
            this, &Backend::handleWebSocketMessage);
}

std::string Backend::exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

void Backend::onStartServerRequested()
{
    if (m_rippledProcess->state() != QProcess::NotRunning) {
        appendLogLine("[INFO] rippled already running.");
        return;
    }

    QString program = "/Users/akin/rippled/rippled/.build/rippled";
    QStringList args = {
        "--conf",
        "/Users/akin/rippled/rippled/cfg/rippled.cfg"
    };

    appendLogLine("[INFO] Starting rippled...");
    emit serverStateChanged(1);

    m_rippledProcess->start(program, args);

    if (!m_rippledProcess->waitForStarted(3000)) {
        appendLogLine("[ERROR] Failed to start rippled: " +
                  m_rippledProcess->errorString());
        emit serverStateChanged(0);
        return;
    }

    appendLogLine("[INFO] rippled process started.");

    m_pollTimer->start();

    appendLogLine("[INFO] Connecting to WebSocket endpoint ws://127.0.0.1:6006 …");

    QTimer::singleShot(10000, this, [this](){
        m_wsClient.connectToServer();
    });
}

void Backend::onStopServerRequested()
{
    if (m_pollTimer->isActive())
        m_pollTimer->stop();

    if (m_rippledProcess->state() == QProcess::NotRunning) {
        appendLogLine("[INFO] rippled is not running.");
        emit serverStateChanged(0);
        return;
    }

    appendLogLine("[INFO] Stopping rippled…");

    m_rippledProcess->terminate();
    if (!m_rippledProcess->waitForFinished(5000)) {
        appendLogLine("[WARN] rippled did not exit, killing.");
        m_rippledProcess->kill();
        m_rippledProcess->waitForFinished();
    }

    emit serverStateChanged(0);
    appendLogLine("Server stopped.");

    m_wsClient.disconnectFromServer();
}

void Backend::onCommandEntered(const QString &command)
{
    std::string cmdStr = command.trimmed().toStdString();

    try {
        RippledCommand cmd = stringToCommand(cmdStr);
        Q_UNUSED(cmd);
        appendLogLine("[INFO] Rippled command detected: " + command);
        Backend::leswitch(cmd);
    } catch (const std::exception&) {
        appendLogLine("[INFO] Executing shell command: " + command);

        try {
            std::string output = exec(cmdStr.c_str());
            emit commandLogOut(QString::fromStdString(output));
        } catch (const std::exception& e) {
            appendLogLine("[ERROR] Failed to execute: " +
                                     QString::fromStdString(e.what()));
        }
    }
}

void Backend::leswitch(RippledCommand x)
{
    switch (x) {
    case RippledCommand::ACCOUNT_INFO:
        break;
    case RippledCommand::ACCOUNT_CURRENCIES:
        break;
    case RippledCommand::ACCOUNT_LINES:
        break;
    case RippledCommand::ACCOUNT_CHANNELS:
        break;
    case RippledCommand::ACCOUNT_NFTS:
        break;
    case RippledCommand::ACCOUNT_OBJECTS:
        break;
    case RippledCommand::ACCOUNT_OFFERS:
        break;
    case RippledCommand::ACCOUNT_TX:
        break;
    case RippledCommand::AMM_INFO:
        break;
    case RippledCommand::BOOK_CHANGES:
        break;
    case RippledCommand::BOOK_OFFERS:
        break;
    case RippledCommand::GET_AGGREGATE_PRICE:
        break;
    case RippledCommand::NFT_BUY_OFFERS:
        break;
    case RippledCommand::NFT_SELL_OFFERS:
        break;
    case RippledCommand::DEPOSIT_AUTHORIZED:
        break;
    case RippledCommand::LEDGER_CLOSED:
        break;
    case RippledCommand::LEDGER_CURRENT:
        break;
    case RippledCommand::LEDGER_DATA:
        break;
    case RippledCommand::LEDGER_ENTRY:
        break;
    case RippledCommand::LEDGER_HEADER:
        break;
    case RippledCommand::PATH_FIND:
        break;
    case RippledCommand::RIPPLE_PATH_FIND:
        break;
    case RippledCommand::NORIPPLE_CHECK:
        break;
    case RippledCommand::TX:
        break;
    case RippledCommand::TRANSACTION_ENTRY:
        break;
    case RippledCommand::TX_HISTORY:
        break;
    case RippledCommand::TX_REDUCE_RELAY:
        break;
    case RippledCommand::SIGN:
        break;
    case RippledCommand::SIGN_FOR:
        break;
    case RippledCommand::SUBMIT:
        break;
    case RippledCommand::SUBMIT_MULTISIGNED:
        break;
    case RippledCommand::SIMULATE:
        break;
    case RippledCommand::CHANNEL_AUTHORIZE:
        break;
    case RippledCommand::CHANNEL_VERIFY:
        break;
    case RippledCommand::SERVER_INFO:
        break;
    case RippledCommand::SERVER_STATE:
        break;
    case RippledCommand::SERVER_DEFINITIONS:
        break;
    case RippledCommand::FEE:
        break;
    case RippledCommand::PING:
        break;
    case RippledCommand::RANDOM:
        break;
    case RippledCommand::MANIFEST:
        break;
    case RippledCommand::GATEWAY_BALANCES:
        break;
    case RippledCommand::OWNER_INFO:
        break;
    case RippledCommand::SUBSCRIBE:
        break;
    case RippledCommand::UNSUBSCRIBE:
        break;
    case RippledCommand::VAULT_INFO:
        break;
    case RippledCommand::FEATURE:
        break;
    case RippledCommand::VALIDATORS:
        break;
    case RippledCommand::VALIDATOR_INFO:
        break;
    case RippledCommand::VALIDATOR_LIST_SITES:
        break;
    case RippledCommand::CAN_DELETE:
        break;
    case RippledCommand::LEDGER_CLEANER:
        break;
    case RippledCommand::LEDGER_REQUEST:
        break;
    case RippledCommand::LOG_LEVEL:
        break;
    case RippledCommand::LOGROTATE:
        break;
    case RippledCommand::LEDGER_ACCEPT:
        break;
    case RippledCommand::STOP:
        break;
    case RippledCommand::CONNECT:
        break;
    case RippledCommand::PEERS:
        break;
    case RippledCommand::PEER_RESERVATIONS_ADD:
        break;
    case RippledCommand::PEER_RESERVATIONS_DEL:
        break;
    case RippledCommand::PEER_RESERVATIONS_LIST:
        break;
    case RippledCommand::CONSENSUS_INFO:
        break;
    case RippledCommand::FETCH_INFO:
        break;
    case RippledCommand::GET_COUNTS:
        break;
    case RippledCommand::GET_MEMPOOL:
        break;
    case RippledCommand::PRINT:
        break;
    case RippledCommand::UNL_LIST:
        break;
    case RippledCommand::BLACKLIST:
        break;
    case RippledCommand::VALIDATION_CREATE:
        break;
    case RippledCommand::WALLET_PROPOSE:

        m_nextCallback = [this](QString json){
            QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
            QString accountAddress = doc["result"]["account_id"].toString();
            QString keyPhrases = doc["result"]["master_key"].toString();
            QString seed = doc["result"]["master_seed"].toString();
            emit walletGenerated(accountAddress,keyPhrases,seed);
        };

        QString json = R"({
            "command": "wallet_propose",
            "key_type": "secp256k1"
        })";

        m_wsClient.sendCommand(json);
        break;
    }
}

void Backend::appendLog(const QString &line)
{
    emit logLineArrived(line);
}

void Backend::appendLogLine(const QString &line)
{
    emit latestOutputChanged(line);
}

void Backend::commandLog(const QString &line)
{
    emit commandLogOut(line);
}

void Backend::setLedgerStats(int validated, int completed)
{
    emit ledgersValidatedChanged(validated);
    emit completedLedgersChanged(completed);
}

void Backend::handleRippledStdout()
{
    QByteArray data = m_rippledProcess->readAllStandardOutput();
    QString text = QString::fromLocal8Bit(data);
    if (!text.isEmpty()) {
        appendLog(text.trimmed());
    }
}

void Backend::handleRippledStderr()
{
    QByteArray data = m_rippledProcess->readAllStandardError();
    QString text = QString::fromLocal8Bit(data);
    if (!text.isEmpty()) {
        appendLog("[ERR] " + text.trimmed());
    }
}

void Backend::handleRippledFinished(int exitCode, QProcess::ExitStatus status)
{
    Q_UNUSED(exitCode)
    Q_UNUSED(status)

    appendLogLine("[INFO] rippled process exited.");
    emit serverStateChanged(0);
    appendLogLine("Server stopped.");
}

void Backend::pollServerInfo()
{
    const char* cmd =
        "curl -s -X POST http://127.0.0.1:5005/ "
        "-H \"Content-Type: application/json\" "
        "-d '{\"method\":\"server_info\",\"params\":[{}]}'";

    std::string out = exec(cmd);
    QString jsonStr = QString::fromStdString(out);

    if (jsonStr.trimmed().isEmpty()) {
        appendLogLine("[WARN] Empty server_info response");
        return;
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        appendLogLine("[ERROR] Failed to parse server_info JSON: " + err.errorString());
        return;
    }

    QJsonObject root = doc.object();
    QJsonObject result = root.value("result").toObject();
    QJsonObject info = result.value("info").toObject();

    QString state = info.value("server_state").toString();
    QString complete = info.value("complete_ledgers").toString();

    int firstLedger = 0;
    int lastLedger  = 0;

    if (complete.contains('-')) {
        QString firstRange = complete.split(',').first().trimmed();
        QStringList parts = firstRange.split('-');

        if (parts.size() == 2) {
            bool ok1 = false, ok2 = false;
            firstLedger = parts[0].toInt(&ok1);
            lastLedger  = parts[1].toInt(&ok2);

            if (ok1 && ok2) {
                setLedgerStats(lastLedger, firstLedger);
            }
        }
    }

    bool haveRange = (firstLedger > 0 && lastLedger >= firstLedger);

    if (state == "full" && haveRange) {
        appendLogLine("[INFO] Server fully synced. state=" + state +
                  ", complete_ledgers=" + complete);

        emit serverStateChanged(2);
        m_pollTimer->stop();
    }
    else if (state == "connected" || state == "syncing") {
        appendLogLine("[INFO] Server connected but syncing. state=" + state +
                  ", complete_ledgers=" + complete);

        emit serverStateChanged(1);
    }
    else {
        appendLogLine("[INFO] Poll server_info: state=" + state +
                  ", complete_ledgers=" + complete);
        emit serverStateChanged(0);
    }
}

void Backend::handleWebSocketConnected()
{
    appendLogLine("[INFO] WebSocket connected to ws://127.0.0.1:6006");
}

void Backend::handleWebSocketDisconnected()
{
    appendLogLine("[WARN] WebSocket disconnected from rippled endpoint.");
}

void Backend::handleWebSocketError(const QString &message)
{
    appendLogLine("[ERROR] WebSocket error: " + message);
}

void Backend::handleWebSocketMessage(const QString &message)
{
    appendLogLine("[WS] " + message.trimmed());
    if (m_nextCallback) {
        auto fn = m_nextCallback;
        m_nextCallback = nullptr;     // reset
        fn(message);                  // deliver WS output to the function
        return;
    }
}

bool Backend::saveWalletConfig(const QString &walletName,
                               const QString &address,
                               const QString &pubkey,
                               const QString &seed)
{
    const QString path = WalletConfig::defaultPath();
    return WalletConfig::save(path, walletName, address, pubkey, seed);
}

QVariantMap Backend::loadWalletConfig()
{
    const QString path = WalletConfig::defaultPath();
    return WalletConfig::load(path);
}

