import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.12

import org.freedesktop.gstreamer.GLVideoItem 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    x: 30
    y: 30
    color: "black"

    Item {
        anchors.fill:parent

        MouseArea{
            anchors.fill:parent
            onClicked: {
                popup.open();
            }
        }
        GstGLVideoItem {
            id: videoItem1
            objectName: "videoItem1"
            anchors.centerIn: parent
            width: parent.width/4
            height: parent.height/4
        }

        GstGLVideoItem {
            id: videoItem2
            objectName: "videoItem2"

            width: parent.width/4
            height: parent.height/4
        }



    Popup{
        id: popup
        width: 200
        height: 150
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        objectName: "popup"

        Rectangle{
            width:260;
            height:260;
            color:"red"

        }


    }




    }
}
