#include "MyProtocol.h"

MyProtocol::MyProtocol()
{

}

uint8_t MyProtocol::fGetCRC(const QByteArray& data, int _iSize)
{
    //qDebug() << "MyProtocol::fGetCRC 0: " << data.toHex(':') << _iSize << data.size();

    quint8 a_chCRC = 0;

    if(_iSize > data.size())
        return a_chCRC;

    //qDebug() << "MyProtocol::fGetCRC 1: ";

    for(int i = 0; i < _iSize; i++)
    {        

        a_chCRC += static_cast<quint8>(data.at(i));
    }

    //qDebug() << "MyProtocol::fGetCRC 2: " << (int)a_chCRC;

    return a_chCRC;

}

bool MyProtocol::fCRC_isOk(const QByteArray& data, uint8_t _iCRC)
{

    if( fGetCRC(data, data.size()) == _iCRC )
        return true;

    return false;

}

QByteArray MyProtocol::fSendUserLoginPassword(QString  _sLog, QString _sPas, QString _sId, QString _sKey, QString _sServerPas)
{
    //qDebug() << "MyProtocol::fSendUserLoginPassword 0: " << _sLog << _sPas << _sId << _sKey << _sServerPas;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x01);

    QByteArray a_baTemp(_sLog.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendUserLoginPassword 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    a_baSz.clear();
    a_baTemp.clear();

    a_baTemp.append(_sPas.toUtf8());
    a_iSz =  a_baTemp.length();

    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendUserLoginPassword 5: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baSz.clear();
    a_baTemp.clear();

    a_baTemp.append(_sId.toUtf8());
    a_iSz =  a_baTemp.length();
    //qDebug() << "MyProtocol::fSendUserLoginPassword 6.0: " << a_iSz << a_baTemp;

    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendUserLoginPassword 6.1: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    a_baSz.clear();
    a_baTemp.clear();

    a_baTemp.append(_sKey.toUtf8());
    a_iSz =  a_baTemp.length();
    //qDebug() << "MyProtocol::fSendUserLoginPassword 7.0: " << a_iSz << a_baTemp;

    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendUserLoginPassword 7.1: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    //ServerPass
    a_baSz.clear();
    a_baTemp.clear();

    a_baTemp.append(_sServerPas.toUtf8());
    a_iSz =  a_baTemp.length();
    //qDebug() << "MyProtocol::fSendUserLoginPassword 8.0: " << a_iSz << a_baTemp;

    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendUserLoginPassword 8.1: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fSendUserLoginPassword 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSendNewId(QString _sId, unsigned int _iVar)
{
    //qDebug() << "MyProtocol::fSendNewId 0: " << _sId;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x07);

    QByteArray a_baTemp(_sId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendNewId 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baSz.clear();
    a_baSz.append((_iVar >> 24) & 0xFF);
    a_baSz.append((_iVar >> 16) & 0xFF);
    a_baSz.append((_iVar >> 8) & 0xFF);
    a_baSz.append((_iVar >> 0) & 0xFF);

    a_baRequest.append(0x01);    
    a_baRequest.append(a_baSz.at(3));


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fSendNewId 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}


QByteArray MyProtocol::fConnectToDesktop(QString  _sLog, QString _sPas, QString _sId, bool _bStream)
{
    //qDebug() << "MyProtocol::fConnectToDesktop 0: " << _sLog << _sPas;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x02);

    QByteArray a_baTemp(_sLog.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fConnectToDesktop 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    a_baSz.clear();
    a_baTemp.clear();

    a_baTemp.append(_sPas.toUtf8());
    a_iSz =  a_baTemp.length();

    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fConnectToDesktop 5: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baSz.clear();
    a_baTemp.clear();

    a_baTemp.append(_sId.toUtf8());
    a_iSz =  a_baTemp.length();

    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fConnectToDesktop 6: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);




    a_baRequest.append(0x01);
    if(_bStream)
    {
        a_baRequest.append(0x01);
    }
    else
    {
        a_baRequest.append((char) 0x00);
    }



    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fConnectToDesktop 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}


QByteArray MyProtocol::fGetStreamData(QString  _sId)
{
    //qDebug() << "MyProtocol::fGetStreamData 0: " << _sLog;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x03);

    QByteArray a_baTemp(_sId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fGetStreamData 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fGetStreamData 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fStreamDataForClient(QString  _sDesktopId, QString  _sId, QString  _sUrl)
{
    //qDebug() << "MyProtocol::fStreamDataForClient 0: " << _sLog;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x04);

    QByteArray a_baTemp(_sDesktopId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fStreamDataForClient 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    a_baTemp = _sUrl.toUtf8();
    a_iSz =  a_baTemp.length();


    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fStreamDataForClient 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSendMouseEvents(QString  _sUserId, QString  _sDesktopId
                                        , int _iVar, bool _bBtLorR, bool _bPressRelease, int _iX, int _iY)
{
    //qDebug() << "MyProtocol::fSendMouseEvents 0: " << _iVar << _bBtLorR << _bPressRelease << _iX << _iY;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x05);

    QByteArray a_baTemp(_sUserId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fStreamDataForClient 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sDesktopId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fSendMouseEvents 5: " << a_baRequest.length();


    a_iSz = 7;
    a_baSz.resize(0);
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));


    a_iSz =  _iVar;
    a_baSz.resize(0);
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    //qDebug() << "MyProtocol::fSendMouseEvents 6: " << a_baRequest.length();


    if(_bBtLorR)
    {
        a_baRequest.append(0x01);
    }
    else
    {
        a_baRequest.append((char) 0x00);
    }

    if(_bPressRelease)
    {
        a_baRequest.append(0x01);
    }
    else
    {
        a_baRequest.append((unsigned char)'0');
    }

    //qDebug() << "MyProtocol::fSendMouseEvents 7: " << a_baRequest.length();

    a_iSz = _iX;
    //a_baRequest.append((a_iSz >> 24) & 0xFF);
    //a_baRequest.append((a_iSz >> 16) & 0xFF);
    a_baRequest.append((a_iSz >> 8) & 0xFF);
    a_baRequest.append((a_iSz >> 0) & 0xFF);

    //qDebug() << "MyProtocol::fSendMouseEvents 8: " << a_baRequest.length();

    a_iSz = _iY;
    //a_baRequest.append((a_iSz >> 24) & 0xFF);
    //a_baRequest.append((a_iSz >> 16) & 0xFF);
    a_baRequest.append((a_iSz >> 8) & 0xFF);
    a_baRequest.append((a_iSz >> 0) & 0xFF);

    //qDebug() << "MyProtocol::fSendMouseEvents 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );



//    qDebug() << "MyProtocol::fSendMouseEvents 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSendKeyEvents(QString  _sUserId, QString  _sDesktopId
                                        , unsigned int _iVar, unsigned int _iKey, unsigned int _iKeyboardLayout, QString  _sData)
{
    //qDebug() << "MyProtocol::fSendKeyEvents 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x06);

    QByteArray a_baTemp(_sUserId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendKeyEvents 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sDesktopId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fSendKeyEvents 5.0: " << a_baRequest.length();


    a_iSz = 9;
    a_baSz.resize(0);
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));


    a_iSz =  _iVar;
    a_baSz.resize(0);
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));



    a_iSz = _iKey;
    a_baRequest.append((a_iSz >> 24) & 0xFF);
    a_baRequest.append((a_iSz >> 16) & 0xFF);
    a_baRequest.append((a_iSz >> 8) & 0xFF);
    a_baRequest.append((a_iSz >> 0) & 0xFF);


    //qDebug() << "MyProtocol::fSendKeyEvents 5.1: " << _iKeyboardLayout;

    a_iSz = _iKeyboardLayout;
    a_baRequest.append((a_iSz >> 24) & 0xFF);
    a_baRequest.append((a_iSz >> 16) & 0xFF);
    a_baRequest.append((a_iSz >> 8) & 0xFF);
    a_baRequest.append((a_iSz >> 0) & 0xFF);


    a_baTemp = _sData.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    //qDebug() << "MyProtocol::fSendKeyEvents 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fSendKeyEvents 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fGetActiveClient(QString  _sUserId)
{
    //qDebug() << "MyProtocol::fGetActiveClient 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x08);

    QByteArray a_baTemp(_sUserId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fGetActiveClient 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fGetActiveClient 5.0: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fGetActiveClient 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSearchDesktop(QString  _sUserId, QString  _sDesktopLogin)
{
    //qDebug() << "MyProtocol::fSearchDesktop 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x09);

    QByteArray a_baTemp(_sUserId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSearchDesktop 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sDesktopLogin.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fSearchDesktop 5.0: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fSearchDesktop 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fMaybeMyLogin(QString _sDesktopLogin, QString  _sDesktopId)
{
    //qDebug() << "MyProtocol::fMaybeMyLogin 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x0A);

    QByteArray a_baTemp(_sDesktopLogin.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fMaybeMyLogin 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sDesktopId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    //qDebug() << "MyProtocol::fMaybeMyLogin 5.0: " << a_baRequest.length();

    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fMaybeMyLogin 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}


QByteArray MyProtocol::fSendClipboard(QString _sDesktopId, unsigned int _iVar, QString _sData)
{
    //qDebug() << "MyProtocol::fSendClipboard 0: " << _sDesktopId << _sUserId << _iVar << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x0B);

    QByteArray a_baTemp(_sDesktopId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendClipboard 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fSendClipboard 5.0: " << a_baRequest.length();


    a_iSz = 1;
    a_baSz.resize(0);
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));


    a_iSz =  _iVar;
    a_baSz.resize(0);
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));


    a_baTemp.clear();
    a_baTemp = _sData.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fSendClipboard 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fGetFile(QString  _sForId, QString  _sFromId
                                 , QString  _sFilePath, unsigned int _iPos )
{
    //qDebug() << "MyProtocol::fGetFile 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x0C);

    QByteArray a_baTemp(_sForId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fGetFile 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sFromId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fGetFile 5.0: " << a_baRequest.length();


    a_baTemp = _sFilePath.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_iSz =  _iPos;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(0x04);
    a_baRequest.append(a_baSz);


    //qDebug() << "MyProtocol::fGetFile 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fGetFile 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSendFile(QString  _sForId, QString  _sFromId
                                 , QString  _sFilePath, unsigned int _iFileSize
                                 , unsigned int _iPos, QByteArray _baData)
{
    //qDebug() << "MyProtocol::fSendFile 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x0D);

    QByteArray a_baTemp(_sForId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendFile 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sFromId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fSendFile 5.0: " << a_baRequest.length();


    a_baTemp = _sFilePath.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_iSz =  _iFileSize;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(0x04);
    a_baRequest.append(a_baSz);


    a_iSz =  _iPos;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(0x04);
    a_baRequest.append(a_baSz);




    a_iSz =  _baData.length();    

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz);
    a_baRequest.append(_baData);


    //qDebug() << "MyProtocol::fSendFile 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fSendFile 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fComandLineRequest(QString  _sForId, QString  _sFromId
                                 , QString  _sComand, unsigned int _iVar )
{
    //qDebug() << "MyProtocol::fComandLineRequest 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x0E);

    QByteArray a_baTemp(_sForId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fComandLineRequest 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sFromId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fComandLineRequest 5.0: " << a_baRequest.length();


    a_baTemp = _sComand.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    a_iSz =  _iVar;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(0x01);
    a_baRequest.append(a_baSz.at(3));


    //qDebug() << "MyProtocol::fComandLineRequest 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fComandLineRequest 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}


QByteArray MyProtocol::fComandLineResponse(QString  _sForId, QString  _sFromId
                                 , QByteArray  _bComand, unsigned int _iVar )
{
    //qDebug() << "MyProtocol::fComandLineResponse 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x0F);

    QByteArray a_baTemp(_sForId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fComandLineResponse 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sFromId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fComandLineResponse 5.0: " << a_baRequest.length();


    a_baTemp = _bComand;
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    a_iSz =  _iVar;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(0x01);
    a_baRequest.append(a_baSz.at(3));


    //qDebug() << "MyProtocol::fComandLineResponse 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fComandLineResponse 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fMessageStatus(int _iVar, QString  _sData )
{
    //qDebug() << "MyProtocol::fMessageStatus 0: " << _iVar << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x10);

    unsigned int a_iSz =  _iVar;

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fMessageStatus 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(0x01);
    a_baRequest.append(a_baSz.at(3));

    if(_sData.length() > 255)
        _sData = _sData.mid(0, 255);

    QByteArray a_baTemp = _sData.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    //qDebug() << "MyProtocol::fMessageStatus 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fMessageStatus 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');


    return a_baRequest;
}

QByteArray MyProtocol::fWatcher(QString  _sForId, QString  _sFromId)
{
    //qDebug() << "MyProtocol::fWatcher 0: " << _iVar << _iKey << _sData;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x11);

    QByteArray a_baTemp(_sForId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fWatcher 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_baTemp = _sFromId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    //qDebug() << "MyProtocol::fWatcher 5.0: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fWatcher 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fVideoQualitySet(QString  _sForId, QString  _sFromId
                                 , unsigned int _iSizeF, unsigned int _iFPS, unsigned int _iEnvoderV, unsigned int _iEncSpeed, unsigned int _iBetrate, unsigned int _iLatencyZ
                                 , bool _bRtsp, unsigned int _iSound)
{
    //qDebug() << "MyProtocol::fVideoQualitySet 0: ";

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x12);

    QByteArray a_baTemp(_sForId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fVideoQualitySet 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baTemp = _sFromId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_iSz = 8;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iSizeF;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iFPS;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iEnvoderV;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iEncSpeed;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iBetrate;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iLatencyZ;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));


    if(_bRtsp)
    {
        a_baRequest.append(0x01);
    }
    else
    {
        a_baRequest.append((char)0x00);
    }

    a_iSz =  _iSound;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    //qDebug() << "MyProtocol::fVideoQualitySet 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fVideoQualitySet 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fVideoQualityCurent(QString  _sForId, QString  _sFromId
                                 , unsigned int _iSizeF, unsigned int _iFPS, unsigned int _iEnvoderV, unsigned int _iEncSpeed, unsigned int _iBetrate, unsigned int _iLatencyZ
                                 , bool _bRtsp, unsigned int _iSound )
{
    //qDebug() << "MyProtocol::fVideoQualityCurent 0: ";

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x13);

    QByteArray a_baTemp(_sForId.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fVideoQualityCurent 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baTemp = _sFromId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_iSz = 8;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iSizeF;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iFPS;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iEnvoderV;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iEncSpeed;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iBetrate;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    a_iSz =  _iLatencyZ;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));


    if(_bRtsp)
    {
        a_baRequest.append(0x01);
    }
    else
    {
        a_baRequest.append((char)0x00);
    }


    a_iSz =  _iSound;
    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));

    //qDebug() << "MyProtocol::fVideoQualityCurent 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


//    qDebug() << "MyProtocol::fVideoQualityCurent 200: "
//             << a_baRequest.length()
//             << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSomeDataForUser(QString  _sForUserID, QString  _sFromUserId, QByteArray _baData )
{
    //qDebug() << "MyProtocol::fSomeDataForUser 0: ";

    //_baData structure
    //dataID = 2Bt ( < 255)
    //dataSZ = 1Bt
    //DATA   = dataSZ ( < 251)

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x14);

    QByteArray a_baTemp(_sForUserID.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSomeDataForUser 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baTemp = _sFromUserId.toUtf8();
    a_iSz =  a_baTemp.length();

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);



    a_iSz =  _baData.length();

    if(a_iSz > 250 || a_iSz < 4 )// || _baData.at(0) == (char)0xFF)
    {
        a_baRequest.append((char)0x00);
    }
    else
    {
        a_baSz.clear();
        a_baSz.append((a_iSz >> 24) & 0xFF);
        a_baSz.append((a_iSz >> 16) & 0xFF);
        a_baSz.append((a_iSz >> 8) & 0xFF);
        a_baSz.append((a_iSz >> 0) & 0xFF);

        a_baRequest.append(a_baSz.at(3));
        a_baRequest.append(_baData);
    }

    //qDebug() << "MyProtocol::fSomeDataForUser 9: " << a_baRequest.length();


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );


    // qDebug() << "MyProtocol::fSomeDataForUser 200: "
    //          << a_baRequest.length()
    //          << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSendCurrentTime(quint8 _UserId)
{

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x15);


    QByteArray a_baTemp( QString::number( QDateTime::currentSecsSinceEpoch() ).toUtf8() );
    unsigned int a_iSz =  a_baTemp.length();

    a_baRequest.append(0x01);
    a_baRequest.append( QString::number( _UserId ).toUtf8() );

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendCurrentTime 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);

    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fSendCurrentTime 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}



QByteArray MyProtocol::fSendVersion(QString  _sVar)
{
    //qDebug() << "MyProtocol::fSendVersion 0: ";

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x01);

    QByteArray a_baTemp(_sVar.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendVersion 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fSendVersion 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSendStatIP(QString  _sVar)
{
    //qDebug() << "MyProtocol::fSendStatIP 0: " << _sVar;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x16);

    QByteArray a_baTemp(_sVar.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendStatIP 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    qDebug() << "MyProtocol::fSendStatIP 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSendClientTimeControl(QString  _sIp, int _iVar)
{
    //qDebug() << "MyProtocol::fSendClientTimeControl 0: " << _sVar;

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x02);

    QByteArray a_baTemp(_sIp.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendClientTimeControl 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_iSz =  _iVar;

    a_baSz.clear();
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);

    a_baRequest.append(0x01);
    a_baRequest.append(a_baSz.at(3));

    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fSendClientTimeControl 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fMustStreamRestart()
{
    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x15);

    QByteArray a_baTemp(QString("MustSreamRestart").toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fMustStreamRestart 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fMustStreamRestart 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fKeyClienValid(QString _sKey)
{
    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x17);

    QByteArray a_baTemp(_sKey.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fMustStreamRestart 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fMustStreamRestart 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QString MyProtocol::fEncoderClienKey(QString _sKey)
{
    //qDebug() << "MyProtocol::fEncoderClienKey 0: " << _sKey;

    if(_sKey.length() < 4)
        return "";

    QByteArray a_baTemp(_sKey.toUtf8());
    uint8_t a_iSum = 0;

    //qDebug() << "MyProtocol::fEncoderClienKey 5: " << QString::fromStdString(a_baTemp.toStdString());

    for(int i = 0; i < a_baTemp.length(); i++)
    {
        a_iSum += (static_cast<quint8>(a_baTemp.at(i)) + static_cast<quint8>(a_baTemp.at(3)));
    }

    //qDebug() << "MyProtocol::fEncoderClienKey 7: " << a_iSum;

    return QString::number(a_iSum);
}

QString MyProtocol::fIdGenerator(QString _sIn, QString _sPref, uint8_t _iMin, uint8_t _iMax)
{
    QString a_sOut = "";

    if(_iMin == 0)
        _iMin = 8;

    if(_iMin <= _iMax)
        _iMax = _iMin + 1;

    if(_sIn.length() < 4)
        _sIn = "1234567890";

    int a_iSz = QRandomGenerator::global()->bounded(_iMin, _iMax);

    for(int i = 0; i < a_iSz; i++)
    {
        if(QRandomGenerator::global()->bounded(_sIn.length()-1) % 2 == 0)
            a_sOut += _sIn.at( QRandomGenerator::global()->bounded(_sIn.length()-1) ).toLower();
        else
            a_sOut += _sIn.at( QRandomGenerator::global()->bounded(_sIn.length()-1) );
    }




    if(_sPref.length() > 6)
    {
        int a_iUelL = a_sOut.length() / 4;
        int a_iIdL = _sPref.length() / 3;

        QString a_Temp = a_sOut.mid(0, a_iUelL);
        a_Temp += _sPref.mid(0, a_iIdL);
        a_Temp += a_sOut.mid(a_iUelL, a_iUelL);
        a_Temp += _sPref.mid(a_iIdL, a_iIdL);
        a_Temp += a_sOut.mid(2 * a_iUelL, a_iUelL );
        a_Temp += _sPref.mid(2 * a_iIdL, a_sOut.length() - 2 * a_iIdL );
        a_Temp += a_sOut.mid(3 * a_iUelL, a_sOut.length() - 3 * a_iUelL );

        a_sOut = a_Temp;
    }

    //qDebug() << "MyProtocol::fIdGenerator 5: " << a_sOut;

    return a_sOut;
}

QByteArray MyProtocol::fSendToken(QString  _sVar)
{
    //qDebug() << "MyProtocol::fSendToken 0: ";

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x18);

    QByteArray a_baTemp(_sVar.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendToken 3: " << a_baSz.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fSendToken 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}

QByteArray MyProtocol::fSendLowActivityTime(QString _sData)
{

    QByteArray a_baRequest;
    a_baRequest.append(0xFF);
    a_baRequest.append(0x19);


    QByteArray a_baTemp(_sData.toUtf8());
    unsigned int a_iSz =  a_baTemp.length();

    QByteArray a_baSz;
    a_baSz.append((a_iSz >> 24) & 0xFF);
    a_baSz.append((a_iSz >> 16) & 0xFF);
    a_baSz.append((a_iSz >> 8) & 0xFF);
    a_baSz.append((a_iSz >> 0) & 0xFF);
    //qDebug() << "MyProtocol::fSendToken 3: " << fSendLowActivityTime.length() << a_baSz.toHex(':');

    a_baRequest.append(a_baSz.at(3));
    a_baRequest.append(a_baTemp);


    a_baRequest.append( fGetCRC(a_baRequest.mid(1), a_baRequest.size()-1) );

    //qDebug() << "MyProtocol::fSendLowActivityTime 200: " << a_baRequest.toHex(':');

    return a_baRequest;
}






