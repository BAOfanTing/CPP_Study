import QtQuick 2.15
/******************************************************************************
 *
 * @file       Button.qml
 * @brief      按钮 Function
 *
 * @author     纯真丁一郎
 * @date       2024/09/14
 * @Blog       https://www.relxdingyilang.cn/
 * @history
 *****************************************************************************/

Rectangle{
    id: root
    border.width: 1
    border.color: "#dcdfe6"
    radius: 10
    property alias source:img.source
    signal clicked

    Image {
        id:img
        width:30;height: 30
        anchors.centerIn: parent
    }
    MouseArea{
        anchors.fill:parent
        onClicked: {
            root.clicked()
        }
        onPressed: {
            root.color = "gray"
        }
        onReleased: {
            root.color = "white"
        }
    }
}