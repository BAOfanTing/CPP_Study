import QtQuick 2.13


//颜色,字体,图标
//自己是user,对方是sender
QtObject{

    //TitleItem
    // property color urlCloseIcon: bLightModel ? "qrc:/icon/close_light.png" : "qrc:/icon/close_dark.png";  //关闭按钮样式    这样设置显示不了不知道为啥

    //ToolItem
    readonly property string leftModel: bLightModel ? "qrc:/icon/expression_light.png,qrc:/icon/file_light.png,qrc:/icon/record_light.png" :
                                            "qrc:/icon/expression_dark.png,qrc:/icon/file_dark.png,qrc:/icon/record_dark.png"; //左侧按钮
    readonly property string rightModel:bLightModel ? "qrc:/icon/phone_light.png,qrc:/icon/video_light.png" : "qrc:/icon/phone_light.png,qrc:/icon/video_dark.png" ; //右侧按钮


    //InputItem
    readonly property string strTextFont: "微软雅黑";   //字体
    readonly property string strTextColor: bLightModel ? "#111111" : "#f8f8f8"  //标题颜色,sender字体颜色
    property color strBackgroundColor: bLightModel ? "#f5f5f5" : "#111111";     //微信背景色
    property color strSendBtnColor: bLightModel ? "#e9e9e9" : "#07c160";     //发送按钮背景色,鼠标未移入
    property color strSendBtnSelectedColor: bLightModel ? "#d2d2d2" : "#239b56";     //发送按钮背景色,鼠标移入
    property color strSendBtnTextColor: bLightModel ? "#07c160" : "#ffffff";     //发送按钮字体颜色

    //TalkItemText
    readonly property color strUserBubbleBackgroundColor: bLightModel ? "#95ec69" : "#3eb575"  //用户气泡颜色
    readonly property color strSenderBubbleBackgroundColor: bLightModel ? "#ffffff" : "#2c2c2c"  //对方气泡颜色
    readonly property color strTimeTextColor: bLightModel ? "#111111" : "#8f8f8f"  //时间字体颜色

    //Icon图标鼠标选中背景
    readonly property color strBtnBackgroundUnselect: "transparent";    //透明背景
    readonly property color strBtnBackgroundSelect: "#969799";          //背景加深

    //表情
    readonly property color strEmojiBackgroundColor: bLightModel ? "#ffffff" : "#2c2c2c"  //对方气泡颜色





    readonly property color strDividerColor: bLightModel ? "lightgray" : "#292929";  //分割线颜色

    readonly property color strTimeBackgroundColor: bLightModel ? "#dadada" : "transparent";    //时间背景

    readonly property color lightgray: "lightgray";
    readonly property color green: "#89d961";
    readonly property color white: "#ffffff";
}
