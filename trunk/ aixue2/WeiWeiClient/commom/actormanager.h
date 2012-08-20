#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include <QObject>
#include <QMap>
#include <Theron/Actor.h>
#include <Theron/Address.h>
#include <Theron/Framework.h>
#include <Theron/Receiver.h>
#include <commom/wwmessage.h>
#include <client/wwglobal.h>
#include <access/xmpp/xmppmessagesessionactor.h>

using namespace std;

class ActorManager : public QObject
{
    Q_OBJECT
public:
    explicit ActorManager(QObject *parent = 0);


    void RegisterActor(Theron::ActorRef *actor, const char *actorName);

    void UnRegisterActor(Theron::ActorRef *actor);
    Theron::ActorRef* GetActor(const char *actorName);
    void SendSessionMessage2Actor(const char *actorName, WWSessionMessage &wwMessage);
signals:
    
public slots:
private:
    QMap<const char*,Theron::ActorRef*> *actorMap_;
    Theron::Framework *framework_;
    Theron::Receiver *receiver_;


};

#endif // ACTORMANAGER_H
