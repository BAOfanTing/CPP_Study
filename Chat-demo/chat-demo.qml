import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "./qml/UI"
import "./qml/TalkItem"
import "./Common/config"
import "./Common"
import TalkModel 1.0

// 使用模块在main.cpp里添加上
// #include "./Common/Model/TalkListDefine.h"
// #include "./Common/Model/talklistmodel.h"
// #include "./Common/Model/filemodel.h"

// qmlRegisterType<TalkData>("TalkModel",1,0,"TalkData");
// QQmlApplicationEngine engine;
// //获取单例
// TalkListModel* talkListModel = TalkListModel::getInstance();
// engine.rootContext()->setContextProperty("talkListModel",talkListModel);
// //文件单例
// FileModel* fileModel = FileModel::getInstance();
// engine.rootContext()->setContextProperty("fileModel",fileModel);

Rectangle {
    property bool bLightModel: true
    property url filePath: "";
    property var fileInfo;
    width: 720
    height: 1024
    color: "transparent"

    //UI高宽配置文件
    TalkConfig{
        id:talkConfig
    }

    //颜色和图标配置文件
    ColorConfig {
        id: colorConfig
    }

    //表情弹窗
    Popup{
        id:emojiItemPopup
        x:0
        y:toolItem.y-emojiItem.height-5
        width:285;
        height:180;
        //设置背景
        background: Rectangle{
            color: "transparent"
            border.color: "transparent"
        }
        contentItem:EmojiItem{
            id:emojiItem;
            anchors.fill:parent
        }
    }

    Rectangle{
        anchors.fill: parent
        //标题栏
        TitleItem{
            id:titleItem
            height: 80
            anchors.top: parent.top
            width: parent.width
        }
        //消息框
        ChatContentItem{
            id:chatContentItem
            width: parent.width
            anchors.top: titleItem.bottom
            anchors.bottom: toolItem.top
            TalkListView{
                id:talk_view
                anchors.fill:parent
                model:talkListModel
            }
        }
        //工具栏
        ToolItem{
            id:toolItem
            width: parent.width
            anchors.bottom:chatInputItem.top
        }
        //输入框
        ChatInputItem{
            id:chatInputItem
            height:150;
            width: parent.width
            anchors.bottom: parent.bottom
        }
    }

    //信号连接,换肤
    Connections{
        target: titleItem
        onSigModifySkin:{
            bLightModel = !bLightModel
        }
    }
    property int clickCount: 0
    //选择文件传送
    Connections{
        target:toolItem
        onSigBtnClicked:{
            //按下的是文件按钮
            console.log(btnName)
            if(btnName === "qrc:/icon/file_dark.png" || btnName === "qrc:/icon/file_light.png")
            {
                filePath = fileModel.getSelectedFileUrl();
                fileInfo = fileModel.extractFileInfo(filePath)
                clickCount++
                if(filePath.toString() !== "") //选择了一个文件
                {
                    //图片文件
                    if(fileInfo.fileSuffix === "jpg" || fileInfo.fileSuffix === "jpeg" || fileInfo.fileSuffix === "png")
                    {
                        if(clickCount %2 === 0)
                        {
                            talkListModel.appendImage("A","A",filePath.toString())
                        }
                        else{
                            talkListModel.appendImage("B","A",filePath.toString())
                        }
                    }
                    else   //其他文件类型
                    {
                        if(clickCount %2 === 0)
                        {
                            talkListModel.appendOtherFile("A","A",filePath.toString(),fileInfo.fileName,fileInfo.fileSize,fileInfo.fileSuffix);
                        }
                        else{
                            talkListModel.appendOtherFile("B","A",filePath.toString(),fileInfo.fileName,fileInfo.fileSize,fileInfo.fileSuffix);
                        }
                    }
                }
            }
            else if(btnName === "qrc:/icon/expression_light.png" || btnName === "qrc:/icon/expression_dark.png")   //按下的表情按钮
            {
                console.log("表情按下");
                emojiItemPopup.open();
            }
        }
    }

    //表情发送
    Connections{
        target:emojiItem
        onSigEmojiBtnClicked:{
            var emojiPath = "qrc:/icon/emoji/"+btnName;
            var insertStr = "<img src='" + emojiPath + "' width='20' height='20' style='vertical-align:baseline;'/>"

            //插入表情
            chatInputItem.textArea.insert(chatInputItem.textArea.cursorPosition,insertStr)
        }
    }  
}


