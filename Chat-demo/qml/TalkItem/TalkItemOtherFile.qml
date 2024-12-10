import QtQuick 2.13

//其他文件delegate
TalkItemBase{
    id:talkItemOtherFile

    //截取文件名
    function extractTextFileName(){
        var TextSize = 0; //字符长度
        var TextCount = 0; //计数
        for(TextCount;TextCount < model.fileName.length;TextCount++)
        {
            TextSize += model.fileName.charCodeAt(TextCount) > 255 ? 2 : 1  //中文为2个字符,英文为1个
            if(TextSize > 38)
            {
                return model.fileName.substring(0,TextCount) + "..."
            }
        }
        return fileName;
    }

    Rectangle{
        width:40
        height:20
        color: colorConfig.strTimeBackgroundColor
        radius:4
        //显示时间
        x:contentWidth/2-width/2
        visible:bShowTime //控制时间显示
        TalkLabel{
            id:timeItem
            text:model.datetime
            padding:0
            anchors.centerIn: parent
            font{
                pixelSize: 14
            }
            color: colorConfig.strTimeTextColor;
            visible: bShowTime  //控制时间显示
        }
    }

    Row{
        width: talkItemOtherFile.contentWidth
        layoutDirection: talkItemOtherFile.isUser ? Qt.RightToLeft : Qt.LeftToRight
        Rectangle{
            id:wrapItem
            radius:4
            width:250
            height:80
            color: colorConfig.strSenderBubbleBackgroundColor //跟发送者气泡颜色一样

            //指向发言人的小三角
            Rectangle{
                width:10;
                height:10;
                y:talkConfig.nMessageHeight/2-10;
                anchors.horizontalCenter: talkItemOtherFile.isUser ? parent.right :parent.left
                rotation: 45
                color:colorConfig.strSenderBubbleBackgroundColor //气泡颜色
            }
            TalkLabel{
                id:textItem;
                width: 200
                height: 40
                // text:model.fileName.length > 18 ? model.fileName.substring(0,16) + "..." : model.fileName;
                text: extractTextFileName();
                persistentSelection: true  //点击右键不会取消文本选中 5.15才有?
                color:colorConfig.strTextColor;
                font.pixelSize: 16
                padding:12
                wrapMode: TextEdit.WrapAnywhere
            }
            Image{
                id:chatImage
                anchors.verticalCenter: parent.verticalCenter
                x:190
                source:
                    switch(model.fileSuffix)
                        {
                            case "pdf":
                            {
                                return "qrc:/icon/file/PDF.png";
                            }
                            case "docx":
                            {
                                return "qrc:/icon/file/WORD.png";
                            }
                            case "csv":
                            {
                                return "qrc:/icon/file/EXCEL.png";
                            }
                            case "xlsx":
                            {
                                return "qrc:/icon/file/EXCEL.png";
                            }
                            case "txt":
                            {
                                return "qrc:/icon/file/TXT.png";
                            }
                            case "ppt":
                            {
                                return "qrc:/icon/file/PPT.png";
                            }
                            case "mp4":
                            {
                                return "qrc:/icon/file/VIDEO.png";
                            }
                            case "zip":
                            {
                                return "qrc:/icon/file/ZIP.png";
                            }
                            default:
                            {
                                return "qrc:/icon/file/UNKNOWN.png"
                            }
                        }
                smooth: true
            }
            //文件大小
            Text{
                y:45
                padding:12
                id:fileSizeText
                text:model.fileSize
                font.pixelSize: 12
                font.family: colorConfig.strTextFont
                color:"#999999"
            }
        }
    }

}
