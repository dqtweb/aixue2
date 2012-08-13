#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include <QWidget>
#include "client/model/mroster.h"
#include "client/chatwindow.h"
#include "client/viewmodel/chatviewmodel.h"

class MainViewModel : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void Click(int index);
    MainViewModel(QObject *parent = 0);
    QList<QObject*> *RosterList;
    WWConn* conn;
signals:
    
public slots:
    
};

#endif // MAINVIEWMODEL_H
