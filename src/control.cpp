#include "control.h"

#ifdef Q_OS_WIN
#include <windows.h>
#else
#ifdef Q_OS_LINUX
//#include <X11/Xlib.h>
//sudo apt-get install libxtst-dev
#include <X11/extensions/XTest.h>
#endif
#endif




Control::Control(QStringList _sDataIn)
{
    //qDebug() << "Control::Control 0:" << _sDataIn;

    //fGenerateLogPass();

    fPropertySet( _sDataIn );


    if( SettingsApp::slDevServer() )
        slServerUpdateData(  slServerIP()
                            , "0"
                            , "0"
                            , "0"
                            , SettingsApp::slKeyDevServer()
                            , slServerPassword()
                           );
    else
        slServerUpdateData(  slServerIP()
                           , QString::number( slPortTCP() )
                           , "0"
                           , "0"
                           , SettingsApp::slKeyDevServer()
                           , slServerPassword()
                           );


    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Control::slotTimer);
    timer->setInterval(1000);
    timer->start();

}

Control::~Control()
{
    //qDebug() << "Control::~Control 0: ";

    slotDestruction();

    //QThread::sleep(2);

    //qDebug() << "Control::~Control 10: ";
}

void Control::slotDestruction()
{
    qDebug() << "Control::slotDestruction 0: ";

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

    QThread::msleep(200);

    qDebug() << "Control::slotDestruction 200: " << a_iStop  << m_iThClientSoc;
}

void Control::slotTimer()
{
    emit sgTimer();

    fConnectClientStatus();

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
    if(_sLogin.length() == 0 || _sPassword.length() == 0)
        return;

    StaticData::m_sLogin = _sLogin;
    StaticData::m_sPassword = _sPassword;

    slClientControl("", 3, "0");

    //fConnectToServer("192.168.1.189", StaticData::m_sPortTCP, StaticData::m_sLogin, StaticData::m_sPassword);
    //fConnectToServer("127.0.0.1", StaticData::m_sPortTCP, StaticData::m_sLogin, StaticData::m_sPassword);
    fConnectToServer(slServerIP(), slPortTCP(), slLogin(), slPassword() );
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
        //qDebug() << "Control::slClientControl 1.2: " << _sId << _iVar << _sData;

    }
    break;
    case 2:
    {

        //qDebug() << "Control::slClientControl 2.2: " << m_sNewStreamUrl << _sData;

    }
    break;
    case 3:
    {


    }
    break;
    case 4:
    {
        //if(this->m_pStreamWriter)
        m_iTimeConnectNotActive = 0;

        //qDebug() << "Control::slClientControl 4: " << _sId << _iVar << _sData;
    }
    break;
    case 5:
    {

    }
    break;
    case 6:
    {

    }
    break;
    case 8:
    {

    }
    break;
    case 9:
    {

    }
    break;
    case 10:
    {
        //qDebug() << "Control::slClientControl 10: " << _sId  << _sData;


    }
    break;
    case 11:
    {

    }
    break;
    case 12:
    {
        qDebug() << "Control::slClientControl 12.0: " << _sId << _sId.toInt() << _sData;

        if(StaticData::m_sDeskId.length() != 0
            || _sId.toInt() == 200 + 2
            || _sId.toInt() == 200 + 4
            || _sId.toInt() == 200 + 5
            || _sId.toInt() == 200 + 6
            || _sId.toInt() == 200 + 7
            || _sId.toInt() == 200 + 8
            || _sId.toInt() == 200 + 9
            || _sId.toInt() == 200 + 10
            )
        {
            //qDebug() << "Control::slClientControl 12.1: " << _sData;
        }

        if(_sId.toInt() > 200)
        {
            //qDebug() << "Control::slClientControl 12.2.0: ";

            if(_sId.toInt() == 200 + 2
                || _sId.toInt() == 200 + 5
                || _sId.toInt() == 200 + 7
                || _sId.toInt() == 200 + 9
                || _sId.toInt() == 200 + 10
                || _sId.toInt() == 200 + 11
                )
            {
                if(_sId.toInt() == 200 + 9)
                {
                    QApplication::quit();
                }

                if(_sId.toInt() == 200 + 11)
                    emit sgControl( "", 24, "", "");

                //qDebug() << "Control::slClientControl 12.2.2: " << _sId;
            }
        }
    }
    break;
    case 13:
    {

    }
    break;
    case 14:
    {
        //qDebug() << "Control::slClientControl 14.0: " << _sId << _sId.toInt() << _sData;
    }
    break;
    case 15:
    {
        //qDebug() << "Control::slClientControl 15.0: " << _sId << _sId.toInt() << _sData;
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

            slServerUpdateData(slServerIP()
                               , "0"
                               , "0"
                               , "0"
                               , slKeyDevServer()
                               , slServerPassword() );
        }
        else
        {
            slServerUpdateData(slServerIP()
                               , QString::number(slPortTCP())
                               , "0"
                               , "0"
                               , slKeyDevServer()
                               , slServerPassword() );
        }

    }
    break;

    default:
        break;
    }

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
    if(m_iTimeConnectNotActive < 10)
        m_iTimeConnectNotActive++;

    if(m_iTimeConnectNotActive > 7)
    {
        m_bConnectClient = false;

        m_iTimeReConnectToDesktop++;

        if(m_iTimeReConnectToDesktop > 7)
        {
            m_iTimeReConnectToDesktop = 0;

            //qDebug() << "fConnectClientStatus 3: " << "ReConnectToDesktop";
        }


    }
    else
    {
        m_iTimeReConnectToDesktop = 4;
        m_bConnectClient = true;
    }

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

    }
    else
    {

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

void Control::fGenerateLogPass()
{
    //qDebug() << "fGenerateLogPass 0: ";

    StaticData::m_sLogin = MyProtocol::fIdGenerator(MyProtocol::m_sPrefix, "", 8, 10);

    StaticData::m_sPassword = MyProtocol::fIdGenerator(MyProtocol::m_sPrefix, "", 6, 8);

    //qDebug() << "Control::fGenerateLogPass 10: " << StaticData::m_sLogin << StaticData::m_sPassword;
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

        slConnectToServer(slLogin(), slPassword() );

        //qDebug() << "Control::slServerUpdateData 5: " << slServerIP() << slPortTCP() << slPortRTSP() << slPortRTMP() << SettingsApp::slDevServer() << SettingsApp::slKeyDevServer();
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
    if(_iVar == 1)
    {
        if(StaticData::m_sDeskId.length() > 0)
            emit sgSendMassang( MyProtocol::fComandLineRequest( StaticData::m_sDeskId
                                                              , StaticData::m_sMyId
                                                              , _sData
                                                              , _iVar)
                               );
    }

    //$ping -n 20 158.101.219.244
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

void Control::fPropertySet(QStringList _sDataIn)
{
    //qDebug() << "Control::fPropertySet 0:" << _sDataIn;

    StaticData::m_bDevServer = false;
    StaticData::m_sKeyDevServer = "xxxxxxxx";

    _sDataIn.removeFirst();

    _sDataIn = fCorrectDataIn(_sDataIn);

    //qDebug() << "Control::fPropertySet 1:" << _sDataIn;

    QString a_sLog;
    QString a_sPas;

    quint16 a_iSz = _sDataIn.length();

    if(a_iSz > 1)
    {
        if(a_iSz%2 != 0)
        {
            //qDebug() << "Control::fPropertySet 2.0:" << "parmeters are incorrect. Sz: " << a_iSz;

            _sDataIn.removeLast();
            a_iSz--;

            //qDebug() << "Control::fPropertySet 2.1:" << _sDataIn;
        }

        for(quint16 i = 0; i < a_iSz; i+=2)
        {
            if(_sDataIn.at(i) == "-spas")
            {
                if(i + 1 < a_iSz)
                {
                    if(_sDataIn.at(i+1).length() > 0)
                        StaticData::m_sServerPassword = _sDataIn.at(i+1);
                }
            }
            else
            if(_sDataIn.at(i) == "-sip")
            {
                if(i + 1 < a_iSz)
                {
                    if(StaticData::fIsIP( _sDataIn.at(i+1) ))
                    {
                        StaticData::m_sServerIP = _sDataIn.at(i+1);
                    }
                }
            }
            else
                if(_sDataIn.at(i) == "-ptcp")
                {
                    if(i + 1 < a_iSz)
                    {
                        bool b;
                        quint16 a_iPort = _sDataIn.at(i+1).toUShort(&b);

                        if(b && a_iPort > 1024)
                        {
                            StaticData::m_sPortTCP = a_iPort;
                        }
                    }
                }
                else
                    if(_sDataIn.at(i) == "-log")
                    {
                        if(i + 1 < a_iSz)
                        {
                            if( _sDataIn.at(i+1).length() > 3)
                            {
                                a_sLog = _sDataIn.at(i+1);
                            }
                        }
                    }
                    else
                        if(_sDataIn.at(i) == "-pas")
                        {
                            if(i + 1 < a_iSz)
                            {
                                if( _sDataIn.at(i+1).length() > 3)
                                {
                                    a_sPas = _sDataIn.at(i+1);
                                }
                            }
                        }
                        else
                            if(_sDataIn.at(i) == "-ds")
                            {
                                if(i + 1 < a_iSz)
                                {
                                    bool b;
                                    quint8 a_iB = _sDataIn.at(i+1).toUShort(&b);

                                    if(b && a_iB > 0)
                                        StaticData::m_bDevServer = true;

                                }
                            }
                            else
                                if(_sDataIn.at(i) == "-kds")
                                {
                                    if(i + 1 < a_iSz)
                                    {
                                        if( _sDataIn.at(i+1).length() > 7)
                                        {
                                            StaticData::m_sKeyDevServer = _sDataIn.at(i+1);
                                        }
                                    }
                                }
        }

        if(a_sLog.length() > 0 && a_sPas.length() > 0)
        {
            StaticData::m_sLogin = a_sLog;
            StaticData::m_sPassword = a_sPas;
        }
    }

    if(!StaticData::m_bDevServer)
    {
        SettingsApp::fUpdateServerData();

        //qDebug() << "Control::fPropertySet 5:" << StaticData::m_bDevServer;
    }

   qDebug() << "Control::fPropertySet 10: "
            << StaticData::m_sServerPassword
            << StaticData::m_sServerIP
            << StaticData::m_sPortTCP
            << StaticData::m_sLogin
            << StaticData::m_sPassword
            << StaticData::m_bDevServer;
}

QStringList Control::fCorrectDataIn(QStringList _sDataIn)
{
    QString a_sTemp;
    for(QString s : _sDataIn) {

        if(a_sTemp.length() > 0)
            a_sTemp += " ";

        while(s.indexOf(" ") >= 0)
        {
            s = s.replace(" ", "");
        }

        a_sTemp += s;
    }

    while(a_sTemp.indexOf("  ") >= 0)
    {
        a_sTemp = a_sTemp.replace("  ", " ");
    }

    return a_sTemp.split(" ");
}

void Control::fClientDisconnect()
{
    //qDebug() << "Control::fClientDisconnect 0: ";
    emit sgClientStop();

    //qDebug() << "Control::fClientDisconnect 10: ";
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
