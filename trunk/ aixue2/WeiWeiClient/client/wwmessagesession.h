#ifndef WWMESSAGESESSION_H
#define WWMESSAGESESSION_H

#include <QObject>
#include <messageeventhandler.h>
#include <messagehandler.h>
#include <messagesession.h>
#include <chatstatehandler.h>
using namespace std;
using namespace gloox;

class WWMessageSession : public QObject,MessageEventHandler, MessageHandler, ChatStateHandler
{
    Q_OBJECT
public:
    explicit WWMessageSession(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // WWMESSAGESESSION_H
