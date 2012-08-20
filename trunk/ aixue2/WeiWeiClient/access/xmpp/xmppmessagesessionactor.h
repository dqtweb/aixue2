#ifndef XMPPMESSAGESESSIONACTOR_H
#define XMPPMESSAGESESSIONACTOR_H

#include <QObject>

#include <Theron/Actor.h>
#include <Theron/Address.h>
#include <Theron/Framework.h>
#include <Theron/Receiver.h>

#include <messagesession.h>
#include <access/xmpp/wwmessagesession.h>
#include <commom/wwsessionmessage.h>

using namespace gloox;

class XmppMessageSessionActor : public Theron::Actor
{
public:
    XmppMessageSessionActor();
    static const char *s_actor_key;
private:
    void RecieveHandler(const MessageSession *message, const Theron::Address from);
    void SendHandler(const MessageSession *message, const Theron::Address from);
    void SessionHandler(const WWSessionMessage &message, const Theron::Address from);

    
};

#endif // XMPPMESSAGESESSIONACTOR_H
