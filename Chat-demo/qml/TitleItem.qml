import QtQuick 2.13
import "../Common/config"

Rectangle{
    width:700;
    height:80;
    color: colorConfig.strTitleColor;
    property var window: null;
    property point dragStartPos: Qt.point(0, 0);

    Text{

        x:30
        y:parent.height/2-15
        text: "这是标题"
        font.pixelSize: 30
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
                console.log("change")
                window.x += (mouse.x - dragStartPos.x);
                window.y += (mouse.y - dragStartPos.y);
            }
        }


    }

}
