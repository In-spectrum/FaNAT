import QtQuick 2.12


Item {
    id: root
    objectName: "obVideo"
    anchors.fill: parent
    focus: true

    property bool m_bFocus: parent.focus
    property bool m_bFrameRealSize: true
    property bool m_bPlay: false
    property int m_iFrame: -1;
    property int m_iFramePrew: -1;
    property int m_iRestartNew: 0
    property int m_iPlayRestart: 0

    property int m_iFPS: 0
    property int m_iDataFPS: 0
    property int m_iLowFPS: 0
    property int m_iShowFPS: 60

    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)

    onM_bFocusChanged:
        root.focus = m_bFocus;

    Component.onCompleted:
    {
    }

    Component.onDestruction:
    {

    }

    Keys.onPressed:
        (event)=>
        {
            contextMain.slSendKeyEvent(1, event.key, event.text);
            event.accepted = true;
    }

    Keys.onReleased:
        (event)=>
        {
            contextMain.slSendKeyEvent(2, event.key, event.text);
            event.accepted = true;
    }


    MouseArea
    {
        id: id_mouseMain
        anchors.fill: parent

        property int a_iMousStartX : 0
        property int a_iMousStartY : 0
        property int a_iMove : 0
        property bool a_bDoubleClicked: false

        onWheel: (wheel)=> {

            if(wheel.angleDelta.y > 0)
            {
            }
            else
            {
                if(wheel.angleDelta.y < 0)
                {

                }
            }
       }

        onPositionChanged:
        {
            if(id_tMouseMainLongPress.running)
            {
                id_tMouseMainLongPress.m_iLongPress = 0
                id_tMouseMainLongPress.stop();
            }

            if( a_bDoubleClicked )
            {
                a_bDoubleClicked = false;
                id_tMouseMainDoubleClicked.stop()
            }

            if(Math.abs( mouseY - id_mouseMain.a_iMousStartY ) > Math.abs( mouseX - id_mouseMain.a_iMousStartX ))
            {
                if(Math.abs( mouseY - id_mouseMain.a_iMousStartY ) > 5)
                {
                    id_mouseMain.a_iMousStartY = mouseY
                }
            }
            else
            {
                id_mouseMain.a_iMove = mouseX - id_mouseMain.a_iMousStartX;
                id_mouseMain.a_iMousStartX = mouseX;

            }


        }

        onPressed: (mouse)=>
        {

            root.parent.focus = true;

            id_mouseMain.a_iMousStartX = mouseX;
            id_mouseMain.a_iMousStartY = mouseY;

                       if(!id_tMouseMainDoubleClicked.running)
                       {
                           a_bDoubleClicked = false;
                           id_tMouseMainDoubleClicked.start()
                       }
                       else
                       {
                           a_bDoubleClicked = true;
                       }

                       id_tMouseMainLongPress.m_iLongPress = 0
                       id_tMouseMainLongPress.start();
        }

        onReleased: (mouse)=>
        {
            id_mouseMain.a_iMousStartX = 0;
            id_mouseMain.a_iMousStartY = 0;


                        if( a_bDoubleClicked )
                        {
                            a_bDoubleClicked = false;
                            id_tMouseMainDoubleClicked.stop()
                        }
                        else
                        {
                            if( id_mouseMain.a_iMove == 0 )
                            {


                            }
                        }

                        id_tMouseMainLongPress.m_iLongPress = 0
                        id_tMouseMainLongPress.stop();

                        id_mouseMain.a_iMove = 0;
        }

        Timer
        {
            id: id_tMouseMainDoubleClicked
            interval: 200;
            repeat: false

            onTriggered:
            {
            }
        }

        Timer
        {
            id: id_tMouseMainLongPress
            interval: 200;
            repeat: true

            property int m_iLongPress: 0

            onTriggered:
            {
                m_iLongPress++;

                if(m_iLongPress > 4)
                {
                    m_iLongPress = 0;
                    stop();
                }
            }
        }

    }


    function fTimer()
    {
        if(m_bPlay && id_itLoading.m_bLoading < 10)
            id_itLoading.m_bLoading++;

        fVideoReload();
    }

    function fVideoStartStop(_sData, _iVar)
    {
        root.m_iRestartNew = root.m_iPlayRestart = 0;

        if(_iVar > 0)
        {
            m_bPlay = true;
        }
        else
        {
            m_bPlay = false;

        }

        id_itLoading.m_bLoading = 5;
        root.m_iFrame = root.m_iFramePrew = -1;

    }

    function fVideoReload()
    {
        //print("fVideoReload 0: " + root.m_iRestartNew + " / " + m_iPlayRestart);

        if(!root.m_bPlay)
            return;

        if(root.m_iFramePrew == root.m_iFrame)
        {
            if(root.m_iRestartNew < 6)
            {
                //print("fVideoReload 1: " + root.m_iRestartNew);

                root.m_iPlayRestart++;

                if(root.m_iPlayRestart > 10)
                {
                    //print("fVideoReload 2: " + root.m_iPlayRestart);

                    contextMain.slReConnectToDesktop();

                    root.m_iPlayRestart = 0;

                    root.m_iRestartNew++;
                }
            }
            else
            {
                contextMain.slDisConnectDesktop(1);
            }
        }

        root.m_iFramePrew = root.m_iFrame;

    }



    function fDescktopRealSize(_bVar)
    {
         root.m_bFrameRealSize = !root.m_bFrameRealSize;
    }



    function updateFrame(_uFrameCounter, _iWf, _iHf)
    {
        id_itLoading.m_bLoading = 0;

        id_imVideo.source = "image://streamNum_"
                + "1"
                + "/stream_"
                + _uFrameCounter;

        id_imVideo.m_iFrameW = _iWf;
        id_imVideo.m_iFrameH = _iHf;

        root.m_iFrame = _uFrameCounter;
        root.m_iRestartNew = root.m_iPlayRestart = 0;
    }



    Image {
        id:id_imVideo
        anchors.centerIn: parent

//        height: m_iTempFrameH * m_dKWH > parent.width ? parent.width / m_dKWH : m_iTempFrameH
//        width: m_iTempFrameH * m_dKWH > parent.width ? parent.width :  m_iTempFrameH * m_dKWH

        height: m_iTempFrameH * m_dKWH > m_iDrawFrameW ? m_iDrawFrameW / m_dKWH : m_iTempFrameH
        width: m_iTempFrameH * m_dKWH > m_iDrawFrameW ? m_iDrawFrameW : m_iTempFrameH * m_dKWH

        //source: "image/save.png"

        property int m_iFrameW: 0
        property int m_iFrameH: 0

        property int m_iTempFrameH: !root.m_bFrameRealSize || m_iFrameW > parent.width || m_iFrameH > parent.height ?  parent.height : m_iFrameH
        property double m_dKWH : m_iFrameW / m_iFrameH

        property int m_iDrawFrameW: !root.m_bFrameRealSize || m_iFrameW > parent.width || m_iFrameH > parent.height ? parent.width : m_iFrameW

        MouseArea
        {
            id: id_mouseVideo
            anchors.fill: parent
            hoverEnabled: true

            property var a_bBtPress: [false, false]
            property bool a_bBtLeftPressed: false


            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onWheel: (wheel)=> {

                if(wheel.angleDelta.y > 0)
                {
                }
                else
                {
                    if(wheel.angleDelta.y < 0)
                    {

                    }
                }

                         contextMain.slSendMouseEvent(4, wheel.angleDelta.y < 0 ? 0 : 1
                                                      , 1
                                                      , 100 * (100 * mouseX/parent.width)
                                                      , 100 * (100 * mouseY/parent.height) );
           }


            onPressed: (mouse)=>
            {
                           root.parent.focus = true;

                           a_bBtLeftPressed = false;

                           if (mouse.button === Qt.RightButton)
                           {
                               a_bBtPress[1] = true;
                           }
                           else
                           if (mouse.button === Qt.LeftButton)
                           {
                               a_bBtPress[0] = true;

                               a_bBtLeftPressed = true;
                           }

                           contextMain.slSendMouseEvent(1, a_bBtLeftPressed, 1
                                                        , 100 * (100 * mouseX/parent.width)
                                                        , 100 * (100 * mouseY/parent.height) );

                           //print("onPressed 5: " + a_bBtLeftPressed + " / " + a_bBtPress + " / " + mouseX + " / " + mouseY);

            }

            onReleased: (mouse)=>
            {
                            a_bBtLeftPressed = false;

                            if (mouse.button === Qt.RightButton)
                            {
                                a_bBtPress[1] = false;
                            }
                            else
                            if (mouse.button === Qt.LeftButton)
                            {
                                a_bBtLeftPressed = true;

                                a_bBtPress[0] = false;
                            }

                            contextMain.slSendMouseEvent(2, a_bBtLeftPressed, 0
                                                         , 100 * (100 * mouseX/parent.width)
                                                         , 100 * (100 * mouseY/parent.height) );

                            //print("onReleased 5: " + a_bBtLeftPressed + " / " + a_bBtPress + " / " + mouseX + " / " + mouseY);

            }

            onPositionChanged:
            {
                //print("onPositionChanged 5: " + a_bBtLeftPressed + " / " + a_bBtPress + " / " + mouseX + " / " + mouseY);

                //print("onReleased 5: " + id_imVideo.width + " / " + mouseX + " / " + (100 * mouseX/id_imVideo.width) + " / " + 100 * (100 * mouseX/id_imVideo.width));


                contextMain.slSendMouseEvent(3, a_bBtLeftPressed, 0
                                             , 100 * (100 * mouseX/parent.width)
                                             , 100 * (100 * mouseY/parent.height) );
            }

        }


    }

    Item {
        id: id_itLoading
        anchors.right: parent.right
        anchors.rightMargin: y
        y:2
        rotation: 0
        visible: m_bPlay && m_bLoading > 2 ? true : false

        property real m_bLoading: 3

        property int size: 40
        property int lineWidth: 5
        property real value: 0

        property color primaryColor: "#99ff0000"
        property color secondaryColor: "#00e0e0e0"

        property int animationDuration: 1000

        width: size
        height: size

        onValueChanged: {
            canvas.degree = value * 360;
        }

        Canvas {
            id: canvas

            property real degree: 250

            anchors.fill: parent
            antialiasing: true

            onDegreeChanged: {
                requestPaint();
            }

            onPaint: {
                var ctx = getContext("2d");

                var x = id_itLoading.width/2;
                var y = id_itLoading.height/2;

                var radius = id_itLoading.size/2 - id_itLoading.lineWidth
                var startAngle = (Math.PI/180) * 270;
                var fullAngle = (Math.PI/180) * (270 + 360);
                var progressAngle = (Math.PI/180) * (270 + degree);

                ctx.reset()

                ctx.lineCap = 'round';
                ctx.lineWidth = id_itLoading.lineWidth;

                ctx.beginPath();
                ctx.arc(x, y, radius, startAngle, fullAngle);
                ctx.strokeStyle = id_itLoading.secondaryColor;
                ctx.stroke();

                ctx.beginPath();
                ctx.arc(x, y, radius, startAngle, progressAngle);
                ctx.strokeStyle = id_itLoading.primaryColor;
                ctx.stroke();
            }

            // Behavior on degree {
            //     NumberAnimation {
            //         duration: root.animationDuration
            //     }
            // }
        }

        Timer
        {
            interval: 50; running: parent.visible; repeat: true
            onTriggered:
            {
                parent.rotation += 30;

                if(parent.rotation > 360)
                {
                    parent.rotation -= 360;
                }
            }
        }

    }

}
