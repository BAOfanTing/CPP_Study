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
            color: talkItemText.isUser ? colorConfig.strUserBubbleBackgroundColor : colorConfig.strSenderBubbleBackgroundColor  //气泡颜色

            //指向发言人的小三角
            Rectangle{
                width:10;
                height:10;
                y:talkItemText.messageHeight/2-10;
                anchors.horizontalCenter: talkItemText.isUser ? parent.right :parent.left
                rotation: 45
                color:talkItemText.isUser ? colorConfig.strUserBubbleBackgroundColor : colorConfig.strSenderBubbleBackgroundColor  //气泡颜色
            }

            TalkLabel{
                id:textItem;
                text:model.text;
                persistentSelection: true  //点击右键不会取消文本选中 5.15才有?
                width:talkItemText.contentWidth < 400 ? Math.min(talkItemText.contentWidth,textItem.implicitWidth):
                                                        Math.min(textItem.implicitWidth,Math.min(talkItemText.contentWidth/4*3,800)); //聊天记录的宽度
                color:talkItemText.isUser ? "#111111" :colorConfig.strTextColor ;
            }
            CopyPaste{
                id:pasteBtn
            }
            //聊天记录只有复制信号
            Connections{
                target: pasteBtn
                onSigCopy:{
                    textItem.copy();
                }
            }

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
            color: colorConfig.strTimeTextColor;
        }
    }



}
