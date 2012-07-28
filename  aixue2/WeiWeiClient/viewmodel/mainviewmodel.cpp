#include "mainviewmodel.h"

MainViewModel::MainViewModel(QObject *parent) :
    QObject(parent)
{
	RosterList=new  QList<QObject*>();
}
void MainViewModel::Click(int index)
{
   ChatWindow *widget=new ChatWindow(conn);
   MRoster* roster=(MRoster*)(RosterList->at(index));
   widget->setWindowTitle(roster->name());
   Qt::WindowFlags flag=Qt::Dialog;
   widget->setJid(roster->name());
   widget->setWindowFlags(flag);
   widget->showNormal();
}
