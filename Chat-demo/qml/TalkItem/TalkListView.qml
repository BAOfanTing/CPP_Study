import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import TalkModel 1.0
//聊天框listview

ListView{
    id:listView

    clip:true;

    headerPositioning: ListView.OverlayHeader
    footerPositioning: ListView.OverlayFooter
    boundsBehavior: Flickable.StopAtBounds
    highlightFollowsCurrentItem: true
    highlightMoveDuration: 0
    highlightResizeDuration: 0
    spacing:10

    delegate: Loader{
        sourceComponent: {
            switch(model.type){
            case TalkData.Text:
                return text_comp;
            }
            return null_comp;
        }

        Component{
            id:text_comp
            TalkItemText{}
        }
    }
    header: Item{
        height:10;
    }
    footer:Item{
        height:10;
    }

    //竖向滚动条
    ScrollBar.vertical: ScrollBar{
        id:scroll_vertical
        contentItem: Item{
            visible: (scroll_vertical.size < 1.0);
            implicitWidth: 10;
            Rectangle{
                anchors.centerIn: parent;
                width:parent.width
                radius: 4;
                height: parent.height > 20 ? parent.height : 20
                color: (scroll_vertical.hovered || scroll_vertical.pressed) ? "#bababa" : "#d2d2d2"

            }
        }
    }


}
