#include "chatviewmodel.h"
#include <string>
using namespace std;
ChatViewModel::ChatViewModel(QObject *parent) :
QObject(parent)
{
}

void ChatViewModel::send(const QString &msg)
{
    Tag* html = new Tag( "html" );
    html->setXmlns( XMLNS_XHTML_IM );
    Tag* body = new Tag( html, "body" );
    body->setXmlns("http://www.w3.org/1999/xhtml");
	string cmsg=string((const char *)msg.toLocal8Bit());
    body->setCData(cmsg);
    XHtmlIM *xHtmlIM=new XHtmlIM(html);
    //Message *message=new Message();
    //message.addExtension(xHtmlIM);
	string cjid=string((const char *)(jid).toLocal8Bit());
    conn->send(xHtmlIM,cjid);
}
