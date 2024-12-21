#include "control.h"

#ifdef Q_OS_ANDROID

#else
#ifdef Q_OS_WIN
#include <windows.h>
#else
#ifdef Q_OS_LINUX
//#include <X11/Xlib.h>
//sudo apt-get install libxtst-dev
#include <X11/extensions/XTest.h>
#endif
#endif
#endif




Control::Control(QQmlApplicationEngine *_pApp)
{
    m_pApp = _pApp;
    m_obMain = m_obVideo = m_obMenu = nullptr;


    fKeyEventClear();

    fGenerateLogPass();

}

Control::~Control()
{
    qDebug() << "Control::~Control 0: ";
}

void Control::slotDestruction()
{
    m_obMain = nullptr;
    m_obVideo = nullptr;
    m_obMenu = nullptr;

    fClientDisconnect();

    int a_iStop = 0;
    while (a_iStop < 5 * 10
           && m_iThClientSoc > 0
           )
    {
        //qDebug() << "Control::slotDestruction 4:" << a_iStop  << m_iThClientSoc;
        QThread::msleep(100);
        a_iStop++;
    }

    QThread::msleep(1000);

    qDebug() << "Control::slotDestruction 200: " << a_iStop  << m_iThClientSoc;
}

void Control::slotFindCheldren()
{
    m_obMain = m_pApp->rootObjects().first();
    m_obVideo = m_obMain->findChild<QObject*>("obVideo");
    m_obMenu = m_obMain->findChild<QObject*>("obMenu");

    slConnectToServer(StaticData::m_sLogin, StaticData::m_sPassword);
}

void Control::slotTimer()
{
    emit sgTimer();

    fConnectClientStatus();

    if(m_iTimeForBuffer < 10)
        m_iTimeForBuffer++;

    if(m_obVideo)
    {
        QMetaObject::invokeMethod(m_obVideo, "fTimer");
    }

    fNewStream();
}


void Control::fStreamReaderDelete(QQmlEngine *_engineMain)
{
    //qDebug() << "fStreamReaderDelete 0: ";


    StaticData::m_iTimeForStream = 10;
    m_iNewStream = 5;
    m_bErrStream = false;


    //qDebug() << "fStreamReaderDelete 10: ";
}

QString Control::fStreamReadGST()
{
    //gst-pipeline: rtmpsrc location='rtmp://localhost/111/ live=1' ! queue ! decodebin ! videoconvert ! qtvideosink
    QString rtpCamStr;

    //if( slStreamRTSP() )
    {
        rtpCamStr = "";
        rtpCamStr.append(QLatin1String("rtsp://"));
        rtpCamStr.append( slServerIP() );
        rtpCamStr.append(QLatin1String(":"));
        rtpCamStr.append( QString::number( slPortRTSP() ) );
        rtpCamStr.append(QLatin1String("/live/"));
        rtpCamStr.append(m_sNewStreamUrl);
    }
    // else
    // {
    //     #ifdef Q_OS_WIN

    //             rtpCamStr = "";
    //             rtpCamStr.append(QLatin1String("rtsp://"));
    //             rtpCamStr.append( slServerIP() );
    //             rtpCamStr.append(QLatin1String(":"));
    //             rtpCamStr.append( QString::number( slPortRTSP() ) );
    //             rtpCamStr.append(QLatin1String("/live/"));
    //             rtpCamStr.append(m_sNewStreamUrl);
    //     #else
    //             rtpCamStr = "";
    //             rtpCamStr.append(QLatin1String("rtmp://"));
    //             rtpCamStr.append( slServerIP() );
    //             rtpCamStr.append(QLatin1String(":"));
    //             rtpCamStr.append( QString::number( slPortRTMP() ) );
    //             rtpCamStr.append(QLatin1String("/live/"));
    //             rtpCamStr.append(m_sNewStreamUrl);
    //             //rtpCamStr.append(QLatin1String("/"));
    //             //rtpCamStr.append(QLatin1String(" live=1"));
    //     #endif
    // }

    rtpCamStr = rtpCamStr.replace("localhost", "127.0.0.1");

    //qDebug() << "fStreamReadGST 10: " << rtpCamStr;

    return rtpCamStr;
}

void Control::fConnectToServer(QString _sIp, int _iPort, QString _sLogin, QString _sPassword)
{
    emit sgClientStop();

    QThread::msleep(55);

    // Every new connection will be run in a newly created thread
    NewClient *a_thread = new NewClient(_sIp, _iPort, _sLogin, _sPassword, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(a_thread, SIGNAL(finished()), a_thread, SLOT(deleteLater()));
    connect(a_thread, &NewClient::sgControl, this, &Control::slClientControl);
    connect(a_thread, SIGNAL(finished()), this, SLOT(slThClientFin()), Qt::DirectConnection);
    connect(this, SIGNAL(sgClientStop()), a_thread, SLOT( slStop()));
    connect(this, &Control::sgSendMassang, a_thread, &NewClient::slAddDataWrite, Qt::QueuedConnection);
    connect(this, &Control::sgSendMouseEvent, a_thread, &NewClient::slSendMouseEvent);
    connect(this, &Control::sgSendKeyEvent, a_thread, &NewClient::slSendKeyEvent);
    connect(this, &Control::sgTimer, a_thread, &NewClient::slTimer);
    connect(this, &Control::sgControl, a_thread, &NewClient::slControl, Qt::QueuedConnection);

    m_mtxThClientSoc.lock();
    //qDebug() << "Control::fConnectToServer 5.0: " << m_iThClientSoc;
    m_iThClientSoc++;
    //qDebug() << "Control::fConnectToServer 5.1: " << m_iThClientSoc;
    m_mtxThClientSoc.unlock();
    a_thread->start();
}

void Control::slConnectToServer(QString _sLogin, QString _sPassword)
{
    fStreamReadClear();

    if(_sLogin.length() == 0 || _sPassword.length() == 0)
        return;

    StaticData::m_sLogin = _sLogin;
    StaticData::m_sPassword = _sPassword;

    slClientControl("", 3, "0");

    //fConnectToServer("192.168.1.189", StaticData::m_sPortTCP, StaticData::m_sLogin, StaticData::m_sPassword);
    //fConnectToServer("127.0.0.1", StaticData::m_sPortTCP, StaticData::m_sLogin, StaticData::m_sPassword);
    fConnectToServer(slServerIP(), slPortTCP(), StaticData::m_sLogin, StaticData::m_sPassword);
}

void Control::slDisConnectDesktop(int _bVar)
{

    m_bDisconnect = _bVar > 0 ? true : false;

    if(_bVar == 1)
    {
        fStreamReadClear();

        m_bStream = false;

        if(m_obVideo && !m_bStream)
        {
            QMetaObject::invokeMethod(m_obVideo, "fVideoStartStop"
                                      , Q_ARG(QVariant, "")
                                      , Q_ARG(QVariant, 0) );
        }

        emit sgSendMassang( MyProtocol::fConnectToDesktop("0", "0", StaticData::m_sDeskId, m_bStream) );



        StaticData::m_sDeskLogin = "";
        StaticData::m_sDeskPassword = "";
        StaticData::m_sDeskId = "";

        fConnectClientStatus();
        fStatusConnectToDesktop(false);
    }
    else
    {
        if(_bVar == 2)
        {
            fStreamReadClear();

            m_bStream = false;

            if(m_obVideo && !m_bStream)
            {
                QMetaObject::invokeMethod(m_obVideo, "fVideoStartStop"
                                          , Q_ARG(QVariant, "")
                                          , Q_ARG(QVariant, 0) );
            }

            emit sgSendMassang( MyProtocol::fConnectToDesktop("0", "0", "0", m_bStream) );
            StaticData::m_sDeskId = "";

            fConnectClientStatus();
            fStatusConnectToDesktop(false);
        }
    }

}

void Control::slConnectToDesktop(bool _bStream, QString _sLogin, QString _sPassword, QString _sId)
{
    //qDebug() << "Control::slConnectToDesktop 0: " << _bStream;

    m_bStream = _bStream;

    if(m_obVideo && !m_bStream)
    {
        QMetaObject::invokeMethod(m_obVideo, "fVideoStartStop"
                                  , Q_ARG(QVariant, "")
                                  , Q_ARG(QVariant, 0) );
    }

    fStreamReadClear();


    if(_sLogin.length() > 0
        && _sPassword.length() > 0
        && _sId.length() > 0 )
    {

        fStatusConnectToDesktop(false);

        StaticData::m_sDeskLogin = _sLogin;
        StaticData::m_sDeskPassword = _sPassword;
        StaticData::m_sDeskId = _sId;

        emit sgSendMassang( MyProtocol::fConnectToDesktop(StaticData::m_sDeskLogin, StaticData::m_sDeskPassword, StaticData::m_sDeskId, m_bStream) );
    }


}

void Control::slClientControl(QString _sId, int _iVar, QString _sData)
{
    //qDebug() << "Control::slClientControl 0: " << _sId << _iVar << _sData;

    switch (_iVar) {
    case 0:

        //qDebug() << "Control::slClientControl 0.1: " << _sId << _iVar << _sData;

        m_iTimeConnectNotActive = 10;
        fConnectClientStatus();

        break;
    case 1:
    {
        m_iTimeStreamWrite = 0;

        emit sgSendMassang( MyProtocol::fVideoQualityCurent( StaticData::m_sDeskId, StaticData::m_sMyId
                                                           , StaticData::_iCurSizeFr,  StaticData::_iCurFPS,  StaticData::_iCurEnvoderV
                                                           , StaticData::_iCurEncSpeed,  StaticData::_iCurBetrate, StaticData::_iCurLatencyZ
                                                           , StaticData::_iCurStreamRTSP, StaticData::_iCurSoundCapture)
                           );

        if(_sData != m_sCurrentWriteUrl)
        {
            //qDebug() << "Control::slClientControl 1.1: " << m_sCurrentWriteUrl << _sData;

        }

        m_sCurrentWriteUrl = _sData;

        //qDebug() << "Control::slClientControl 1.2: " << _sId << _iVar << _sData;

    }
    break;
    case 2:
    {
        if(m_sNewStreamUrl != _sData)
        {
            m_iNewStream = 0;

            //qDebug() << "Control::slClientControl 2.1: " << m_sNewStreamUrl << _sData;
        }

        m_sNewStreamUrl = _sData;
        m_bErrStream = false;

        if(_sData == StaticData::m_sWithoutStream)
        {
            //qDebug() << "Control::slClientControl 2.2: " << _sId << _iVar << _sData;

            slDisConnectDesktop(2);


            if(m_obMain)
            {

                QObject *a_Ob = m_obMain->findChild<QObject*>("obMessageStatus");
                if(a_Ob)
                {
                    QMetaObject::invokeMethod(a_Ob, "fStatus"
                                              , Q_ARG(QVariant, 102)
                                              , Q_ARG(QVariant, "User '" + StaticData::m_sDeskLogin
                                                                  + "' not support screen capture."
                                                                  + "\nOnly command line use.")
                                              );
                }

            }
        }

        //qDebug() << "Control::slClientControl 2.3: " << m_sNewStreamUrl << _sData;

    }
    break;
    case 3:
    {
        if(m_obMenu)
        {
            QMetaObject::invokeMethod(m_obMenu, "fConnectServer"
                                      , Q_ARG(QVariant, _sData)
                                      );

            QObject *a_Ob = m_obMenu->findChild<QObject*>("obMenuLogin");
            if(a_Ob)
            {
                QMetaObject::invokeMethod(a_Ob, "fConnect"
                                          , Q_ARG(QVariant, _sData)
                                          );
            }

            a_Ob = m_obMenu->findChild<QObject*>("obMenuServer");
            if(a_Ob)
            {
                QMetaObject::invokeMethod(a_Ob, "fConnect"
                                          , Q_ARG(QVariant, _sData)
                                          );
            }
        }

    }
    break;
    case 4:
    {
        //if(this->m_pStreamWriter)
        m_iTimeConnectNotActive = 0;

        //qDebug() << "Control::slClientControl 4: " << _sId << _iVar << _sData;

        if(StaticData::m_sDeskId.length())
            fStatusConnectToDesktop(true);
    }
    break;
    case 5:
    {
        if(m_obMenu)
        {

            QObject *a_Ob = m_obMenu->findChild<QObject*>("obMenuDesktop");
            if(a_Ob)
            {
                QMetaObject::invokeMethod(a_Ob, "fAddDesktop"
                                          , Q_ARG(QVariant, _sData)
                                          , Q_ARG(QVariant, _sId)
                                          );
            }
        }
    }
    break;
    case 6:
    {

    }
    break;
    case 8:
    {
        bool a_bOk;
        fBufferWrite(_sId.toInt(&a_bOk, 16), _sData);
    }
    break;
    case 9:
    {
        fClipboardSend(true);
    }
    break;
    case 10:
    {
        //qDebug() << "Control::slClientControl 10: " << _sId  << _sData;

        if(m_obMenu)
        {

            QObject *a_Ob = m_obMenu->findChild<QObject*>("obMenuFileCopy");
            if(a_Ob)
            {
                QMetaObject::invokeMethod(a_Ob, "fFileWrited"
                                          , Q_ARG(QVariant, _sId)
                                          , Q_ARG(QVariant, _sData)
                                          );
            }
        }
    }
    break;
    case 11:
    {
        if(m_obMenu)
        {

            QObject *a_Ob = m_obMenu->findChild<QObject*>("obComandLine");
            if(a_Ob)
            {
                QMetaObject::invokeMethod(a_Ob, "fResponse"
                                          , Q_ARG(QVariant, _sId)
                                          , Q_ARG(QVariant, _sData)
                                          );
            }
        }
    }
    break;
    case 12:
    {
        //qDebug() << "Control::slClientControl 12.0: " << _sId << _sId.toInt() << _sData;

        if(_sId.toInt() > 200)
        {
            //qDebug() << "Control::slClientControl 12.1: ";
            m_bErrStream = true;

            if(_sId.toInt() == 200 + 2
                || _sId.toInt() == 200 + 5
                || _sId.toInt() == 200 + 7
                || _sId.toInt() == 200 + 9
                || _sId.toInt() == 200 + 10
                )
            {
                slDisConnectDesktop(1);

                if(_sId.toInt() == 200 + 9)
                {
                    //qDebug() << "Control::slClientControl 12.3.1: ";

                    fClientDisconnect();

                    if(m_obMenu)
                    {
                        QMetaObject::invokeMethod(m_obMenu, "fConnectServer"
                                                  , Q_ARG(QVariant, "0")
                                                  );
                    }
                }

                //qDebug() << "Control::slClientControl 12.3.2: ";
            }
        }

        if(StaticData::m_sDeskId.length() != 0
            || _sId.toInt() == 200 + 2
            || _sId.toInt() == 200 + 4
            || _sId.toInt() == 200 + 5
            || _sId.toInt() == 200 + 6
            || _sId.toInt() == 200 + 7
            || _sId.toInt() == 200 + 8
            || _sId.toInt() == 200 + 9
            || _sId.toInt() == 200 + 10
            || _sId.toInt() == 200 + 11
            )
        {

            if(m_obMain)
            {

                QObject *a_Ob = m_obMain->findChild<QObject*>("obMessageStatus");
                if(a_Ob)
                {
                    QMetaObject::invokeMethod(a_Ob, "fStatus"
                                              , Q_ARG(QVariant, _sId.toInt())
                                              , Q_ARG(QVariant, _sData)
                                              );
                }
            }


            if(_sId.toInt() == 200 + 11)
                emit sgControl( "", 24, "", "");
        }
    }
    break;
    case 13:
    {
        m_iTimeStreamWrite = 0;
    }
    break;
    case 14:
    {
        //qDebug() << "Control::slClientControl 14.0: " << _sId << _sId.toInt() << _sData;
        fVideoQualitySet(_sData);
    }
    break;
    case 15:
    {
        //qDebug() << "Control::slClientControl 15.0: " << _sId << _sId.toInt() << _sData;
        fVideoQualityCurent(_sData);
    }
    break;
    case 16:
    {
        //qDebug() << "Control::slClientControl 16.0: ";

        if(_sId == "0")
        {
            if(!StaticData::m_bDevServer)
            {
                StaticData::m_sMyId = fGetIdForDevServer();
            }

            StaticData::m_bDevServer = true;

            if(m_obMenu)
            {
                QObject *a_Ob = m_obMenu->findChild<QObject*>("obMenuServer");

                if(a_Ob)
                {
                    QObject *a_ObChkServDev = a_Ob->findChild<QObject*>("obChkServDev");

                    if(a_ObChkServDev
                        && !a_ObChkServDev->property("checked").toBool() )
                    {
                        a_ObChkServDev->setProperty("checked", true);
                    }
                }
            }

            if(StaticData::m_sMyId.indexOf("_uds") > 0)
            {
                if(StaticData::m_sMyId.indexOf("-") < 0)
                    fIdForDevServerSave(StaticData::m_sMyId);
                else
                {
                    QStringList a_asT = StaticData::m_sMyId.split("-");
                    if(a_asT.length() > 1 && a_asT.at(1).length() > 0 && a_asT.at(1).at(0) != ' ')
                    {
                        fIdForDevServerSave( a_asT.at(1) );
                    }
                }
            }

            slServerUpdateData(slServerIP(), "0", "0", "0", slKeyDevServer(), slServerPassword() );
        }
        else
        {
            slServerUpdateData(slServerIP(), QString::number(slPortTCP())
                               , QString::number(slPortRTSP()), QString::number(slPortRTMP()), slKeyDevServer(), slServerPassword() );
        }
    }
    break;
    case 17:
    {
        //qDebug() << "Control::slClientControl 17.0: " << _sId << _sId.toInt() << _sData;

        if(_sId.toInt() > 300)
        {
            if( _sId.toInt() == 300 + 8
                )
            {

                if(m_obMain)
                {

                    QObject *a_Ob = m_obMain->findChild<QObject*>("obMessageStatus");
                    if(a_Ob)
                    {
                        QMetaObject::invokeMethod(a_Ob, "fStatus"
                                                  , Q_ARG(QVariant, _sId.toInt())
                                                  , Q_ARG(QVariant, _sData)
                                                  );
                    }
                }
            }
        }
    }
    break;
    case 18:
    {
        //qDebug() << "Control::slClientControl 18.0: " << _sId << _sId.toInt() << _sData;

        m_iNewStream = 0;

        if(!m_bDisconnect && m_bStream && StaticData::m_sDeskId.length() > 0)
        {
            m_iTimeStreamRestart = 0;
            m_bStreamRestart = true;
        }

    }
    break;

    default:
        break;
    }

}

void Control::slSendMouseEvent(int _iVar, bool _bBtLorR, bool _bPressRelease, int _iX, int _iY)
{
    //qDebug() << "slSendMouseEvent 0: " << _iVar << _bBtLorR << _bPressRelease << _iX << _iY;

    if(!m_bConnectClient || !m_bStream)
        return;

    emit sgSendMouseEvent( _iVar, _bBtLorR, _bPressRelease, _iX, _iY );

    m_iTimeForBuffer = 0;
}

void Control::slSendKeyEvent(unsigned int _iVar, int _iKey, QString _sData)
{
    //qDebug() << "Control::slSendKeyEvent 0: ";

    if(!m_bConnectClient || !m_bStream)
        return;

    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << _iKey;

    unsigned int x = 0;

#ifdef Q_OS_WIN
    HKL currentLayout = GetKeyboardLayout(0);
    x = (quintptr)currentLayout & 0x0000FFFF;

//qDebug() << "slSendKeyEvent 3.1: " << byteArray.toHex(':') << _iKey << _sData << x;
#endif

    emit sgSendKeyEvent(_iVar, _iKey, x, _sData);

    m_iTimeForBuffer = 0;
}

QString Control::slLogin()
{
    return StaticData::m_sLogin;
}

QString Control::slPassword()
{
    return StaticData::m_sPassword;
}

void Control::fConnectClientStatus()
{
    bool a_bRecon = true;

    if(m_bStreamRestart && m_iTimeStreamRestart < 10)
        m_iTimeStreamRestart++;

    if(m_bStreamRestart && m_iTimeStreamRestart > 1)
    {
        //qDebug() << "Control::fConnectClientStatus 2: " << "ReConnectToDesktop";

        m_bStreamRestart = false;
        m_iTimeConnectNotActive = 0;
        m_iTimeReConnectToDesktop = 0;
        a_bRecon = false;


        m_bConnectClient = false;
        if(!m_bDisconnect)
        {
            slReConnectToDesktop();
        }
    }


    if(m_iTimeConnectNotActive < 10)
        m_iTimeConnectNotActive++;

    if(a_bRecon && m_iTimeConnectNotActive > 7)
    {
        m_bConnectClient = false;

        m_iTimeReConnectToDesktop++;

        if(m_iTimeReConnectToDesktop > 7)
        {
            m_iTimeReConnectToDesktop = 0;

            //qDebug() << "fConnectClientStatus 3: " << "ReConnectToDesktop";

            if(!m_bDisconnect)
                slReConnectToDesktop();
        }


    }
    else
    {
        m_iTimeReConnectToDesktop = 4;
        m_bConnectClient = true;
    }

    if(m_obMenu)
    {
        QMetaObject::invokeMethod(m_obMenu, "fConnectClient"
                                  , Q_ARG(QVariant, m_bConnectClient)
                                  );
    }

    if(!m_bConnectClient)
        fStatusConnectToDesktop(m_bConnectClient);

    if(m_iTimeConnectNotActive > 3
        && m_iTimeConnectNotActive%2 == 0)
    {
        emit sgSendMassang( MyProtocol::fGetActiveClient( StaticData::m_sMyId ) );

        if(m_iTimeConnectNotActive >= 10)
            m_iTimeConnectNotActive = 8;
    }


    ///////Stream status
    ///

    if(StaticData::m_iTimeForStream < 10)
        StaticData::m_iTimeForStream++;

    if(StaticData::m_iTimeForStream > 3)
    {
        if(m_obMenu)
        {
            QMetaObject::invokeMethod(m_obMenu, "fStream"
                                      , Q_ARG(QVariant, false)
                                      );
        }
    }
    else
    {
        if(m_obMenu)
        {
            QMetaObject::invokeMethod(m_obMenu, "fStream"
                                      , Q_ARG(QVariant, true)
                                      );
        }

        if(StaticData::m_sDeskId.length() > 0)
        {
            m_iTimeForWatcher++;

            if(m_iTimeForWatcher%5 == 0)
            {
                //qDebug() << "fConnectClientStatus 5: " << "fWatcher";
                emit sgSendMassang( MyProtocol::fWatcher( StaticData::m_sDeskId, StaticData::m_sMyId ) );
            }

            if(m_iTimeForWatcher >= 10)
                m_iTimeForWatcher = 0;
        }

    }


    //qDebug() << "fConnectClientStatus 10: " << m_bConnectClient;
}

void Control::slSearchDesktop(QString _sUser)
{
    //qDebug() << "slSearchDesktop 5: " << _sUser;

    emit sgSendMassang( MyProtocol::fSearchDesktop(StaticData::m_sMyId, _sUser) );
}

void Control::fStatusConnectToDesktop(bool _bVar)
{
    if(m_obMenu)
    {
        QMetaObject::invokeMethod(m_obMenu, "fFileCopyVisible"
                                  , Q_ARG(QVariant, _bVar)
                                  );

        if(StaticData::m_sDeskId.length() == 0)
            _bVar = true;

        QObject *a_Ob = m_obMenu->findChild<QObject*>("obMenuDesktop");
        if(a_Ob)
        {
            QMetaObject::invokeMethod(a_Ob, "fConnect"
                                      , Q_ARG(QVariant, _bVar)
                                      );
        }
    }
}

void Control::fStreamReadClear()
{
    //qDebug() << "fStreamReadClear 0: " << m_bConnectClient;

    fStreamReaderDelete(m_pApp);
    m_iTimeConnectNotActive = 10;
    m_sNewStreamUrl = "";

}

void Control::fGenerateLogPass()
{
    //qDebug() << "fGenerateLogPass 0: ";
    if(StaticData::m_bTest)
    {
        StaticData::m_sLogin = StaticData::m_sDeskLogin = "nico";
        StaticData::m_sPassword = StaticData::m_sDeskPassword = "1242";

        return;
    }


    StaticData::m_sLogin = MyProtocol::fIdGenerator(MyProtocol::m_sPrefix, "", 8, 10);

    StaticData::m_sPassword = MyProtocol::fIdGenerator(MyProtocol::m_sPrefix, "", 6, 8);
}

void Control::slDesktopRealSize(bool _bVar)
{
    if(m_obVideo)
    {
        QMetaObject::invokeMethod(m_obVideo, "fDescktopRealSize"
                                  , Q_ARG(QVariant, _bVar)
                                  );
    }
}

void Control::slFullScreen(bool _bVar)
{
    if(m_obMain)
    {
        QMetaObject::invokeMethod(m_obMain, "fFullScreen"
                                  , Q_ARG(QVariant, _bVar)
                                  );
    }
}

void Control::fClipboardSend(bool _bLock)
{
    //qDebug() << "Control::slClipboardSend 0: ";

    if(StaticData::m_sMyId == "0" || !m_bStream)
        return;

    //qDebug() << "Control::slClipboardSend 1: ";

    if(_bLock)
    {
        //qDebug() << "Control::mitex 9: ";
        m_mtxClipboard.lock();
        //qDebug() << "Control::mitex 8: ";
    }


    QClipboard *clipboard = QGuiApplication::clipboard();


    //qDebug() << "Control::fClipboardSend 1.0: " << m_sBufferPrev;

    const QMimeData *mimeData = clipboard->mimeData();

    for(auto format : mimeData->formats())
    {
        //        qDebug() << "Control::fClipboardSend 2.1.0: " << format;
        //        qDebug() << "Control::fClipboardSend 2.1.1: " << QString::fromStdString(mimeData->data(format).toStdString());

        if(format == "text/plain"
            || format == "text/uri-list")
        {
            //qDebug() << "Control::fClipboardSend 2.2: " << mimeData->data(format).toHex(':');
            //qDebug() << "Control::fClipboardSend 2.3: " << QString::fromStdString(mimeData->data(format).toStdString());

            emit sgSendMassang( MyProtocol::fSendClipboard(StaticData::m_sMyId, 0, "") );

            int a_iSend = 0;
            int a_iPos = 0;
            int a_iPlas = 250;
            QString a_sTemp = mimeData->text();
            int a_iSz = a_sTemp.length();

            //qDebug() << "Control::fClipboardSend 2.4.0: " << a_sTemp;
            //qDebug() << "Control::fClipboardSend 2.4.1: " << a_iSz;

            for(a_iPos = 0; a_iPos < a_iSz; a_iPos += a_iPlas )
            {
                if(a_iPos + a_iPlas <= a_iSz)
                {
                    if(a_iPos + a_iPlas < a_iSz)
                    {
                        //qDebug() << "Control::fClipboardSend 3.2: " << a_iPos;

                        emit sgSendMassang( MyProtocol::fSendClipboard(StaticData::m_sMyId, 1
                                                                      , a_sTemp.mid(a_iPos, a_iPlas)) );

                        //qDebug() << "Control::fClipboardSend 3.2.1: " << a_sTemp.mid(a_iPos, a_iPlas);

                        a_iSend += a_iPlas;
                    }
                    else
                    {
                        //qDebug() << "Control::fClipboardSend 3.3: " << a_iPos;

                        emit sgSendMassang( MyProtocol::fSendClipboard(StaticData::m_sMyId, 2
                                                                      , a_sTemp.mid(a_iPos, a_iPlas)) );

                        //qDebug() << "Control::fClipboardSend 3.3.1: " << a_sTemp.mid(a_iPos, a_iPlas);

                        a_iSend += a_iPlas;
                    }
                }
            }

            if(a_iSend + a_iPlas > a_iSz)
            {
                //qDebug() << "Control::fClipboardSend 3.4: " << a_iSz << a_iPos << a_iSend;

                emit sgSendMassang( MyProtocol::fSendClipboard(StaticData::m_sMyId, 2
                                                              , a_sTemp.mid(a_iSend, a_iSz - a_iSend)) );

                //qDebug() << "Control::fClipboardSend 3.4.1: " << a_sTemp.mid(a_iSend, a_iSz - a_iSend);
            }

            //qDebug() << "Control::fClipboardSend 4: " << a_iSz << a_iPos << a_iSend;
        }
    }

    if(_bLock)
    {
        m_mtxClipboard.unlock();
        //qDebug() << "Control::mitex 7: ";
    }

    //qDebug() << "Control::fClipboardSend 10: " << _bLock;

}

void Control::fBufferWrite(int _iVar, QString _sData)
{
    //qDebug() << "Control::fBufferWrite 0: " << _iVar << _sData;


    if(_iVar == 0 || !m_bStream)
    {
        m_sBufferWrite = "";
    }
    else
    {
        if(_iVar == 1)
        {
            m_sBufferWrite += _sData;
        }
        else
        {
            if(_iVar == 2)
            {
                m_sBufferWrite += _sData;

                //qDebug() << "Control::fBufferWrite 4: " << m_sBufferWrite;

                if(StaticData::m_sMyId != "0"
                    && m_iTimeForBuffer < 5 )
                {
                    //qDebug() << "Control::mitex 5: ";
                    m_mtxClipboard.lock();
                    //qDebug() << "Control::mitex 5: ";
                    QClipboard *clipboard = QGuiApplication::clipboard();
                    clipboard->clear();
                    clipboard->setText(m_sBufferWrite);
                    m_mtxClipboard.unlock();
                    //qDebug() << "Control::mitex 4: ";

                }
                //               else
                //                   qDebug() << "Control::fBufferWrite 5: " << m_iTimeForBuffer;
            }
        }
    }

}

void Control::slFileCopy(int _iVar, QString _sPath)
{

    if(_iVar == 0)
    {
        emit sgControl( "", 12, "", "");
    }
    else
        if(_iVar == 1)
        {
            if(StaticData::m_sDeskId.length() > 0)
                emit sgSendMassang( MyProtocol::fGetFile( StaticData::m_sDeskId
                                                        , StaticData::m_sMyId
                                                        , _sPath
                                                        , 0) );
            else
                slClientControl("2", 10, "0" );
        }
        else
            if(_iVar == 2)
            {
                if(StaticData::m_sDeskId.length() > 0)
                    emit sgControl( "", 9, "", MyProtocol::fGetFile( StaticData::m_sMyId
                                                                   , StaticData::m_sDeskId
                                                                   , _sPath
                                                                   , 0) );
                else
                    slClientControl("2", 10, "0" );
            }
}

QString Control::slServerIP()
{
    return StaticData::m_sServerIP;
}

unsigned short Control::slPortTCP()
{
    return StaticData::m_sPortTCP;
}

unsigned short Control::slPortRTSP()
{
    return StaticData::m_sPortRTSP;
}

unsigned short Control::slPortRTMP()
{
    return StaticData::m_sPortRTMP;
}

void Control::slServerUpdateData(QString _sIP, QString _sPortTCP, QString _sPortRTSP, QString _sPortRTMP, QString _sKeyDevServer, QString _sServerPas)
{
    if(slIsIP(_sIP)
        && slIsNumber(_sPortTCP)
        && slIsNumber(_sPortRTSP)
        && slIsNumber(_sPortRTMP)
        && _sPortTCP.indexOf('-') < 0
        && _sPortRTSP.indexOf('-') < 0
        && _sPortRTMP.indexOf('-') < 0
        )
    {
        SettingsApp::fSaveServerData(_sIP, _sPortTCP, _sPortRTSP, _sPortRTMP, _sKeyDevServer, _sServerPas);

        slConnectToServer(StaticData::m_sLogin, StaticData::m_sPassword);
    }
}

bool Control::slIsNumber(QString _lIn)
{
    return StaticData::fIsNumber(_lIn);
}

bool Control::slIsIP(QString _lIn)
{
    return StaticData::fIsIP(_lIn);
}

void Control::slComandLine(QString _sData, int _iVar)
{
    if(    _iVar == 1
        || _iVar == 2
        )
    {
        if(StaticData::m_sDeskId.length() > 0)
            emit sgSendMassang( MyProtocol::fComandLineRequest( StaticData::m_sDeskId
                                                              , StaticData::m_sMyId
                                                              , _sData
                                                              , _iVar)
                               );
    }

    //$ping -n 20 12.3.213.214
}

bool Control::slComandLineStatus()
{
    //qDebug() << "Control::slUseComandLine 0: " << m_bComandLine;

    return m_bComandLine;
}

void Control::slUseComandLine(bool _bVar)
{
    m_bComandLine = _bVar;
}

QString Control::slDeskLogin()
{
    return StaticData::m_sDeskLogin;
}

QString Control::slDeskPassword()
{
    return StaticData::m_sDeskPassword;
}

void Control::slVideoQualityStatus()
{

    if(m_obMenu)
    {

        QObject *a_Ob = m_obMain->findChild<QObject*>("obMenuVideoQuality");
        if(a_Ob)
        {
            QMetaObject::invokeMethod(a_Ob, "fSetStatus"
                                      , Q_ARG(QVariant, StaticData::_iSizeFr)
                                      , Q_ARG(QVariant, StaticData::_iFPS)
                                      , Q_ARG(QVariant, StaticData::_iEnvoderV)
                                      , Q_ARG(QVariant, StaticData::_iEncSpeed)
                                      , Q_ARG(QVariant, StaticData::_iBetrate)
                                      , Q_ARG(QVariant, StaticData::_iLatencyZ)
                                      , Q_ARG(QVariant, StaticData::_iStreamRTSP)
                                      , Q_ARG(QVariant, StaticData::_iSoundCapture)
                                      );
        }
    }
}

void Control::slVideoQualityGet(int _iSizeF, int _iFPS, int _iEnvoderV, int _iEncSpeed, int _iBetrate, int _iLatencyZ, bool _bRtsp, int _iSound)
{
    if(m_bStream && StaticData::m_sDeskId.length() > 0)
    {
        if( StaticData::_iSizeFr == _iSizeF
            && StaticData::_iFPS == _iFPS
            && StaticData::_iEnvoderV == _iEnvoderV
            && StaticData::_iEncSpeed == _iEncSpeed
            && StaticData::_iBetrate == _iBetrate
            && StaticData::_iLatencyZ == _iLatencyZ
            && StaticData::_iStreamRTSP == _bRtsp
            && StaticData::_iSoundCapture == _iSound
            )
            return;


        StaticData::_iSizeFr = _iSizeF;
        StaticData::_iFPS = _iFPS;
        StaticData::_iEnvoderV = _iEnvoderV;
        StaticData::_iEncSpeed = _iEncSpeed;
        StaticData::_iBetrate = _iBetrate;
        StaticData::_iLatencyZ = _iLatencyZ;
        StaticData::_iStreamRTSP = _bRtsp;
        StaticData::_iSoundCapture = _iSound;

        emit sgSendMassang( MyProtocol::fVideoQualitySet( StaticData::m_sDeskId, StaticData::m_sMyId
                                                        ,_iSizeF,  _iFPS,  _iEnvoderV,  _iEncSpeed,  _iBetrate, _iLatencyZ
                                                        , _bRtsp, _iSound)
                           );
    }
}

void Control::fVideoQualitySet(QString _sData)
{
    //qDebug() << "Control::fVideoQualitySet 0: " << _sData << _sData.length();


    if(_sData.length() != 8)
        return;

    QByteArray a_baTemp(_sData.toUtf8());

    //qDebug() << "Control::fVideoQualitySet 1: " << a_baTemp.toHex(':');

    if( StaticData::_iCurSizeFr == static_cast<quint8>( a_baTemp.at(0) )
        && StaticData::_iCurFPS == static_cast<quint8>( a_baTemp.at(1) )
        && StaticData::_iCurEnvoderV == static_cast<quint8>( a_baTemp.at(2) )
        && StaticData::_iCurEncSpeed == static_cast<quint8>( a_baTemp.at(3) )
        && StaticData::_iCurBetrate == static_cast<quint8>( a_baTemp.at(4) )
        && StaticData::_iCurLatencyZ == static_cast<quint8>( a_baTemp.at(5) )
        && StaticData::_iCurStreamRTSP == static_cast<quint8>( a_baTemp.at(6) )
        && StaticData::_iCurSoundCapture == static_cast<quint8>( a_baTemp.at(7) )
        )
        return;

    StaticData::m_sRtspDescriptor = "";

    StaticData::_iCurSizeFr = static_cast<quint8>( a_baTemp.at(0) );
    StaticData::_iCurFPS = static_cast<quint8>( a_baTemp.at(1) );

    if( !StaticData::fAvailableNvh264enc() )
        StaticData::_iCurEnvoderV = 0;
    else
        StaticData::_iCurEnvoderV = static_cast<quint8>( a_baTemp.at(2) );

    StaticData::_iCurEncSpeed = static_cast<quint8>( a_baTemp.at(3) );
    StaticData::_iCurBetrate = static_cast<quint8>( a_baTemp.at(4) );
    StaticData::_iCurLatencyZ = static_cast<quint8>( a_baTemp.at(5) );
    StaticData::_iCurStreamRTSP = static_cast<quint8>( a_baTemp.at(6) );
    StaticData::_iCurSoundCapture = static_cast<quint8>( a_baTemp.at(7) );

    if( !StaticData::fAvailableNvh264enc() )
        StaticData::_iCurEnvoderV = 0;



    SettingsApp::fSaveEvcoderType(StaticData::_iCurEnvoderV);
    SettingsApp::fSaveStreamRTSP((bool)StaticData::_iCurStreamRTSP);

    //qDebug() << "Control::fVideoQualitySet 3: " << StaticData::_iCurEnvoderV;

}

void Control::fVideoQualityCurent(QString _sData)
{
    //qDebug() << "Control::fVideoQualityCurent 0: " << _sData << _sData.length();


    if(_sData.length() != 8)
        return;

    QByteArray a_baTemp(_sData.toUtf8());

    //qDebug() << "Control::fVideoQualityCurent 1: " << a_baTemp.toHex(':');

    if( StaticData::_iSizeFr == static_cast<quint8>( a_baTemp.at(0) )
        && StaticData::_iFPS == static_cast<quint8>( a_baTemp.at(1) )
        && StaticData::_iEnvoderV == static_cast<quint8>( a_baTemp.at(2) )
        && StaticData::_iEncSpeed == static_cast<quint8>( a_baTemp.at(3) )
        && StaticData::_iBetrate == static_cast<quint8>( a_baTemp.at(4) )
        && StaticData::_iLatencyZ == static_cast<quint8>( a_baTemp.at(5) )
        && StaticData::_iStreamRTSP == static_cast<quint8>( a_baTemp.at(6) )
        && StaticData::_iSoundCapture == static_cast<quint8>( a_baTemp.at(7) )
        )
        return;


    StaticData::_iSizeFr = static_cast<quint8>( a_baTemp.at(0) );
    StaticData::_iFPS = static_cast<quint8>( a_baTemp.at(1) );
    StaticData::_iEnvoderV = static_cast<quint8>( a_baTemp.at(2) );
    StaticData::_iEncSpeed = static_cast<quint8>( a_baTemp.at(3) );
    StaticData::_iBetrate = static_cast<quint8>( a_baTemp.at(4) );
    StaticData::_iLatencyZ = static_cast<quint8>( a_baTemp.at(5) );
    StaticData::_iStreamRTSP = static_cast<quint8>( a_baTemp.at(6) );
    StaticData::_iSoundCapture = static_cast<quint8>( a_baTemp.at(7) );

    SettingsApp::fSaveEvcoderType(StaticData::_iEnvoderV);
    SettingsApp::fSaveStreamRTSP((bool)StaticData::_iStreamRTSP);

    // qDebug() << "Control::fVideoQualityCurent 2: " << StaticData::_iSizeFr << StaticData::_iSizeFr
    //                 << StaticData::_iEnvoderV << StaticData::_iEncSpeed
    //                 << StaticData::_iBetrate << StaticData::_iLatencyZ
    //                 << StaticData::_iStreamRTSP
    //                 << StaticData::_iSoundCapture;


    slVideoQualityStatus();

    m_iNewStream = 0;
}

void Control::fNewStream()
{
    if(m_iNewStream < 2)
    {
        m_iNewStream++;
    }

    if(m_iNewStream == 2)
    {
        m_iNewStream++;

        //qDebug() << "Control::fNewStream 12.0: ";
        if(m_bStream && !m_bErrStream)
        {
            //qDebug() << "Control::fNewStream 12.1: ";

            if(slPlayerVar() == 0)
            {
                if(m_obVideo)
                {
                    QMetaObject::invokeMethod(m_obVideo, "fVideoStartStop"
                                              , Q_ARG(QVariant, fStreamReadGST())
                                              , Q_ARG(QVariant, 1) );
                }
            }
            else
            {
                fInitStreamReader(m_pApp);

                if(m_obVideo)
                {
                    QMetaObject::invokeMethod(m_obVideo, "fVideoStartStop"
                                              , Q_ARG(QVariant, "")
                                              , Q_ARG(QVariant, 1) );
                }
            }
        }

        //qDebug() << "Control::fNewStream 12.2: ";
    }
}

void Control::slReConnectToDesktop()
{
    slConnectToDesktop(m_bStream, StaticData::m_sDeskLogin, StaticData::m_sDeskPassword, StaticData::m_sDeskId);
}

void Control::fKeyEventClear()
{
#ifdef Q_OS_WIN
    keybd_event(VK_CONTROL ,
                0,
                KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                0);

    keybd_event(164,
                0,
                KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                0);

    keybd_event(165,
                0,
                KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                0);
#endif


}

bool Control::slStreamRTSP()
{
    return StaticData::_iStreamRTSP;
}

QString Control::slAppName()
{
    return StaticData::m_sNameApp + " - " + StaticData::m_sVersion;
}

void Control::fTestSomeDataForUser()
{
    QByteArray a_baRequest;
    a_baRequest.append((char) 0x00);
    a_baRequest.append(0x01);

    QString a_sHello = "Hello. It's data test.";

    QByteArray a_baTemp(a_sHello.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSomeDataForUser 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    emit sgSendMassang( MyProtocol::fSomeDataForUser(StaticData::m_sDeskId, StaticData::m_sMyId, a_baRequest) );
}

int Control::slPlayerVar()
{
    return StaticData::_iPlayerVar;
}

void Control::fInitStreamReader(QQmlEngine *_engineMain)
{


}

void Control::slUpdateFrame(int _iFrame, int _iWf, int _iHf)
{
    //qDebug() << "Control::slUpdateFrame -> " << _iFrame;

    StaticData::m_iTimeForStream = 0;

    if(_iHf > 0 && m_obVideo)
    {
        QMetaObject::invokeMethod(m_obVideo, "updateFrame"
                                  , Q_ARG(QVariant, _iFrame)
                                  , Q_ARG(QVariant, _iWf)
                                  , Q_ARG(QVariant, _iHf));
    }

}

void Control::fClientDisconnect()
{
    //qDebug() << "Control::fClientDisconnect 0: ";
    emit sgClientStop();
    //qDebug() << "Control::fClientDisconnect 1: ";
    fStreamReaderDelete(m_pApp);
    //qDebug() << "Control::fClientDisconnect 2: ";

    //qDebug() << "Control::fClientDisconnect 10: ";
}

void Control::slSendStatIP(QString  _sVar)
{
    qDebug() << "Control::slSendStatIP 0: " << _sVar;

    emit sgSendMassang( MyProtocol::fSendStatIP(_sVar) );
}

void Control::slSleep(unsigned long _lmSec)
{
    QThread::msleep(_lmSec);
}

void Control::slThClientFin()
{
    m_mtxThClientSoc.lock();
    //qDebug() << "Control::slThClientFin 5.0: " << m_iThClientSoc;
    m_iThClientSoc--;
    //qDebug() << "Control::slThClientFin 5.1: " << m_iThClientSoc;
    m_mtxThClientSoc.unlock();
    //qDebug() << " Control::slThClientFin 200: " << "Client thread end. ----------------------";
}

void Control::slLowActivityDiscTime(QString _sData)
{
    if(StaticData::fIsNumber( _sData) && _sData.toInt() >= 0)
    {
        //qDebug() << " Control::slLowActivituDiscTime 5: " << _sData;

        emit sgSendMassang( MyProtocol::fSendLowActivityTime( _sData ) );
    }
}
