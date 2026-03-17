#pragma once

#include <QVariantMap>
#include <QString>

// Small utility for persisting wallet information to disk. The methods are
// static to make them easy to call from both QML and C++ without repeatedly
// instantiating helper objects.
class WalletConfig
{
public:
    static QString defaultPath();
    static bool save(const QString &path,
                     const QString &name,
                     const QString &address,
                     const QString &pubkey,
                     const QString &seed);
    static QVariantMap load(const QString &path);
};
