import QtQuick 2.12
import QtMultimedia 5.15

Rectangle {
    id: root
    objectName: "obUserUI"
    anchors.fill: parent
    color: "#0047AB"
    //color: "#ff0000"


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


    Loader {
       id: id_loadPlayer
       anchors.fill: parent
       focus: true

       source: contextMain.slPlayerVar() === 0 ? "playerNew.qml" : "player.qml";

       onLoaded:
       {
           item.signalData.connect(slotData)
       }

       Component.onDestruction: {
                   if (item) {
                       item.signalData.disconnect(slotData)
                   }
               }


       function slotData(_iId, _vData_1, _vData_2, _vData_3, _vData_4, _vData_5, _vData_6)
       {
          //print("id_loadPlayer::slotData 0: " + _iId)


       }

    }

    Loader {
       id: id_loadMenu
       anchors.fill: parent

       source:"menu.qml";

       onLoaded:
       {
           item.signalData.connect(slotData)
       }

       Component.onDestruction: {
                   if (item) {
                       item.signalData.disconnect(slotData)
                   }
               }


       function slotData(_iId, _vData_1, _vData_2, _vData_3, _vData_4, _vData_5, _vData_6)
       {
          //print("id_loadPlayer::slotData 0: " + _iId)


       }

    }

    Loader {
       id: id_loadMessageStatus
       anchors.fill: parent

       source:"messageStatus.qml";

       visible: false

       onLoaded:
       {
           item.signalData.connect(slotData)
       }

       Component.onDestruction: {
                   if (item) {
                       item.signalData.disconnect(slotData)
                   }
               }


       function slotData(_iId, _vData_1, _vData_2, _vData_3, _vData_4, _vData_5, _vData_6)
       {
          //print("id_loadMessageStatus::slotData 0: " + _iId)

           switch(_iId)
           {
               case 0:
                   id_loadMessageStatus.visible = false;
                   break;
           }


       }

    }

}
