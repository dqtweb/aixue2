#ifndef WWSESSIONMESSAGE_H
#define WWSESSIONMESSAGE_H

#include <messagesession.h>
#include "wwmessage.h"

using namespace gloox;

class WWSessionMessage : public WWMessage
{
public:
    WWSessionMessage();
    WWSessionMessage(MessageSession *messagesession);
    inline const MessageSession* const GetMessageSession()
    {
        return messagesession_;
    }

public:
    MessageSession *messagesession_;
};

#endif // WWSESSIONMESSAGE_H
