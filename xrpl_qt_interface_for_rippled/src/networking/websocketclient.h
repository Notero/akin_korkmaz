#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>

// Placeholder Qt object for future WebSocket integrations. Keeping this type
// helps the QML layer compile while we refactor toward the typed client classes
// used elsewhere in the codebase.
class websocketclient : public QObject
{
    Q_OBJECT
public:
    explicit websocketclient();
};

#endif // WEBSOCKETCLIENT_H
