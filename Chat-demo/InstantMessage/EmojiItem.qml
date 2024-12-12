import QtQuick 2.13
import QtQuick.Controls 2.13
import "../Common"

Item
{
    id:emojiItem
    width:285;
    height:180;
    //直接Rectangle有黑边而且有背景,使用contentItem就没有了
    signal sigEmojiBtnClicked(string btnName);
    Rectangle{
        anchors.fill: parent
        color: colorConfig.strEmojiBackgroundColor;
        radius: 8;

        GridView{
            anchors.fill: parent
            anchors.margins: 5
            cellWidth: 25  // 单元格宽度
            cellHeight: 25 // 单元格高度
            layoutDirection: Qt.LeftToRight
            flow: GridView.FlowLeftToRight

            // 禁止滚动行为
            interactive: false // 禁用用户交互滚动

            model:fileModel.getEmojiName();
            delegate:IconButton{
                width:20
                height:20
                imageSource:talkConfig.emojiDirPrefix+modelData
                imgHeight: 20
                imgWidth: 20

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        sigEmojiBtnClicked(modelData)
                    }
                }
            }
        }

        //小三角
        Rectangle{
            width:40
            height: 40
            rotation: 45
            z:-1
            anchors.bottom: parent.bottom
            color: colorConfig.strEmojiBackgroundColor;
        }
    }
}




