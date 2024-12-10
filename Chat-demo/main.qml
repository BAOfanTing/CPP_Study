import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "./qml"
import "./Common/config"

Window {
    id:mainWindow
    width: 700
    height: 730
    visible: true
    color: "#f5f5f5"
    flags:Qt.FramelessWindowHint //去掉原始标题栏

    ColorConfig {
        id: colorConfig
    }
    Column{
        TitleItem{
            window: mainWindow
        }

        TextShowItem{

        }

        ToolItem{

        }

        InputItem{

        }
    }


}


