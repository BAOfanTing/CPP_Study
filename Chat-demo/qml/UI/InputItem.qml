import QtQuick 2.13
import QtQuick.Controls 2.12
import TalkModel 1.0
Rectangle{
    color: colorConfig.weChatDefult;
    width:700;
    height:150;

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
            readOnly: false // 根据需要设置是否只读
            wrapMode: TextEdit.Wrap //开启换行

            //开启选择文本
            selectByMouse: true;
            selectionColor: "#3399ff";
            selectedTextColor: "#ffffff";

            text: "132132131313131321321a3sdfasdfasd32f132132132132132132132132132132132132132132132132132132132131321321312"
        }
    }

    //发送按钮
    Rectangle{
        id:sendBtn
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;
        anchors.right: parent.right;
        anchors.rightMargin: 30;

        width:120;
        height:40;
        color: "#e9e9e9"
        radius: 5

        Text {
            anchors.centerIn: parent
            color:"#07c160";
            text: qsTr("发送")
            font.pixelSize: 20;
            font.family: colorConfig.strTextFont
        }

        MouseArea{
            anchors.fill:parent;
            hoverEnabled: true; //启用鼠标悬浮检测
            onClicked: {
                console.log("send");
                talkListModel.appendText("B","A",textArea.text)
                console.log(textArea.text)
            }
            onEntered: {
                sendBtn.color = "#d2d2d2";
            }
            onExited: {
                sendBtn.color = "#e9e9e9";
            }

        }
    }
}
