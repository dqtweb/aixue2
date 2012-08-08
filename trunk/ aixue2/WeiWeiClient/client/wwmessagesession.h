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
    WWMessageSession(MessageSession *messageSession,QObject *parent = 0);
    virtual void handleMessage(const Message& msg, MessageSession * /*session*/ );
    virtual void handleMessageEvent(const JID& from, MessageEventType event);
    virtual void handleChatState(const JID& from, ChatStateType state);
signals:
    
public slots:

private:
    MessageSession *messageSession_;
	MessageEventFilter *messageEventFilter_;
    ChatStateFilter *chatStateFilter_;
};

#endif // WWMESSAGESESSION_H
