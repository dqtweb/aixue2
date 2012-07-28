#ifndef WEIWEI_H
#define WEIWEI_H

#include <QtGui/QMainWindow>
#include "ui_weiwei.h"
#include "wwconn.h"

class WeiWei : public QMainWindow
{
	Q_OBJECT

public:
	WeiWei(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WeiWei();

private:
	Ui::WeiWeiClass ui;
protected:
	    bool winEvent(MSG *message, long *result);
public slots:
	void  Hello();
	void Hello2();

private slots:
    void connectXmpp();
	void disconnectXmpp(ConnectionError e);
	void tlsConnect( const CertInfo& info );
};

#endif // WEIWEI_H
