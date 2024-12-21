import QtQuick
import QtQuick.Controls.Basic

Rectangle {
    id: root
    objectName: "obMenuVideoQuality"
    width: parent.width
    color: "#808080"
    height: parent.height
    border.color: "#000000"
    border.width: 1

     property int m_iH: id_recTitle.height + id_colData.height + id_recCancel.height

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


    function fSetStatus(_iSizeF, _iFPS, _iEnvoderV, _iEncSpeed, _iBetrate, _iLatencyZ, _iStreamRTSP, _iSoundCapture)
    {
        switch(_iSizeF)
        {
        case 1:
            id_rbFS2.checked = true;
            break;
        case 2:
            id_rbFS3.checked = true;
            break;
        case 3:
            id_rb480.checked = true;
            break;
        default:
            id_rbFS1.checked = true;
            break;
        }

        id_slFPS.value = _iFPS;

        switch(_iEnvoderV)
        {
        case 1:
            id_rbGPU.checked = true;
            break;
        default:
            id_rbCPU.checked = true;
            break;
        }

        switch(_iEncSpeed)
        {
        case 1:
            id_rbSpeedE2.checked = true;
            break;
        case 2:
            id_rbSpeedE3.checked = true;
            break;
        case 3:
            id_rbSpeedE4.checked = true;
            break;
        default:
            id_rbSpeedE1.checked = true;
            break;
        }

        id_slBt.value = _iBetrate/10;

        id_cbLatZ.checked = _iLatencyZ;

        switch(_iStreamRTSP)
        {
        case 1:
            id_rbRTSP.checked = true;
            break;
        default:
            id_rbRTMP.checked = true;
            break;
        }

        id_cbSoundCapture.checked = _iSoundCapture;

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
            text: qsTr("- Video quality")
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

           Component.onCompleted:
           {
               contextMain.slVideoQualityStatus();
           }

          Item {
              width: 1
              height: 20
          }

           GroupBox {
               width: parent.width
               height: 70
               title: qsTr("Stream")
               font.bold: true
               font.pixelSize: 16

               //visible: false

               Component.onCompleted:
               {
                   if(contextMain.slStreamRTSP())
                   {
                       id_rbRTSP.checked = true
                       id_rbRTMP.checked = false
                   }
                   else
                   {
                       id_rbRTSP.checked = false
                       id_rbRTMP.checked = true
                   }
               }


               Row
               {
                   anchors.verticalCenter: parent.verticalCenter
                   height: 20                 

                   RadioButton {
                       id: id_rbRTMP
                       anchors.verticalCenter: parent.verticalCenter
                       text: qsTr("RTMP")
                       checked: true
                   }

                   RadioButton {
                       id: id_rbRTSP
                       width: 120
                       anchors.verticalCenter: parent.verticalCenter
                       text: qsTr("RTSP")
                       font.pixelSize: 16
                   }
               }
           }


           Item {
               width: 1
               height: 20
           }



           GroupBox {
               width: parent.width
               height: 70
               title: qsTr("Frame size")
               font.bold: true
               font.pixelSize: 16


               Row
               {
                   anchors.verticalCenter: parent.verticalCenter
                   height: 20

                   RadioButton {
                       id: id_rbFS1
                       width: 120
                       anchors.verticalCenter: parent.verticalCenter
                       checked: true
                       text: qsTr("Original")
                       font.pixelSize: 16

                   }

                   RadioButton {
                       id: id_rbFS2
                       width: 120
                       anchors.verticalCenter: parent.verticalCenter
                       text: qsTr("Full HD")
                       font.pixelSize: 16

                   }

                   RadioButton {
                       id: id_rbFS3
                       anchors.verticalCenter: parent.verticalCenter
                       text: qsTr("HD")


                   }

                   RadioButton {
                       id: id_rb480
                       anchors.verticalCenter: parent.verticalCenter
                       text: qsTr("480h")
                       visible: false


                   }
               }
           }


           Item {
               width: 1
               height: 10
           }


           GroupBox {
               width: parent.width
               height: 70
               title: qsTr("FPS")
               font.bold: true
               font.pixelSize: 16

               Row
               {
                   anchors.verticalCenter: parent.verticalCenter
                   height: 20



                   Slider {
                       id: id_slFPS
                       width: parent.parent.width - 85
                       anchors.verticalCenter: parent.verticalCenter
                       from: 10
                       value: 30
                       to: 60
                       stepSize: 5
                   }

                   Text {
                       width: 30
                       anchors.verticalCenter: parent.verticalCenter
                       text: "  " + (parent.children[0].value == 0 ? 1 : Math.round(parent.children[0].value) )
                       font.bold: true
                       font.pixelSize: 16
                       color: "#000000"
                   }


               }
           }


           Item {
               width: 1
               height: 10
           }

           GroupBox {
               width: parent.width
               height: 70
               title: qsTr("Encoder h.264")
               font.bold: true
               font.pixelSize: 16


               Row
               {
                   anchors.verticalCenter: parent.verticalCenter
                   height: 20

                   RadioButton {
                       id: id_rbCPU
                       width: 120
                       anchors.verticalCenter: parent.verticalCenter
                       checked: true
                       text: qsTr("use CPU")
                       font.pixelSize: 16
                   }

                   RadioButton {
                       id: id_rbGPU
                       anchors.verticalCenter: parent.verticalCenter
                       text: qsTr("use GPU")
                   }
               }
           }


           Item {
               width: 1
               height: 10
               visible: !id_rbGPU.checked
           }

           GroupBox {
               width: parent.width
               title: qsTr("Encoding speed")
               font.bold: true
               font.pixelSize: 16
               visible: !id_rbGPU.checked


               Column
               {
                   Row
                   {
                       RadioButton {
                           id: id_rbSpeedE1
                           width: 120
                           text: qsTr("ultrafast")
                           font.pixelSize: 16

                           onCheckedChanged:
                           {
                               if(checked)
                               {
                                   parent.parent.children[1].children[0].checked = false;
                                   parent.parent.children[1].children[1].checked = false;
                               }
                           }

                       }

                       RadioButton {
                           id: id_rbSpeedE2
                           checked: true
                           text: qsTr("veryfast")

                           onCheckedChanged:
                           {
                               if(checked)
                               {
                                   parent.parent.children[1].children[0].checked = false;
                                   parent.parent.children[1].children[1].checked = false;
                               }
                           }

                       }
                   }

                   Row
                   {
                       RadioButton {
                           id: id_rbSpeedE3
                           width: 120
                           text: qsTr("medium")
                           font.pixelSize: 16

                           onCheckedChanged:
                           {
                               if(checked)
                               {
                                   parent.parent.children[0].children[0].checked = false;
                                   parent.parent.children[0].children[1].checked = false;
                               }
                           }
                       }

                       RadioButton {
                           id: id_rbSpeedE4
                           text: qsTr("slower")

                           onCheckedChanged:
                           {
                               if(checked)
                               {
                                   parent.parent.children[0].children[0].checked = false;
                                   parent.parent.children[0].children[1].checked = false;
                               }
                           }
                       }
                   }
               }
           }


           Item {
               width: 1
               height: 10
           }

           GroupBox {
               width: parent.width
               height: 70
               title: qsTr("Bitrate")
               font.bold: true
               font.pixelSize: 16

               Row
               {
                   anchors.verticalCenter: parent.verticalCenter
                   height: 20

                   Slider {
                       id: id_slBt
                       width: id_slFPS.width
                       anchors.verticalCenter: parent.verticalCenter
                       from: 0.5
                       value: 4
                       to: 10
                       stepSize: 0.5
                   }

                   Text {
                       width: 30
                       anchors.verticalCenter: parent.verticalCenter
                       text: "  " + parent.children[0].value.toFixed(1) + " Mbit."
                       font.bold: true
                       font.pixelSize: 16
                       color: "#000000"
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

               MyCheckBox {
                   id: id_cbLatZ
                   x: 5
                   text: qsTr("Zero latency")
                   visible: !id_rbGPU.checked

               }

               MyCheckBox {
                   id: id_cbSoundCapture
                   anchors.right: parent.right
                   anchors.rightMargin: id_cbLatZ.x
                   text: qsTr("Sound capture")
               }


           }



           Item {
               width: 1
               height: 20
           }

           Item {
               width: parent.width
               height: children[0].height

               Rectangle
               {
                   width: parent.width/2 - 20
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
                               var a_iSizeF = 0;
                               if(id_rbFS2.checked)
                                   a_iSizeF = 1;
                               else
                               if(id_rbFS3.checked)
                                   a_iSizeF = 2;
                               else
                               if(id_rb480.checked)
                                   a_iSizeF = 3;

                               var a_iEnvoderV = 0;
                               if(id_rbGPU.checked)
                                   a_iEnvoderV = 1;


                               var a_iEncSpeed = 0;
                               if(id_rbSpeedE2.checked)
                                   a_iEncSpeed = 1;
                               else
                               if(id_rbSpeedE3.checked)
                                   a_iEncSpeed = 2;
                               else
                               if(id_rbSpeedE4.checked)
                                   a_iEncSpeed = 3;


                               var a_iLatencyZ = 0;
                               if(id_cbLatZ.checked)
                                   a_iLatencyZ = 1;

                               var a_iSound = 0;
                               if(id_cbSoundCapture.checked)
                                   a_iSound = 1;

                               contextMain.slVideoQualityGet(a_iSizeF, id_slFPS.value, a_iEnvoderV,  a_iEncSpeed, 10*id_slBt.value, a_iLatencyZ, id_rbRTSP.checked, a_iSound);
                       }
                   }

                   Text {
                       anchors.centerIn: parent
                       text: qsTr("Apply")
                       font.bold: true
                       font.pixelSize: 14
                       color: "#000000"
                   }
               }




               Item
               {
                   width: children[1].width + 20
                   height: children[1].height + 20

                   anchors.right: parent.right
                   anchors.verticalCenter: parent.verticalCenter

                   opacity: children[0].pressed ? 0.6 : 1.0


                   MouseArea
                   {
                       anchors.fill: parent

                       onPressed:
                           (mouse)=>
                       {

                               id_slFPS.value = 30;
                               id_rbFS1.checked = true;
                               id_rbCPU.checked = true;
                               id_rbSpeedE2.checked = true;
                               id_slBt.value = 2.5;
                               id_cbLatZ.checked = true;
                               id_cbSoundCapture.checked = false;
                       }
                   }

                   Text {
                       anchors.centerIn: parent
                       text: qsTr("Default propertys")
                       font.underline: true
                       font.bold: true
                       font.pixelSize: 16
                       color: "#90000000"
                   }
               }

           }


           Item {
               width: 1
               height: 10
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
