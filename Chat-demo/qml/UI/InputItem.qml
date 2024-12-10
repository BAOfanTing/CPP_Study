import QtQuick 2.13
import QtQuick.Controls 2.12
import TalkModel 1.0
import "../../Common"


//最小 550*150
Rectangle{
    color: colorConfig.strBackgroundColor;

    //添加文字滚动效果
    ScrollView{
        id:view
        width:parent.width-20;
        height:parent.height-60;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 10;

        TextArea{
            id:textArea
            width: parent.width;
            font.pixelSize: 20;
            font.family: colorConfig.strTextFont;

            color:colorConfig.strTextColor
            readOnly: false // 根据需要设置是否只读
            wrapMode: TextEdit.Wrap //开启换行

            //开启选择文本
            selectByMouse: true;
            selectionColor: "#3399ff";
            selectedTextColor: "#ffffff";
            persistentSelection: true  //点击右键不会取消文本选中 5.15才有?

            text: "132132131313131321321a3sdfasdfasd32f13213213212"
        }

        //连接复制粘贴的信号
        Connections{
            target: pasteBtn
            onSigPaste:{
                textArea.paste();
            }
            onSigCopy:{
                textArea.copy();
            }
        }
    }

    CopyPaste{
        id:pasteBtn
    }
    property bool bHover: false  //鼠标是否选中按钮
    //发送按钮
    Rectangle{
        id:sendBtn
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;
        anchors.right: parent.right;
        anchors.rightMargin: 30;

        width:120;
        height:40;
        color: bHover ? colorConfig.strSendBtnSelectedColor :colorConfig.strSendBtnColor
        radius: 5

        Text {
            anchors.centerIn: parent
            color:colorConfig.strSendBtnTextColor;
            text: qsTr("发送")
            font.pixelSize: 20;
            font.family: colorConfig.strTextFont
        }

        MouseArea{
            anchors.fill:parent;
            hoverEnabled: true; //启用鼠标悬浮检测
            onClicked: {
                // 清理文本末尾的空白字符（包括空格、换行符）
                var trimmedText = textArea.text.replace(/\s+$/, ""); // 正则表达式匹配末尾空白字符
                talkListModel.appendText("A","A",trimmedText)
                // console.log(textArea.text)
            }
            onEntered: {
                bHover = true;
            }
            onExited: {
                bHover = false;
            }

        }
    }

    //发送按钮
    Rectangle{
        id:sendBtn2
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;
        anchors.left: parent.left;
        anchors.leftMargin: 30;

        width:120;
        height:40;
        color: bHover ? colorConfig.strSendBtnSelectedColor :colorConfig.strSendBtnColor
        radius: 5

        Text {
            anchors.centerIn: parent
            color:colorConfig.strSendBtnTextColor;
            text: qsTr("发送")
            font.pixelSize: 20;
            font.family: colorConfig.strTextFont
        }

        MouseArea{
            anchors.fill:parent;
            hoverEnabled: true; //启用鼠标悬浮检测
            onClicked: {
                // console.log("send");
                var trimmedText = textArea.text.replace(/\s+$/, ""); // 正则表达式匹配末尾空白字符
                talkListModel.appendText("B","A",trimmedText)
                // console.log(textArea.text)
            }
            onEntered: {
                bHover = true;
            }
            onExited: {
                bHover = false;
            }

        }
    }
}
