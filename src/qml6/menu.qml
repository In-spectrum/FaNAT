import QtQuick 2.12
import QtQuick.Controls.Basic

Item {
    id: root
    objectName: "obMenu"
    anchors.fill: parent


    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
    }

    Component.onDestruction:
    {

    }

    onHeightChanged:
    {
        if(id_loadMenuItem.visible)
        {
            id_loadMenuItem.fHeightUpdate();
        }
    }

    MouseArea
    {
        anchors.fill: id_colMenu
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

    function fConnectClient(_bVar)
    {
        id_Stream.m_bConnectClient = _bVar;
    }

    function fConnectServer(_iVar)
    {
        //print("fConnectServer 0: " + _iVar )

        if(_iVar == 1)
        {
            id_Connect.color = "#0096FF";
            id_itLogin.enabled = true;
            id_recConnecting.visible = false;
        }
        else
        {
            id_Connect.color = "#ccffffff";
            id_itLogin.enabled = false;

            if(_iVar == 2)
                id_recConnecting.visible = true;
            else
                id_recConnecting.visible = false;
        }

    }

    function fFileCopyVisible(_bVar)
    {
        id_itFileCopy.enabled = _bVar;

        if(!_bVar && id_loadMenuItem.m_iPage == 4)
            id_loadMenuItem.m_iPage = 0;

    }

    function fStream(_bVar)
    {
        id_itComandLine.m_bAcvive = !_bVar;
        //id_itVideoQuality.enabled = _bVar;
    }

    Column
    {
        id: id_colMenu
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle
        {
            id: id_recMenuTab
            anchors.horizontalCenter: parent.horizontalCenter
            width: children[1].width
            height: id_TitleM.visible ? 50 : children[1].height + 3
            color: id_loadMenuItem.m_iPage == 0 ?
                       id_TitleM.visible ? "#808080" : "#99808080"
                       : "#000000"

            border.color: id_TitleM.visible ? "#000000" : "#00000000"
            border.width: 1

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
                        if(id_loadMenuItem.m_iPage == 0)
                        {
                            if(id_Open.rotation == 0)
                            {
                                id_Open.rotation = 180;
                            }
                            else
                            {
                                id_Open.rotation = 0;
                            }
                        }

                        id_loadMenuItem.m_iPage = 0;
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


            Row
            {
                anchors.verticalCenter: parent.verticalCenter
                Row
                {
                    anchors.verticalCenter: parent.verticalCenter
                    Item {
                        width: 3
                        height: 1
                    }

                    Rectangle
                    {
                        id: id_Connect
                        anchors.verticalCenter: parent.verticalCenter
                        color: "#ccffffff"
                        width: 8
                        height: width
                        border.color: "#90000000"
                    }

                    Text {
                        id: id_Open
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("  ^  ")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#ccffffff"
                        rotation: 180

                    }

                    Rectangle
                    {
                        id: id_Stream
                        anchors.verticalCenter: parent.verticalCenter
                        color: id_Stream.m_bConnectClient ? "#ff0000" : "#ccffffff"
                        width: id_Connect.width
                        height: width
                        border.color: id_Connect.border.color

                        property bool m_bConnectClient: false
                    }

                    Item {
                        width: 5
                        height: 1
                    }

                }

                Text {
                    id: id_TitleM
                    width: 110
                    text: qsTr("Menu")
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    font.pixelSize: 24
                    color: "#ffffff"
                    visible: id_Open.rotation == 0 ? true : false
                }
            }

            Rectangle
            {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                //anchors.bottomMargin: 1
                width: parent.width - 2
                height: 2
                color: "#ffffff"
                visible: id_TitleM.visible
            }

            Rectangle
            {
                id: id_recConnecting
                anchors.right: parent.left
                anchors.rightMargin: 2
                anchors.verticalCenter: parent.verticalCenter
                width: children[0].width + 10
                height: parent.children[1].height + 3
                color: "#90ff0000"
                visible: false

                Text {
                    anchors.centerIn: parent
                    text: qsTr("connecting...  ")
                    font.bold: true
                    font.pixelSize: 14
                    color: "#ffffff"
                }
            }
        }

        Rectangle
        {
            width: parent.width
            height: id_colData.visible ? children[0].height + 2 : 0
            color: id_recMenuTab.color
            visible: id_TitleM.visible

            border.color: "#000000"
            border.width: 1

            clip: true

            onVisibleChanged:
            {
                if(!visible)
                    id_loadMenuItem.m_iPage = 0;
            }

            Flickable {
                x: 0
                width: parent.width - 2 * x
                height: id_colData.height + id_recMenuTab.height < root.height - 10 ? id_colData.height : root.height - id_recMenuTab.height - 10
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
                    width: id_scrollBar.visible ? (parent.width - id_scrollBar.width - 0) : parent.width
                    visible: !id_loadMenuItem.visible

                    Item {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width - 6
                        height: 50


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
                                id_loadMenuItem.m_iPage = 3;
                            }

                            onPositionChanged:
                                (mouse)=>
                            {

                            }
                        }


                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Server")
                            font.bold: true
                            font.pixelSize: 18
                            color: "#ffffff"
                            opacity: parent.children[0].pressed ? 0.5 : 1.0
                        }

                        Rectangle
                        {
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 1
                            color: "#ffffff"
                        }

                    }


                    Item {
                        id: id_itLogin
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width - 6
                        height: 50

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
                                id_loadMenuItem.m_iPage = 1;
                            }

                            onPositionChanged:
                                (mouse)=>
                            {
                            }
                        }


                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Login")
                            font.bold: true
                            font.pixelSize: 18
                            color: parent.enabled ? "#ffffff" : "#30000000"
                            opacity: parent.children[0].pressed ? 0.5 : 1.0
                        }

                        Rectangle
                        {
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 1
                            color: "#ffffff"
                        }

                    }

                    Item {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width - 6
                        height: 50
                        enabled: id_itLogin.enabled


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
                                id_loadMenuItem.m_iPage = 2;
                            }

                            onPositionChanged:
                                (mouse)=>
                            {
                            }
                        }


                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Desktop")
                            font.bold: true
                            font.pixelSize: 18
                            color: parent.enabled ? "#ffffff" : "#30000000"
                            opacity: parent.children[0].pressed ? 0.5 : 1.0
                        }

                        Rectangle
                        {
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 1
                            color: "#ffffff"
                        }

                    }

                    Item {
                        id: id_itFileCopy
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width - 6
                        height: 50
                        //visible: false
                        enabled: false


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
                                id_loadMenuItem.m_iPage = 4;

                            }

                            onPositionChanged:
                                (mouse)=>
                            {
                            }
                        }


                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("File copy")
                            font.bold: true
                            font.pixelSize: 18
                            color: parent.enabled ? "#ffffff" : "#30000000"
                            opacity: parent.children[0].pressed ? 0.5 : 1.0
                        }

                        Rectangle
                        {
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 1
                            color: "#ffffff"
                        }

                    }


                    Item {
                        id: id_itComandLine
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width - 6
                        height: 50
                        //enabled: id_itFileCopy.enabled && m_bAcvive ? true : false
                        enabled: id_itFileCopy.enabled ? true : false

                        property bool m_bAcvive: false


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
                                id_loadMenuItem.m_iPage = 6
                            }

                            onPositionChanged:
                                (mouse)=>
                            {
                            }
                        }


                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Command line")
                            font.bold: true
                            font.pixelSize: 18
                            color: parent.enabled ? "#ffffff" : "#30000000"
                            opacity: parent.children[0].pressed ? 0.5 : 1.0
                        }

                        Rectangle
                        {
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 1
                            color: "#ffffff"
                        }

                    }


                    Item {
                        id: id_itVideoQuality
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width - 6
                        height: 50
                        //enabled: false;


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
                                id_loadMenuItem.m_iPage = 7;
                            }

                            onPositionChanged:
                                (mouse)=>
                            {
                            }
                        }


                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Video quality")
                            font.bold: true
                            font.pixelSize: 18
                            color: parent.enabled ? "#ffffff" : "#30000000"
                            opacity: parent.children[0].pressed ? 0.5 : 1.0
                        }

                        Rectangle
                        {
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 1
                            color: "#ffffff"
                        }

                    }


                    Item {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width - 6
                        height: 50


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
                                id_loadMenuItem.m_iPage = 5;
                            }

                            onPositionChanged:
                                (mouse)=>
                            {
                            }
                        }


                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("View size")
                            font.bold: true
                            font.pixelSize: 18
                            color: "#ffffff"
                            opacity: parent.children[0].pressed ? 0.5 : 1.0
                        }

                        Rectangle
                        {
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 1
                            color: "#ffffff"
                        }

                    }

                    Item {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width - 6
                        height: 50


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
                                id_loadMenuItem.m_iPage = 8;
                            }

                            onPositionChanged:
                                (mouse)=>
                            {
                            }
                        }


                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Support")
                            font.bold: true
                            font.pixelSize: 18
                            color: "#ffffff"
                            opacity: parent.children[0].pressed ? 0.5 : 1.0
                        }

                        Rectangle
                        {
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 1
                            color: "#ffffff"
                        }

                    }



                    Item {
                        width: 1
                        height: 5
                    }

                }

            }
        }

    }



    Loader {
       id: id_loadMenuItem
       y: id_recMenuTab.height - 2
       width: id_loadMenuItem.m_iPage == 6 ? root.width
                                           : 400 >= root.width ? root.width - 10 : 400
       anchors.horizontalCenter: parent.horizontalCenter
       height: parent.height - id_colMenu.children[0].height


       visible: m_iPage == 0 ? false : true
       active: m_iPage == 0 ? false : true
       source: m_iPage == 0 ? ""
             : m_iPage == 1 ? "menu_Login.qml"
             : m_iPage == 2 ? "menu_Desktop.qml"
             : m_iPage == 3 ? "menu_Server.qml"
             : m_iPage == 4 ? "menu_FileCopy.qml"
             : m_iPage == 5 ? "menu_ViewSize.qml"
             : m_iPage == 6 ? "menu_ComandLine.qml"
             : m_iPage == 7 ? "menu_VideoQuality.qml"
             :                "menu_Support.qml"

       property int m_iPage: 0

       onLoaded:
       {
           item.signalData.connect(slotData)

           if(id_loadMenuItem.m_iPage == 3)
                item.fConnect(id_itLogin.enabled)

           fHeightUpdate();
       }

       Component.onDestruction: {
                   if (item) {
                       item.signalData.disconnect(slotData)
                   }
               }


       function slotData(_iId, _vData_1, _vData_2, _vData_3, _vData_4, _vData_5, _vData_6)
       {
          //print("id_loadMenuItem::slotData 0: " + _iId)

           switch(_iId)
           {
               case 0:
                   id_loadMenuItem.m_iPage = 0;
                   break;
               case 1:
                   fHeightUpdate();
                   break;
           }

       }

       function fHeightUpdate()
       {
           if(id_loadMenuItem.m_iPage == 6)
               id_loadMenuItem.height = parent.height - y;
           else
           {
               if(parent.height - id_colMenu.children[0].height < id_loadMenuItem.item.m_iH )
               {
                   id_loadMenuItem.height = parent.height - id_colMenu.children[0].height;
               }
               else
               {
                   id_loadMenuItem.height = id_loadMenuItem.item.m_iH
               }
           }
       }

    }


}
