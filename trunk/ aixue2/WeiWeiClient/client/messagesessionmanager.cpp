#include "messagesessionmanager.h"

MessageSessionManager::MessageSessionManager(QObject *parent) :
    QObject(parent)
{
    messageSessionList_ = new QMap<MessageSession*,WWMessageSession*>();
}
MessageSessionManager::~MessageSessionManager()
{
   //É¾³ımessagesession
   //delete messageSessionList
}
void MessageSessionManager::Add(MessageSession *messageSession)
{
    if (messageSessionList_->contains(messageSession)) {

        WWMessageSession *wwMessageSession = new WWMessageSession(messageSession);
        messageSessionList_->insert(messageSession,wwMessageSession);
    }

}
