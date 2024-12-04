import QtQuick 2.13
import "../../Common"

//图片delegate
TalkItemBase{
    id:talkItemImage

    Row{
        width: talkItemImage.contentWidth
        layoutDirection: talkItemImage.isUser ? Qt.RightToLeft : Qt.LeftToRight
        Image{
            source: model.imagePath;
        }
    }
}
