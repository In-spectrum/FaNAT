#ifndef MYPROTOCOL_H
#define MYPROTOCOL_H

#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>

#ifdef Q_OS_ANDROID

#else
#ifdef Q_OS_LINUX
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #include <QtCore/QTextCodec>
    #else
    #include <QtCore5Compat/QTextCodec>
    #endif
#endif
#endif


class MyProtocol
{
public:
    MyProtocol();

    static inline QString m_sPrefix = "56Q47TYUAWERSDFGHJKLZIOP38XCVBNM1290";

    static uint8_t fGetCRC(const QByteArray& data, int _iSize);
    static bool fCRC_isOk(const QByteArray& data, uint8_t _iCRC);

    static QByteArray fSendUserLoginPassword(QString  _sLog, QString _sPas, QString _sId, QString _sKey, QString _sServerPas);
    static QByteArray fSendNewId(QString _sId, unsigned int _iVar);
    static QByteArray fConnectToDesktop(QString  _sLog, QString _sPas, QString _sId, bool _bStream);
    static QByteArray fGetStreamData(QString  _sLog);
    static QByteArray fStreamDataForClient(QString  _sDesktopId, QString  _sId, QString  _sUrl);

    static QByteArray fSendMouseEvents(QString  _sUserId, QString  _sDesktopId, int _iVar, bool _bBtLorR, bool _bPressRelease, int _iX, int _iY);
    static QByteArray fSendKeyEvents(QString  _sUserId, QString  _sDesktopId, unsigned int _iVar, unsigned int _iKey, unsigned int _iKeyboardLayout, QString  _sData);

    static QByteArray fGetActiveClient( QString  _sUserId);
    static QByteArray fSearchDesktop(QString  _sUserId, QString  _sDesktopLogin);
    static QByteArray fMaybeMyLogin(QString  _sDesktopLogin, QString  _sDesktopId);
    static QByteArray fSendClipboard(QString  _sDesktopId, unsigned int _iVar, QString _sData);
    static QByteArray fGetFile(QString  _sForId, QString  _sFromId, QString  _sFilePath, unsigned int _iPos);
    static QByteArray fSendFile(QString  _sForId, QString  _sFromId, QString  _sFilePath, unsigned int _iFileSize, unsigned int _iPos, QByteArray _baData);    
    static QByteArray fComandLineRequest(QString  _sForId, QString  _sFromId, QString  _sComand, unsigned int _iVar);
    static QByteArray fComandLineResponse(QString  _sForId, QString  _sFromId, QByteArray  _bComand, unsigned int _iVar);
    static QByteArray fMessageStatus(int _iVar, QString  _sData );
    static QByteArray fWatcher(QString  _sForId, QString  _sFromId);
    static QByteArray fVideoQualitySet(QString  _sForId, QString  _sFromId, unsigned int _iSizeF, unsigned int _iFPS, unsigned int _iEnvoderV, unsigned int _iEncSpeed, unsigned int _iBetrate, unsigned int _iLatencyZ, bool _bRtsp, unsigned int _iSound );
    static QByteArray fVideoQualityCurent(QString  _sForId, QString  _sFromId, unsigned int _iSizeF, unsigned int _iFPS, unsigned int _iEnvoderV, unsigned int _iEncSpeed, unsigned int _iBetrate, unsigned int _iLatencyZ, bool _bRTSP, unsigned int _iSound );
    static QByteArray fSomeDataForUser(QString  _sForUserID, QString  _sFromUserId, QByteArray _baData );
    static QByteArray fSendCurrentTime(quint8 _UserId);
    static QByteArray fSendVersion(QString  _sVar);
    static QByteArray fSendStatIP(QString  _sVar);
    static QByteArray fSendClientTimeControl(QString  _sIp, int _iVar);
    static QByteArray fMustStreamRestart();
    static QByteArray fKeyClienValid(QString _sKey);
    static QByteArray fSendToken(QString  _sVar);
    static QByteArray fSendLowActivityTime(QString _sData);

    static QString fEncoderClienKey(QString _sKey);
    static QString fIdGenerator(QString _sIn = "", QString _sPref = "", uint8_t _iMin = 8, uint8_t _iMax = 16);

};

#endif // MYPROTOCOL_H

