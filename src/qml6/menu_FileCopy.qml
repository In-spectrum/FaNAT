import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    id: root
    objectName: "obMenuFileCopy"
    width: 300
    color: "#808080"
    height: parent.height
    border.color: "#000000"
    border.width: 1

    property int m_iH: id_recTitle.height + id_colData.height + id_recCancel.height + 20

    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
        if(!id_tiFilePath.cursorVisible)
        {
            id_tiFilePath.cursorPosition  = id_tiFilePath.text.length;
            id_tiFilePath.cursorVisible = true
            id_tiFilePath.forceActiveFocus();
        }
    }

    Component.onDestruction:
    {

    }

    function fFileWrited(_iVar, _Data)
    {
        //print("fFileWrited: " + _iVar + " / " + _Data)

        if(_iVar == 4)
        {
            id_StatusCopy.text = _Data;

            return;
        }

        id_FileWrited.value = _Data/100

        id_ProcCopy.text = (_Data + " %")

        if(_iVar == 0)
        {
            id_StatusCopy.text = "Invalid file path."
        }
        else
        if(_iVar == 1)
        {
            id_StatusCopy.text = ""
        }
        else
        {
            if(_iVar == 2)
            {
                id_StatusCopy.text = "Failed copy."
            }
            else
            {
                if(_iVar == 3)
                {
                    id_StatusCopy.text = "Success copy."
                }
                else
                {

                }
            }
        }
    }



    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true

       //  onWheel:
       //      (wheel)=> {
       // }


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
        color: "#000000"

        Item {
            width: 2 * children[0].width
            height: parent.height

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
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("- File copy")
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

    Flickable {
        x: 5
        width: parent.width - 2 * x
        anchors.top: id_recTitle.bottom
        anchors.bottom: id_recCancel.top
        //interactive: id_scrollBar.size < 1 ? true : false

        clip: true

        ScrollBar.vertical: ScrollBar {
            id: id_scrollBar
                policy: id_scrollBar.size < 1 ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                visible: size < 1 ? true : false
            }

        //contentWidth: parent.width - x - 5    // The important part
        contentHeight: id_colData.height  // Same

        Column
        {
            id: id_colData
            width: id_scrollBar.visible ? (parent.width - id_scrollBar.width - 10) : parent.width

            Item {
                width: 1
                height: 20
            }

            Column
            {
                width: parent.width

                Text {
                    text: qsTr("File path:")
                    color: "#ffffff"
                    font.bold: true
                    font.pixelSize: 20

                    MouseArea
                    {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                                if(!id_tiFilePath.cursorVisible)
                                {
                                    id_tiFilePath.cursorPosition  = id_tiFilePath.text.length;
                                    id_tiFilePath.cursorVisible = true
                                    id_tiFilePath.forceActiveFocus();
                                }
                        }

                        onDoubleClicked:
                            (mouse)=>
                        {
                                id_tiFilePath.selectAll();
                        }
                    }
                }

                Item {
                    width: 1
                    height: 5
                }

                Rectangle
                {

                    width: parent.width
                    height: children[0].height + 10
                    color: "#10000000"


                    TextInput {
                        id: id_tiFilePath
                        width: parent.width - 6
                        anchors.centerIn: parent

                        text: ""
                        color: "#ffffff"
                        font.pixelSize: 14

                        clip: true

                        onTextChanged:
                        {
                            if(text.length == 0)
                                return;

                            while(text.charAt(0) == ' ')
                                text = text.substring(1);

                            if( text.indexOf("file:///") == 0)
                            {
                                text = text.substring( ("file:///").length );
                            }
                        }

                        onAccepted:
                        {
                        }
                    }
                }


            }

            Item {
                width: 1
                height: 30
            }



            Item {
                width: parent.width
                height: children[0].height


                Rectangle
                {
                    width: parent.width/2 - 20
                    height: children[1].height + 20
                    color: "#ffffff"
                    border.color: "#000000"
                    radius: 7
                    opacity: children[0].pressed ? 0.6 : 1.0
                    visible: id_FileWrited.value == 0 ? true : false

                    MouseArea
                    {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                                id_FileWrited.value = 0;
                                contextMain.slFileCopy(1, id_tiFilePath.text.trim());

                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Get file")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#000000"
                    }
                }

                Rectangle
                {
                    width: parent.width/2 - 20
                    height: children[1].height + 20
                    anchors.right: parent.right
                    color: "#ffffff"
                    border.color: "#000000"
                    radius: 7
                    opacity: children[0].pressed ? 0.6 : 1.0
                    visible: id_FileWrited.value == 0 ? true : false

                    MouseArea
                    {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                                id_FileWrited.value = 0;
                                contextMain.slFileCopy(2, id_tiFilePath.text.trim());

                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Send file")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#000000"
                    }
                }

                Rectangle
                {
                    width: parent.width
                    height: children[1].height + 20
                    color: "#ffffff"
                    border.color: "#000000"
                    radius: 7
                    opacity: children[0].pressed ? 0.6 : 1.0
                    visible: id_FileWrited.value > 0 ? true : false

                    MouseArea
                    {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                                //id_FileWrited.value = 0;
                                contextMain.slFileCopy(0, "");
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Stop")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#000000"
                    }
                }

            }

            Item {
                width: 1
                height: 30
                visible: id_FileWrited.value
            }

            ProgressBar {
                id: id_FileWrited
                width: parent.width
                value: 0.0
                visible: value == 0 ? false : true
           }

            Text {
                id: id_ProcCopy
                anchors.right: id_FileWrited.right
                text: qsTr("")
                //font.bold: true
                font.pixelSize: 16
                color: "#000000"
                visible: id_FileWrited.value

            }

            Item {
                width: 1
                height: 30
                visible: id_StatusCopy.visible
            }

            Text {
                id: id_StatusCopy
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("")
                wrapMode: Text.Wrap
                //font.bold: true
                font.pixelSize: 18
                color: "#000000"
                visible: text.length == 0 ? false : true
            }

            Item {
                width: 1
                height: 5
            }

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
