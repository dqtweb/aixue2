#include "actormanager.h"

ActorManager::ActorManager(QObject *parent) :
    QObject(parent)
{
    actorMap_ = new QMap<const char*,Theron::ActorRef*>();
    framework_ = new Theron::Framework();
    receiver_ = new Theron::Receiver();
    this->RegisterActor<XmppMessageSessionActor>(XMPP_MESSAGE_SESSION);

}

template <class ActorType>
void ActorManager::RegisterActor(const char *actorName)
{
   // Theron::ActorRef actor(framework_->CreateActor<ActorType>());
    //actorMap_->insert(actorName,&actor);
}

void ActorManager::UnRegisterActor(Theron::ActorRef *actor)
{

}

 Theron::ActorRef* ActorManager::GetActor(const char *actorName)
 {
     return actorMap_->value(actorName);
 }


 void ActorManager::SendMessage2Actor(const char *actorName, const WWMessage &wwMessage)
 {
    Theron::ActorRef* actor = ActorManager::GetActor(actorName);
    if (actor != NULL) {
        actor->Push(wwMessage,receiver_->GetAddress());
    }
 }
