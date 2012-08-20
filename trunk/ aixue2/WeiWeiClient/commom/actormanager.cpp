#include "actormanager.h"

ActorManager::ActorManager(QObject *parent) :
    QObject(parent)
{
    actorMap_ = new QMap<const char*,Theron::ActorRef*>();
    framework_ = new Theron::Framework();
    receiver_ = new Theron::Receiver();
    Theron::ActorRef actor(framework_->CreateActor<XmppMessageSessionActor>());
	this->RegisterActor(&actor,XmppMessageSessionActor::s_actor_key);

}


void ActorManager::RegisterActor(Theron::ActorRef *actor, const char *actorName)
{

    actorMap_->insert(actorName,actor);
}

void ActorManager::UnRegisterActor(Theron::ActorRef *actor)
{

}

 Theron::ActorRef* ActorManager::GetActor(const char *actorName)
 {

     if (actorMap_->contains(actorName)) {
         return actorMap_->value(actorName);
     } else {
         return NULL;
     }

 }


 void ActorManager::SendMessage2Actor(const char *actorName, WWMessage &wwMessage)
 {
    Theron::ActorRef* actor = ActorManager::GetActor(actorName);
    //WWSessionMessage mm =  (WWSessionMessage)(*wwMessage);
    if (actor != NULL) {
        framework_->Send(wwMessage,actor->GetAddress(),receiver_->GetAddress());
        //actor->Push(wwMessage,receiver_->GetAddress());
    }
 }
