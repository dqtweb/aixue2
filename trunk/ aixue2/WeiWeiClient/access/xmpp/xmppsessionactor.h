#ifndef XMPPSESSIONACTOR_H
#define XMPPSESSIONACTOR_H

#include <QObject>
#include <Theron/Actor.h>
#include <Theron/Address.h>
#include <Theron/Framework.h>
#include <Theron/Receiver.h>

class XmppSessionActor : public QObject, Theron::Actor
{
    Q_OBJECT
public:
    XmppSessionActor();
};

#endif // XMPPSESSIONACTOR_H
