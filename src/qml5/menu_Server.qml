import QtQuick 2.12
import QtQuick.Controls 2.15

Rectangle {
    id: root
    objectName: "obMenuServer"
    width: 300
    color: "#808080"
    height: parent.height
    border.color: "#000000"
    border.width: 1

    property int m_iH: id_recTitle.height + id_colData.height + id_recCancel.height + 20
    property int m_iTitleW: 120

    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
        id_tiIP.text = contextMain.slServerIP();
        id_tiPortTCP.text = contextMain.slPortTCP();
        id_tiRtspPort.text = contextMain.slPortRTSP();
        id_tiRtmpPort.text = contextMain.slPortRTMP();
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
            text: qsTr("- Server")
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


            Column
            {
                Item {
                    width: 1
                    height: 20
                }

                MyCheckBox {
                    id: id_chkServDev
                    objectName: "obChkServDev"
                    text: qsTr("use the developer server")
                    //font.bold: true
                    font.pixelSize: 18

                    Component.onCompleted:
                    {
                        id_chkServDev.checked = contextMain.slDevServer();
                    }

                    onCheckedChanged:
                    {
                        if(!id_chkServDev.checked)
                        {
                            contextMain.fUpdateServerData();
                            id_tiPortTCP.text = contextMain.slPortTCP();
                            id_tiRtspPort.text = contextMain.slPortRTSP();
                            id_tiRtmpPort.text = contextMain.slPortRTMP();
                        }
                    }

                }

                Item {
                    anchors.right: id_chkServDev.right
                    anchors.rightMargin: 5
                    width: children[0].width
                    height: children[0].height

                    Text {
                        y: -7
                        text: qsTr("(limited time)")
                        color: "#000000"
                        font.pixelSize: 16
                    }
                }



                Item {
                    width: 1
                    height: 15
                    visible: id_chkServDev.checked
                }

                Row
                {
                    visible: id_chkServDev.checked

                    Text {
                        text: qsTr("key:")
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
                                    if(!id_tiKey.cursorVisible)
                                    {
                                        id_tiKey.cursorPosition  = id_tiKey.text.length;
                                        id_tiKey.cursorVisible = true
                                        id_tiKey.forceActiveFocus();
                                    }
                            }

                            onDoubleClicked:
                                (mouse)=>
                            {
                                    id_tiKey.selectAll();
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
                            id: id_tiKey
                            width: parent.width - 6
                            anchors.centerIn: parent

                            text: ""
                            color: "#ffffff"
                            font.pixelSize: 20

                            clip: true

                            onTextChanged:
                            {
                                text = text.replace(" ","");
                            }

                            Component.onCompleted:
                            {
                                id_tiKey.text = contextMain.slKeyDevServer();
                            }
                        }
                    }

                }
            }

            Item {
                width: 1
                height: 40
            }

            Column{
                visible: !id_chkServDev.checked

                Row
                {
                    Text {
                        text: qsTr("password:")
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
                                    if(!id_tiPassword.cursorVisible)
                                    {
                                        id_tiPassword.cursorPosition  = id_tiPassword.text.length;
                                        id_tiPassword.cursorVisible = true
                                        v.forceActiveFocus();
                                    }
                            }

                            onDoubleClicked:
                                (mouse)=>
                            {
                                    id_tiPassword.selectAll();
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
                            id: id_tiPassword
                            width: parent.width - 6
                            anchors.centerIn: parent

                            text: ""
                            color: "#ffffff"
                            font.pixelSize: 20

                            clip: true

                            onTextChanged:
                            {
                                text = text.replace(" ","");
                            }

                            Component.onCompleted:
                            {
                                id_tiPassword.text = contextMain.slServerPassword();
                            }

                        }
                    }

                }

                Item {
                    width: 1
                    height: 15
                }
            }



            Row
            {
                Text {
                    text: qsTr("ip:")
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
                                if(!id_tiIP.cursorVisible)
                                {
                                    id_tiIP.cursorPosition  = id_tiIP.text.length;
                                    id_tiIP.cursorVisible = true
                                    id_tiIP.forceActiveFocus();
                                }
                        }

                        onDoubleClicked:
                            (mouse)=>
                        {
                                id_tiIP.selectAll();
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
                        id: id_tiIP
                        width: parent.width - 6
                        anchors.centerIn: parent

                        text: ""
                        color: "#ffffff"
                        font.pixelSize: 20

                        clip: true

                        onTextChanged:
                        {
                            text = text.replace(" ","");
                        }

                    }
                }



            }

            Column{
                visible: !id_chkServDev.checked


                Item {
                    width: 1
                    height: 15

                }

                Row
                {

                    Text {
                        text: qsTr("port:")
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
                                    if(!id_tiPortTCP.cursorVisible)
                                    {
                                        id_tiPortTCP.cursorPosition  = id_tiPortTCP.text.length;
                                        id_tiPortTCP.cursorVisible = true
                                        id_tiPortTCP.forceActiveFocus();
                                    }
                            }

                            onDoubleClicked:
                                (mouse)=>
                            {
                                    id_tiPortTCP.selectAll();
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
                            id: id_tiPortTCP
                            width: parent.width - 6
                            anchors.centerIn: parent

                            text: ""
                            color: "#ffffff"
                            font.pixelSize: 20

                            clip: true

                            onTextChanged:
                            {
                                text = text.replace(" ","");
                            }

                        }
                    }
                }

                Item {
                    width: 1
                    height: 30
                    //visible: false
                }

                Row
                {
                    //visible: false

                    Text {
                        text: qsTr("rtsp-port:")
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
                                    if(!id_tiRtspPort.cursorVisible)
                                    {
                                        id_tiRtspPort.cursorPosition  = id_tiRtspPort.text.length;
                                        id_tiRtspPort.cursorVisible = true
                                        id_tiRtspPort.forceActiveFocus();
                                    }
                            }

                            onDoubleClicked:
                                (mouse)=>
                            {
                                    id_tiRtspPort.selectAll();
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
                            id: id_tiRtspPort
                            width: parent.width - 6
                            anchors.centerIn: parent

                            text: ""
                            color: "#ffffff"
                            font.pixelSize: 20

                            clip: true

                            onTextChanged:
                            {
                                text = text.replace(" ","");
                            }

                        }
                    }

                }

                Item {
                    width: 1
                    height: 15
                    //visible: false
                }

                Row
                {
                    //visible: false

                    Text {
                        text: qsTr("rtmp-port:")
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
                                    if(!id_tiRtmpPort.cursorVisible)
                                    {
                                        id_tiRtmpPort.cursorPosition  = id_tiRtmpPort.text.length;
                                        id_tiRtmpPort.cursorVisible = true
                                        id_tiRtmpPort.forceActiveFocus();
                                    }
                            }

                            onDoubleClicked:
                                (mouse)=>
                            {
                                    id_tiRtmpPort.selectAll();
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
                            id: id_tiRtmpPort
                            width: parent.width - 6
                            anchors.centerIn: parent

                            text: ""
                            color: "#ffffff"
                            font.pixelSize: 20

                            clip: true

                            onTextChanged:
                            {
                                text = text.replace(" ","");
                            }
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
                                if(id_chkServDev.checked)
                                {
                                    if(contextMain.slIsIP(id_tiIP.text)
                                       && id_tiKey.text.length > 7
                                       && id_tiPassword.text.length > 3
                                       )
                                    {
                                        contextMain.slServerUpdateData(id_tiIP.text, "0", "0", "0", id_tiKey.text, id_tiPassword.text);
                                    }
                                }
                                else
                                if(contextMain.slIsIP(id_tiIP.text)
                                   && contextMain.slIsNumber(id_tiPortTCP.text)
                                   && contextMain.slIsNumber(id_tiRtspPort.text)
                                   && contextMain.slIsNumber(id_tiRtmpPort.text)
                                   && id_tiPortTCP.text.indexOf('-') < 0
                                   && id_tiRtspPort.text.indexOf('-') < 0
                                   && id_tiRtmpPort.text.indexOf('-') < 0                                   
                                   && id_tiPassword.text.length > 3
                                   )
                                {
                                    contextMain.slServerUpdateData(id_tiIP.text, id_tiPortTCP.text, id_tiRtspPort.text, id_tiRtmpPort.text, "xxxxxxxx", id_tiPassword.text);
                                }
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
                        interval: 100; running: false; repeat: true
                        onTriggered:
                        {
                            parent.rotation += 15;
                            if(parent.rotation > 360)
                                parent.rotation = 15;
                        }
                    }
                }

            }




            Column
            {
                width: parent.width
                visible: !id_chkServDev.checked

                Item {
                    width: 1
                    height: 30
                }

                Item
                {
                    width: parent.width
                    height: children[1].height

                    Text {
                        text: qsTr("low activity disconnect time:")
                        //width: root.m_iTitleW
                        color: "#ffffff"
                        font.bold: true
                        font.pixelSize: 20
                        anchors.bottom: parent.children[1].bottom

                        MouseArea
                        {
                            anchors.fill: parent

                            onPressed:
                                (mouse)=>
                            {
                                    if(!id_tiTimeLA.cursorVisible)
                                    {
                                        id_tiTimeLA.cursorPosition  = id_tiTimeLA.text.length;
                                        id_tiTimeLA.cursorVisible = true
                                        id_tiTimeLA.forceActiveFocus();
                                    }
                            }

                            onDoubleClicked:
                                (mouse)=>
                            {
                                    id_tiTimeLA.selectAll();
                            }
                        }
                    }

                    Rectangle
                    {
                        height: children[0].height + 4
                        color: "#10000000"
                        anchors.left: parent.children[0].right
                        anchors.right: parent.children[2].left
                        anchors.leftMargin: 10
                        anchors.rightMargin: 3


                        TextInput {
                            id: id_tiTimeLA
                            width: parent.width - 6
                            anchors.centerIn: parent

                            text: "0"
                            color: "#ffffff"
                            font.pixelSize: 20

                            clip: true

                            onTextChanged:
                            {
                                text = text.replace(" ","");
                            }
                        }
                    }

                    Text {
                        text: qsTr("sec.")
                        color: "#ffffff"
                        font.pixelSize: 20
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.bottom:  parent.children[1].bottom
                    }

                }

                Item {
                    width: 1
                    height: 10
                }

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
                                contextMain.slLowActivityDiscTime(id_tiTimeLA.text);
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: qsTr(" Apply ")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#000000"
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
