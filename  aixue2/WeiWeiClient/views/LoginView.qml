// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import QtDesktop 0.1
import "qrc:/."
import "qrc:/Controls"

Rectangle {
    id:root
    anchors.fill: parent
    Grid{
        anchors.fill: root
        rows:3
        Rectangle {
            height: 10;
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            id:topRect
        }
        Rectangle {
            height: 150;
            anchors.top: topRect.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            id:imageRect
            Image {
                height: 130
                width:130
                id: logoImg
                anchors.centerIn: parent
                source: "../Images/login.jpg"

            }
        }
        Rectangle {
            height: 50;
            anchors.topMargin: 10
            anchors.top: imageRect.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            id:userNameRect
            CLLineEdit {
                height: 25
                width: 200
                anchors.centerIn: parent
                id:userNameTF
                placeholderText: "用户名称"
                KeyNavigation.down: pwdTF
                KeyNavigation.tab: pwdTF
            }
        }
        Rectangle {
            id:pwdRect
            height: 50;
            anchors.top: userNameRect.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            CLLineEdit {
                id:pwdTF
                height: 25
                width: 200
                anchors.centerIn: parent
                echoMode :  TextInput.Password
                placeholderText: "用户密码"
                KeyNavigation.up: userNameTF
                KeyNavigation.tab: loginbtn
            }
        }
        Rectangle {
            id:btnRect
            anchors.top: pwdRect.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: bottomRect.top
            height: 50;
            CLButton {
                anchors.centerIn: parent
                text: "登  录"
                id:loginbtn
                KeyNavigation.tab: userNameTF
                onClicked: {
                    if (loginViewModel.login(userNameTF.text,pwdTF.text)) {
                    }
                }
            }
        }
        Rectangle {
            anchors.top: btnRect.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: bottomRect.top
            height: 50;
            id:fillRect
        }
        Rectangle {
            height: 50;width:50;
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            id:bottomRect
        }
    }
}










