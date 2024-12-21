#ifndef CONTROL_H
#define CONTROL_H



#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QClipboard>
#include <QMimeData>
#include <QScreen>


#include "ping.h"
#include "settingsapp.h"
#include "newclient.h"



class Control : public SettingsApp
{
    Q_OBJECT

public:
    Control(QQmlApplicationEngine *_pApp);
    ~Control();

public slots:
    void slotDestruction();
    void slotFindCheldren();
    void slotTimer();
    void slConnectToServer(QString _sLogin, QString _sPassword);
    void slConnectToDesktop(bool _bStream, QString _sLogin, QString _sPassword, QString _sId = "0");
    void slDisConnectDesktop(int);
    void slClientControl(QString _sId, int _iVar, QString _sData);
    void slSendMouseEvent(int _iVar, bool _bBtLorR, bool _bPressRelease, int _iX, int _iY);
    void slSendKeyEvent(unsigned int _iVar, int _iKey, QString _sData);
    void slDesktopRealSize(bool _bVar);
    void slFileCopy(int _iVar, QString _sPath);
    QString slServerIP();
    unsigned short slPortTCP();
    unsigned short slPortRTSP();
    unsigned short slPortRTMP();
    void slServerUpdateData(QString _sIP, QString _sPortTCP, QString _sPortRTSP, QString _sPortRTMP, QString _sKeyDevServer, QString _sServerPas);
    bool slIsNumber(QString _lIn);
    bool slIsIP(QString _lIn);
    int slPlayerVar();
    void slUpdateFrame(int, int _iWf, int _iHf);
    void slSendStatIP(QString  _sVar);
    void slSleep(unsigned long _lmSec);
    void slThClientFin();
    void slLowActivityDiscTime(QString  _sData);

    void slFullScreen(bool _bVar);
    QString slLogin();
    QString slPassword();
    void slSearchDesktop(QString _sUser);
    void slComandLine(QString _sData, int _iVar);
    bool slComandLineStatus();
    void slUseComandLine(bool);
    QString slDeskLogin();
    QString slDeskPassword();
    void slVideoQualityStatus();
    void slVideoQualityGet(int _iSizeF, int _iFPS, int _iEnvoderV, int _iEncSpeed, int _iBetrate, int _iLatencyZ, bool _bRtsp, int _iSound);
    void slReConnectToDesktop();
    bool slStreamRTSP();
    QString slAppName();

private:
    QQmlApplicationEngine *m_pApp;
    QObject *m_obMain;
    QObject *m_obVideo;
    QObject *m_obMenu;
    int m_iTimeConnectNotActive = 10;
    int m_iTimeReConnectToDesktop = 0;
    int m_iTimeForBuffer = 10;    
    int m_iTimeForWatcher = 10;
    int m_iTimeStreamWrite = 0;
    bool m_bConnectClient = false;
    QString m_sCurrentWriteUrl = "";
    QString m_sBufferWrite = "";
    QString m_sBufferPrev = "";
    QString m_sKeyPrev = "";
    QString m_sBufferSaved = "";
    QVariant m_varBufferPrev = "";
    bool m_bStream = true;
    bool m_bComandLine = false;
    bool m_bDisconnect = true;
    QString m_sNewStreamUrl = "";
    int m_iNewStream = 5;
    bool m_bErrStream = false;
    QMutex m_mtxClipboard;

    int m_iTimeStreamRestart = 10;
    bool m_bStreamRestart = false;
    QMutex m_mtxThClientSoc;
    int m_iThClientSoc = 0;


    void fStreamReaderDelete(QQmlEngine *_engineMain);
    void fConnectToServer(QString _sIp, int _iPort, QString _sLogin, QString _sPassword);
    void fConnectClientStatus();
    void fStatusConnectToDesktop(bool _bVar);
    void fStreamReadClear();
    void fGenerateLogPass();
    void fBufferWrite(int _iVar, QString _sData);
    void fClipboardSend(bool);
    void fVideoQualitySet(QString _sData);
    void fVideoQualityCurent(QString _sData);
    void fNewStream();
    QString fStreamReadGST();
    void fKeyEventClear();
    void fTestSomeDataForUser();

    void fInitStreamReader(QQmlEngine *_engineMain);
    void fClientDisconnect();

public:
    signals:
    void sgStopStreamRead();
    void sgClientStop();
    void sgSendMassang(QByteArray);
    void sgSendMouseEvent(int _iVar, bool _bBtLorR, bool _bPressRelease, int _iX, int _iY);
    void sgSendKeyEvent(unsigned int _iVar, unsigned int _iKey, unsigned int _iKeyboardLayout, QString _sData);
    void sgTimer();
    void sgBufferDataParserStop();
    void sgControl(QString _sId, int _iVar, QString _sData, QByteArray _baIn);
    void sgComanfLineControl(int _iVar, QByteArray _baIn);
    void sgStopWriteGST();



};

#endif // CONTROL_H
