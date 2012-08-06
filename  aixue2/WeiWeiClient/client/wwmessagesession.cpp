#include "wwmessagesession.h"

WWMessageSession::WWMessageSession(QObject *parent) :
    QObject(parent)
{
}

WWMessageSession::WWMessageSession(MessageSession *messageSession, QObject *parent) :
    QObject(parent)
{
    /*messageSession_ = messageSession;
    //j->disposeMessageSession( m_session );
    m_session = session;
    m_session->registerMessageHandler(this);
    m_messageEventFilter = new MessageEventFilter(m_session);
    m_messageEventFilter->registerMessageEventHandler(this);
    m_chatStateFilter = new ChatStateFilter(m_session);
    m_chatStateFilter->registerChatStateHandler(this);*/
}

void WWMessageSession::handleMessageEvent(const JID& from, MessageEventType event)
{
    printf( "received event: %d from: %s\n", event, from.full().c_str());
}

void WWMessageSession::handleChatState(const JID& from, ChatStateType state)
{
    printf( "received state: %d from: %s\n", state, from.full().c_str() );
}
void WWMessageSession::handleMessage(const Message &msg, MessageSession *session)
{
    /*
    Tag* m = msg.tag();
    Parser *p = new Parser( this );
    string body= msg.body();
    p->feed(body);//
    Tag *x = m->findChild( "xtls", "xmlns", "test:xtls" );
    if( x )
    {
        printf( "decrypting: %d\n", x->cdata().length() );
        m_tls->decrypt( Base64::decode64( x->cdata() ) );
        xtlsSend();
    }

    if( msg.body() == "quit" )
        j->disconnect();
      else if( msg.body() == "subscribe" )
        j->rosterManager()->subscribe( msg.from() );
      else if( msg.body() == "unsubscribe" )
        j->rosterManager()->unsubscribe( msg.from() );
      else if( msg.body() == "cancel" )
        j->rosterManager()->cancel( msg.from() );
      else if( msg.body() == "remove" )
        j->rosterManager()->remove( msg.from() );
      else
        printf( "msg: %s\n", msg.body().c_str() );
    delete m;
    */
}

