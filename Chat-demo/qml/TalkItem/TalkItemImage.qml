import QtQuick 2.13
import "../../Common"

//图片delegate
TalkItemBase{
    id:talkItemImage

    //显示时间
    TalkLabel{
        id:timeItem
        text:model.datetime
        anchors.horizontalCenter: parent.horizontalCenter
        padding:0
        font{
            pixelSize: 14
        }
        color: colorConfig.strTimeTextColor;
        visible: bShowTime  //控制时间显示
    }
    Row{
        width: talkItemImage.contentWidth
        layoutDirection: talkItemImage.isUser ? Qt.RightToLeft : Qt.LeftToRight
        Image{
            id:chatImage
            source: model.imagePath;
            //判断是否需要缩放图像
            Component.onCompleted: {
                if(chatImage.sourceSize.width > talkConfig.nImageMaxWidth || chatImage.sourceSize.height > talkConfig.nImageMaxHeight )
                {
                    var ratio = Math.max(chatImage.sourceSize.width / talkConfig.nImageMaxWidth , chatImage.sourceSize.height /talkConfig.nImageMaxHeight);
                    chatImage.sourceSize = Qt.size(chatImage.sourceSize.width / ratio,chatImage.sourceSize.height / ratio )
                }
            }
        }
    }
}
