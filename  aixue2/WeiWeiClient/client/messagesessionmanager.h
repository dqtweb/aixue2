#ifndef MESSAGESESSIONMANAGER_H
#define MESSAGESESSIONMANAGER_H

#include <QObject>
#include <QList>

#include <messagesession.h>
using std;
using namespace gloox;
class MessageSessionManager : public QObject
{
    Q_OBJECT
public:
    explicit MessageSessionManager(QObject *parent = 0);
    virtual ~QObject();
signals:
    
public slots:
private:
    QList<MessageSession> *messageSessionList;
    
};

#endif // MESSAGESESSIONMANAGER_H
