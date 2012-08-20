#include "wwapplication.h"

WWApplication::WWApplication(int &argc, char **argv, bool GUIenabled)
    : QApplication(argc,argv,GUIenabled)
{
    actorManager_=new ActorManager();
}

WWApplication::~WWApplication()
{

}

ActorManager* WWApplication::GetActorManager()
{
    return actorManager_;
}
