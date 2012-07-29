// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "qrc:/View"
import "qrc:/."
import "qrc:/Controls"
import QtDesktop 0.1
import QtWebKit 1.0


SplitterColumn {
    objectName:"hello"
    function myQmlFunction(msg) {
            console.log("Got message:", msg)
            //messageWebView.showMessage(msg,iType)
            return "some return value"
    }

    Rectangle {
        WebView {
             id:messageWebView
             url:"file:///d:/test/sample-dynamic.html"
             preferredWidth: 490
             preferredHeight: 400
             smooth: false
             settings.javascriptEnabled:true

             function showMessage(msg,iType){
                 if (iType == 1 )
                 {
                   evaluateJavaScript("settext('b^2-4ac','maojian')")
                 }else
                   if( iType==2 )
                   {
                       evaluateJavaScript("settext('b^2-4ac','maojian')")
                   }
             }
         }


    }
    Rectangle  {
       // Splitter.minimumSize: 50
        Splitter.expanding: true
        Column {
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


}
