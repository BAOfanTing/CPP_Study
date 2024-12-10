import QtQuick 2.15
import QtQuick.Window 2.15


Window {
    id:root
    width: 300
    height: 480
    visible: true
    title: qsTr("Hello World")

    //时间显示
    Text{
        id:timerDisplay
        x:parent.width/2-timerDisplay.width/2
        y:parent.height/2-timerDisplay.width/2
        font.pixelSize: 36
        text: "00:00:00"

    }
    property bool timerDisplay_anim_once: true
    property  bool firstclick:false

    //开始暂停按钮
    Button{
        id:start_pause
        x:parent.width/2-start_pause.width/2
        y:parent.height/2+150
        width:40;height:40
        source:"fig/start.svg"

        //当在button里已经定义了click时,外部就不需要mouseArea了,直接监听click型号
        onClicked: {

            if(myTimer.running){
                myTimer.stop()
                start_pause.source = "fig/start.svg"
                console.log("暂停计时")

                //将终止图标替换为记录
                if(firstclick){
                    stop_record.source = "fig/stop.svg"
                }
            }
            else{
                myTimer.start()
                start_pause.source = "fig/pause.svg"
                console.log("开始计时")

                //将暂停图标替换为终止
                if(firstclick){
                    stop_record.source = "fig/record.svg"
                }
            }
            if(!firstclick){
                start_pause_anim1.start()
                stop_record.visible = true
                stop_record_anim1.start()
                firstclick = !firstclick
            }
        }

    }

    property int index: 0
    //终止_记录按钮
    Button{
        id:stop_record
        visible: false
        x:parent.width/2-start_pause.width/2
        y:parent.height/2+150
        width:40;height:40
        source:"fig/record.svg"
        onClicked: {
            if(source == "qrc:/fig/record.svg"){
                console.log("记录")
                if(timerDisplay_anim_once){
                    timerDisplay_anim1.start()
                    timerDisplay_anim_once = !timerDisplay_anim_once
                }
                listrect.visible = true

                //把记录加入list模型

                //recordlistmodel.append({"text": index.toString() +"   "+caculatetime(totaltime)})
                recordlistmodel.insert(0,{"text": index.toString() +"   "+caculatetime(totaltime)})
                index += 1
            }
            else{
                //终止按钮
                console.log("终止")
                myTimer.stop()
                timerDisplay.text = "00:00:00"
                start_pause.source = "fig/start.svg"
                start_pause_anim2.start()
                stop_record_anim2.start()
                timerDisplay_anim2.start()
                timerDisplay_anim_once = true
                stop_record.visible = false
                stop_record.source = "fig/record.svg"
                listrect.visible = false
                index = 0
                firstclick = false
                recordlistmodel.clear()

            }
        }

    }

    Rectangle{
        id:listrect
        width:200;height:300
        x:(root.width-listrect.width)/2;y:45
        border.color: "#48D1CC"
        border.width: 2
        visible: false
        radius: 8

        ListView{
            id:list1
            anchors.fill:parent
            anchors.margins: 20 //让元素离listview有边界
            clip: true
            model:recordlistmodel
            delegate: recordlist
            spacing: 5

        }

        Component{
            id:recordlist

            Rectangle{
                width: 150
                height:40
                color: "transparent" // 设置背景为透明
                Text {
                    anchors.centerIn: parent
                    text: model.text
                }
            }
        }
    }



    property int totaltime: 0
    //启动计时器
    Timer{
        id:myTimer
        interval: 1//每隔1毫秒触发
        running:false
        repeat: true //会重复运行,不加只运行一次

        onTriggered: {
            totaltime +=1
            timerDisplay.text = caculatetime(totaltime)
            //console.log("timer")
        }
    }


    function caculatetime(time){
        var millisecond =time % 1000
        millisecond = Math.floor(millisecond/10)
        var second = Math.floor(time /1000)%60
        var minute = Math.floor(time/1000 /60) %60

        return (minute<10 ? '0':'') + minute+':'+
                (second<10 ? '0':'') + second + ':'+
                (millisecond<10 ? '0':'')+millisecond

    }

    NumberAnimation{
        id:start_pause_anim1
        target: start_pause
        properties: "x"
        from:root.width/2-start_pause.width/2
        to:(root.width/2-start_pause.width/2)+50
        duration: 200
    }
    NumberAnimation{
        id:stop_record_anim1
        target: stop_record
        properties: "x"
        from:root.width/2-stop_record.width/2
        to:(root.width/2-stop_record.width/2)-50
        duration: 200
    }
    NumberAnimation{
        id:start_pause_anim2
        target: start_pause
        properties: "x"
        to:root.width/2-start_pause.width/2
        from:(root.width/2-start_pause.width/2)+50
        duration: 200
    }
    NumberAnimation{
        id:stop_record_anim2
        target: stop_record
        properties: "x"
        to:root.width/2-stop_record.width/2
        from:(root.width/2-stop_record.width/2)-50
        duration: 200
    }
    NumberAnimation{
        id:timerDisplay_anim1
        target: timerDisplay
        properties: "y"
        from:root.width/2-stop_record.width/2
        to:0
        duration: 200
    }
    NumberAnimation{
        id:timerDisplay_anim2
        target: timerDisplay
        properties: "y"
        to:root.width/2-stop_record.width/2
        from:0
        duration: 200
    }

    ListModel{
        id:recordlistmodel
    }
}
