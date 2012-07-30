// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "qrc:/View"
import "qrc:/."
import "qrc:/Controls"
import QtDesktop 0.1

SplitterColumn {

    Rectangle {


    }

    Rectangle  {
       // Splitter.minimumSize: 50
        Splitter.expanding: true


        RichTextBox {
            anchors.top: rect1.bottom
            anchors.bottom: parent.bottom
            id:richTextBox1
            anchors.fill: parent;
        }

        Rectangle {
           // Splitter.maximumSize: 400
            color: "gray"
            height: 200

                id:rect1

                CLButton {

                text:"发送"
                onClicked:
                {
                    chatViewModel.send(richTextBox1.text);
                }
            }
        }

    }


}
