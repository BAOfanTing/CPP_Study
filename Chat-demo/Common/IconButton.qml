import QtQuick 2.0

Rectangle{
    id:btnRect
    width:30;
    height: 30
    color:colorConfig.strBtnBackgroundUnselect
    property string imageSource: ""
    property int imgWidth :24;
    property int imgHeight : 24;

    Image{
        id:btnImage;
        width:imgWidth;
        height:imgHeight;
        anchors.centerIn: parent;
        source: imageSource;

        MouseArea{
            anchors.fill: parent;
            hoverEnabled: true; //启用鼠标悬浮检测
            onEntered: {
                btnRect.color = colorConfig.strBtnBackgroundSelect//鼠标进入背景变深
            }
            onExited: {
                btnRect.color = colorConfig.strBtnBackgroundUnselect //鼠标移开颜色变浅
            }
        }

    }
}
