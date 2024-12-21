#include "settingsapp.h"

SettingsApp::SettingsApp()
{
    fReadSettings();
}

void SettingsApp::fReadSettings()
{
    StaticData::m_sPathData = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    //QSettings a_setReg(QLatin1String("Inspectrum"), StaticData::m_sNameApp );
    QSettings a_setReg(StaticData::m_sSettingsFile, QSettings::IniFormat );
    a_setReg.beginGroup(QLatin1String("/Settings"));
    StaticData::m_sServerIP = a_setReg.value(tr("/serverIP"), "localhost").toString(); //12.3.213.214
    StaticData::m_sServerPassword = a_setReg.value(tr("/serverPassword"), "1111").toString();
    StaticData::m_sPortTCP = a_setReg.value(tr("/portTCP"), 1235).toString().toUShort(); //1235
    StaticData::m_sPortRTSP = a_setReg.value(tr("/portRTSP"), 8554).toString().toUShort(); //8504
    StaticData::m_sPortRTMP = a_setReg.value(tr("/portRTMP"), 1935).toString().toUShort(); //1935
    StaticData::_iCurStreamRTSP = StaticData::_iStreamRTSP = a_setReg.value(tr("/streamRTSP"), 0).toBool(); //false
    StaticData::_iCurEnvoderV = StaticData::_iEnvoderV = a_setReg.value(tr("/streamEncoderType"), 0).toString().toUShort(); //0

    if(!StaticData::fAvailableNvh264enc())
        StaticData::_iCurEnvoderV = 0;

    StaticData::m_sKeyDevServer = a_setReg.value(tr("/keyDevServer"), "xxxxxxxx").toString();
    StaticData::m_bDevServer = a_setReg.value(tr("/devServer"), 0).toBool(); //false
    if(StaticData::m_bDevServer)
    {
        StaticData::m_sPortTCP = 1267;
        StaticData::m_sPortRTSP = 8512;
        StaticData::m_sPortRTMP = 1959;
        StaticData::m_sMyId = fGetIdForDevServer();
    }

    //qDebug() << "SettingsApp::fReadSettings 8: " << a_setReg.fileName();

    a_setReg.endGroup();

    //qDebug() << "SettingsApp::fReadSettings 10: " << StaticData::m_sServerIP;
}


void SettingsApp::fSaveServerData(QString _sIP, QString _sPortTCP, QString _sPortRTSP, QString _sPortRTMP, QString _sKeyDevServer, QString _sServerPas)
{
    //QSettings a_setReg(QLatin1String("Inspectrum"), StaticData::m_sNameApp );
    QSettings a_setReg(StaticData::m_sSettingsFile, QSettings::IniFormat );
    a_setReg.beginGroup(QLatin1String("/Settings"));

    StaticData::m_sServerIP = _sIP;
    StaticData::m_sServerPassword = _sServerPas;

    if(_sPortTCP == "0" && _sPortRTSP == "0" &&_sPortRTMP == "0" )
    {
        if(!StaticData::m_bDevServer)
        {
            StaticData::m_sMyId = fGetIdForDevServer();
        }

        StaticData::m_bDevServer = true;
        StaticData::m_sKeyDevServer = _sKeyDevServer;
        StaticData::m_sPortTCP = 1267;
        StaticData::m_sPortRTSP = 8512;
        StaticData::m_sPortRTMP = 1959;
    }
    else
    {
        if(StaticData::m_bDevServer)
        {
            StaticData::m_sMyId = "0";
        }

        StaticData::m_bDevServer = false;
        StaticData::m_sPortTCP = _sPortTCP.toUShort();
        StaticData::m_sPortRTSP = _sPortRTSP.toUShort();
        StaticData::m_sPortRTMP = _sPortRTMP.toUShort();

        a_setReg.setValue(QLatin1String("/portTCP"), _sPortTCP);
        a_setReg.setValue(QLatin1String("/portRTSP"), _sPortRTSP);
        a_setReg.setValue(QLatin1String("/portRTMP"), _sPortRTMP);
    }


    a_setReg.setValue(QLatin1String("/serverIP"), StaticData::m_sServerIP);
    a_setReg.setValue(QLatin1String("/devServer"), StaticData::m_bDevServer);
    a_setReg.setValue(QLatin1String("/keyDevServer"), StaticData::m_sKeyDevServer);
    a_setReg.setValue(QLatin1String("/serverPassword"), StaticData::m_sServerPassword);
    a_setReg.endGroup();

}

void SettingsApp::fSaveStreamRTSP(bool _bVar)
{
    StaticData::_iStreamRTSP = _bVar;

    //QSettings a_setReg(QLatin1String("Inspectrum"), StaticData::m_sNameApp );
    QSettings a_setReg(StaticData::m_sSettingsFile, QSettings::IniFormat );
    a_setReg.beginGroup(QLatin1String("/Settings"));
    a_setReg.setValue(QLatin1String("/streamRTSP"), StaticData::_iStreamRTSP);
    a_setReg.endGroup();
}

void SettingsApp::fSaveEvcoderType(int _iVar)
{
    StaticData::_iCurEnvoderV = _iVar;

    //QSettings a_setReg(QLatin1String("Inspectrum"), StaticData::m_sNameApp );
    QSettings a_setReg(StaticData::m_sSettingsFile, QSettings::IniFormat );
    a_setReg.beginGroup(QLatin1String("/Settings"));
    a_setReg.setValue(QLatin1String("/streamEncoderType"), StaticData::_iCurEnvoderV);
    a_setReg.endGroup();
}

void SettingsApp::fUpdateServerData()
{
    //QSettings a_setReg(QLatin1String("Inspectrum"), StaticData::m_sNameApp );
    QSettings a_setReg(StaticData::m_sSettingsFile, QSettings::IniFormat );
    a_setReg.beginGroup(QLatin1String("/Settings"));
    StaticData::m_sPortTCP = a_setReg.value(tr("/portTCP"), 1235).toString().toUShort(); //1235
    StaticData::m_sPortRTSP = a_setReg.value(tr("/portRTSP"), 8554).toString().toUShort(); //8504
    StaticData::m_sPortRTMP = a_setReg.value(tr("/portRTMP"), 1935).toString().toUShort(); //1935
    a_setReg.endGroup();

    //qDebug() << "SettingsApp::fUpdateServerData 10:" << StaticData::m_sPortTCP;
}

bool SettingsApp::slDevServer()
{
    return StaticData::m_bDevServer;
}

QString SettingsApp::slKeyDevServer()
{
    return StaticData::m_sKeyDevServer;
}

QString SettingsApp::slServerPassword()
{
    return StaticData::m_sServerPassword;
}

QString SettingsApp::fGetIdForDevServer()
{
    QSettings a_setReg(StaticData::m_sSettingsFile, QSettings::IniFormat );
    a_setReg.beginGroup(QLatin1String("/Settings"));
    QString a_sId = a_setReg.value(tr("/idForDevServer"), "0").toString(); //0
    a_setReg.endGroup();

    if(a_sId != "0")
        a_sId += "_uds";

    return a_sId;
}

void SettingsApp::fIdForDevServerSave(QString _sId)
{
    //if(fGetIdForDevServer() == "0")
    {
        QStringList a_sId = _sId.split("_");

        if(a_sId.length() > 0 && a_sId.at(0).length() > 0)
        {
            QSettings a_setReg(StaticData::m_sSettingsFile, QSettings::IniFormat );
            a_setReg.beginGroup(QLatin1String("/Settings"));
            a_setReg.setValue(QLatin1String("/idForDevServer"), a_sId.at(0));
            a_setReg.endGroup();
        }
    }

}
