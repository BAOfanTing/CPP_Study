import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "./qml"
import "./Common/config"

Window {
    id:window
    width: 700
    height: 720
    visible: true
    color: "#f5f5f5"
    flags:Qt.FramelessWindowHint
    ColorConfig {
        id: colorConfig
    }
    TitleItem{

    }
}


