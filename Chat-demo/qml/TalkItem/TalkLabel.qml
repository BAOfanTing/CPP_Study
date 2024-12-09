import QtQuick 2.13
import QtQuick.Controls 2.12

//Text不能被选中所以采用了,TextEdit做

TextEdit{
    id:textEdit;
    padding:14;
    font{
        family: colorConfig.strTextFont;
        pixelSize: 18;
    }

    // verticalAlignment: TextEdit.AlignVCenter;
    // horizontalAlignment: TextEdit.AlignLeft;
    readOnly: true;

    //开启鼠标选择
    selectByMouse: true;
    selectionColor: "#3399ff";
    selectedTextColor: "#ffffff";

    wrapMode: TextEdit.Wrap

}


