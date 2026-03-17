#include "walletconfig.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

// Compute a default file path next to the application binary. Centralizing the
// location keeps the UI logic simple.
QString WalletConfig::defaultPath()
{
    return QDir(QCoreApplication::applicationDirPath()).filePath("walletconfig.txt");
}

// Persist wallet details to disk as a JSON document. The format is intentionally
// human-readable to simplify debugging and manual edits during development.
bool WalletConfig::save(const QString &path,
                        const QString &name,
                        const QString &address,
                        const QString &pubkey,
                        const QString &seed)
{
    QJsonObject root;
    root.insert("name", name);
    root.insert("address", address);
    root.insert("pubkey", pubkey);
    root.insert("seed", seed);

    QJsonDocument doc(root);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QTextStream stream(&file);
    stream << doc.toJson(QJsonDocument::Indented);
    file.close();
    return true;
}

// Load a wallet configuration from disk. Returning an empty QVariantMap keeps
// the calling code simple when the file is missing or malformed.
QVariantMap WalletConfig::load(const QString &path)
{
    QVariantMap map;
    QFile file(path);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return map;
    }

    QByteArray bytes = file.readAll();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        return map;
    }

    QJsonObject root = doc.object();
    map["name"] = root.value("name").toString();
    map["address"] = root.value("address").toString();
    map["pubkey"] = root.value("pubkey").toString();
    map["seed"] = root.value("seed").toString();
    return map;
}
