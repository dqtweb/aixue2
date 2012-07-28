// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    property alias text: textElement.text
    signal clicked()
    Text
    {
        id:textElement
        anchors.horizontalCenter: if(textAlign == "center") rectangle.horizontalCenter
               anchors.left: if(textAlign == "left") rectangle.left
               anchors.right: if(textAlign == "right" ) rectangle.right
               anchors.rightMargin: rightMargin
               anchors.leftMargin: leftMargin
               anchors.verticalCenter: rectangle.verticalCenter
               font.family: fontFamily
               font.pointSize: 0.001 + fontSize
               color: textColor
               font.weight: fontWeight

               MouseArea {

                      id: mouseArea1
                      anchors.fill: parent
                      onClicked:
                      {

                          console.log("Sending to 1");

                          root.clicked();
                          console.log("Sending to 2");
                      }

                  }

    }
    id:root
    color:"blue"
    MouseArea {

           id: mouseArea2
           anchors.fill: parent
           onClicked:
           {

               console.log("Sending to 1");

               root.clicked();
               console.log("Sending to 2");
           }

       }

}
