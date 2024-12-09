import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import TalkModel 1.0
//聊天框listview

ListView{
    id:listView
    clip:true
    headerPositioning: ListView.OverlayHeader   // 头部显示方式：覆盖式（可以与内容重叠）
    footerPositioning: ListView.OverlayFooter   // 底部显示方式：覆盖式（可以与内容重叠）
    boundsBehavior: Flickable.StopAtBounds      // 内容超出时，停止在边界处
    // highlightFollowsCurrentItem: true           // 高亮项跟随当前项
    // highlightMoveDuration: 0
    // highlightResizeDuration: 0
    spacing:10

    //消息滚动到最新
    Timer{
        id:timer
        interval:10;
        running: false;
        repeat:false;
        onTriggered:positionViewAtEnd();
    }
    onCountChanged:{
        if(count > 0)
        {
            timer.restart();
        }
    }


    // 委托：加载不同类型的组件，基于 `model.type` 的值选择合适的组件
    delegate: Loader{
        sourceComponent: {
            switch(model.type){
            case TalkData.Text:
            {
                return textComp;
            }
            case TalkData.Image:
            {
                return imageComp;
            }
            case TalkData.Other:
            {
                return otherComp;
            }

            return nullComp;
            }   
        }
        Component{
            id:textComp
            TalkItemText{}
        }
        Component{
            id:imageComp
            TalkItemImage{}
        }
        Component{
            id:otherComp
            TalkItemOtherFile{}
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
                color: (scroll_vertical.hovered || scroll_vertical.pressed) ? "#2c2c2d" : "#929292"

            }
        }
    }
}
