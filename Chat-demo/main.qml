import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "./qml/UI"
import "./qml/TalkItem"
import "./Common/config"
import "./Common"
import TalkModel 1.0

Window {
    property bool bLightModel: true
    property real initialWidth: 900  // 定义初始宽度
    property real initialHeight: 730  // 定义初始高度
    property real initialMouseX: 0  // 定义初始鼠标X坐标
    property real initialMouseY: 0  // 定义初始鼠标Y坐标
    property url filePath: "";
    property var fileInfo;
    id:mainWindow
    width: 720
    height: 1024
    visible: true
    color: "transparent"
    flags:Qt.Window | Qt.FramelessWindowHint //去掉原始标题栏

    //UI高宽配置文件
    TalkConfig{
        id:talkConfig
    }

    //颜色和图标配置文件
    ColorConfig {
        id: colorConfig
    }

    //表情弹窗
    EmojiItem{
        id:emojiItem;
        x:0
        y:toolItem.y-emojiItem.height-10
    }


    Rectangle{
        anchors.fill: parent
        //标题栏
        TitleItem{
            id:titleItem
            height: 80
            anchors.top: parent.top
            width: parent.width
            window: mainWindow
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
            anchors.bottom:inputItem.top
        }
        //输入框
        InputItem{
            id:inputItem
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
                count++
                if(filePath.toString() !== "") //选择了一个文件
                {
                    //图片文件
                    if(fileInfo.fileSuffix === "jpg" || fileInfo.fileSuffix === "jpeg" || fileInfo.fileSuffix === "png")
                    {
                        if(count %2 === 0)
                        {
                            talkListModel.appendImage("A","A",filePath.toString())
                        }
                        else{
                            talkListModel.appendImage("B","A",filePath.toString())
                        }
                    }
                    else   //其他文件类型
                    {
                        if(count %2 === 0)
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
                emojiItem.open();
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
            inputItem.textArea.insert(inputItem.textArea.cursorPosition,insertStr)
        }
    }

    property int count: 0
    //窗口缩放,使用一个透明的小矩形在右下角
    Rectangle{
        id:resizeHandle
        width:15
        height:15
        color:"transparent"
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        MouseArea{
            id:resizeArea
            anchors.fill: parent
            cursorShape: Qt.SizeFDiagCursor  //把鼠标形状变为对角线
            onPressed: {
                //记录初始的鼠标位置和窗口大小
                initialWidth = mainWindow.width;
                initialHeight = mainWindow.height;
                initialMouseX = mouse.x
                initialMouseY = mouse.y
            }

            onPositionChanged: {
                //计算鼠标相对位置,调整窗口的宽度和高度
                if(mouse.x !== initialMouseX || mouse.y !== initialMouseY)
                {
                    var deltaX = mouse.x - initialMouseX;
                    var deltaY = mouse.y - initialMouseY;
                    mainWindow.width = Math.max(initialWidth + deltaX,talkConfig.nMinWidth) //设置最小宽度值
                    mainWindow.height = Math.max(initialHeight + deltaY,talkConfig.nMinHeight) //设置最小宽度值

                }
            }
            //----------------------------测试单击缩放是否闪烁,删
            onClicked: {
                count++
                if(count%2 === 0)
                {
                    mainWindow.width = 550
                    mainWindow.height = 620
                }
                else{
                    mainWindow.width = 1600
                    mainWindow.height = 1020
                }
            }
        }
    }

}


