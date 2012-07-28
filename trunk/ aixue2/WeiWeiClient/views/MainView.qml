// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 100
    height: 62
    Component
    {
       id:mydelegate
       Rectangle {
           height: 25
           width: 100
           Text { text: name }
           MouseArea {
              anchors.fill: parent
              onClicked: {
                   mainViewModel.Click(index);
               }
          }

       }
    }
    Row {
        Rectangle {
           id:topRect
           height: 50
        }
        ListView {
            height:200
            id:mainLv
            focus: true
            model: rosterModel
            delegate:mydelegate
            //anchors.fill: parent
        }
        Rectangle {
           id:bottomRect
           height: 50
        }
    }

}
