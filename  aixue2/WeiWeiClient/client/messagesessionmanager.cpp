#include "messagesessionmanager.h"

MessageSessionManager::MessageSessionManager(QObject *parent) :
    QObject(parent)
{
    messageSessionList = new QList<MessageSession>();
}
MessageSessionManager::~MessageSessionManager()
{
   //ɾ��messagesession
   //delete messageSessionList
}
