#ifndef MESSAGESESSIONMANAGER_H
#define MESSAGESESSIONMANAGER_H

#include <QObject>
#include <QMap>

#include <messagesession.h>
#include "wwmessagesession.h"
using namespace std;
using namespace gloox;
class MessageSessionManager : public QObject
{
    Q_OBJECT
public:
    explicit MessageSessionManager(QObject *parent = 0);
    virtual ~MessageSessionManager();
    void Add(MessageSession *messageSession);
signals:
    
public slots:

private:
    QMap<MessageSession*,WWMessageSession*> *messageSessionList_;
    
};

#endif // MESSAGESESSIONMANAGER_H
