import QtQuick 2.13
import QtQuick.Controls 2.13


Item {
    anchors.fill: parent
    property bool bHovered1: false
    property bool bHovered2: false
    signal sigPaste();
    signal sigCopy();
    Menu{
        id:contextMenu
        width:80
        background: Rectangle {
                    color: colorConfig.white  // 背景色
                    radius: 2  // 圆角
        }
        font: {
            pixelSize:8
            family: colorConfig.strTextFont
        }
        MenuItem{
            height:34
            text: qsTr("复制")
            background:Rectangle {
                id:copyBackground
                color:bHovered1 ? "#e2e2e2" :colorConfig.white // 背景色
                radius: 2  // 圆角
            }
            onHoveredChanged: {
                bHovered1 = !bHovered1;
            }
            //发送复制信号
            MouseArea{
                anchors.fill:parent
                onClicked: {
                    sigCopy();
                    contextMenu.close();
                }
            }
        }
        MenuItem{
            id:pasteBtn
            height:34
            text: qsTr("粘贴")
            background:Rectangle {
                color:bHovered2 ? "#e2e2e2" :colorConfig.white // 背景色
                radius: 2  // 圆角
            }
            onHoveredChanged: {
                bHovered2 = !bHovered2;
            }
            //发送粘贴信号
            MouseArea{
                anchors.fill:parent
                onClicked: {
                    sigPaste();
                    contextMenu.close();
                }
            }
        }
    }
    MouseArea{
        anchors.fill:parent
        acceptedButtons: Qt.RightButton
        onClicked : {
            contextMenu.x = mouse.x
            contextMenu.y = mouse.y
            contextMenu.popup();
        }
    }
}
