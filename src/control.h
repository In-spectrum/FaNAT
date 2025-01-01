#ifndef CONTROL_H
#define CONTROL_H

#include <QApplication>
#include <QDebug>
#include <QMimeData>

#include "settingsapp.h"
#include "newclient.h"



class Control : public SettingsApp
{
    Q_OBJECT

public:
    Control(QStringList _sDataIn);
    ~Control();

public slots:
    void slotDestruction();
    void slotTimer();
    void slConnectToServer(QString _sLogin, QString _sPassword);
    void slClientControl(QString _sId, int _iVar, QString _sData);
    void slFileCopy(int _iVar, QString _sPath);
    QString slServerIP();
    unsigned short slPortTCP();
    void slServerUpdateData(QString _sIP, QString _sPortTCP, QString _sPortRTSP, QString _sPortRTMP, QString _sKeyDevServer, QString _sServerPas);
    bool slIsNumber(QString _lIn);
    bool slIsIP(QString _lIn);

    QString slLogin();
    QString slPassword();
    void slComandLine(QString _sData, int _iVar);
    bool slComandLineStatus();
    void slUseComandLine(bool);
    QString slDeskLogin();
    QString slDeskPassword();
    QString slAppName();
    void slSleep(unsigned long _lmSec);
    void slThClientFin();

private:
    int m_iTimeConnectNotActive = 10;
    int m_iTimeReConnectToDesktop = 0;
    int m_iTimeForWatcher = 10;
    bool m_bConnectClient = false;
    QVariant m_varBufferPrev = "";
    bool m_bStream = false;
    bool m_bComandLine = false;
    bool m_bDisconnect = true;

    QMutex m_mtxThClientSoc;
    int m_iThClientSoc = 0;


    void fConnectToServer(QString _sIp, int _iPort, QString _sLogin, QString _sPassword);
    void fConnectClientStatus();
    void fGenerateLogPass();
    void fTestSomeDataForUser();
    void fPropertySet(QStringList);
    QStringList fCorrectDataIn(QStringList _sDataIn);

    void fClientDisconnect();

public:
    signals:
    void sgClientStop();
    void sgSendMassang(QByteArray);
    void sgTimer();
    void sgControl(QString _sId, int _iVar, QString _sData, QByteArray _baIn);
    void sgComanfLineControl(int _iVar, QByteArray _baIn);



};

#endif // CONTROL_H
