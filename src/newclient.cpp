#include "newclient.h"

NewClient::NewClient(QString _sIp, uint _iPort, QString _sLogin, QString _sPassword, QObject *parent) :
    QThread(parent)
{
    m_iTimeMs = QDateTime::currentMSecsSinceEpoch(),

    m_sIp = _sIp;
    m_iPort = _iPort;
    m_sLogin = _sLogin;
    m_sPassword = _sPassword;

    m_iTimeOut = 1000;

    socket = nullptr;
    m_bConnect = false;
    m_bRun = true;

    m_pParserSocket = nullptr;
    m_tWrite = m_tParser = nullptr;
    m_bStop = true;

    //qDebug() << "NewClient::NewClient 200: " << "ClientID:" << m_iTimeMs;
}


void NewClient::run()
{
    m_pParserSocket = new ParserSocketData();
    m_pParserSocket->m_baLogin = m_sLogin.toUtf8();
    m_pParserSocket->m_baPassword = m_sLogin.toUtf8();
    connect(m_pParserSocket, &ParserSocketData::sgControl, this, &NewClient::slControl);
    connect(m_pParserSocket, &ParserSocketData::sgAddDataWrite, this, &NewClient::slAddDataWrite);



    m_tParser = new QTimer();
    m_tParser->setInterval(0);
    m_tParser->setSingleShot(true);
    connect(m_tParser, &QTimer::timeout, this, &NewClient::slParser, Qt::DirectConnection);
    connect(this, SIGNAL(sgTimerParserStart()), m_tParser, SLOT(start()), Qt::QueuedConnection);
    connect(this, &NewClient::sgTimerStop, m_tParser, &QTimer::stop);
    connect(this, &NewClient::finished, m_tParser, &QTimer::stop);


    m_tWrite = new QTimer();
    m_tWrite->setInterval(0);
    m_tWrite->setSingleShot(true);
    connect(m_tWrite, &QTimer::timeout, this, &NewClient::slWriteToSoccet, Qt::DirectConnection);
    connect(this, SIGNAL(sgTimerWriteStart()), m_tWrite, SLOT(start()), Qt::QueuedConnection);
    connect(this, &NewClient::sgTimerStop, m_tWrite, &QTimer::stop);
    connect(this, &NewClient::finished, m_tWrite, &QTimer::stop);

    m_tThreadTask = new QTimer();
    m_tThreadTask->setInterval(0);
    m_tThreadTask->setSingleShot(true);
    connect(m_tThreadTask, &QTimer::timeout, this, &NewClient::slThreadTask, Qt::DirectConnection);
    connect(this, SIGNAL(sgThreadTask()), m_tThreadTask, SLOT(start()), Qt::QueuedConnection);
    connect(this, &NewClient::sgTimerStop, m_tThreadTask, &QTimer::stop);
    connect(this, &NewClient::finished, m_tThreadTask, &QTimer::stop);


    //qDebug() << "NewClient::run 6:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

    fConnect();

    exec();

    m_mutexDestroy.lock();

    //qDebug() << "NewClient::run 7:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

    m_bStop = true;

    emit sgFileWriteControl("", 0, "");
    emit sgFileReadControl("", 0, "");
    emit sgComanfLineControl("", 0, "");

    QThread::msleep(200);

    if(m_tWrite)
    {
        //qDebug() << "NewClient::run 8:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        m_tWrite->stop();
        QThread::msleep(200);
        delete m_tWrite;
        m_tWrite = nullptr;
    }

    //qDebug() << "NewClient::run 9:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

    if(socket)
    {
        if(socket->isOpen())
        {
            //qDebug() << "NewClient::run 10.0:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
            socket->close();
        }

        //qDebug() << "NewClient::run 10.1:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        socket->deleteLater();
    }

    //qDebug() << "NewClient::run 12:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
    m_mutexDestroy.unlock();


    if(m_pParserSocket)
    {
        //qDebug() << "NewClient::run 13:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        delete m_pParserSocket;
        m_pParserSocket = nullptr;
    }

    //qDebug() << "NewClient::run 14:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

    if(m_tParser)
    {
        //qDebug() << "NewClient::run 15:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

        m_tParser->stop();
        QThread::msleep(200);
        delete m_tParser;
        m_tParser = nullptr;
    }

    if(m_tThreadTask)
    {
        //qDebug() << "NewClient::run 16:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        m_tThreadTask->stop();
        QThread::msleep(200);
        delete m_tThreadTask;
        m_tThreadTask = nullptr;
    }

    //qDebug() << "NewClient::run 17:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

    if(!m_baDataWrite.isEmpty())
        m_baDataWrite.clear();

    //qDebug() << "NewClient::run 200:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId() << "Disconnected. Thread end. ----------------------";
}

void NewClient::fConnect()
{
    emit sgControl("", 0, "0");

    if(socket)
    {
        //qDebug() << "NewClient::fConnect 1.0:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

        disconnect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        disconnect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

        //qDebug() << "NewClient::fConnect 1.1:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        socket->close();
        //qDebug() << "NewClient::fConnect 1.2:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        socket->deleteLater();
        //qDebug() << "NewClient::fConnect 1.3:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        socket = nullptr;

        qDebug() << "NewClient::fConnect 1:" << "new connecting...";

        if(m_bLowActivity)
        {
            emit sgControl("", 3, "2");

            for(int i = 0; i < 30 * 10; i++)
            {
                if(!m_bRun)
                    break;

                QThread::msleep(100);
            }
        }
    }

    m_bLowActivity = false;

    m_bConnect = false;

    if(m_bRun)
        socket = new QTcpSocket();

    while(m_bRun && socket)
    {
        socket->connectToHost(m_sIp, m_iPort);

        if(socket->waitForConnected(m_iTimeOut))
        {
            //qDebug() << "NewClient::fConnect 2:" << "Connected!" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

            slControl(0, 3, "1", "");

            m_bConnect = true;
            m_bStop = false;

            connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
            connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));


            if(m_sLogin.length() > 0 && m_sPassword.length() > 0 && m_pParserSocket)
            {
                // if(m_pParserSocket)
                //     slAddDataWrite( MyProtocol::fSendToken(m_pParserSocket->m_sTokenId) );
                slAddDataWrite( MyProtocol::fSendUserLoginPassword(m_sLogin, m_sPassword, StaticData::m_sMyId, StaticData::m_sKeyDevServer, StaticData::m_sServerPassword) );
                slAddDataWrite( MyProtocol::fSendCurrentTime(1) );
            }
            else
                slStop();

            break;
        }
        else
        {
            if(m_bRun)
            {
                emit sgControl("", 3, "2");

                // something's wrong, we just emit a signal
                //qDebug() << "NewClient::run 4: " << "error: " << socket->errorString() ;
                emit error(socket->error());
                QThread::msleep(m_iTimeOut + 10);
            }

            qDebug() << "NewClient::fConnect 5:"  << m_sIp <<  "not connected!" ;
        }
    }
}

void NewClient::readyRead()
{
    // get the information
    QByteArray Data = socket->readAll();

    // will write on server side window
    //qDebug() << "NewClient::readyRead 5: " << "socket =" << socketDescriptor << " Data in: " << Data.toHex(':');

    if(m_pParserSocket)
    {
        m_pParserSocket->fAddData( Data );

        //qDebug() << "NewClient::slSendMassang 1: " << m_bArrWrite.length();

        if(m_tParser && !m_tParser->isActive() )
        {
            //qDebug() << "NewClient::slSendMassang 2: " << "timerStart";
            emit sgTimerParserStart();
        }
    }

}

void NewClient::fWrite(QByteArray _abIn)
{
    if(socket && socket->isOpen())
    {
        socket->write(_abIn);
    }
}

void NewClient::slAddDataWrite(QByteArray _baIn)
{
    if(!m_bConnect)
        return;

    m_mutexNewDataWrite.lock();

    m_baDataWrite.append(_baIn);

    m_mutexNewDataWrite.unlock();

    if(m_tWrite && !m_tWrite->isActive() )
    {
        //qDebug() << "NewClient::slAddDataWrite 2: " << "timerStart";
        emit sgTimerWriteStart();
    }
}

void NewClient::slWriteToSoccet()
{
    if(m_bConnect)
    {
        while(!m_bStop && !m_baDataWrite.isEmpty())
        {

            m_mutexNewDataWrite.lock();

            QByteArray a_Data = m_baDataWrite.at(0);
            m_baDataWrite.removeFirst();

            m_mutexNewDataWrite.unlock();


            fWrite(a_Data);
        }


        if(m_bStop)
        {
            m_mutexNewDataWrite.lock();

            if(!m_baDataWrite.isEmpty())
                m_baDataWrite.clear();

            m_mutexNewDataWrite.unlock();

        }
    }


    if(!m_bConnect)
    {
        //qDebug() << "NewClient::slWriteToSoccet 5: " << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        fConnect();
    }
}



void NewClient::slParser()
{
    while(!m_bStop && m_pParserSocket && !m_pParserSocket->fIsEpty())
    {
        m_pParserSocket->fParser();
    }
}

void NewClient::disconnected()
{
    m_mutexDestroy.lock();
    //qDebug() << "NewClient::disconnected 0: " << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

    if(!m_bStop)
        emit sgControl("", 3, "0");

    emit sgFileWriteControl("", 0, "");
    emit sgFileReadControl("", 0, "");
    emit sgComanfLineControl("", 0, "");

    m_bConnect = false;

    //qDebug() << "NewClient::disconnected 1: " << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

    if(!m_bStop && m_tWrite && !m_tWrite->isActive() )
    {
        //qDebug() << "NewClient::disconnected 2: " << "timerStart" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();
        emit sgTimerWriteStart();
    }

    //qDebug() << "NewClient::disconnected 199: " << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

    m_mutexDestroy.unlock();

    //qDebug() << "NewClient::disconnected 200: ";
}

void NewClient::slStop()
{
    if(m_bRun)
    {
        //qDebug() << "NewClient::slStop 1:" << "ClientID:" << m_iTimeMs << "ThreadID:" << QThread::currentThreadId();

        emit sgControl("", 3, "0");
        m_bRun = false;

        m_iTaskVar = 0;
        emit sgThreadTask();
    }

}

void NewClient::slControl(QString _sId, int _iVar, QString _sData, QByteArray _baIn)
{
    //qDebug() << "NewClient::slControl 0: " << _sId << _iVar << _sData;

    switch (_iVar) {
    case 0:

        break;
    case 1:
    {
        emit sgControl(_sId, 1, _sData);
        emit sgControl("", 4, "");
    }
    break;
    case 2:
    {
        emit sgControl(_sId, 2, _sData);
    }
    break;
    case 3:
    {
        emit sgControl(_sId, 3, _sData);
    }
    break;
    case 5:
    {
        emit sgControl(_sId, 5, _sData);
    }
    break;
    case 6:
    {
        emit sgControl(_sId, 6, QString::fromStdString(_baIn.toStdString()));
        emit sgControl("", 4, "");
    }
    break;
    case 8:
    {
        emit sgControl(_sId, 8, _sData);
    }
    break;
    case 9:
    {
        fFileRead(_baIn);
        emit sgControl("", 4, "");
    }
    break;
    case 10:
    {
        fFileWrite(_baIn);
        emit sgControl("", 4, "");
    }
    break;
    case 11:
    {
        if(!_baIn.isEmpty())
        {
            slAddDataWrite( _baIn );
        }

        emit sgControl(_sId, 10, _sData );
    }
    break;
    case 12:
    {
        slAddDataWrite( MyProtocol::fGetFile( StaticData::m_sDeskId
                                            , StaticData::m_sMyId
                                            , "stopCopy"
                                            , 10) );

        fFileRead( MyProtocol::fGetFile( StaticData::m_sMyId
                                       , StaticData::m_sDeskId
                                       , "stopCopy"
                                       , 10)  );

        emit sgControl("2", 10, "0" );

        emit sgFileWriteControl("", 0, "");
        emit sgFileReadControl("", 0, "");
    }
    break;
    case 13:
    {
        fComandLine(_baIn);
        emit sgControl("", 4, "");
    }
    break;
    case 14:
    {
        slAddDataWrite( MyProtocol::fComandLineResponse( _sId
                                                       , StaticData::m_sMyId
                                                       , _baIn
                                                       , _sData.toInt()) );
    }
    break;
    case 15:
    {
        //qDebug() << "NewClient::slControl 15: " << _sId << _sData;
        emit sgControl(_sId, 11, _sData);
        emit sgControl("", 4, "");

    }
    break;
    case 16:
    {
        //qDebug() << "NewClient::slControl 16: " << _sId << _sData << QString::fromStdString(_baIn.toStdString());

        if(_sId == "4")
        {
            emit sgControl(_sId, 10, QString::fromStdString(_baIn.toStdString()) );
        }
        else
        {
            if(_baIn.isEmpty())
            {
                emit sgControl(_sId, 10, _sData );

            }
            else
            {
                slAddDataWrite( _baIn );
            }
        }
    }
    break;
    case 17:
    {
        emit sgControl("", 4, "");
    }
    break;
    case 18:
    {
        emit sgControl(_sId, 12, _sData);
        //emit sgControl("", 4, "");
    }
    break;
    case 19:
    {
        emit sgControl(_sId, 13, _sData);
        emit sgControl("", 4, "");
    }
    break;
    case 20:
    {
        //qDebug() << "NewClient::slControl 20: " << QString::fromStdString(_baIn.toStdString() );

        emit sgControl(_sId, 14, QString::fromStdString(_baIn.toStdString()));
        emit sgControl("", 4, "");
    }
    break;
    case 21:
    {
        //qDebug() << "NewClient::slControl 20: " << QString::fromStdString(_baIn.toStdString() );

        emit sgControl(_sId, 15, QString::fromStdString(_baIn.toStdString()));
        emit sgControl("", 4, "");
    }
    break;
    case 22:
    {
        emit sgControl(_sId, 16, "");
    }
    break;
    case 24:
    {
        m_bLowActivity = true;
    }
    break;


    default:
        break;
    }

}

void NewClient::slSendMouseEvent(int _iVar, bool _bBtLorR, bool _bPressRelease, int _iX, int _iY)
{
    //qDebug() << "NewClient::slSendMouseEvent 0: " << _iVar << _bBtLorR << _bPressRelease << _iX << _iY;

    if(m_pParserSocket->m_baDeskTopID.length() > 0
        && StaticData::m_iTimeForStream < 2)
        slAddDataWrite( MyProtocol::fSendMouseEvents( StaticData::m_sMyId.toUtf8()
                                                    , m_pParserSocket->m_baDeskTopID
                                                    , _iVar, _bBtLorR, _bPressRelease, _iX, _iY) );

}

void NewClient::slTimer()
{

    emit sgTimer();
}

void NewClient::fFileWrite(QByteArray _baIn)
{
    //qDebug() << "NewClient::fFileWrite 0: " << _baIn.length() << _baIn.toHex(':') << "--------------------------";

    //qDebug() << "NewClient::fFileWrite 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "NewClient::fFileWrite 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "NewClient::fFileWrite 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "NewClient::fFileWrite 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "NewClient::fFileWrite 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return;

    int a_iData_5 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos - 1 ) );

    //qDebug() << "NewClient::fFileWrite 2.3: " << a_iData_4;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos + 1)
        return;

    int a_iData_6 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos - 1 ) );

    bool a_bOk;
    a_iData_6 = _baIn.mid(3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos - 1, 4).toHex().toUInt(&a_bOk, 16);

    //qDebug() << "NewClient::fFileWrite 2.3: " << a_iData_4;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3 + 1)
        return;




    //    qDebug() << "NewClient::fFileWrite 2.3: "
    //             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos)
    //                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3 + 1 )) )
        return;

    // qDebug() << "NewClient::fFileWrite 3: ";

    QByteArray a_baForId;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baForId.append(_baIn[i]);
    }

    QByteArray a_baFromId;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baFromId.append(_baIn[i]);
    }


    //FilePath

    QByteArray a_baFilePath;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baFilePath.append(_baIn[i]);
    }

    //FileSize

    QByteArray a_baFileSize;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos; i++)
    {
        a_baFileSize.append(_baIn[i]);
    }



    //Poss

    QByteArray a_baPoss;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos;
         i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos;
         i++)
    {
        a_baPoss.append(_baIn[i]);
    }

    //Data

    QByteArray a_baData;
    a_iPlasPos += 4;

    for(int i = 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos;
         i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos;
         i++)
    {
        a_baData.append(_baIn[i]);
    }

    //////


    bool m_bOk;
    //qDebug() << "NewClient::fFileWrite 4: " << QString::fromStdString(a_baFilePath.toStdString()) << a_baPoss.toHex().toUInt(&m_bOk, 16);

    if(QString::fromStdString(a_baFilePath.toStdString()) != "stopCopy"
        && a_baPoss.toHex().toUInt(&m_bOk, 16) == 0)
    {
        FileWrite *a_pFlR = new FileWrite(QString::fromStdString(a_baFromId.toStdString()));
        connect(a_pFlR, &FileWrite::sgControl, this, &NewClient::slControl);
        connect(this, &NewClient::sgTimer, a_pFlR, &FileWrite::slTimer, Qt::QueuedConnection);
        connect(this, &NewClient::sgFileWriteControl, a_pFlR, &FileWrite::slControl, Qt::QueuedConnection);

        a_pFlR->start();
    }

    emit sgFileWriteControl(QString::fromStdString(a_baFromId.toStdString()), 1, _baIn);

}

void NewClient::fFileRead(QByteArray _baIn)
{
    //qDebug() << "NewClient::fFileRead 0: " << _baIn.length() << _baIn.toHex(':') << "--------------------------";

    if(_baIn.length() < 4)
        return;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "NewClient::fFileRead 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "NewClient::fFileRead 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "NewClient::fFileRead 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "NewClient::fFileRead 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return;

    //    qDebug() << "NewClient::fFileRead 2.3: "
    //             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
    //                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 )) )
        return;


    //qDebug() << "NewClient::fFileRead 3: ";

    QByteArray a_baForId;
    a_iPlasPos = 0;

    //    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    //    {
    //        a_baForId.append(_baIn[i]);
    //    }

    QByteArray a_baFromId;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baFromId.append(_baIn[i]);
    }

    //FilePath

    QByteArray a_baFilePath;
    a_iPlasPos++;

    //    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    //    {
    //        a_baFilePath.append(_baIn[i]);
    //    }

    //Poss

    QByteArray a_baPoss;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos; i++)
    {
        a_baPoss.append(_baIn[i]);
    }


    //////////////////
    ///
    bool m_bOk;
    //qDebug() << "NewClient::fFileRead 4: " << QString::fromStdString(a_baFilePath.toStdString()) << a_baPoss.toHex().toUInt(&m_bOk, 16);

    if(QString::fromStdString(a_baFilePath.toStdString()) != "stopCopy"
        && a_baPoss.toHex().toUInt(&m_bOk, 16) == 0)
    {
        FileRead *a_pFlR = new FileRead(QString::fromStdString(a_baFromId.toStdString()));
        connect(a_pFlR, &FileRead::sgControl, this, &NewClient::slControl, Qt::QueuedConnection);
        connect(this, &NewClient::sgTimer, a_pFlR, &FileRead::slTimer, Qt::QueuedConnection);
        connect(this, &NewClient::sgFileReadControl, a_pFlR, &FileRead::slControl, Qt::QueuedConnection);

        a_pFlR->start();
    }

    emit sgFileReadControl(QString::fromStdString(a_baFromId.toStdString()), 1, _baIn);
}

void NewClient::fComandLine(QByteArray _baIn)
{
    //qDebug() << "NewClient::fComandLine 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "NewClient::fComandLine 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "NewClient::fComandLine 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "NewClient::fComandLine 2.2: " << (3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1) << a_iData_3;


    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "NewClient::fComandLine 2.3: "  << (3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1) << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return;


    //    qDebug() << "NewClient::fComandLine 2.3: "
    //             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
    //                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 )) )
        return;

    //    qDebug() << "NewClient::fComandLine 3: ";

    QByteArray a_baForId;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baForId.append(_baIn[i]);
    }

    QByteArray a_baFromId;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baFromId.append(_baIn[i]);
    }


    //ComandLine

    QByteArray a_baData;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }

    //Var

    QByteArray a_baVar;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos; i++)
    {
        a_baVar.append(_baIn[i]);
    }


    //    qDebug() << "NewClient::fComandLine 7: "
    //             << (3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
    //             << _baIn.mid(0, 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1).toHex(':');

    //qDebug() << "NewClient::fComandLine 7.1: " << QString::fromStdString(a_baData.toStdString());


    //////////////////

    if(a_baData.length() > 0
        && QString::fromStdString(a_baData.toStdString()) != "stopRun"
        && QString::fromStdString(a_baData.toStdString()).length() > 1 )
    {
        emit sgComanfLineControl(QString::fromStdString(a_baFromId.toStdString()), 2, "");

        bool a_bOk;
        ComandLine *a_pFlR = new ComandLine( QString::fromStdString(a_baFromId.toStdString())
                                            , a_baVar.toHex().toInt(&a_bOk, 16)
                                            );

        connect(a_pFlR, &ComandLine::sgControl, this, &NewClient::slControl);
        connect(this, &NewClient::sgComanfLineControl, a_pFlR, &ComandLine::slControl);

        a_pFlR->start();

        emit sgComanfLineControl(QString::fromStdString(a_baFromId.toStdString()), 1, a_baData);
    }
    else
    {
        if(a_baData.length() > 0
            && QString::fromStdString(a_baData.toStdString()) == "stopRun")
        {
            emit sgComanfLineControl(QString::fromStdString(a_baFromId.toStdString()), 2, a_baData);
        }
    }


}

void NewClient::slThreadTask()
{
    //qDebug() << "NewClient::slThreadTask 0:" << "ThreadID:" << QThread::currentThreadId();

    if(m_iTaskVar == 0)
    {
        exit(0);
    }
}
