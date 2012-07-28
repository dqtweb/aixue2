// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import QtDeskTop 1.0

//![0]
ListView {
    width: 100; height: 100
    anchors.fill: parent

    model: myModel
    delegate: Rectangle {
        Row
        {
        Image
        {

        }
        Column
        {
            Text
            {
            }
            Text
            {
            }
        }
        Column
        {
            ProgressBar
            {
            }
            Button
            {
            }
            Button
            {
            }
        }
        }

        height: 25
        width: 100
        color: model.modelData.color
        Text { text: name }
    }
}
