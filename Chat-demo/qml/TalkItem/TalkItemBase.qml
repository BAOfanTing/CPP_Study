import QtQuick 2.13
import QtQuick.Layouts 1.12

Item {
    id:talkItemBase;
    width: parent.ListView.view.width;
    height: Math.max(talkConfig.nProfilePictureHeight,contentItem.height) ;

    property int contentWidth:Math.max(200,talkItemBase.width-talkConfig.nLeftWidth-talkConfig.nRightWidth);
    property bool isUser: (model.user === model.sender);
    property variant  lastShowTime: null;  //记录上次显示的时间
    property bool bShowTime : model.datetime === "08:00" ? false : true

    //让继承的子qml的内容能够被放入content_Item,从而获取内容的高度
    default property alias contentItems: contentItem.children


    Row{
        //左侧头像
        Item {
            id: leftItem;
            width:talkConfig.nLeftWidth;
            height:talkItemBase.height;         //整体Item高度为消息内容的高度
            Image{
                y: bShowTime ? 25 : 0           //显示时间时下移头像框
                visible: !talkItemBase.isUser;
                width:talkConfig.nProfilePictureHeight;
                height:talkConfig.nProfilePictureHeight;
                anchors.horizontalCenter: parent.horizontalCenter;
                // source: "qrc:/icon/profile_48_gray.png";
                source: "qrc:/icon/furong.png";
            }
        }
        //消息展示区域
        Column{
            id:contentItem
            width:talkItemBase.contentWidth
            // x:talkConfig.nLeftWidth
            spacing: 6
        }

        //右侧头像
        Item {
            id: rightItem;
            width:talkConfig.nRightWidth;
            height:talkItemBase.height;
            // anchors.right: parent.right
            Image{
                y: bShowTime ? 25 : 0           //显示时间时下移头像框
                visible: talkItemBase.isUser;
                width:talkConfig.nProfilePictureHeight;
                height:talkConfig.nProfilePictureHeight;
                anchors.horizontalCenter: parent.horizontalCenter;
                // source: "qrc:/icon/profile_48_gray.png";
                source: "qrc:/icon/dingzheng2.png";
            }
        }

    }

}
