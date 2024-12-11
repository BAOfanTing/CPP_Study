import QtQuick 2.13
import "../../Common"

//图片delegate
TalkItemBase{
    id:talkItemImage

    Rectangle{
        width:40
        height:20
        color: colorConfig.strTimeBackgroundColor
        radius:4
        //显示时间
        x:contentWidth/2-width/2
        visible:bShowTime //控制时间显示
        TalkLabel{
            id:timeItem
            text:model.datetime
            padding:0
            anchors.centerIn: parent
            font{
                pixelSize: 14
            }
            color: colorConfig.strTimeTextColor;
            visible: bShowTime  //控制时间显示
        }
    }

    Image{
        id:chatImage
        source: model.imagePath;
        smooth: true
        //判断是否需要缩放图像
        x:talkItemImage.isUser ? talkItemImage.contentWidth-chatImage.width : 0 //控制图片左右
        Component.onCompleted: {
            if(chatImage.sourceSize.width > talkConfig.nImageMaxWidth || chatImage.sourceSize.height > talkConfig.nImageMaxHeight )
            {
                var ratio = Math.max(chatImage.sourceSize.width / talkConfig.nImageMaxWidth , chatImage.sourceSize.height /talkConfig.nImageMaxHeight);
                chatImage.sourceSize = Qt.size(chatImage.sourceSize.width / ratio,chatImage.sourceSize.height / ratio )
            }
        }
    }
}
