#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "RippledCommands.h"

// XrplJsonParser
// -----------------------------------------------------------------------------
// Utility helpers for constructing WebSocket JSON payloads that match rippled's
// WebSocket API (see https://github.com/XRPLF/rippled). These helpers centralize
// request formatting so other components can focus on business logic instead of
// manual JSON string building.
// -----------------------------------------------------------------------------
class XrplJsonParser
{
public:
    static QJsonDocument buildRequest(const QString &method,
                                      const QJsonObject &params = {});
    static QJsonDocument buildRequest(RippledCommand command,
                                      const QJsonObject &params = {});
    static std::string commandToString(RippledCommand command);
};

