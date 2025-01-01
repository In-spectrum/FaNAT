#ifndef PARSERSOCKETDATA_H
#define PARSERSOCKETDATA_H

#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QTcpSocket>
#include <QMutex>
#include <MyProtocol.h>
#include "StaticData.h"


class ParserSocketData: public QObject
{
    Q_OBJECT
private:
    QByteArray m_baPareser;
    QByteArrayList m_sArrData;
    QMutex m_mutexNewDataRead;

    void fClearData();

    QByteArray fNextStep(QByteArray _baIn);

    unsigned int fGetStreamData(QByteArray _baIn);
    unsigned int fSetStreamData(QByteArray _baIn);
    unsigned int fMouseEvents(QByteArray _baIn);
    unsigned int fKeyEvents(QByteArray _baIn);
    unsigned int fNewId(QByteArray _baIn);
    unsigned int fGetActiveClient(QByteArray _baIn);
    unsigned int fMaybeMyLogin(QByteArray _baIn);
    unsigned int fBufferData(QByteArray _baIn);
    unsigned int fGetFile(QByteArray _baIn);
    unsigned int fSendFile(QByteArray _baIn);
    unsigned int fComandLine(QByteArray _baIn);
    unsigned int fMessageStatus(QByteArray _baIn);
    unsigned int fWatcher(QByteArray _baIn);
    unsigned int fVideoQualitySet(QByteArray _baIn);
    unsigned int fVideoQualityCurent(QByteArray _baIn);
    unsigned int fSomeData(QByteArray _baIn);
    unsigned int fKeyClienValid(QByteArray _baIn);


public:    
    QByteArray m_baLogin;
    QByteArray m_baPassword;
    QByteArray m_baDeskTopID;
    QString m_sTokenId = "";

    ParserSocketData();
    ~ParserSocketData();
    void fAddData(QByteArray _sData);
    bool fIsEpty();
    void fParser();


signals:
    void sgControl(QString _sId, int _iVar, QString _sData, QByteArray _baIn);
    void sgAddDataWrite( QByteArray );

public slots:


//user data
private:

};

#endif // PARSERSOCKETDATA_H
