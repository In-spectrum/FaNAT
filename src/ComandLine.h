#ifndef COMANDLINE_H
#define COMANDLINE_H

#include <QThread>
#include <QDebug>
#include <QProcess>
#include <QTextCodec>
#include "settingsapp.h"

class ComandLine: public QThread
{
    Q_OBJECT
public:
    explicit ComandLine(QString _sUserId, int _iVar, QObject *parent = 0);
    void run();

signals:
    void sgControl(QString _sId, int _iVar, QString _sData, QByteArray _baIn);

public slots:
    void slControl(QString _sId, int _iVar, QByteArray _baIn);
    void slStop();
    void slErrP(QProcess::ProcessError exitStatus);

private:
    QString m_sUserId = "";
    int m_iTimeStop = 0;
    int m_iVar = 0;
    bool m_bRun = false;
    QByteArrayList m_blData;
    QProcess *process;
    QString m_sComande;
    const QString m_sLineFin = "\r\n-END--------------------------------------\r\n";

    void fParser(QString _baIn);
    void fProgram(QString  _sData);
    bool fPerforming(QStringList  _slData);
    void fProgressStop();
    void fSetWorkingDirectory(QString _sPath);
    void fFolderList(QString _sVar);
    bool fCustomProcess(QStringList);


private:
};

#endif // COMANDLINE_H
