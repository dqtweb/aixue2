#ifndef LOGINVIEWMODEL_H
#define LOGINVIEWMODEL_H

#include <QObject>
#include "access/xmpp/WWConn.h"

class LoginViewModel : public QObject
{
	Q_OBJECT
public:
	LoginViewModel();

	WWConn* Conn;

	Q_INVOKABLE bool login(const QString& userName,const QString& pwd) const;
	public slots:

private:

};


#endif // LOGINVIEWMODEL_H
