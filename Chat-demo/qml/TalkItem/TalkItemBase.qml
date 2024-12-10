import QtQuick 2.13
import QtQuick.Layouts 1.12

Item {
    id:talkItemBase;
    width: parent.width;
    height: parent.height;

    //
    property int profilePictureHeight: 48;  //头像
    property int messageHeight: 48;

    property int leftWidth: 110;
    property int rightWidth: 110;
    property int contentWidth:Math.max(10,talkItemBase.width-talkItemBase.leftWidth-talkItemBase.rightWidth);
    property bool isUser: (model.user === model.sender);
    property color messageBoxColor: talkItemBase.isUser ? "#98E982" : "#FFFFFF";

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

    //右侧头像
    Item {
        id: rightItem;
        width:talkItemBase.rightWidth;
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
        height:talkItemBase.contentWidth
        x:talkItemBase.leftWidth
        spacing: 6
    }


}
