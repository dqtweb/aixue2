#include "messagesessionmanager.h"

MessageSessionManager::MessageSessionManager(QObject *parent) :
    QObject(parent)
{
    messageSessionList = new QList<MessageSession>();
}
MessageSessionManager::~QObject()
{
   //ɾ��messagesession
   //delete messageSessionList
}
