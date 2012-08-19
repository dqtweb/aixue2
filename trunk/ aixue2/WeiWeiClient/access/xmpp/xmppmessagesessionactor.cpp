#include "xmppmessagesessionactor.h"

XmppMessageSessionActor::XmppMessageSessionActor(QObject *parent) :
    QObject(parent)
{
    //RegisterHandler(this, &XmppMessageSessionActor::RecieveHandler);
    //RegisterHandler(this, &XmppMessageSessionActor::SendHandler);
    RegisterHandler(this, &XmppMessageSessionActor::SessionHandler);
}

void XmppMessageSessionActor::RecieveHandler(const MessageSession *messageSession, const Theron::Address from)
{

}

void XmppMessageSessionActor::SendHandler(const MessageSession *messageSession, const Theron::Address from)
{

}

void XmppMessageSessionActor::SessionHandler(const WWSessionMessage &message, const Theron::Address from)
{
  // const MessageSession *messageSession = message.GetMessageSession();
   WWMessageSession *wwMessageSession = new WWMessageSession(message.messagesession_);
}
