#include "parsersocketdata.h"

ParserSocketData::ParserSocketData()
{
}


ParserSocketData::~ParserSocketData()
{
    fClearData();

    //qDebug() << "ParserSocketData::ParserSocketData 200: " << " thread end";
}

void ParserSocketData::fAddData(QByteArray _sData)
{
    //qDebug() << "ParserSocketData::fAddData 0: " << _sData.toHex(':');


    m_mutexNewDataRead.lock();
    m_sArrData.append(_sData);    
    m_mutexNewDataRead.unlock();
}

void ParserSocketData::fClearData()
{
     if(!m_sArrData.isEmpty())
         m_sArrData.clear();

}

void ParserSocketData::fParser()
{
     if(!fIsEpty())
     {
         m_baPareser.append( m_sArrData.at(0) );

         m_mutexNewDataRead.lock();
         m_sArrData.removeFirst();
         m_mutexNewDataRead.unlock();

         m_baPareser = fNextStep(m_baPareser);
         //qDebug() << "ParserSocketData::fParser 10:" << m_baPareser.toHex(':');
     }

    //qDebug() << "ParserSocketData::fParser 200: ";
}

bool ParserSocketData::fIsEpty()
{
    return m_sArrData.isEmpty();
}

QByteArray ParserSocketData::fNextStep(QByteArray _baIn)
{
//    qDebug() << "ParserSocketData::fNextStep 0: "
//             << _baIn.length() << _baIn.toHex(':');
             //<< QString::fromStdString(_baIn.toStdString());

    int a_iStartPos = _baIn.indexOf((char)0xFF);

    if(a_iStartPos < 0)
    {
        _baIn.clear();
        return _baIn;
    }

    _baIn = _baIn.mid(a_iStartPos, _baIn.length() - a_iStartPos);

    int a_iPos = 0;
    int a_iPrevPos = 1;

    while (a_iPos != a_iPrevPos && a_iPos < _baIn.length())
    {
        a_iPrevPos = a_iPos;
        QByteArray a_baData = _baIn.mid(a_iPos, _baIn.length() - a_iPos);

        //qDebug() << "ParserSocketData::fNextStep 2: " << a_iPos << a_baData.length() << a_baData.toHex(':');

        a_iStartPos = a_baData.indexOf((char)0xFF);

        if(a_iStartPos < 0)
        {
            _baIn.clear();
            return _baIn;
        }
        else
        {
            if(a_iStartPos > 0)
                 a_baData = a_baData.mid(a_iStartPos, a_baData.length() - a_iStartPos);
        }

        //qDebug() << "ParserSocketData::fNextStep 3: " << a_iPos << a_baData.length() << a_baData.toHex(':');

        if(a_baData.length() < 2)
            break;

        if(a_baData.at(0) == (char)0xFF)
        {
            switch (a_baData.at(1)) {
            case (char)0x03:
                a_iPos += fGetStreamData(a_baData);
                break;
            case (char)0x04:
                a_iPos += fSetStreamData(a_baData);
                break;
            case (char)0x05:
                a_iPos += fMouseEvents(a_baData);
                break;
            case (char)0x06:
                a_iPos += fKeyEvents(a_baData);
                break;
            case (char)0x07:
                a_iPos += fNewId(a_baData);
                break;
            case (char)0x08:
                a_iPos += fGetActiveClient(a_baData);
                break;
            case (char)0x0A:
                a_iPos += fMaybeMyLogin(a_baData);
                break;
            case (char)0x0B:
                a_iPos += fBufferData(a_baData);
                break;
            case (char)0x0C:
                a_iPos += fGetFile(a_baData);
                break;
            case (char)0x0D:
                a_iPos += fSendFile(a_baData);
                break;
            case (char)0x0E:
                a_iPos += fComandLine(a_baData);
                break;
            case (char)0x0F:
                a_iPos += fComandLine(a_baData);
                break;
            case (char)0x10:
                a_iPos += fMessageStatus(a_baData);
                break;
            case (char)0x11:
                a_iPos += fWatcher(a_baData);
                break;
            case (char)0x12:
                a_iPos += fVideoQualitySet(a_baData);
                break;
            case (char)0x13:
                a_iPos += fVideoQualityCurent(a_baData);
                break;
            case (char)0x14:
                a_iPos += fSomeData(a_baData);
                break;
            case (char)0x17:
                a_iPos += fKeyClienValid(a_baData);
                break;
            default:
                break;
            }
        }
    }

    if(a_iPos < _baIn.length())
    {
        return _baIn.mid(a_iPos, _baIn.length() - a_iPos);
    }

    _baIn.clear();

    return _baIn;
}

unsigned int ParserSocketData::fGetStreamData(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fGetStreamData 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fGetStreamData 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;


    //qDebug() << "ParserSocketData::fGetStreamData 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fGetStreamData 3: ";

    QByteArray a_baClient;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baClient.append(_baIn[i]);
    }


    //generator URL-descriptor

    QString a_Url = StaticData::m_sWithoutStream;

    //qDebug() << "ParserSocketData::fGetStreamData 6: " << a_Url;


    emit sgControl(StaticData::m_sMyId, 1, a_Url, "");

    emit sgAddDataWrite( MyProtocol::fStreamDataForClient( StaticData::m_sMyId
                                                           , QString::fromStdString(a_baClient.toStdString())
                                                           , a_Url) );

    ////------------
    a_iPlasPos++;
    return 3 + a_iData_1 + a_iPlasPos;
}

unsigned int ParserSocketData::fSetStreamData(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fSetStreamData 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fSetStreamData 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fSetStreamData 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fSetStreamData 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    //qDebug() << "ParserSocketData::fSetStreamData 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fSetStreamData 3: ";

    m_baDeskTopID.resize(0);
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        m_baDeskTopID.append(_baIn[i]);
    }

    QByteArray a_baClientId;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baClientId.append(_baIn[i]);
    }

    //Url

    QByteArray a_baUrl;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baUrl.append(_baIn[i]);
    }

//    qDebug() << "ParserSocketData::fSetStreamData 4: "
//             << QString::fromStdString(m_baDeskTopID.toStdString())
//             << QString::fromStdString(a_baClientId.toStdString())
//             << QString::fromStdString(a_baUrl.toStdString());

    //QThread::sleep(2);
    emit sgControl(QString::fromStdString(m_baDeskTopID.toStdString()), 2, QString::fromStdString(a_baUrl.toStdString()), "");

    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos;
}

unsigned int ParserSocketData::fMouseEvents(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fMouseEvents 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fMouseEvents 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fMouseEvents 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fMouseEvents 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    //qDebug() << "ParserSocketData::fMouseEvents 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fMouseEvents 3: ";

    QByteArray a_baDesktopId;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baDesktopId.append(_baIn[i]);
    }

    QByteArray a_baClientId;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baClientId.append(_baIn[i]);
    }

    //Url

    QByteArray a_baData;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }

//    qDebug() << "ParserSocketData::fMouseEvents 4: "
//             << QString::fromStdString(a_baDesktopId.toStdString())
//             << QString::fromStdString(a_baClientId.toStdString())
//             << a_baData.toHex(':');

//    qDebug() << "ParserSocketData::fMouseEvents 5: "
//             << (      ((static_cast<unsigned int>(a_baData.at(3)) & 0xFF) << 8)
//                     + ((static_cast<unsigned int>(a_baData.at(4)) & 0xFF) << 0) )
//             << (  ((static_cast<unsigned int>(a_baData.at(5)) & 0xFF) << 8)
//                 + ((static_cast<unsigned int>(a_baData.at(6)) & 0xFF) << 0) );

    bool a_bOk;
//    qDebug() << "ParserSocketData::fMouseEvents 6: "
//             << a_baData.mid(3,2).toHex().toInt(&a_bOk, 16)/100.
//             << a_baData.mid(5,2).toHex().toInt(&a_bOk, 16)/100.;



    emit sgControl(QString::fromStdString(a_baClientId.toStdString()), 6, "1", "");


    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos;
}

unsigned int ParserSocketData::fKeyEvents(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fKeyEvents 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fKeyEvents 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fKeyEvents 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fKeyEvents 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fKeyEvents 2.3: " << _baIn.mid( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ).toHex(':') << a_iData_4;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return 0;

    // qDebug() << "ParserSocketData::fKeyEvents 2.4: "
    //          <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fKeyEvents 3: ";

    QByteArray a_baLogDesktop;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baLogDesktop.append(_baIn[i]);
    }

    QByteArray a_baLogClient;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baLogClient.append(_baIn[i]);
    }

    //Data

    QByteArray a_baData;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }


    a_iPlasPos++;
    for(int i =  3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }

    // qDebug() << "ParserSocketData::fKeyEvents 4: "
    //          << QString::fromStdString(a_baLogDesktop.toStdString())
    //          << QString::fromStdString(a_baLogClient.toStdString())
    //          << QString::fromStdString(a_baData.toStdString())
    //          << _baIn.mid(0, 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1).toHex(':');


    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos;
}

unsigned int ParserSocketData::fNewId(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fNewId 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fNewId 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fNewId 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;


    //qDebug() << "ParserSocketData::fNewId 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fNewId 3: ";

    QByteArray a_baTemp;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baTemp.append(_baIn[i]);
    }

    StaticData::m_sMyId = QString::fromStdString(a_baTemp.toStdString());

    QByteArray a_baDevServ;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baDevServ.append(_baIn[i]);
    }


    if(StaticData::m_sMyId.length() == 0)
        StaticData::m_sMyId = "0";
    else
    {
        if(StaticData::m_bDevServer
            || ( a_baDevServ.length() > 0 && static_cast<quint8>( a_baDevServ.at(0) ) > 0 )
            )
        {
            QString a_sId = StaticData::m_sMyId;
            a_sId += MyProtocol::fIdGenerator(MyProtocol::m_sPrefix, "", 16, 26);
            a_sId += QString::number( QDateTime::currentMSecsSinceEpoch() );
            a_sId += "_uds";

            //qDebug() << "ParserSocketData::fNewId 9: " << a_sId;

            StaticData::m_sMyId = a_sId;

            emit sgControl("0", 22, "", "");
        }
    }

    //qDebug() << "ParserSocketData::fNewId 200: " << StaticData::m_sMyId << a_baDevServ.toHex(':');

    ////------------
    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iPlasPos;
}

unsigned int ParserSocketData::fGetActiveClient(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fGetActiveClient 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fGetActiveClient 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;


    //qDebug() << "ParserSocketData::fGetActiveClient 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fGetActiveClient 3: ";

    QByteArray a_baClientId;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baClientId.append(_baIn[i]);
    }

    //qDebug() << "ParserSocketData::fGetActiveClient 10: " << QString::fromStdString(a_baClientId.toStdString());

    emit sgControl(QString::fromStdString(a_baClientId.toStdString())
                   , 17
                   , ""
                   , "");

    a_iPlasPos++;
    return 3 + a_iData_1 + a_iPlasPos;
}


unsigned int ParserSocketData::fMaybeMyLogin(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fMaybeMyLogin 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fMaybeMyLogin 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fMaybeMyLogin 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;


    //qDebug() << "ParserSocketData::fMaybeMyLogin 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fMaybeMyLogin 3: ";

    QByteArray a_baDesktopLogin;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baDesktopLogin.append(_baIn[i]);
    }

    QByteArray a_baDesktopId;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baDesktopId.append(_baIn[i]);
    }

    emit sgControl(QString::fromStdString(a_baDesktopLogin.toStdString()), 5, QString::fromStdString(a_baDesktopId.toStdString()), "");


    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iPlasPos;
}

unsigned int ParserSocketData::fBufferData(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fBufferData 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    uint a_iData_1 = static_cast<quint8>(_baIn.at( 2 ));

//    qDebug() << "ParserSocketData::fBufferData 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>(_baIn.at( 3 + a_iData_1 + a_iPlasPos - 1 ));

//    qDebug() << "ParserSocketData::fBufferData 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>(_baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ));

//    qDebug() << "ParserSocketData::fBufferData 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;


//    qDebug() << "ParserSocketData::fBufferData 2.4: "
//             <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 )) )
        return 0;

//    qDebug() << "ParserSocketData::fBufferData 3: ";

    QByteArray a_baDesktopId;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baDesktopId.append(_baIn[i]);
    }

    //Var

    QByteArray a_baVar;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baVar.append(_baIn[i]);
    }

    //Data

    QByteArray a_baData;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }


//    if(static_cast<quint8>(a_baVar.at(0)) == 2)
//        qDebug() << "ParserSocketData::fBufferData 10: "
//             << static_cast<quint8>(a_baVar.at(0))
//             << QString::fromStdString(a_baData.toStdString());

    emit sgControl(QString::number(static_cast<quint8>(a_baVar.at(0)))
                   , 8
                   , QString::fromStdString(a_baData.toStdString())
                   , "");


    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos;
}

unsigned int ParserSocketData::fGetFile(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fGetFile 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fGetFile 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fGetFile 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fGetFile 2.2: " << (3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1) << a_iData_3;


    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fGetFile 2.3: "  << (3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1) << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return 0;


//    qDebug() << "ParserSocketData::fGetFile 2.3: "
//             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
//                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fGetFile 3: ";


    QByteArray a_baForId;
    a_iPlasPos = 0;

//    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
//    {
//        a_baForId.append(_baIn[i]);
//    }

    QByteArray a_baFromId;
    a_iPlasPos++;

//    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
//    {
//        a_baFromId.append(_baIn[i]);
//    }


    //FilePath

    QByteArray a_baData;
    a_iPlasPos++;

//    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
//    {
//        a_baData.append(_baIn[i]);
//    }

    //Poss

    QByteArray a_baPoss;
    a_iPlasPos++;

//    for(int i =  3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos; i++)
//    {
//        a_baPoss.append(_baIn[i]);
//    }



    emit sgControl(""
                   , 9
                   , ""
                   , _baIn.mid(0, 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1));


    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos;
}

unsigned int ParserSocketData::fSendFile(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fSendFile 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fSendFile 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fSendFile 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fSendFile 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fSendFile 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return 0;

    int a_iData_5 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fSendFile 2.3: " << a_iData_4;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos + 1)
        return 0;

    int a_iData_6 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos - 1 ) );

    bool a_bOk;
    a_iData_6 = _baIn.mid(3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos - 1, 4).toHex().toUInt(&a_bOk, 16);

    //qDebug() << "ParserSocketData::fSendFile 2.3: " << a_iData_4;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3 + 1)
        return 0;




//    qDebug() << "ParserSocketData::fSendFile 2.3: "
//             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos)
//                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3 + 1 )) )
        return 0;

   // qDebug() << "ParserSocketData::fSendFile 3: ";

    QByteArray a_baForId;
    a_iPlasPos = 0;

//    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
//    {
//        a_baForId.append(_baIn[i]);
//    }

    QByteArray a_baFromId;
    a_iPlasPos++;

//    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
//    {
//        a_baFromId.append(_baIn[i]);
//    }


    //FilePath

    QByteArray a_baFilePath;
    a_iPlasPos++;

//    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
//    {
//        a_baFilePath.append(_baIn[i]);
//    }

    //FileSize

    QByteArray a_baFileSize;
    a_iPlasPos++;

//    for(int i =  3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos; i++)
//    {
//        a_baFileSize.append(_baIn[i]);
//    }



    //Poss

    QByteArray a_baPoss;
    a_iPlasPos++;

//    for(int i = 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos;
//            i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos;
//        i++)
//    {
//        a_baPoss.append(_baIn[i]);
//    }

    //Poss

    QByteArray a_baData;
    a_iPlasPos += 4;

//    for(int i = 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos;
//            i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos;
//        i++)
//    {
//        a_baData.append(_baIn[i]);
//    }



    emit sgControl(""
                   , 10
                   , ""
                   , _baIn.mid(0, 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 1));


    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos;
}


unsigned int ParserSocketData::fComandLine(QByteArray _baIn)
{
//    qDebug() << "ParserSocketData::fComandLine 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fComandLine 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fComandLine 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fComandLine 2.2: " << (3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1) << a_iData_3;


    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fComandLine 2.3: "  << (3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1) << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return 0;


//    qDebug() << "ParserSocketData::fComandLine 2.3: "
//             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
//                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 )) )
        return 0;

//    qDebug() << "ParserSocketData::fComandLine 3: ";

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


//    qDebug() << "ParserSocketData::fComandLine 7: "
//             << (3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
//             << _baIn.mid(0, 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1).toHex(':');

    switch (_baIn.at(1)) {
        case (char)0x0E:
        emit sgControl(QString::fromStdString(a_baForId.toStdString())
                       , 13
                       , QString::fromStdString(a_baFromId.toStdString())
                       , _baIn.mid(0, 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1));
            break;
        case (char)0x0F:
        bool a_bOk;
        emit sgControl(QString::number(a_baVar.toHex().toInt(&a_bOk, 16))
                       , 15
                       , QString::fromStdString(a_baData.toStdString())
                       , "");
        break;
    }



    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos;
}

unsigned int ParserSocketData::fMessageStatus(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fMessageStatus 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fComandLine 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fComandLine 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;




//    qDebug() << "ParserSocketData::fComandLine 2.3: "
//             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iPlasPos)
//                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iPlasPos)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iPlasPos + 1 )) )
        return 0;

//    qDebug() << "ParserSocketData::fComandLine 3: ";



    QByteArray a_baForId;
    a_iPlasPos = 0;

    int a_iVar = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    QByteArray a_baData;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }


    emit sgControl(QString::number(a_iVar)
                   , 18
                   , a_baData
                   , "");


    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iPlasPos;
}

unsigned int ParserSocketData::fWatcher(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fWatcher 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fWatcher 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fWatcher 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;



//    qDebug() << "ParserSocketData::fWatcher 2.3: "
//             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iPlasPos)
//                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iPlasPos)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iPlasPos + 1 )) )
        return 0;

//    qDebug() << "ParserSocketData::fWatcher 3: ";

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



//    qDebug() << "ParserSocketData::fWatcher 7: "
//             << (3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
//             << _baIn.mid(0, 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1).toHex(':');


    emit sgControl(QString::fromStdString(a_baForId.toStdString())
                   , 19
                   , QString::fromStdString(a_baFromId.toStdString())
                   , "");


    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iPlasPos;
}


unsigned int ParserSocketData::fVideoQualitySet(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fVideoQualitySet 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fVideoQualitySet 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fVideoQualitySet 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fVideoQualitySet 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    //qDebug() << "ParserSocketData::fVideoQualitySet 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fVideoQualitySet 3: ";

    QByteArray a_baLogDesktop;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baLogDesktop.append(_baIn[i]);
    }

    QByteArray a_baLogClient;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baLogClient.append(_baIn[i]);
    }

    //Data

    QByteArray a_baData;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }

//        qDebug() << "ParserSocketData::fVideoQualitySet 4: "
//                 << QString::fromStdString(a_baLogDesktop.toStdString())
//                 << QString::fromStdString(a_baLogClient.toStdString())
//                 << QString::fromStdString(a_baData.toStdString());

    if(a_baData.length() == 8)
    {
        emit sgControl(""
                       , 20
                       , ""
                       , a_baData);
    }

    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos;
}

unsigned int ParserSocketData::fVideoQualityCurent(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fVideoQualityCurent 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fVideoQualityCurent 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fVideoQualityCurent 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fVideoQualityCurent 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    //qDebug() << "ParserSocketData::fVideoQualityCurent 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fVideoQualityCurent 3: ";

    QByteArray a_baLogDesktop;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baLogDesktop.append(_baIn[i]);
    }

    QByteArray a_baLogClient;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baLogClient.append(_baIn[i]);
    }

    //Data

    QByteArray a_baData;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }

    //        qDebug() << "ParserSocketData::fVideoQualityCurent 4: "
    //                 << QString::fromStdString(a_baLogDesktop.toStdString())
    //                 << QString::fromStdString(a_baLogClient.toStdString())
    //                 << QString::fromStdString(a_baData.toStdString());

    if(QString::fromStdString(a_baLogClient.toStdString()) == StaticData::m_sDeskId)
    {
        //qDebug() << "ParserSocketData::fVideoQualityCurent 5: ";

        emit sgControl(""
                       , 21
                       , ""
                       , a_baData);
    }




    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos;
}

unsigned int ParserSocketData::fSomeData(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fSomeData 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fSomeData 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "ParserSocketData::fSomeData 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return 0;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "ParserSocketData::fSomeData 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return 0;

    // qDebug() << "ParserSocketData::fSomeData 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fSomeData 3: ";

    QByteArray _sForUser;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        _sForUser.append(_baIn[i]);
    }

    QByteArray a_baFromUser;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baFromUser.append(_baIn[i]);
    }

    //Data

    QByteArray a_baData;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baData.append(_baIn[i]);
    }

    // qDebug() << "ParserSocketData::fSomeData 4: "
    //          << QString::fromStdString(_sForUser.toStdString())
    //          << QString::fromStdString(a_baFromUser.toStdString())
    //          << a_baData.toHex(':');


    if(a_baData.length() > 3)
    {
        // qDebug() << "ParserSocketData::fSomeData 5: "
        //          << QString::fromStdString(a_baData.mid(3).toStdString());

        //fPareserSomeData(QString::fromStdString(a_baFromUser.toStdString()), a_baData );
    }




    a_iPlasPos++;
    return 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos;
}

unsigned int ParserSocketData::fKeyClienValid(QByteArray _baIn)
{
    //qDebug() << "ParserSocketData::fKeyClienValid 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return 0;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "ParserSocketData::fKeyClienValid 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return 0;


    //qDebug() << "ParserSocketData::fKeyClienValid 2.3: "
    //         <<  MyProtocol::fCRC_isOk(_baIn.mid(1, 1 + a_iData_1 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iPlasPos), _baIn.at( 1 + a_iData_1 + a_iPlasPos + 1 )) )
        return 0;

    //qDebug() << "ParserSocketData::fKeyClienValid 3: ";

    QByteArray a_baClientId;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baClientId.append(_baIn[i]);
    }

    //qDebug() << "ParserSocketData::fKeyClienValid 10: " << QString::fromStdString(a_baClientId.toStdString());

    emit sgAddDataWrite( MyProtocol::fKeyClienValid( MyProtocol::fEncoderClienKey( QString::fromStdString(a_baClientId.toStdString()) ) ) );

    a_iPlasPos++;
    return 3 + a_iData_1 + a_iPlasPos;
}
