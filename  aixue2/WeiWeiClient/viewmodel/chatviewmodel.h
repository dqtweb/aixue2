#ifndef CHATVIEWMODEL_H
#define CHATVIEWMODEL_H

#include <QObject>
#include "client/wwconn.h"
#include <message.h>

class ChatViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ChatViewModel(QObject *parent = 0);
    Q_INVOKABLE void send(const QString &msg);
    WWConn* conn;
    QString jid;
signals:
    
public slots:
    
};

#endif // CHATVIEWMODEL_H
