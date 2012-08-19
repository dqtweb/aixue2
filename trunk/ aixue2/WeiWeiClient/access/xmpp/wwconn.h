#ifndef WWCONN_H
#define WWCONN_H

#include <QApplication>

#include <client.h>
#include <connectionlistener.h>
#include <presence.h>
#include <rostermanager.h>
#include <disco.h>
#include <message.h>
#include <gloox.h>
#include <loghandler.h>
#include <tlshandler.h>
#include <tlsdefault.h>
#include <logsink.h>
#include <messagehandler.h>
#include <base64.h>
#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include <QObject>
#include <qthread.h>
#include <loghandler.h>
#include "client/model/mroster.h"
#include <string>
#include <message.h>
#include <messagesession.h>
#include <messagesessionhandler.h>
#include <messageeventhandler.h>
#include <chatstatehandler.h>
#include <messageeventfilter.h>
#include <chatstatefilter.h>
#include <taghandler.h>
#include <parser.h>
#include <xhtmlim.h>

#include <commom/actormanager.h>
#include <client/wwapplication.h>
#include <client/wwglobal.h>

using namespace std;
using namespace gloox;

class WWConn : public QThread,MessageSessionHandler,RosterListener,ConnectionListener, LogHandler,
    MessageHandler, TLSHandler,MessageEventHandler,ChatStateHandler,TagHandler
{
	Q_OBJECT

public:
	QString UserName;
	QString Password;
	WWConn();
	~WWConn();
protected:
	void run();
public:
    void send(XHtmlIM *msg,string &to);
	void doWork();

	virtual void onConnect();

	virtual void onDisconnect( ConnectionError e );

	virtual bool onTLSConnect( const CertInfo& info );

	void xtlsSend();

	virtual void handleEncryptedData( const TLSBase* /*base*/, const std::string& data );

	virtual void handleDecryptedData( const TLSBase* /*base*/, const std::string& data );

	virtual void handleHandshakeResult( const TLSBase* /*base*/, bool success, CertInfo& /*certinfo*/ );

    virtual void handleMessage( const Message& msg, MessageSession * /*session*/ );

	virtual void handleLog( LogLevel level, LogArea area, const std::string& message );
    virtual void handleTag( Tag* tag );
    virtual void handleMessageSession( MessageSession *session );
    virtual void handleMessageEvent( const JID& from, MessageEventType event );
    
	virtual void handleChatState( const JID& from, ChatStateType state );
	virtual void handleItemAdded( const JID& jid );
	virtual void handleItemSubscribed( const JID& jid );
	virtual void handleItemRemoved( const JID& jid );
	virtual void handleItemUpdated( const JID& jid );
	virtual void handleItemUnsubscribed( const JID& jid );
	virtual void handleRoster( const Roster& roster );
	virtual void handleRosterPresence( const RosterItem& item, const std::string& resource,
		Presence::PresenceType presence, const std::string& msg );

	virtual void handleSelfPresence( const RosterItem& item, const std::string& resource,
		Presence::PresenceType presence, const std::string& msg );
	virtual bool handleSubscriptionRequest( const JID& jid, const std::string& msg );

	virtual bool handleUnsubscriptionRequest( const JID& jid, const std::string& msg );
	virtual void handleNonrosterPresence( const Presence& presence ) ;
	virtual void handleRosterError( const IQ& iq );

private:
	Client *j;
	TLSBase* m_tls;
	std::string m_send;
	const JID rcpt;
	MessageSession *m_session;
    MessageEventFilter *m_messageEventFilter;
    ChatStateFilter *m_chatStateFilter;
    ActorManager *actorManager_;
signals:
	void connect();
	void rosters(QList<QString> *roster);
	void disconnect(ConnectionError e);
	bool tlsConnect( const CertInfo& info );
    

};

#endif // WWCONN_H
