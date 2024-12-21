#ifndef STATICDATA_H
#define STATICDATA_H


#include <QTranslator>
#include <QDebug>
#include <QKeyEvent>
#include <QKeySequence>
#include <QProcess>
#include <QDir>

class StaticData
{

public:
    static inline QString m_sVersion = "1.1.4";
    static inline QString m_sSpliter_1 = ">:<";
    static inline QString m_sNameApp = "FaNAT-Lite";
    static inline QString m_sServerIP = "localhost";
    static inline QString m_sSettingsFile = "setClient.ini";
    static inline QString m_sProcessWorkingDirector = QDir::homePath();
    static inline unsigned short m_sPortTCP = 1235;
    static inline unsigned short m_sPortRTSP = 8554;
    static inline unsigned short m_sPortRTMP = 1935;
    static inline QString m_sPathData = "";
    static inline QString m_sRtspDescriptor = "";
    static inline QString m_sMyId = "0";
    static inline QString m_sLogin = "user";
    static inline QString m_sPassword = "user";
    static inline bool m_bTest = false;

    static inline QString m_sDeskLogin = "";
    static inline QString m_sDeskPassword = "";
    static inline QString m_sDeskId = "";

    static inline QString m_sWithoutStream = "WITHOUT_STREAM";

    static inline int m_iTimeForStream = 10;

    static inline int _iSizeFr = 0;
    static inline int _iFPS = 30;
    static inline int _iEnvoderV = 0;
    static inline int _iEncSpeed = 1;
    static inline int _iBetrate = 25;
    static inline int _iLatencyZ = 1;
    static inline int _iStreamRTSP = 0;
    static inline int _iSoundCapture = 0;

    static inline int _iCurSizeFr = 0;
    static inline int _iCurFPS = 30;
    static inline int _iCurEnvoderV = 0;
    static inline int _iCurEncSpeed = 1;
    static inline int _iCurBetrate = 25;
    static inline int _iCurLatencyZ = 1;
    static inline int _iCurStreamRTSP = 0;
    static inline int _iCurSoundCapture = 0;
    static inline int _iPlayerVar = 0; //0 - use QML-player; 1 - use gstFrame

    static inline QString m_sKeyDevServer = "rFex3x4ue35";
    static inline bool m_bDevServer = false;
    static inline QString m_sServerPassword = "1111";



    static int randInt(int low, int high)
    {
        // Random number between low and high
        return rand() % ((high + 1) - low) + low;
    }

    static  bool fIsNumber(QString _lIn)
    {
        //qDebug() << "StaticData::fIsNumber 1: " << _lIn;

        bool a_bNum = false;

        _lIn.toLongLong(&a_bNum);

        //qDebug() << "StaticData::fIsNumber 2: " << _lIn.toLongLong(&a_bNum);
        //qDebug() << "StaticData::fIsNumber 3: " << a_bNum;

        return a_bNum;
    }

    static  bool fIsNumber(int _lIn)
    {
        return true;
    }

    static bool fIsIP(QString _sData)
    {
        if(_sData == "localhost")
            return true;

        QStringList a_sArr = _sData.split('.');

        if(a_sArr.length() != 4)
            return false;

        if( !fIsNumber( a_sArr.at(0) )
            || !fIsNumber( a_sArr.at(1) )
            || !fIsNumber( a_sArr.at(2) )
            || !fIsNumber( a_sArr.at(3) )
            )
        {
            return false;
        }

        if( a_sArr.at(0).toInt() < 0
            || a_sArr.at(1).toInt() < 0
            || a_sArr.at(2).toInt() < 0
            || a_sArr.at(3).toInt() < 0
            )
        {
            return false;
        }

        if( a_sArr.at(0).toInt() > 255
            || a_sArr.at(1).toInt() > 255
            || a_sArr.at(2).toInt() > 255
            || a_sArr.at(3).toInt() > 255
            )
        {
            return false;
        }

        return true;
    }

    static bool fAvailableNvh264enc()
    {

        QProcess pingProcess;
        pingProcess.setProcessChannelMode(QProcess::MergedChannels);
        pingProcess.setReadChannel(QProcess::StandardOutput);

        // connect(&pingProcess, &QProcess::errorOccurred, [=](QProcess::ProcessError error)
        //         {
        //             qDebug() << " Control::fAvailableNvh264enc 1: error enum val =" << error;
        //         });

        #ifdef Q_OS_WIN
                    //pingProcess.start("gst-inspect-1.0.exe", QStringList() << "|" << "grep" << "nvenc");
                pingProcess.start("gst-inspect-1.0.exe", QStringList() << "nvh264enc");
        #else
        #ifdef Q_OS_LINUX
                    //pingProcess.start("gst-inspect-1.0", QStringList() << "|" << "grep" << "nvenc");
                pingProcess.start("gst-inspect-1.0", QStringList() << "nvh264enc");
        #endif
        #endif

        pingProcess.waitForFinished();

        QString output(pingProcess.readAllStandardOutput());
        //qDebug() << "Control::fAvailableNvh264enc 3.0: " << output;

        if(output.toLower().indexOf("nvh264enc") >= 0
            && output.toLower().indexOf("width:") >= 0
            && output.toLower().indexOf("height:") >= 0
            )
            return true;

        return false;
    }

    static QString fAvailableSoundMonitor()
    {

        QProcess pingProcess;
        pingProcess.setProcessChannelMode(QProcess::MergedChannels);
        pingProcess.setReadChannel(QProcess::StandardOutput);

        pingProcess.start("pactl", QStringList() << "list" << "short" << "sources");

        // if (pingProcess.waitForStarted(-1))
        // {
        //     while(pingProcess.waitForReadyRead(-1))
        //     {
        //         while(pingProcess.canReadLine())
        //         {
        //             QByteArray a_baT = pingProcess.readLine();

        //             qDebug() << "ComandLine::fAvailableSoundMonitor 4: " << QString::fromStdString(a_baT.toStdString());
        //         }

        //     }
        // }

        pingProcess.waitForFinished();

        QString output(pingProcess.readAllStandardOutput());
        //qDebug() << "Control::fAvailableSoundMonitor 3.0: " << output;

        QString s_aRet;

        QStringList a_slTemp = output.split(" ");

        //alsa_output.pci-0000_02_02.0.analog-stereo.monitor

        for(QString s : a_slTemp)
        {
            if(s.toLower().indexOf("output") >= 0
                && s.toLower().indexOf(".monitor") >= 0 )
            {
                s_aRet = s;
                //qDebug() << "Control::fAvailableSoundMonitor 5: " << s_aRet;

                break;
            }
        }

        //qDebug() << "Control::fAvailableSoundMonitor 6: " << s_aRet;

        if(s_aRet.indexOf("\t") >= 0)
        {
            a_slTemp = s_aRet.split("\t");

            for(QString s : a_slTemp)
            {
                if(s.toLower().indexOf("output") >= 0
                    && s.toLower().indexOf(".monitor") >= 0 )
                {
                    s_aRet = s;
                    //qDebug() << "Control::fAvailableSoundMonitor 7: " << s_aRet;

                    break;
                }
            }
        }

        qDebug() << "Control::fAvailableSoundMonitor 10: " << s_aRet;

        return s_aRet;
    }

};

#endif // STATICDATA_H
