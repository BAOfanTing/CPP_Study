import QtQuick 2.13
import QtQuick.Layouts 1.12

Item {
    id:talkItemBase;
    width: parent.ListView.view.width;
    height: Math.max(profilePictureHeight,contentItem.height);

    //
    property int profilePictureHeight: 48;  //头像
    property int messageHeight: 48;

    property int leftWidth: 100;
    property int rightWidth: 100;
    property int contentWidth:Math.max(200,talkItemBase.width-talkItemBase.leftWidth-talkItemBase.rightWidth);
    property bool isUser: (model.user === model.sender);

    //让继承的子qml的内容能够被放入content_Item,从而获取内容的高度
    default property alias contentItems: contentItem.children

    //左侧头像
    Item {
        id: leftItem;
        width:talkItemBase.leftWidth;
        height:talkItemBase.height;
        Image{
            visible: !talkItemBase.isUser;
            width:talkItemBase.profilePictureHeight;
            height:talkItemBase.profilePictureHeight;
            anchors.horizontalCenter: parent.horizontalCenter;
            source: "qrc:/icon/profile_48_gray.png";
        }
    }
    //消息展示区域
    Column{
        id:contentItem
        width:talkItemBase.contentWidth
        x:talkItemBase.leftWidth
        spacing: 6
    }


    //右侧头像
    Item {
        id: rightItem;
        width:talkItemBase.rightWidth;
        height:talkItemBase.height;
        anchors.right: parent.right
        Image{
            visible: talkItemBase.isUser;
            width:talkItemBase.profilePictureHeight;
            height:talkItemBase.profilePictureHeight;
            anchors.horizontalCenter: parent.horizontalCenter;
            source: "qrc:/icon/profile_48_gray.png";
        }
    }



}
