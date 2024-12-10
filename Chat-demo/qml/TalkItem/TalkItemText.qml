import QtQuick 2.13
import "../../Common"
//文本信息delegate
TalkItemBase{
    id:talkItemText

    Row{
        width: talkItemText.contentWidth
        layoutDirection: talkItemText.isUser ? Qt.RightToLeft : Qt.LeftToRight
        Rectangle{
            id:wrapItem
            radius:4
            width:textItem.width
            height:textItem.height
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
                id:textItem;
                text:model.text;
                width:Math.min(talkItemText.contentWidth,textItem.implicitWidth);
            }
            CopyPaste{}
        }
    }

    Row{
        width:talkItemText.contentWidth
        layoutDirection: talkItemText.isUser ? Qt.RightToLeft : Qt.LeftToRight
        TalkLabel{
            text:model.datetime
            padding:0
            font{
                pixelSize: 14
            }
        }
    }



}
