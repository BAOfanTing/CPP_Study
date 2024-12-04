import QtQuick 2.13
import "../../Common"

//图片delegate
TalkItemBase{
    id:talkItemImage

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
    Row{
        width:talkItemImage.contentWidth
        layoutDirection: talkItemImage.isUser ? Qt.RightToLeft : Qt.LeftToRight
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
