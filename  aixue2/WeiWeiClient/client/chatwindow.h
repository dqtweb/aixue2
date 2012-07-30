#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QtDeclarative>
#include <viewmodel/chatviewmodel.h>
#include "client/wwconn.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT
    
public:
    ChatWindow(WWConn* conn,QWidget *parent = 0);
    ~ChatWindow();
    QDeclarativeView *chatView;
    QDeclarativeView *chatHistroyView;
    Q_PROPERTY(QString jid READ jid WRITE setJid NOTIFY jidChanged)
    ChatViewModel *chatViewModel;
    WWConn* conn;
    QString jid() const;
    void setJid(const QString &jid);
signals:
    void jidChanged();

private:
    QString m_jid;
    Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H
