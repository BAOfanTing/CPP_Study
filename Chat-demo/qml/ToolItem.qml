import QtQuick 2.13
import "../Common/config"

Rectangle{
    width:700;
    height:40;
    color: colorConfig.weChatDefult;

    property string leftModel: "qrc:/icon/ic_expression.png,qrc:/icon/ic_file.png,qrc:/icon/ic_record.png"; //左侧按钮
    property string rightModel: "qrc:/icon/ic_camera.png"; //右侧按钮

    // 顶部灰色线条
    Rectangle {
        height: 1; // 线条高度
        width: parent.width; // 与父容器同宽
        color: colorConfig.lightgray; // 浅灰色
        anchors.bottom: parent.top; // 固定在底部
    }


    //左侧标签,文件,记录按钮
    Row{
        anchors.fill: parent
        spacing: 10
        anchors.margins: 5

        //左侧标签,文件,记录按钮
        Repeater{
            model:leftModel.split(",");
            delegate:IconButton{
                imageSource: modelData
            }
        }

        // 占位符，用于填充空白
        Rectangle {
            color: colorConfig.weChatDefult;
            width: parent.width - (leftModel.split(",").length + rightModel.split(",").length) * 30 - 20 * (leftModel.split(",").length + rightModel.split(",").length - 1)
            height: parent.height
        }

        Repeater{
            model:rightModel.split(",");
            delegate:IconButton{
                imageSource: modelData
            }
        }
    }

}
