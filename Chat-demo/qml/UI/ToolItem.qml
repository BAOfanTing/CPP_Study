import QtQuick 2.13
import "../../Common/config"
import "../../Common"

//工具栏高度固定40
Rectangle{
    width:Math.max(550,parent.width);
    height:40;
    color: colorConfig.strBackgroundColor;

    signal sigBtnClicked(string btnName); //工具栏图标按下信号

    // 顶部灰色线条
    Rectangle {
        height: 1; // 线条高度
        width: parent.width; // 与父容器同宽
        color: colorConfig.strDividerColor; // 浅灰色
        anchors.bottom: parent.top; // 固定在底部
    }


    //左侧标签,文件,记录按钮
    Row{
        anchors.fill: parent
        spacing: 10
        anchors.margins: 5

        //左侧标签,文件,记录按钮
        Repeater{
            model:colorConfig.leftModel.split(",");
            delegate:IconButton{
                imageSource: modelData

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        sigBtnClicked(modelData)
                    }
                }
            }
        }

        // 占位符，用于填充空白
        Rectangle {
            color: colorConfig.strBackgroundColor;
            width: parent.width - (colorConfig.leftModel.split(",").length + colorConfig.rightModel.split(",").length) * 30 - 20 * (colorConfig.leftModel.split(",").length + colorConfig.rightModel.split(",").length - 1)
            height: parent.height
        }

        //右侧标签
        Repeater{
            model:colorConfig.rightModel.split(",");
            delegate:IconButton{
                imageSource: modelData
            }
        }
    }

}
