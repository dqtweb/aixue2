#include "weiwei.h"



WeiWei::WeiWei(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
/*	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(Hello()))*/;
	
}

WeiWei::~WeiWei()
{

}
 /*void WeiWei::create(WId = 0, bool initializeWindow = true,
                         bool destroyOldWindow = true)
 {
	
 }*/
void  WeiWei::Hello()
{
	WWConn* conn=new WWConn();
	conn->start();
	connect(conn, SIGNAL(connect()), this, SLOT(connectXmpp()));
	connect(conn, SIGNAL(disconnect(ConnectionError)), this, SLOT(disconnectXmpp(ConnectionError)));
	connect(conn, SIGNAL(tlsConnect( const CertInfo&)), this, SLOT(tlsConnect( const CertInfo&)));
	//delete conn;
}

bool WeiWei::winEvent(MSG *message, long *result)
{  
	if ( message->message == WM_CREATE )   { 
	
          }
return  QMainWindow::winEvent(message, result);
}


void WeiWei::Hello2()
{
}
	void WeiWei::connectXmpp()
	{
	}
	void WeiWei::disconnectXmpp(ConnectionError e)
	{
	}
	void WeiWei::tlsConnect( const CertInfo& info )
	{
	}