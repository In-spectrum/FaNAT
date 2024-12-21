import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    x: 70
    y:30
    width: 900
    height: 700
    //visibility: Window.Maximized
    visible: true    
    title: ""


    Component.onCompleted:
    {
        id_tStart.start();

        title = contextMain.slAppName()
    }

    Component.onDestruction:
    {
        contextMain.slotDestruction();
    }

    function fFullScreen(_bVar)
    {
        if(visibility != Window.FullScreen)
            visibility = Window.FullScreen
        else
            visibility = Window.Maximized
    }


    Loader {
       id: id_loadUserUI
       anchors.fill: parent
       focus: true

       source:"userUI.qml";

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
          //print("id_loadUserUI::slotData 0: " + _iId)


       }

    }


    Timer
    {
        id: id_tStart
        interval: 1000; running: false; repeat: false
        onTriggered:
        {
            contextMain.slotFindCheldren();
        }
    }

    Timer
    {
        id: id_tCurrentTime
        interval: 1000; running: true; repeat: true
        onTriggered:
        {
           contextMain.slotTimer()
        }
    }

}
