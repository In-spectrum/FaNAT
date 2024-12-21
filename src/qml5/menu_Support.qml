import QtQuick 2.12
import QtQuick.Controls 2.15

Rectangle {
    id: root
    objectName: "obMenuSupport"
    width: 300
    color: "#808080"
    height: parent.height
    border.color: "#000000"
    border.width: 1

    property int m_iH: id_recTitle.height + id_colData.height + id_recCancel.height + 10
    property int m_iTitleW: 110

    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
        //id_tiIP.text = contextMain.slServerIP();
    }

    Component.onDestruction:
    {

    }

    onM_iHChanged:
    {
        signalData(1, "", "", "", "", "", "")
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
            text: qsTr("- Support")
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
        x: 10
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

        MouseArea
        {
            anchors.fill: parent
            onReleased:
                (mouse)=>
            {
                    id_txtMail.focus = false
            }

        }

        Column
        {
            id: id_colData
            width: id_scrollBar.visible ? (parent.width - id_scrollBar.width - 10) : parent.width



            Item {
                width: 1
                height: 20
            }

            Image {
                height: 100
                width: 3 * height
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/image/baner.png"

                MouseArea {
                    anchors.fill: parent

                    onReleased:
                    {
                        Qt.openUrlExternally(id_txtFTurl.a_link)
                    }
                }

            }

            Item {
                width: 1
                height: 5
            }

            Item {
                width: parent.width
                height: children[0].height

                Text {
                    id: id_txtFTurl
                    //color: "#ffffff"
                    font.bold: true
                    font.pixelSize: 20
                    text: '<html><style type="text/css" color="white"></style><a href="' + a_link + '">   FaNAT   </a></html>'
                    onLinkActivated: Qt.openUrlExternally(a_link)

                    property string  a_link: "https://in-spectrum.github.io/FaNAT/"

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.NoButton // Don't eat the mouse clicks
                        cursorShape: Qt.PointingHandCursor
                    }
                }


                Text {
                    color: "#ffffff"
                    //font.bold: true
                    font.pixelSize: 16
                    anchors.right: parent.children[2].left
                    anchors.rightMargin: 20
                    anchors.bottom: parent.children[0].bottom
                    text: '<html><style type="text/css"></style><a href="' + a_link + '">   GitHub   </a></html>'
                    onLinkActivated: Qt.openUrlExternally(a_link)

                    property string  a_link: "https://github.com/In-spectrum/FaNAT?tab=readme-ov-file"

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.NoButton // Don't eat the mouse clicks
                        cursorShape: Qt.PointingHandCursor
                    }
                }

                Text {
                    color: "#ffffff"
                    //font.bold: true
                    font.pixelSize: 16
                    anchors.right: parent.right
                    anchors.bottom: parent.children[1].bottom
                    text: '<html><style type="text/css"></style><a href="' + a_link + '">MIT license</a></html>'
                    onLinkActivated: Qt.openUrlExternally(a_link)

                    property string  a_link: "https://github.com/In-spectrum/FaNAT?tab=MIT-1-ov-file#"

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.NoButton // Don't eat the mouse clicks
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }

            Item {
                width: 1
                height: 20
            }

            Item {
                width: parent.width
                height: children[0].height

                Text {
                    color: "#ffffff"
                    font.bold: true
                    font.pixelSize: 18
                    text: "meil"
                }

                TextEdit  {
                    id: id_txtMail
                    color: "#ffffff"
                    //font.bold: true
                    font.pixelSize: 16
                    anchors.right: parent.right
                    anchors.bottom: parent.children[0].bottom
                    text: "alexandr.deryk@gmail.com"
                    readOnly: true
                    persistentSelection: false
                    focus: true
                }
            }



            Column
            {
                width: parent.width

                Item {
                    width: 1
                    height: 20
                }

                Text {
                    color: "#ffffff"
                    font.pixelSize: 20
                    text: "was used:"
                }

                Item {
                    width: 1
                    height: 10
                }

                Item {
                    width: parent.width
                    height: children[0].height

                    Text {
                        color: "#ffffff"
                        //font.bold: true
                        font.pixelSize: 20
                        text: "Qt"
                    }

                    Text {
                        color: "#ffffff"
                        //font.bold: true
                        font.pixelSize: 16
                        anchors.right: parent.right
                        anchors.bottom: parent.children[0].bottom
                        text:  '<html><style type="text/css"></style><a href="' + a_link + '">LGPL-v3 license</a></html>'
                        onLinkActivated: Qt.openUrlExternally(a_link)

                        property string  a_link: "https://www.gnu.org/licenses/lgpl-3.0.txt"

                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.NoButton // Don't eat the mouse clicks
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }

                Item {
                    width: 1
                    height: 10
                    visible: false
                }

                Item {
                    width: parent.width
                    height: children[0].height
                    visible: false

                    Text {
                        color: "#ffffff"
                        //font.bold: true
                        font.pixelSize: 20
                        text: "GStreamer"
                    }

                    Text {
                        color: "#ffffff"
                        //font.bold: true
                        font.pixelSize: 16
                        anchors.right: parent.right
                        anchors.bottom: parent.children[0].bottom
                        text:  '<html><style type="text/css"></style><a href="' + a_link + '">LGPL-v2.1 license</a></html>'
                        onLinkActivated: Qt.openUrlExternally(a_link)

                        property string  a_link: "https://github.com/GStreamer/gstreamer/blob/main/LICENSE"

                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.NoButton // Don't eat the mouse clicks
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }

            }





            Item {
                width: 1
                height: 40
                visible: false
            }

            Row
            {
                visible: false
                Text {
                    text: qsTr("Server IP:")
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


            Item {
                width: 1
                height: 30
            }

            Item {
                visible: false
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
                                if(contextMain.slIsIP(id_tiIP.text)  )
                                {
                                    contextMain.slSendStatIP(id_tiIP.text);
                                }
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("  Apply  ")
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
