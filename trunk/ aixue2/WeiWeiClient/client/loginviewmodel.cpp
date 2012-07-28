#include "loginviewmodel.h"

LoginViewModel::LoginViewModel()
{
}

bool LoginViewModel::login(const QString& userName,const QString& pwd)const
{
    Conn->UserName=userName;
    Conn->Password=pwd;
    Conn->start();
	return true;
}
