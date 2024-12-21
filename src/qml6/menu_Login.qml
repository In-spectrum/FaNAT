import QtQuick 2.12
import QtQuick.Controls 2.15

Rectangle {
    id: root
    objectName: "obMenuLogin"
    width: 300
    color: "#808080"
    height: parent.height
    border.color: "#000000"
    border.width: 1

    property int m_iH: id_recTitle.height + id_colData.height + id_recCancel.height + 20
    property int m_iTitleW: 110

    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
        id_tiLog.text = contextMain.slLogin();
        id_tiPass.text = contextMain.slPassword();

    }

    Component.onDestruction:
    {

    }

    function fConnect(_bVar)
    {
        if(_bVar == 1)
            id_tConnect.stop()
        else
            id_tConnect.start()

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
            text: qsTr("- Your login")
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
        id: id_flMain
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

            Row
            {
                Text {
                    text: qsTr("Login:")
                    width: root.m_iTitleW
                    color: "#ffffff"
                    font.bold: true
                    font.pixelSize: 20

                    MouseArea
                    {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                                if(!id_tiLog.cursorVisible)
                                {
                                    id_tiLog.cursorPosition  = id_tiLog.text.length;
                                    id_tiLog.cursorVisible = true
                                    id_tiLog.forceActiveFocus();
                                }
                        }

                        onDoubleClicked:
                            (mouse)=>
                        {
                                id_tiLog.selectAll();
                        }
                    }
                }

                Rectangle
                {
                    height: children[0].height + 4
                    color: "#10000000"
                    anchors.bottom: parent.children[0].bottom
                    anchors.bottomMargin: -2
                    width: id_flMain.width - parent.children[0].width - 10

                    TextInput {
                        id: id_tiLog
                        width: parent.width - 6
                        anchors.centerIn: parent

                        text: ""
                        color: "#ffffff"
                        font.pixelSize: 20

                        clip: true
                    }
                }
            }

            Item {
                width: 1
                height: 15
            }

            Row
            {

                Text {
                    text: qsTr("Password:")
                    width: root.m_iTitleW
                    color: "#ffffff"
                    font.bold: true
                    font.pixelSize: 20

                    MouseArea
                    {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                                if(!id_tiPass.cursorVisible)
                                {
                                    id_tiPass.cursorPosition  = id_tiPass.text.length;
                                    id_tiPass.cursorVisible = true
                                    id_tiPass.forceActiveFocus();
                                }
                        }

                        onDoubleClicked:
                            (mouse)=>
                        {
                                id_tiPass.selectAll();
                        }
                    }
                }

                Rectangle
                {
                    height: children[0].height + 4
                    color: "#10000000"
                    anchors.bottom: parent.children[0].bottom
                    anchors.bottomMargin: -2
                    width: id_flMain.width - parent.children[0].width - 10

                    TextInput {
                        id: id_tiPass
                        width: parent.width - 6
                        anchors.centerIn: parent

                        text: ""
                        color: "#ffffff"
                        font.pixelSize: 20

                        clip: true
                    }
                }

            }

            Item {
                width: 1
                height: 25
            }

            Item {
                width: parent.width
                height: children[0].height


                Rectangle
                {
                    width: children[1].width + 20
                    height: children[1].height + 20
                    color: "#ffffff"
                    border.color: "#000000"
                    radius: 7
                    opacity: children[0].pressed ? 0.6 : 1.0

                    MouseArea
                    {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                            contextMain.slConnectToServer(id_tiLog.text, id_tiPass.text);
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("New connection")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#000000"
                    }
                }

                Rectangle
                {
                    width: 20
                    height: 2
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#000000"
                    rotation: 0
                    visible: id_tConnect.running

                    Timer
                    {
                        id: id_tConnect
                        interval: 10; running: false; repeat: true
                        onTriggered:
                        {
                            parent.rotation += 5;
                            if(parent.rotation > 360)
                                parent.rotation = 5;
                        }
                    }
                }

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
