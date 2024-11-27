import QtQuick 2.13
import "../Common/config"



Rectangle{
    width:700
    height:80
    color: colorConfig.strTitleColor

    Text{

        x:30
        y:parent.height/2
        text: "这是标题"
        font.pixelSize: 30
    }

    //拖拽窗口
    MouseArea{
        anchors.fill:parent;
        onPressed: {
            window.drag();
        }

    }

}
