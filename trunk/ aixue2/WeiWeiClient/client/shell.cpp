#include "shell.h"
#include "ui_shell.h"
#include <cstring>

Shell::Shell(QWidget *parent) :
QWidget(parent),
ui(new Ui::Shell)
{
	ui->setupUi(this);
    conn=new WWConn();
	this->setMinimumSize(260,570);
	this->resize(260,570);
	//conn->start();
	connect(conn, SIGNAL(connect()), this, SLOT(connectXmpp()));
	connect(conn, SIGNAL(rosters(QList<QString> *)), this, SLOT(rosters(QList<QString> *)));
	//connect(conn, SIGNAL(disconnect(ConnectionError)), this, SLOT(disconnectXmpp(ConnectionError)));
	//connect(conn, SIGNAL(tlsConnect( const CertInfo&)), this, SLOT(tlsConnect( const CertInfo&)));
	
	//delete conn;
    mainViewModel=new MainViewModel();
	loginView=new QDeclarativeView();
    LoginViewModel *loginViewModel=new LoginViewModel();
	loginViewModel->Conn=conn;
	loginView->rootContext()->setContextProperty("loginViewModel",loginViewModel);
	loginView->setSource(QUrl("qrc:/View/LoginView"));//loginView
	loginView->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	ui->verticalLayout->addWidget(loginView);
}

Shell::~Shell()
{
	delete ui;
}
void Shell::connectXmpp()
{
    QList<QObject*> dataList=*(mainViewModel->RosterList);
	mainView=new QDeclarativeView();
	ui->verticalLayout->removeWidget(loginView);

	mainView->setSource(QUrl("qrc:/View/MainView"));
	mainView->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	ui->verticalLayout->addWidget(mainView);
}
void Shell::disconnectXmpp(ConnectionError e)
{
}

void Shell::tlsConnect( const CertInfo& info )
{


}
void Shell::rosters(QList<QString> *rosters)
{
	QList<QObject*> *dataList=new QList<QObject*>();
	
	for ( int i=0; i!=rosters->size(); ++i )
	{
		MRoster *mroster=new MRoster();
        mroster->setName(rosters->at(i));
        dataList->append(mroster);
	}
    mainViewModel->RosterList=dataList;
    mainViewModel->conn=conn;
    mainView->rootContext()->setContextProperty("rosterModel",QVariant::fromValue(*dataList));
	mainView->rootContext()->setContextProperty("mainViewModel",mainViewModel);

}
