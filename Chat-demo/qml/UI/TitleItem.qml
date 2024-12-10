import QtQuick 2.13
import "../../Common/config"

Rectangle{
    width:700;
    height:80;
    color: colorConfig.strTitleColor;
    property var window: null;
    property point dragStartPos: Qt.point(0, 0);

    Text{
        x:30;
        y:parent.height/2-15;
        text: "这是标题"
        font.pixelSize: 30;
        font.family: colorConfig.strTextFont;
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
        anchors.top: parent.top;
        anchors.right: parent.right;
        imageSource: "qrc:/icon/ic_close.png"; //设置图标

        MouseArea{
            anchors.fill:parent;
            onClicked: {
                if(window){
                    window.close();
                }
            }
        }
    }

    // 底部灰色线条
    Rectangle {
        height: 1; // 线条高度
        width: parent.width; // 与父容器同宽
        color: colorConfig.lightgray; // 浅灰色
        anchors.bottom: parent.bottom; // 固定在底部
    }





}
