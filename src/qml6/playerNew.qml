import QtQuick
import QtMultimedia

Item {
    id: root
    objectName: "obVideo"
    anchors.fill: parent
    focus: true

    property bool m_bFocus: parent.focus
    property bool m_bFrameRealSize: true
    property string m_sURL: ""
    property int m_iPlayRestart: 0
    property int m_iRestartNew: 0
    property bool m_bReConnect: false
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
            //print("Keys.onPressed 0:")

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
        anchors.fill: parent

        onReleased: (mouse)=>
        {

        }
    }


    function fTimer()
    {
        fVideoReload();
    }

    function fDescktopRealSize(_bVar)
    {
         root.m_bFrameRealSize = !root.m_bFrameRealSize;
    }

    function fVideoStartStop(_sUrl, _iVar)
    {
        //print("fVideoStartStop 0: " + _sUrl);

        root.m_iRestartNew = 0;
        root.m_iPlayRestart = 0;
        id_Player.m_bFrameNew = true;
        id_Player.m_iFramePrew = 0;


        if(_sUrl.length > 0)
        {
            m_iFPS = m_iDataFPS = m_iShowFPS = 0;

            root.fPlay(_sUrl, _iVar)
        }
        else
            root.fPlay("", 0)

    }


    function fVideoReload()
    {

        //print("fVideoReload 0: " + root.m_iRestartNew + " / " + m_iPlayRestart);

        if(id_Player.m_iFramePrew < 0)
        {
            id_Player.m_bFrameNew = false;

            if(root.m_iRestartNew < 6 && root.m_sURL.length > 0)
            {
                //print("fVideoReload 1: " + root.m_iRestartNew);

                root.m_iPlayRestart++;

                if(root.m_iPlayRestart > 10)
                {
                    //print("fVideoReload 2: " + root.m_iPlayRestart);


                    // if(root.m_bReConnect)
                    //     fPlay(root.m_sURL, 1);
                    // else
                        contextMain.slReConnectToDesktop();

                    root.m_bReConnect = !root.m_bReConnect;

                    root.m_iPlayRestart = 0;

                    root.m_iRestartNew++;
                }
            }
            else
                root.m_sURL = "";

        }
        else
        {
            id_Player.m_bFrameNew = true;

            root.m_iDataFPS = root.m_iFPS;

            //print("fVideoReload 5.0: " + root.m_iDataFPS);

            if(root.m_iDataFPS > 0 && root.m_iDataFPS < 3 && root.m_sURL.length > 0)
            {
                root.m_iLowFPS++;
                if(root.m_iLowFPS > 3)
                {
                    //print("fVideoReload 5.1: ");

                    root.m_iLowFPS = 0;
                    root.fPlay("", 0)
                    //root.fPlay(root.m_sURL, 1)
                    contextMain.slReConnectToDesktop();
                    //root.fPlay("gst-pipeline: rtspsrc location=rtsp://127.0.0.1:8504/live/111 ! queue ! decodebin3 ! videoconvert  ! qtvideosink", 1)
                }
            }
            else
                root.m_iLowFPS = 0;

            root.m_iFPS = 0;

            if(root.m_iShowFPS == 60)
                root.m_iShowFPS = 0;

        }

        id_Player.m_iFramePrew = -1;


        if(root.m_iShowFPS < 60)
            root.m_iShowFPS++;


    }


    function fPlay(_sUrl, _iPlay)
    {
        id_Player.source = ""

        root.m_sURL = _sUrl;

        //print("fPlay 0: url = " + root.m_sURL);

        if(_iPlay > 0)
        {

            if(_iPlay == 1)
            {
                if(root.m_sURL.length > 0)
                    root.m_iShowFPS = 60;


                id_Player.source = root.m_sURL;
                id_Player.play();
            }
            else
                id_Player.pause()
        }
        else
        {
            id_Player.stop();
        }

        if(root.m_sURL.length > 0)
            id_Player.m_iFramePrew = -1;
        else
            id_Player.m_iFramePrew = 0;
    }


    Item {
        id: id_itBoxVideo
        anchors.centerIn: parent

        height: m_iTempFrameH * m_dKWH > m_iDrawFrameW ? m_iDrawFrameW / m_dKWH : m_iTempFrameH
        width: m_iTempFrameH * m_dKWH > m_iDrawFrameW ? m_iDrawFrameW : m_iTempFrameH * m_dKWH


        property int m_iFrameW: id_videoOutput.sourceRect.width
        property int m_iFrameH: id_videoOutput.sourceRect.height
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

                           if(root.m_sURL.length > 0 && root.m_iPlayRestart < 2)
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

                if(root.m_sURL.length > 0 && root.m_iPlayRestart < 2)
                contextMain.slSendMouseEvent(3, a_bBtLeftPressed, 0
                                             , 100 * (100 * mouseX/parent.width)
                                             , 100 * (100 * mouseY/parent.height) );
            }

        }


        MediaPlayer {
               id: id_Player
               source: ""
               //source: "rtmp://localhost/111/ live=1"
               //source: "gst-pipeline: rtmpsrc location='rtmp://localhost/111/ live=1' ! queue ! decodebin3 ! videoconvert ! qtvideosink"
               //source: "gst-pipeline: rtmpsrc location='rtmp://localhost/111/ live=1' ! queue ! decodebin3 ! videoconvert ! vpudec ! fpsdisplaysink video-sink=glimagesink

               //autoPlay: true
               videoOutput: id_videoOutput

               property bool m_bFrameNew: false
               property int m_iFramePrew: 0


               onMediaStatusChanged:
               {
                   var a_sVar = "";


                   print("player status: code " + mediaStatus);

                   // if(status != 2 && status != 6)
                     //print("player 1: status: \n    src: " + source + "\n    code: " + mediaStatus + "\n    " + a_sVar);


                   // print("player 2: " + source.toString().length);


               }


               onErrorChanged:
               {
                   var a_sVar = "";


                   print("player error: code " + error);
                   //print("player error: \n    src: " + source + "\n    code: " + error + "\n    " + a_sVar  + "\n    " + errorString);

               }



               onPositionChanged :
               {
                   contextMain.slUpdateFrame(1, 1, 0);

                   root.m_iRestartNew = 0;
                   root.m_iPlayRestart = 0;
                   id_Player.m_bFrameNew = true;
                   id_Player.m_iFramePrew++;

                   if(id_Player.m_iFramePrew > 100000)
                       id_Player.m_iFramePrew = 1

                   root.m_iFPS++;

                   //print("id_Player 1: " + id_Player.m_iFramePrew + " / " + id_Player.m_bFrameNew + " / " + id_Player.position)

               }

           }

        VideoOutput {
            id: id_videoOutput
            anchors.fill: parent
        }

    }

    Item {
        id: id_itLoading
        anchors.right: parent.right
        anchors.rightMargin: y
        y:2
        rotation: 0
        visible: root.m_sURL.length > 0 && !id_Player.m_bFrameNew ? true : false

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


    Rectangle
    {
        x: 3
        y: 3
        width: children[0].width + 5
        height: children[0].height + 10
        visible: false //root.m_sURL.length > 0 && root.m_iShowFPS > 0 && root.m_iShowFPS < 30 && !id_itLoading.visible ? true : false

        Text {
            anchors.centerIn: parent
            text: root.m_iDataFPS + qsTr(" fps")
            font.bold: true
            font.pixelSize: 20
            color: "#ff0000"
        }
    }

}
