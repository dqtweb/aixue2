#-------------------------------------------------
#
# Project created by QtCreator 2012-06-16T18:00:26
#
#-------------------------------------------------

QT       += core gui
QT += declarative
QT += script
TARGET = WeiWeiClient
TEMPLATE = app


# 源代码文件pri
include(src.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    access/xmpp/wwconn.cpp \
    client/weiwei.cpp \
    client/shell.cpp \
    client/loginviewmodel.cpp \
    client/model/mroster.cpp \
    client/viewmodel/mainviewmodel.cpp \
    client/chatwindow.cpp \
    client/viewmodel/chatviewmodel.cpp \
    access/xmpp/messagesessionmanager.cpp \
    client/wwacount.cpp \
    client/wwglobal.cpp \
    access/xmpp/wwmessagesession.cpp

HEADERS  += mainwindow.h \
    access/xmpp/wwconn.h \
    client/weiwei.h \
    client/shell.h \
    client/loginviewmodel.h \
    client/model/mroster.h \
    client/viewmodel/mainviewmodel.h \
    client/chatwindow.h \
    client/viewmodel/chatviewmodel.h \
    access/xmpp/messagesessionmanager.h \
    client/wwacount.h \
    client/wwglobal.h \
    access/xmpp/wwmessagesession.h

FORMS    += mainwindow.ui \
    client/weiwei.ui \
    client/shell.ui \
    client/chatwindow.ui

OTHER_FILES += \
    src.pri \
    client/view/Myqml.qml \
    client/view/RichTextBox.qml \
    client/MainView.qml \
    MyQml/WwButton.qml \
    MyQml/RichEditToolButton.qml \
    client/view/LoginView.qml \
    client/view/MainView.qml \
    views/RichTextBox.qml \
    views/MainView.qml \
    views/LoginView.qml \
    views/ChatView.qml \
    views/ChatHistroyView.qml

RESOURCES += \
    controls.qrc

INCLUDEPATH +=thirdparty/gloox/src \
    thirdparty/Theron/include
