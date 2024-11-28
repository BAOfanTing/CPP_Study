import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "./qml/UI"
import "./qml/TalkItem"
import "./Common/config"
import TalkModel 1.0

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

        ChatContentItem{
            SplitView{
                anchors.fill:parent
                anchors.margins: 10;
                orientation:Qt.Vertical;

                TalkListView{
                    id:talk_view
                    anchors.fill:parent
                    model:talkListModel
                }
            }

        }

        ToolItem{

        }

        InputItem{

        }
    }


}


