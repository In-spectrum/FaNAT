#ifndef NEWCLIENT_H
#define NEWCLIENT_H


#include "parsersocketdata.h"

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QDateTime>

#include "fileRead.h"
#include "fileWrite.h"
#include "ComandLine.h"

class NewClient: public QThread
{
    Q_OBJECT
public:
    explicit NewClient(QString _sIp, uint _iPort, QString _sLogin, QString _sPassword, QObject *parent = 0);
    void run();


signals:
    void error(QTcpSocket::SocketError socketerror);
    void siSendData(int _iVar, QString _sData);
    void sgTimerParserStart();
    void sgTimerWriteStart();
    void sgTimerStop();
    void sgSearchDesktop(NewClient *_pClient, QString, QString);
    void sgControl(QString _sId, int _iVar, QString _sData);
    void sgTimer();
    void sgFileReadControl(QString _sId, int _iVar, QByteArray _baIn);
    void sgFileWriteControl(QString _sId, int _iVar, QByteArray _baIn);
    void sgComanfLineControl(QString _sId, int _iVar, QByteArray _baIn);
    void sgThreadTask();

public slots:
    void slStop();
    void readyRead();
    void disconnected();
    void slWriteToSoccet();
    void slAddDataWrite(QByteArray _baIn);
    void slParser();
    void slControl(QString _sId, int _iVar, QString _sData, QByteArray _baIn);
    void slSendMouseEvent(int _iVar, bool _bBtLorR, bool _bPressRelease, int _iX, int _iY);
    void slTimer();
    void slThreadTask();


private:
    uint64_t m_iTimeMs;

    QString m_sIp;
    uint m_iPort;
    QString m_sLogin;
    QString m_sPassword;
    bool m_bConnect;
    bool m_bStop;
    bool m_bLowActivity = false;
    bool m_bRun;
    short m_iTimeOut;
    QTimer *m_tParser;
    QTimer *m_tWrite;
    QTimer *m_tThreadTask;
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QByteArrayList m_baDataWrite;
    QMutex m_mutexNewDataWrite;
    QMutex m_mutexDestroy;
    uint8_t m_iTaskVar = 0;


    void fConnect();
    void fWrite(QByteArray _abIn);
    void fFileWrite(QByteArray _baData);
    void fFileRead(QByteArray _baData);
    void fComandLine(QByteArray _baIn);

    ParserSocketData *m_pParserSocket;
};

#endif // NEWCLIENT_H
