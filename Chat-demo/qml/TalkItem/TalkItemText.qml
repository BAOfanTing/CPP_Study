import QtQuick 2.13

//文本信息delegate
TalkItemBase{
    id:talkItemText

    Row{
        width: talkItemText.contentWidth
        layoutDirection: talkItemText.isUser ? Qt.RightToLeft : Qt.LeftToRight
        Rectangle{
            id:wrap_item
            radius:4
            width:text_item.width
            height:text_item.height
            color: talkItemText.messageBoxColor

            //指向发言人的小三角
            Rectangle{
                width:10;
                height:10;
                y:talkItemText.messageHeight/2-10;
                anchors.horizontalCenter: talkItemText.isUser ? parent.right :parent.left
                rotation: 45
                color:talkItemText.messageBoxColor
            }

            TalkLabel{
                id:text_item;
                text:model.text_text;
                width:Math.min(talkItemText.contentWidth,text_item.implicitWidth);
            }
        }
    }

    Row{
        width:talkItemText.contentWidth
        layoutDirection: talkItemText.isUser ? Qt.RightToLeft : Qt.LeftToRight
        TalkLabel{
            text:model.datetime
            padding:0
        }

    }
}
