import QtQuick 2.13

QtObject{
    property int nMinWidth: 550;        //窗口最小宽度
    property int nMinHeight: 620;       //窗口最小高度

    property int nProfilePictureHeight: 48;  //头像默认高宽
    property int nMessageHeight: 48;          //消息默认高度

    //左右侧头像范围宽度
    property int nLeftWidth: 90;
    property int nRightWidth: 90;

    //发送图片高宽限制
    property int nImageMaxWidth: 250;
    property int nImageMaxHeight: 250;

    readonly property string fileDirPrefix: "qrc:/InstantMessage/icon/file/"  //文件图标所在路径前缀
    readonly property string emojiDirPrefix: "qrc:/InstantMessage/icon/emoji/"  //表情图标所在路径前缀


}
