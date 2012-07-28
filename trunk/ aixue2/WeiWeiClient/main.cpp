#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QDeclarativeExtensionPlugin>
#include <QtScript/QScriptValue>
#include <QtCore/QTimer>
#include <QFileSystemModel>
#include "client/shell.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));

    Shell shell;
    shell.show();;
    /*QDeclarativeView* view=new QDeclarativeView();
    view->setSource(QUrl("qrc:/loginView"));
    view->show();*/
    return a.exec();

}

