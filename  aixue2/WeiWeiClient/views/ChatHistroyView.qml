// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import QtQuick 1.1
import "qrc:/View"
import "qrc:/."
import "qrc:/Controls"
import QtWebKit 1.0

Rectangle {
    function myQmlFunction(msg,iType) {
            console.log("Got message:", msg)
            messageWebView.showMessage(msg,iType)
            return "some return value"
    }
        WebView {
             anchors.fill: parent
             id:messageWebView
             url:"file:///d:/test/sample-dynamic.html"
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
