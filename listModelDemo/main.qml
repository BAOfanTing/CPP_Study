import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Window 2.0

import QtGraphicalEffects 1.0
Window {
    visible: true
    width: 1500
    height: 800
    title: qsTr("Hello World")
    property int nindex: 0
    property int currentPage: 0
    property int pageSize: 35
    property bool isLoading : false
    TabView{
        id:tabview
        anchors.fill: parent;
        // 记录开始时间
        onCurrentIndexChanged: {
            var startTime = Date.now(); // 记录开始时间

            // 获取当前选中的标签页的索引
            var currentIndex = tabview.currentIndex;

            // 这里是个小延迟，以模拟加载完成的情况
            Qt.callLater(function(){
                // 模拟加载完成
                var endTime = Date.now(); // 记录结束时间
                var loadTime = endTime - startTime; // 计算加载时间
                console.log("Page " + (currentIndex + 1) + " loaded in " + loadTime + " ms");
            });
        }

    }

    Component.onCompleted: {
        for(var i = 0;i<mylistmodel.rowCount();i++){
            var tab = tabview.addTab("page"+ i,tabcompent);
            nindex = i;
        }
    }

    Component{
        id:tabcompent
        Item{
            Rectangle{
                id:nextpage
                width: 40;
                height: 40;

                color: "lightgreen";
                x:1400
                y:0;
                z:3;
                Text{
                    anchors.centerIn: parent;
                    text: "下一页"
                }
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        if(currentPage>6){
                            return
                        }

                        var startTime = Date.now(); // 记录开始时间
                        currentPage++;
                        gridview.model = mylistmodel.getMemberModel(tabview.currentIndex, currentPage, pageSize);

                        Qt.callLater(function(){
                            // 模拟加载完成
                            var endTime = Date.now(); // 记录结束时间
                            var loadTime = endTime - startTime; // 计算加载时间
                            console.log(" 一页loaded in " + loadTime + " ms");
                        });
                    }
                }

            }
            Rectangle{
                id:lastpage
                width: 40;
                height: 40;

                color: "lightblue";
                x:1350
                y:0;
                z:3;
                Text{
                    anchors.centerIn: parent;
                    text: "上一页"
                }
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        if(currentPage<=0){
                            return
                        }

                        var startTime = Date.now(); // 记录开始时间
                        currentPage--;
                        gridview.model = mylistmodel.getMemberModel(tabview.currentIndex, currentPage, pageSize);

                        Qt.callLater(function(){
                            // 模拟加载完成
                            var endTime = Date.now(); // 记录结束时间
                            var loadTime = endTime - startTime; // 计算加载时间
                            console.log(" 一页loaded in " + loadTime + " ms");
                        });
                    }
                }

            }

            // Flickable {
            //     id: flickable
            //     anchors.fill: parent
            //     contentHeight: 800
                GridView{
                    id:gridview
                    anchors.fill: parent;
                    cellWidth: 300
                    cellHeight: 160

                    model: mylistmodel.getMemberModel(nindex,0,35)
                    delegate: Rectangle {
                        id:colorrect
                        width:280;
                        height:140;
                        color: Qt.rgba(Math.random(),Math.random(),Math.random(),1)
                        border.color: "black";
                        radius: 5
                        gradient: Gradient{
                            GradientStop{position:0.0 ;color: Qt.rgba(Math.random(),Math.random(),Math.random(),1)}
                        }
                        layer.enabled: true
                        layer.effect:DropShadow{
                            horizontalOffset: 2
                            verticalOffset: 2
                            radius: 5
                            color: "#888888"
                        }

                        Text{
                            text: model.m_name
                            anchors.centerIn: parent;
                        }


                    }
                    // //滚动加载测试
                    // onContentYChanged: {
                    //     if(!isLoading && contentY+height >= contentHeight -50){
                    //         var startTime = Date.now(); // 记录开始时间
                    //         isLoading = true;
                    //         currentPage++;
                    //         gridview.model = mylistmodel.getMemberModel(tabview.currentIndex, currentPage, pageSize);

                    //         Qt.callLater(function(){
                    //            isLoading = false;
                    //             // 模拟加载完成
                    //             var endTime = Date.now(); // 记录结束时间
                    //             var loadTime = endTime - startTime; // 计算加载时间
                    //             console.log(" 一页loaded in " + loadTime + " ms");
                    //         });
                    //     }
                    //     else if(!isLoading && contentY < 0&&currentPage >0){
                    //         var startTime = Date.now(); // 记录开始时间
                    //         isLoading = true;
                    //         currentPage--;
                    //         gridview.model = mylistmodel.getMemberModel(tabview.currentIndex, currentPage, pageSize);

                    //         Qt.callLater(function(){
                    //            isLoading = false;
                    //             // 模拟加载完成
                    //             var endTime = Date.now(); // 记录结束时间
                    //             var loadTime = endTime - startTime; // 计算加载时间
                    //             console.log(" 一页loaded in " + loadTime + " ms");
                    //         });
                    //     }
                    // }
                // }

            }
        }
    }
}
