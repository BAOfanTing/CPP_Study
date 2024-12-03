import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "./qml/UI"
import "./qml/TalkItem"
import "./Common/config"
import TalkModel 1.0

Window {
    property bool bLightModel: true
    property real initialWidth: 900  // 定义初始宽度
    property real initialHeight: 730  // 定义初始高度
    property real initialMouseX: 0  // 定义初始鼠标X坐标
    property real initialMouseY: 0  // 定义初始鼠标Y坐标
    id:mainWindow
    width: 900
    height: 730
    visible: true
    color: "#f5f5f5"
    flags:Qt.FramelessWindowHint //去掉原始标题栏

    //UI高宽配置文件
    TalkConfig{
        id:talkConfig
    }

    //颜色和图标配置文件
    ColorConfig {
        id: colorConfig
    }

    Column{
        anchors.fill: parent
        TitleItem{
            id:titleItem
            window: mainWindow
        }

        ChatContentItem{
            id:chatContentItem
            anchors.top:titleItem.bottom
            TalkListView{
                id:talk_view
                anchors.fill:parent
                model:talkListModel
            }
        }

        ToolItem{
            id:toolItem
            anchors.top: chatContentItem.bottom

        }

        InputItem{
            id:inputItem
            anchors.bottom: parent.bottom
            anchors.top:toolItem.bottom
        }
    }

    //信号连接
    Connections{
        target: titleItem
        onSigModifySkin:{
            bLightModel = !bLightModel
        }
    }


    //窗口缩放,使用一个透明的小矩形在右下角
    Rectangle{
        id:resizeHandle
        width:15
        height:15
        color:"transparent"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        MouseArea{
            id:resizeArea
            anchors.fill: parent
            cursorShape: Qt.SizeFDiagCursor  //把鼠标形状变为对角线
            onPressed: {
                //记录初始的鼠标位置和窗口大小
                initialWidth = mainWindow.width;
                initialHeight = mainWindow.height;
                initialMouseX = mouse.x
                initialMouseY = mouse.y
            }

            onReleased: {
                //更新窗口
                initialWidth = mainWindow.width
                initialHeight = mainWindow.height
            }

            onPositionChanged: {
                //计算鼠标相对位置,调整窗口的宽度和高度
                if(mouse.x !== initialMouseX || mouse.y !== initialMouseY)
                {
                    var deltaX = mouse.x - initialMouseX;
                    var deltaY = mouse.y - initialMouseY;
                    mainWindow.width = Math.max(initialWidth + deltaX,550) //设置最小宽度值
                    mainWindow.height = Math.max(initialHeight + deltaY,620) //设置最小宽度值

                }
            }
        }
    }

}


