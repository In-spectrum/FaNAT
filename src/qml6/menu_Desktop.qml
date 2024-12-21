import QtQuick
import QtQuick.Controls.Basic

Rectangle {
    id: root
    objectName: "obMenuDesktop"
    width: 300
    color: "#808080"
    height: parent.height
    border.width: 1

    property int m_iH: id_recTitle.height + id_colData.height + id_recCancel.height + 20
    property bool m_bUserSelected: false

    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
        if(!id_tiLog.cursorVisible)
        {
            id_tiLog.cursorPosition  = id_tiLog.text.length;
            id_tiLog.cursorVisible = true
            id_tiLog.forceActiveFocus();
        }
    }

    Component.onDestruction:
    {
        id_tSearch.stop();

        id_lmDesktopUser.clear();
    }

    function fChkComandLine(_bVar)
    {
        if(_bVar)
        {
            id_chkScreen.checked = false
            id_chkComandLine.checked = true
        }
        else
        {

            id_chkScreen.checked = true
            id_chkComandLine.checked = false
        }
    }

    function fConnect(_bVar)
    {
        if(_bVar)
            id_tConnect.stop()
        else
            id_tConnect.start()
    }

    function fAddDesktop(_sUser, _sDesctopId)
    {
        //print("fAddDesktop 0: " + _sUser + " / " + _sDesctopId)

        if(_sUser == "0" && _sDesctopId == "0")
        {
            id_lvUser.m_bNewSelect = true;
            var a_bSel = false;

            for(var i = 0, s = id_lmDesktopUser.count - 1; s >= i; s--)
            {
                if( id_lmDesktopUser.get(s).obOld )
                {                    
                    id_lmDesktopUser.remove(s);
                }
                else
                {
                    if(id_lmDesktopUser.get(s).obId === id_lvUser.m_sIdD)
                        a_bSel = true;
                }
            }

            for(var i = 0, s = id_lmDesktopUser.count - 1; s >= i; s--)
            {
                id_lmDesktopUser.get(s).obOld = true;
            }

            root.m_bUserSelected = a_bSel;

            return;
        }

        id_lvUser.m_bNewSelect = false;

        id_tSearch.m_iSearch = 0;

        var a_bAdd = true;

        for(var i = 0, s = id_lmDesktopUser.count - 1; s >= i; s--)
        {
            //print("fAddDesktop 4.0: " + id_lmDesktopUser.get(s).obTitle + " / " + _sUser)

            // if(id_lmDesktopUser.get(s).obTitle.indexOf( _sUser ) >= 0 )
            // {
            //    print("fAddDesktop 4.1: " + id_lmDesktopUser.get(s).obTitle + " / " + _sUser)

            //    id_lmDesktopUser.remove(s);
            // }
            // else
            {
                //print("fAddDesktop 4.2: " + id_lmDesktopUser.get(s).obTitle + " / " + _sUser)

                if(id_lmDesktopUser.get(s).obId === _sDesctopId )
                {
                    //print("fAddDesktop 4.3: " + id_lmDesktopUser.get(s).obTitle + " / " + _sUser)

                    id_lmDesktopUser.get(s).obOld = false;
                    a_bAdd = false;

                    break;
                }

            }
        }

        if(a_bAdd)
        {
            //print("fAddDesktop 6.0: " + _sDesctopId + " / " + _sUser)

            if(_sDesctopId == id_lvUser.m_sIdD && id_lvUser.m_sLoginD === _sUser)
            {
                //print("fAddDesktop 6.1: ")

                id_lmDesktopUser.append({ obId: _sDesctopId
                                      , obTitle:  _sUser
                                      , obSelect: true
                                      , obScrollW: 0
                                      , obOld: false
                                     })

                root.m_bUserSelected = true;
            }
            else
            {
                if(id_lvUser.m_sIdD.length == 0
                        && id_tiLog.text === _sUser)
                {
                    //print("fAddDesktop 6.2: ")

                    id_lmDesktopUser.append({ obId: _sDesctopId
                                          , obTitle:  _sUser
                                          , obSelect: true
                                          , obScrollW: 0
                                          , obOld: false
                                         })

                    id_lvUser.m_sIdD = _sDesctopId;
                    id_lvUser.m_sLoginD = _sUser;
                    root.m_bUserSelected = true;
                }
                else
                {
                    //print("fAddDesktop 6.3: ")

                    id_lmDesktopUser.append({ obId: _sDesctopId
                                          , obTitle:  _sUser
                                          , obSelect: false
                                          , obScrollW: 0
                                          , obOld: false
                                         })
                }
            }
        }

        //print("fAddDesktop 10: " + "---------------------------------------------")

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
            text: qsTr("- Desktop")
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

                Item
                {
                    width: parent.width
                    height: children[0].height

                    Text {
                        text: qsTr("Search login:")
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
                        anchors.right: parent.right
                        //anchors.rightMargin: 5
                        anchors.left:  parent.children[0].right
                        anchors.leftMargin: 5

                        TextInput {
                            id: id_tiLog
                            width: parent.width - 4
                            anchors.centerIn: parent

                            text: ""
                            color: "#ffffff"
                            font.pixelSize: 20

                            clip: true

                            Component.onCompleted:
                            {
                               text = contextMain.slDeskLogin();
                            }


                            onTextChanged:
                            {
                                id_lvUser.m_bNewSelect = true;
                                fSearch();
                            }

                            onAccepted:
                            {
                                id_lvUser.m_bNewSelect = true;
                                fSearch();
                            }

                            function fSearch()
                            {
                                id_tSearch.m_iSearch = 0;

                                if(id_lvUser.m_bNewSelect)
                                {
                                    id_lvUser.m_bNewSelect = false;
                                    id_lmDesktopUser.clear();
                                }

                                if(id_tiLog.text.length > 0)
                                {
                                    root.fAddDesktop("0", "0");
                                    contextMain.slSearchDesktop(id_tiLog.text);
                                }
                            }

                        }
                    }


                }

                Timer
                {
                    id: id_tSearch
                    interval: 500; running: true; repeat: true
                    property int m_iSearch: 0
                    onTriggered:
                    {
                        m_iSearch++;

                        if(m_iSearch > 4)
                        {
                            m_iSearch = 0;
                            id_tiLog.fSearch();
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
                width: parent.width
                height: 1
                color: "#90000000"
            }

            ListView {
                id: id_lvUser
                width: parent.width;
                height: 140
                clip: true

                property string m_sLoginD: ""
                property string m_sIdD: ""
                property bool m_bNewSelect: false

                ScrollBar.vertical: ScrollBar
                {
                        policy: size < 1 ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                        //visible: size < 1

                        onSizeChanged:
                        {
                            for(var i = 0; i < id_lmDesktopUser.count; i++)
                            {
                                if(size < 1)
                                {
                                    id_lmDesktopUser.get(i).obScrollW = this.width + 1;
                                }
                                else
                                {
                                    id_lmDesktopUser.get(i).obScrollW = 0;
                                }
                            }
                        }
                }

                ListModel {
                    id: id_lmDesktopUser
                }


                model: id_lmDesktopUser
                delegate: id_comItem

                Component {
                        id: id_comItem
                        Item {
                            width: parent == null ? 1 : parent.width - obScrollW
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
                                            for(var i = 0, s = id_lmDesktopUser.count; i < s; i++)
                                            {
                                                id_lmDesktopUser.get(i).obSelect = false;
                                            }

                                            obSelect = true;
                                            root.m_bUserSelected = true;

                                            id_lvUser.m_sLoginD = obTitle
                                            id_lvUser.m_sIdD = obId

                                            if(!id_tiPass.cursorVisible)
                                            {
                                                id_tiPass.cursorPosition  = id_tiPass.text.length;
                                                id_tiPass.cursorVisible = true
                                                id_tiPass.forceActiveFocus();
                                            }
                                    }
                                }

                                Text {
                                    x: 5
                                    width: parent.width - 2*x
                                    anchors.verticalCenter: parent.verticalCenter
                                    //font.bold: true
                                    font.pointSize: 14
                                    text: obTitle // + "-" + obId + "-" + index
                                    color: obSelect ? "#80000000" : "white"
                                    clip: true
                                }

    //                            Rectangle
    //                            {
    //                                width: parent.width
    //                                height: 1
    //                                anchors.bottom: parent.bottom
    //                                color: "#cc000000"
    //                            }

                            }
                      }
                    }

            }

            Rectangle
            {
                width: parent.width
                height: 1
                color: "#90000000"
            }

            Item {
                width: 1
                height: 15
            }


            Item
            {
                width: parent.width
                height: children[0].height

                Text {
                    text: qsTr("Password:")
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
                                id_tiLog.update()
                        }
                    }
                }


                Rectangle
                {
                    height: children[0].height + 4
                    color: "#10000000"
                    anchors.bottom: parent.children[0].bottom
                    anchors.bottomMargin: -2
                    anchors.right: parent.right
                    //anchors.rightMargin: 5
                    anchors.left:  parent.children[0].right
                    anchors.leftMargin: 5

                    TextInput {
                        id: id_tiPass
                        width: parent.width - 4
                        anchors.centerIn: parent

                        text: ""
                        color: "#ffffff"
                        font.pixelSize: 20

                        clip: true

                        Component.onCompleted:
                        {
                           text = contextMain.slDeskPassword();
                        }

                    }
                }


            }

            Item {
                width: 1
                height: 20
            }

            Item {
                width: parent.width
                height: 50


                MyCheckBox {
                    id: id_chkScreen
                    checked: true
                    text: qsTr("Screen capture")
                    font.bold: true
                    font.pixelSize: 14

                    onPressed:
                    {
                            id_chkComandLine.checked = false
                            id_chkScreen.checked = false

                        //id_recNewConnect.fConnect(true);

                    }


                }

                MyCheckBox {
                    id: id_chkComandLine
                    anchors.right: parent.right
                    text: qsTr("Command line")
                    font.bold: true
                    font.pixelSize: 14

                    Component.onCompleted:
                    {
                        if(!contextMain.slComandLineStatus())
                        {
                            fChkComandLine(false);
                        }
                        else
                        {
                            fChkComandLine(true);
                        }
                    }




                    onPressed:
                    {
                            id_chkScreen.checked = false
                            id_chkComandLine.checked = false

                        //id_recNewConnect.fConnect(false);
                    }
                }
            }

            Item {
                width: 1
                height: 15
            }

            Item {
                width: parent.width
                height: children[0].height


                Rectangle
                {
                    id: id_recNewConnect
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
                                id_recNewConnect.fConnect(id_chkScreen.checked);
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("New connection")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#000000"
                    }

                    function fConnect(_bVar)
                    {
                        //print("fConnect 0: " + id_lvUser.m_sLoginD + " / " + id_tiPass.text + " / " + root.m_bUserSelected)

                        if( (root.m_bUserSelected
                             && (id_lvUser.m_sLoginD.length > 0 && id_tiPass.text.length > 0)
                                //|| (contextMain.slDeskLogin().length > 0 && contextMain.slDeskPassword().length > 0)
                                )
                            )
                        {
                            contextMain.slDisConnectDesktop(0);

                            contextMain.slUseComandLine(!_bVar);
                            contextMain.slConnectToDesktop(_bVar, id_lvUser.m_sLoginD, id_tiPass.text, id_lvUser.m_sIdD);

                        }
                        else
                        {
                            contextMain.slClientControl("308", 17, "Select user...");
                        }
                    }
                }

                Rectangle
                {
                    width: 20
                    height: 2
                    anchors.centerIn: parent
                    color: "#000000"
                    rotation: 0
                    visible: id_tConnect.running && id_lvUser.m_sLoginD.length > 0 && id_tiPass.text.length ? true : false

                    Timer
                    {
                        id: id_tConnect
                        interval: 10; running: false; repeat: true
                        onTriggered:
                        {
                            parent.rotation += 5;
                            if(parent.rotation > 360)
                                parent.rotation = 5;

                            if(!root.m_bUserSelected)
                                id_recDisConnect.fDisConnect();
                        }
                    }
                }

                Rectangle
                {
                    id: id_recDisConnect
                    width: id_recNewConnect.width
                    height: id_recNewConnect.height
                    anchors.right: parent.right
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
                                id_recDisConnect.fDisConnect();
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Disconnect")
                        font.bold: true
                        font.pixelSize: 14
                        color: "#000000"
                    }

                    function fDisConnect()
                    {
                        contextMain.slDisConnectDesktop(1);
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
