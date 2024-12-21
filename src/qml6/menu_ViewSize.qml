import QtQuick 2.12
import QtQuick.Controls 2.15

Rectangle {
    id: root
    objectName: "obMenuViewSize"
    width: 300
    color: "#808080"    
    border.color: "#000000"
    border.width: 1

    property int m_iH: id_recTitle.height + id_colData.height + id_recCancel.height + 50

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
            text: qsTr("- View size")
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
                height: 15
            }

            Item {
                width: parent.width
                height: 40


                Item
                {
                    anchors.fill: parent
                    opacity: children[0].pressed ? 0.5 : 1.0

                    MouseArea {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                                contextMain.slFullScreen(true);
                        }
                    }

                    Text {
                        x: 5
                        width: parent.width - 2*x
                        anchors.verticalCenter: parent.verticalCenter
                        //font.bold: true
                        font.pointSize: 18
                        text: "Application full size"
                        color: "white"
                        clip: true
                    }

                    Rectangle
                    {
                        width: parent.width
                        height: 1
                        anchors.bottom: parent.bottom
                        color: "#cc000000"
                    }

                }
           }

            Item {
                width: 1
                height: 15
            }

            Item {
                width: parent.width
                height: 40


                Item
                {
                    anchors.fill: parent
                    opacity: children[0].pressed ? 0.5 : 1.0

                    MouseArea {
                        anchors.fill: parent

                        onPressed:
                            (mouse)=>
                        {
                                contextMain.slDesktopRealSize(true);
                        }
                    }

                    Text {
                        x: 5
                        width: parent.width - 2*x
                        anchors.verticalCenter: parent.verticalCenter
                        //font.bold: true
                        font.pointSize: 18
                        text: "Real desktop size"
                        color: "white"
                        clip: true
                    }

                    Rectangle
                    {
                        width: parent.width
                        height: 1
                        anchors.bottom: parent.bottom
                        color: "#cc000000"
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
