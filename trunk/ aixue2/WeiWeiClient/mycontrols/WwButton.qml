// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 100
    height: 62

    MouseArea {
           id: mouseArea

           anchors.fill: parent
           //onClicked: rectangle.clicked()
           hoverEnabled: true
       }
}
