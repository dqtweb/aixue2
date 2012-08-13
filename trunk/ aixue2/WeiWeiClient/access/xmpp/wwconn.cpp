#include "wwconn.h"
#include <QString>
#include <cstring>

WWConn::WWConn()
: m_tls( new TLSDefault( this, "", TLSDefault::AnonymousClient ) ),
rcpt( "hello@weiwei.com" ) {

}

WWConn::~WWConn()
{
	delete m_tls;
} 
  void WWConn::handleMessageEvent( const JID& from, MessageEventType event )
    {
      printf( "received event: %d from: %s\n", event, from.full().c_str() );
    }

void WWConn::handleChatState( const JID& from, ChatStateType state )
    {
      printf( "received state: %d from: %s\n", state, from.full().c_str() );
    }
void  WWConn::handleTag( Tag* tag )
{
}
void WWConn::handleMessageSession( MessageSession *session )
    {
      //printf( "got new session\n");
      // this example can handle only one session. so we get rid of the old session
      j->disposeMessageSession( m_session );
      m_session = session;
      m_session->registerMessageHandler( this );
      m_messageEventFilter = new MessageEventFilter( m_session );
      m_messageEventFilter->registerMessageEventHandler( this );
      m_chatStateFilter = new ChatStateFilter( m_session );
      m_chatStateFilter->registerChatStateHandler( this );
    }
void WWConn::doWork()
{
	const QByteArray ba = UserName.toUtf8();
	const char* data = ba.constData();

	const QByteArray ba2 = Password.toUtf8();
	const char* data2 = ba2.constData();

	JID jid(data);
	j = new Client( jid, data2);
	j->registerConnectionListener( this );
	j->registerStanzaExtension(new XHtmlIM());
	//j->registerMessageHandler( this );
	//j->registerTagHandler(this);
	j->registerMessageSessionHandler( this, 0 );
	j->rosterManager()->registerRosterListener( this );
	j->disco()->setVersion( "messageTest", GLOOX_VERSION, "Linux" );
	j->disco()->setIdentity( "client", "bot" );
	j->disco()->addFeature( XMLNS_CHAT_STATES );

	j->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );

	if(j->connect())
	{
		emit connect();
	}

	//delete j;
}

void WWConn::onConnect()
{
	printf( "connected!\n" );
	m_tls->handshake();
	xtlsSend();
	m_send = "";
	emit connect();
}

void WWConn::onDisconnect( ConnectionError e )
{
	printf( "message_test: disconnected: %d\n", e );
	if( e == ConnAuthenticationFailed )
		printf( "auth failed. reason: %d\n", j->authError() );
	emit disconnect(e);
}

bool WWConn::onTLSConnect( const CertInfo& info )
{
	time_t from( info.date_from );
	time_t to( info.date_to );

	/* printf( "status: %d\nissuer: %s\npeer: %s\nprotocol: %s\nmac: %s\ncipher: %s\ncompression: %s\n"
	"from: %s\nto: %s\n",
	info.status, info.issuer.c_str(), info.server.c_str(),
	info.protocol.c_str(), info.mac.c_str(), info.cipher.c_str(),
	info.compression.c_str(), ctime( &from ), ctime( &to ) );*/
	emit tlsConnect(info);
	return true;
}

void WWConn::xtlsSend()
{
	Tag *m = new Tag( "message" );
	m->addAttribute( "to", rcpt.full() );
	m->addAttribute( "type", "chat" );
	Tag *x = new Tag( m, "xtls", Base64::encode64( m_send ) );
	x->addAttribute( "xmlns", "test:xtls" );
	m_send = "";
	j->send( m );
}

void WWConn::handleEncryptedData( const TLSBase* /*base*/, const std::string& data )
{
	printf( "caching %d bytes of encrypted data\n", data.length() );
	m_send += data;
}

void WWConn::handleDecryptedData( const TLSBase* /*base*/, const std::string& data )
{
	printf( "decrypted packet contents: %s\n", data.c_str() );
	m_tls->encrypt( "bye" );
	xtlsSend();
	j->disconnect();
}

void WWConn::handleHandshakeResult( const TLSBase* /*base*/, bool success, CertInfo& /*certinfo*/ )
{
	if( success )
	{
		printf( "xtls handshake successful!\n" );
		m_tls->encrypt( "ping" );
		xtlsSend();
	}
	else
	{
		printf( "xtls handshake failed!\n" );
		j->disconnect();
	}
}

void WWConn::handleMessage( const Message& msg, MessageSession * session)
{
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
}



void WWConn::handleLog( LogLevel level, LogArea area, const std::string& message )
{
	printf("log: level: %d, area: %d, %s\n", level, area, message.c_str() );
}

void WWConn::run()
{
	this->doWork();
}

void WWConn::handleItemSubscribed( const JID& jid )
{
	printf( "subscribed %s\n", jid.bare().c_str() );
}

void WWConn::handleItemAdded( const JID& jid )
{
	printf( "added %s\n", jid.bare().c_str() );
}

void WWConn::handleItemUnsubscribed( const JID& jid )
{
	printf( "unsubscribed %s\n", jid.bare().c_str() );
}

void WWConn::handleItemRemoved( const JID& jid )
{
	printf( "removed %s\n", jid.bare().c_str() );
}

void WWConn::handleItemUpdated( const JID& jid )
{
	printf( "updated %s\n", jid.bare().c_str() );
}

void WWConn::handleRoster( const Roster& roster )
{
	printf( "roster arriving\nitems:\n" );
	Roster::const_iterator it = roster.begin();
    QList<QString> *dataList=new QList<QString>();
    for( ; it != roster.end(); ++it ) 
	{
		printf( "jid: %s, name: %s, subscription: %d\n",
			(*it).second->jid().c_str(), (*it).second->name().c_str(),
			(*it).second->subscription() );
		StringList g = (*it).second->groups();
		StringList::const_iterator it_g = g.begin();
		for( ; it_g != g.end(); ++it_g )
			printf( "\tgroup: %s\n", (*it_g).c_str() );
		RosterItem::ResourceMap::const_iterator rit = (*it).second->resources().begin();
		//char *buff=new char(strlen((*it).second->jid().c_str()));
        //strcpy(buff,(*it).second->jid().c_str());
		QString str;
		str+=(*it).second->jid().c_str();
		dataList->append(str);

		for( ; rit != (*it).second->resources().end(); ++rit )
			printf( "resource: %s\n", (*rit).first.c_str() );
	}
    emit rosters(dataList);
}

void WWConn::handleRosterError( const IQ& /*iq*/ )
{
	printf( "a roster-related error occured\n" );
}

void WWConn::handleRosterPresence( const RosterItem& item, const std::string& resource,
								  Presence::PresenceType presence, const std::string& /*msg*/ )
{
	printf( "presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

void WWConn::handleSelfPresence( const RosterItem& item, const std::string& resource,
								Presence::PresenceType presence, const std::string& /*msg*/ )
{
	printf( "self presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

bool WWConn::handleSubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	printf( "subscription: %s\n", jid.bare().c_str() );
	StringList groups;
	JID id( jid );
	j->rosterManager()->subscribe( id, "", groups, "" );
	return true;
}

bool WWConn::handleUnsubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	printf( "unsubscription: %s\n", jid.bare().c_str() );
	return true;
}

void WWConn::handleNonrosterPresence( const Presence& presence )
{
	printf( "received presence from entity not in the roster: %s\n", presence.from().full().c_str() );
}

void WWConn::send(XHtmlIM *msg,string &to)
{
    //Message msg( tag );
    MessageSession *mess = new MessageSession(j,JID(to));
    StanzaExtensionList list;
    list.push_back(msg);
    //mess->send("1","",list);
	mess->send("1","");

    //j->disposeMessageSession(mess);
    //j->send(tag);
}
