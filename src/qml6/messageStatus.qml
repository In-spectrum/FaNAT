import QtQuick 2.12

Rectangle {
    id: root
    objectName: "obMessageStatus"
    anchors.fill: parent
    color: "#30000000"


    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
    }

    Component.onDestruction:
    {

    }

    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true

        onWheel:
            (wheel)=> {
       }


        onPressed:
            (mouse)=>
        {

        }

        onReleased:
            (mouse)=>
        {
                id_recCancel.fCancel();
        }

        onPositionChanged:
            (mouse)=>
        {

        }
    }


    function fStatus(_iVar, _sData)
    {       
        //print("fStatus 0: " + _iVar + " -> " + _sData)

        id_txtTitle.text = "";



        if(_iVar > 300)
        {
            id_txtInfo.text = "";
        }
        else
        if(_iVar > 200)
        {

            switch(_iVar%10)
            {
            case 1:
                id_txtTitle.text = "- Error";
                break;
            case 2:
                id_txtTitle.text = "- Warning";
                break;
            }

            id_txtInfo.text = "Server data:\n\n";

        }
        else
        {
            switch(_iVar%10)
            {
            case 1:
                id_txtTitle.text = "- Error";
                break;
            case 2:
                id_txtTitle.text = "- Warning";
                break;
            }

            id_txtInfo.text = "Client data:\n\n";
        }


        id_txtInfo.text += _sData;

        root.parent.visible = true;

    }

    Rectangle {
        id: id_recStatus
        anchors.centerIn: parent
        width: parent.width - 20 > 600 ? 600 : parent.width - 20
        color: "#808080"
        height: parent.height - 20 > 400 ? 400 : parent.height - 20
        border.color: "#000000"
        border.width: 1


        signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


        Component.onCompleted:
        {

        }

        Component.onDestruction:
        {

        }


        MouseArea
        {
            anchors.fill: parent
            hoverEnabled: true

            onWheel:
                (wheel)=> {
           }


            onPressed:
                (mouse)=>
            {

            }

            onReleased:
                (mouse)=>
            {
            }

            onPositionChanged:
                (mouse)=>
            {
            }
        }


        Rectangle
        {
            id: id_recTitle
            width: parent.width
            height: 50
            color: "#90ff0000"

            Item {
                width: 2 * children[0].width
                height: parent.height
                visible: false

                Text {
                    x: 10
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("<-")
                    font.bold: true
                    font.pixelSize: 20
                    color: "#ffffff"
                }

                MouseArea
                {
                    anchors.fill: parent

                    onPressed:
                        (mouse)=>
                    {
                           id_recCancel.fCancel()
                    }
                }
            }


            Text {
                id: id_txtTitle
                anchors.right: parent.right
                anchors.rightMargin: 15
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("-")
                font.bold: true
                font.pixelSize: 20
                color: "#ffffff"
            }

            Rectangle
            {
                width: parent.width - 2 * root.border.width
                anchors.horizontalCenter: parent.horizontalCenter
                height: 2
                anchors.bottom: parent.bottom
                color: "#ffffff"
            }
        }



        Item {
            width: parent.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: id_recTitle.bottom
            anchors.topMargin: 20
            anchors.bottom: id_recCancel.top
            anchors.bottomMargin: 20

            Text {
                id: id_txtInfo
                anchors.fill: parent

                text: qsTr("")
                font.bold: true
                font.pixelSize: 18
                color: "#ffffff"
                wrapMode: Text.Wrap
            }

        }

        Item
        {
            id: id_recCancel
            width: parent.width
            height: 50
            anchors.bottom: parent.bottom

            Rectangle
            {
                width: parent.width - 2 * root.border.width
                anchors.horizontalCenter: parent.horizontalCenter
                height: 2
                color: "#ffffff"
            }

            Rectangle
            {
                width: children[1].width + 30
                height: parent.height - 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 7
                color: "#70000000"
                border.color: "#ffffff"
                radius: 7
                opacity: children[0].pressed ? 0.6 : 1.0

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true

                    onWheel:
                        (wheel)=> {
                   }


                    onPressed:
                        (mouse)=>
                    {
                             id_recCancel.fCancel()
                    }

                    onReleased:
                        (mouse)=>
                    {
                    }

                    onPositionChanged:
                        (mouse)=>
                    {
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: qsTr("Cancel")
                    font.bold: true
                    font.pixelSize: 14
                    color: "#ffffff"
                }
            }


            function fCancel()
            {
                root.signalData(0, 0, 0, 0, 0, 0, 0)
            }
        }

    }



}
