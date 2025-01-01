#ifndef FILEWRITE_H
#define FILEWRITE_H

#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QFile>


#include <MyProtocol.h>
#include "StaticData.h"

class FileWrite: public QThread
{
    Q_OBJECT
public:
    explicit FileWrite(QString _sUserId, QObject *parent = 0);
    void run();


signals:
    void sgControl(QString _sId, int _iVar, QString _sData, QByteArray _baIn);

public slots:
    void slControl(QString _sId, int _iVar, QByteArray _baIn);
    void slTimer();


private:
    QString m_sUserId = "";

    QFile *m_fWrite;
    unsigned int m_iFileSize = 0;
    short m_iTimeFileWrite = 10;
    QMutex m_mutexFileWrite;

    void fFileWrite(QByteArray _baData);
};

#endif // FILEWRITE_H
