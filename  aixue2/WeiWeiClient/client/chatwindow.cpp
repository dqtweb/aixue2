#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(WWConn* conn,QWidget *parent) :
QWidget(parent),
ui(new Ui::ChatWindow)
{
	ui->setupUi(this);
	chatViewModel=new ChatViewModel();
	chatView=new QDeclarativeView();
	chatViewModel->conn=conn;
	chatView->rootContext()->setContextProperty("chatViewModel",chatViewModel);
	chatView->setSource(QUrl("qrc:/View/ChatView"));
	chatView->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	ui->verticalLayout->addWidget(chatView);
	QVariant returnedValue;
	QObject *item = qobject_cast<QObject*>(chatView->rootObject()); 
	QObject *item1 = chatView->findChild<QObject *>("hello"); 
	QVariant msg = "Hello from C++";
	QMetaObject::invokeMethod(item, "myQmlFunction",Q_RETURN_ARG(QVariant, returnedValue),Q_ARG(QVariant, msg));
	qDebug() << "QML function returned:" << returnedValue.toString();
}

ChatWindow::~ChatWindow()
{
	delete ui;
}

QString ChatWindow::jid() const
{
	return m_jid;
}

void ChatWindow::setJid(const QString &jid)
{
	if (jid != m_jid) {
		m_jid = jid;
		chatViewModel->jid=m_jid;
		emit jidChanged();
	}
}
