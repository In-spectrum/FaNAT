import QtQuick 2.12
import QtMultimedia 5.12

Item {
    id: root
    objectName: "obPlayerRtsp"
    anchors.fill: parent


    signal signalData(int _iId, var _vData_1, var _vData_2, var _vData_3, var _vData_4, var _vData_5, var _vData_6)


    Component.onCompleted:
    {
    }

    Component.onDestruction:
    {

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

    function fSetUrl(_sUrl)
    {
        print(_sUrl);

       id_vRTSP.source = _sUrl;
       id_vRTSP.source = "gst-launch-1.0 /udpsrc port=5012 ! application/x-rtp, encoding-name=H264, payload=96 ! rtph264depay ! queue ! h264parse ! avdec_h264 ! videoconvert ! autovideosink"
       id_vRTSP.play();
    }



//    Video {
//            id: id_vRTSP
//            anchors.fill: parent
//            source: ""
//            autoPlay: false
//            opacity: 1.0
//            fillMode: Image.Stretch
//            muted: false
//        }

    MediaPlayer {
           id: id_vRTSP
           source: ""
           muted: false
           autoPlay: false
       }

       VideoOutput {
           id: camera1
           anchors.fill: parent
           source: id_vRTSP
       }

}
