import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "./qml/UI"
import "./qml/TalkItem"
import "./Common/config"
import TalkModel 1.0

Window {
    property bool bLightModel: true
    id:mainWindow
    width: 700
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
        TitleItem{
            id:titleItem
            window: mainWindow
        }

        ChatContentItem{   
            TalkListView{
                id:talk_view
                anchors.fill:parent
                model:talkListModel
            }

        }

        ToolItem{

        }

        InputItem{

        }
    }


    //信号连接
    Connections{
        target: titleItem
        onSigModifySkin:{
            bLightModel = !bLightModel
        }
    }

}


