#include "messagesessionmanager.h"

MessageSessionManager::MessageSessionManager(QObject *parent) :
    QObject(parent)
{
    messageSessionList = new QList<MessageSession>();
}
MessageSessionManager::~QObject()
{
   //É¾³ımessagesession
   //delete messageSessionList
}
