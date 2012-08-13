#ifndef SHELL_H
#define SHELL_H

#include <QWidget>
#include <QtDeclarative>
#include "access/xmpp/wwconn.h"
#include "client/loginviewmodel.h"
#include "viewmodel/mainviewmodel.h"
namespace Ui {
class Shell;
}

//
class Shell : public QWidget
{
    Q_OBJECT
    
public:
    explicit Shell(QWidget *parent = 0);
    ~Shell();
     QDeclarativeView *loginView;
     QDeclarativeView *mainView;
     WWConn* conn;
private:
     Ui::Shell *ui;
     MainViewModel *mainViewModel;

private slots:
    void connectXmpp();
    void disconnectXmpp(ConnectionError e);
    void tlsConnect(const CertInfo& info);
	void rosters(QList<QString> *roster);
};

#endif // SHELL_H
