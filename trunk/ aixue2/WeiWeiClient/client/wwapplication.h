#ifndef WWAPPLICATION_H
#define WWAPPLICATION_H

#include <QApplication>

#include <Theron/Actor.h>
#include <Theron/Address.h>
#include <Theron/Framework.h>
#include <Theron/Receiver.h>
#include <commom/actormanager.h>
#include <client/wwglobal.h>

#include <access/xmpp/xmppmessagesessionactor.h>

class WWApplication : public QApplication
{
	Q_OBJECT
public:
     WWApplication(int &argc, char **argv, bool GUIenabled = true);
     ~WWApplication();
     ActorManager* GetActorManager();
private:
    ActorManager *actorManager_;
};

#endif // WWAPPLICATION_H
