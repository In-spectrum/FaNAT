import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    id: root
    objectName: "obComandLine"
    anchors.fill: parent
    color: "#808080"
    border.color: "#000000"
    border.width: 1

    property int m_iH: id_recTitle.height + id_colData.height + id_recCancel.height + 20

    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
        parent.height = parent.parent.height;

        id_tiReguest.text = "";

        if(!id_tiReguest.cursorVisible)
        {
            id_tiReguest.cursorPosition  = id_tiReguest.text.length;
            id_tiReguest.cursorVisible = true
            id_tiReguest.forceActiveFocus();
        }


    }

    Component.onDestruction:
    {

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


    function fResponse(_iVar, _sData)
    {
        id_tiResponse.text += _sData;
        id_tiResponse.cursorPosition = id_tiResponse.text.length;
        id_svResp.scrollToBottom();
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
            text: qsTr("- Command line")
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

    Column
    {
        id: id_colData
        x: 5
        width: parent.width - 2 * x
        anchors.top: id_recTitle.bottom

        Item {
            width: 1
            height: 20
        }

        Column
        {
            width: parent.width

            Text {
                text: qsTr("Input:")
                color: "#ffffff"
                font.bold: true
                font.pixelSize: 20
                font.underline: true

                MouseArea
                {
                    anchors.fill: parent

                    onPressed:
                        (mouse)=>
                    {
                            if(!id_tiReguest.cursorVisible)
                            {
                                id_tiReguest.cursorPosition  = id_tiReguest.text.length;
                                id_tiReguest.cursorVisible = true
                                id_tiReguest.forceActiveFocus();
                            }
                    }

                    onDoubleClicked:
                        (mouse)=>
                    {
                            id_tiReguest.selectAll();
                    }
                }
            }

            Item {
                width: 1
                height: 10
            }

            Rectangle
            {
                width: parent.width
                height: root.height/8
                color: "#ffffff"



                ScrollView {
                    anchors.fill: parent
                    rightPadding: 7


                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                    TextArea {
                        id: id_tiReguest
                        wrapMode: Text.Wrap

                        text: ""
                        color: "#000000"
                        font.pixelSize: 16

                        selectByMouse: true

                        clip: true

                        onTextChanged:
                        {

                        }

//                        Keys.onPressed:
//                            (event)=>
//                            {
//                                if(event.key == )
//                                contextMain.slSendKeyEvent(1, event.key, event.text);
//                                event.accepted = true;
//                        }

                        Keys.onReturnPressed: {
                            id_recReguest.fPress();
                        }
                        Keys.onEnterPressed: {
                            id_recReguest.fPress();
                        }

                    }
                }



            }
        }

        Item {
            width: 1
            height: 10
        }

        Item
        {
            width: parent.width
            height: 50

            Rectangle
            {
                id: id_recReguest
                width: parent.width/3
                height: 40
                color: "#ffffff"
                border.color: "#000000"
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
                            id_recReguest.fPress();
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

                function fPress()
                {
                    if(id_tiReguest.text.length < 2)
                        return;

                    if(id_tiResponse.text.lastIndexOf("->") != id_tiResponse.text.length - 2)
                    {
                        id_tiResponse.text += "\n->";
                    }

                    id_tiResponse.text += id_tiReguest.text
                    id_tiResponse.text += "\r\n-BEGIN------------------------------------\r\n";
                    id_tiResponse.cursorPosition = id_tiResponse.text.length;
                    id_svResp.scrollToBottom();

                    if(id_chkCyrillic.checked)
                        contextMain.slComandLine(id_tiReguest.text, 2);
                    else
                        contextMain.slComandLine(id_tiReguest.text, 1);

                    // id_tiReguest.text = "";
                    // id_tiReguest.cursorPosition  = id_tiReguest.text.length;

                }

                Text {
                    anchors.centerIn: parent
                    text: qsTr("Request")
                    font.bold: true
                    font.pixelSize: 14
                    color: "#000000"
                }
            }


            Rectangle
            {
                width: parent.width/3
                height: 40
                anchors.right: parent.right
                anchors.rightMargin: 7
                color: "#ffffff"
                border.color: "#000000"
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
                            contextMain.slComandLine("stopRun", 1);
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
                    text: qsTr("Kill")
                    font.bold: true
                    font.pixelSize: 14
                    color: "#000000"
                }
            }

            Rectangle
            {
                width: parent.width - 2 * root.border.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                height: 1
                color: "#000000"
            }
        }


        Item {
            width: 1
            height: 10
        }

    }

    Column
    {
        width: id_colData.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: id_recCancel.top
        anchors.bottomMargin: 10
        visible: children[2].height > 0 ? true : false

        Item {
            width: parent.width
            height: children[0].height > children[1].height ? children[0].height : children[1].height

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Output:")
                color: "#ffffff"
                font.bold: true
                font.pixelSize: 20
                font.underline: true

                MouseArea
                {
                    anchors.fill: parent

                    onPressed:
                        (mouse)=>
                    {
                            if(!id_tiResponse.cursorVisible)
                            {
                                id_tiResponse.cursorPosition  = id_tiResponse.text.length;
                                id_tiResponse.cursorVisible = true
                                id_tiResponse.forceActiveFocus();
                            }
                    }

                }
            }

            MyCheckBox {
                id: id_chkCyrillic
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: qsTr("use cyrillic")
                //font.bold: true
                font.pixelSize: 18
            }

        }


        Item {
            width: 1
            height: 10
        }

        Rectangle
        {
            width: parent.width
            height: root.height - (id_colData.y + id_colData.height) - id_recCancel.height
                    - parent.children[0].height - parent.children[1].height
                    - parent.children[3].height - parent.children[4].height - 10
            color: "#ffffff"



            ScrollView {
                id: id_svResp
                anchors.fill: parent
                rightPadding: 7


                contentWidth: children.implicitWidth
                contentHeight: children.implicitHeight
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                clip: true

                function scrollToBottom() {
                                ScrollBar.vertical.position = 1.0 - ScrollBar.vertical.size
                            }


                TextArea {
                    id: id_tiResponse
                    wrapMode: Text.Wrap

                    text: ""
                    color: "#000000"
                    font.pixelSize: 16
                    selectByMouse: true

                    clip: true

                    onTextChanged:
                    {

                    }
                }
            }


        }

        Item {
            width: 1
            height: 10
        }

        Rectangle
        {
            width: children[1].width + 40
            height: 40
            color: "#ffffff"
            border.color: "#000000"
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
                        id_tiResponse.text = "";
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
                text: qsTr("C lear")
                font.bold: true
                font.pixelSize: 14
                color: "#000000"
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
