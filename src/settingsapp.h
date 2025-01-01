#ifndef SETTINGSAPP_H
#define SETTINGSAPP_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>
#include "StaticData.h"


class SettingsApp : public QObject
{
    Q_OBJECT

public:
    SettingsApp();

public slots:
    void fReadSettings();
    void fSaveServerData(QString _sIP, QString _sPortTCP, QString _sPortRTSP, QString _sPortRTMP, QString _sKeyDevServer, QString _sServerPas);
    void fUpdateServerData();

    bool slDevServer();
    QString slKeyDevServer();
    QString slServerPassword();

public:
    QString fGetIdForDevServer();
    void fIdForDevServerSave(QString _sId);

};

#endif // SETTINGSAPP_H
