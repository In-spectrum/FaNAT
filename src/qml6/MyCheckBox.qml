import QtQuick
import QtQuick.Controls.Basic


CheckBox {
    id: id_cbCast

    indicator: Rectangle {
        implicitWidth: 28
        implicitHeight: implicitWidth
        x: id_cbCast.leftPadding
        y: parent.height / 2 - height / 2
        radius: 3
        border.color: id_cbCast.down ? "#80000000" : "#000000"

        Rectangle {
            width: parent.width - 10
            height: parent.height - 10
            anchors.centerIn: parent
            radius: 2
            color: id_cbCast.down ? "#80000000" : "#000000"
            visible: id_cbCast.checked
        }
    }

    contentItem: Text {
        text: id_cbCast.text
        font.bold: true
        font.pixelSize: 16
        opacity: enabled ? 1.0 : 0.3
        color: id_cbCast.down ? "#80000000" : "#000000"
        verticalAlignment: Text.AlignVCenter
        leftPadding: id_cbCast.indicator.width + id_cbCast.spacing
    }
}
