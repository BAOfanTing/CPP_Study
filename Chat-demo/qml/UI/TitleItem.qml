import QtQuick 2.13
import "../../Common/config"
import "../../Common"

//标题栏,高度固定80
Rectangle{
    color: colorConfig.strBackgroundColor;
    property var window: null;
    property point dragStartPos: Qt.point(0, 0);
    signal sigModifySkin(); //跟换皮肤信号

    Text{
        x:30;
        y:parent.height/2-15;
        text: "这是标题"
        font.pixelSize: 30;
        font.family: colorConfig.strTextFont;
        color: colorConfig.strTextColor
    }

    //拖拽窗口
    MouseArea{
        anchors.fill:parent;
        preventStealing: true;
        onPressed: {
            dragStartPos = Qt.point(mouse.x,mouse.y); //记录初始位置
        }

        onPositionChanged: {
            if(window){
                window.x += (mouse.x - dragStartPos.x);
                window.y += (mouse.y - dragStartPos.y);
            }
        }
    }

    //关闭界面
    IconButton{
        id:closeIcon
        anchors.top: parent.top;
        anchors.topMargin: 5
        anchors.right: parent.right;
        anchors.rightMargin: 10
        imageSource: bLightModel ? "qrc:/icon/close_light.png" : "qrc:/icon/close_dark.png"; //设置图标

        MouseArea{
            anchors.fill:parent;
            onClicked: {
                if(window){
                    window.close();
                }
            }
        }
    }
    IconButton{
        id:skinIcon
        anchors.top: closeIcon.top;
        anchors.right: closeIcon.left;
        imageSource: bLightModel ? "qrc:/icon/skin_light.png" : "qrc:/icon/skin_dark.png"; //设置图标

        MouseArea{
            anchors.fill:parent;
            onClicked: {
                sigModifySkin();
            }
        }
    }


    // 底部灰色线条
    Rectangle {
        height: 1; // 线条高度
        width: parent.width; // 与父容器同宽
        color: colorConfig.strDividerColor; // 浅灰色
        anchors.bottom: parent.bottom; // 固定在底部
    }





}
