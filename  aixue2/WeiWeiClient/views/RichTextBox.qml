// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import QtWebKit  1.0
import QtDesktop  0.1
import "qrc:/."
import "qrc:/Controls"
Rectangle {
 property alias text: editView.html
id:root
Rectangle {
    height: 100
    id:rcbutoon

    Row

    {
        anchors.top: rcbutton.top
        height: 50
        id:fontBarColumn
        ComboBox
        {
             width: 100
             MenuItem {
                   text: "Pineapple"
                   onTriggered: console.debug(text)

                 }
                MenuItem {
                     text: "Grape"
                     onTriggered: console.debug(text)
                 }
        }
        ComboBox
        {
             width: 100
             MenuItem {
                   text: "9"
                   onTriggered: console.debug(text)

                 }
                MenuItem {
                     text: "10"
                     onTriggered: console.debug(text)
                 }
        }
     /*   RichEditToolButton
        {
            width:50
            text:"粗体"
            id:bBtn
        }
        RichEditToolButton
        {
               width:50
            text:"斜体"
            id:fBtn

        }
        RichEditToolButton
        {
               width:50
            text:"下划线"
            id:uBtn

        }
        RichEditToolButton
        {
               width:50
            text:"颜色"
            id:cBtn

        }*/
    }

    Row
    {

        anchors.top: fontBarColumn.bottom
        id:toolrow
        height: 50
        CLButton
        {
           width:50
           text:"img"
           id:imgBtn
        }
        CLButton
        {
            anchors.left: imgBtn.right
               width:50
            text:"字体"
            id:fontBtn
        }
        CLButton
        {
              anchors.left: fontBtn.right
               width:50
            text:"表情"
            id:iBtn

        }

    }

    anchors.top: parent.top
    anchors.left: root.left
    anchors.right: root.right
}
Rectangle
{
    id:rect
    anchors.top: rcbutoon.bottom
    anchors.bottom: root.bottom
    anchors.left: root.left
    anchors.right: root.right
    EditView
    {
        id:editView
        anchors.topMargin: 5
        anchors.fill: parent
        url: "file:///d:/test/sample-dynamic.html"
        scale: 1
        smooth: false
        settings.javascriptEnabled:true

        Component.onCompleted: {
            console.log("Sending to post");
            imgBtn.clicked.connect(sendToPost);
            rect.color="green";
            console.log("Sending to post1")
        }
        function sendToPost() {
            console.log("Sending to post3");
           // evaluateJavaScript("document.execCommand('inserthtml', false,'<div id=\"maojian\"></div>')");
            // evaluateJavaScript("document.execCommand('inserthtml', false, '<p>b^2-4ac</p>')")
            evaluateJavaScript("settext('b^2-4ac','maojian')");
            //evaluateJavaScript("document.execCommand('inserthtml', false, '<p>b^2-4ac</p>')");
            //evaluateJavaScript("document.execCommand('insertimage', false, 'd:/Balloon.bmp')");
            console.log("Sending to post4");
            }
        function insertImg(){
            //console.log("Sending to post5")
             document.execCommand("insertimage", false, "file://d:\\a.jpg");

        }
        function insert(html)
        {

            if(window.event)
            document.selection.createRange().pasteHTML(html);
            else
            format("insertHTML", html);
        }

    }

}



}
