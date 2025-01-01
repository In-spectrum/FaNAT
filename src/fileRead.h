#ifndef FILEREAD_H
#define FILEREAD_H

#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QFile>


#include <MyProtocol.h>

class FileRead: public QThread
{
    Q_OBJECT
public:
    explicit FileRead(QString _sUserId, QObject *parent = 0);
    void run();


signals:
    void sgControl(QString _sId, int _iVar, QString _sData, QByteArray _baIn);

public slots:
    void slControl(QString _sId, int _iVar, QByteArray _baIn);
    void slTimer();


private:
    QString m_sUserId = "";

    QFile *m_fRead;
    unsigned int m_iFileSize = 0;
    short m_iTimeFileRead = 10;
    QMutex m_mutexFileRead;

    void fFileRead(QByteArray _baData);
};

#endif // FILEREAD_H
