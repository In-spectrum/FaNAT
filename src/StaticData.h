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
    static inline QString m_sVersion = "1.1.5";
    static inline QString m_sSpliter_1 = ">:<";
    static inline QString m_sNameApp = "BypassNAT-Lite";
    static inline QString m_sServerIP = "localhost";
    static inline QString m_sSettingsFile = "setClient.ini";
    static inline QString m_sProcessWorkingDirector = QDir::homePath();
    static inline unsigned short m_sPortTCP = 1235;
    static inline QString m_sPathData = "";
    static inline QString m_sMyId = "0";
    static inline QString m_sLogin = "user";
    static inline QString m_sPassword = "user";

    static inline QString m_sDeskLogin = "";
    static inline QString m_sDeskPassword = "";
    static inline QString m_sDeskId = "";

    static inline int m_iTimeForStream = 10;

    static inline bool m_bDevServer = false;
    static inline QString m_sKeyDevServer = "rFex3x4ue35";
    static inline QString m_sServerPassword = "1111";



    static inline QString m_sWithoutStream = "WITHOUT_STREAM";

    static inline QString m_sSupport = "Support:"
                                       "\r\n * GitHub - https://github.com/In-spectrum/BypassNAT?tab=readme-ov-file;"
                                       "\r\n * BypassNAT - MIT license ( https://github.com/In-spectrum/BypassNAT/blob/main/LICENSE );"
                                       "\r\nwas used:"
                                       "\r\n * Qt - LGPL-v3 license ( https://www.gnu.org/licenses/lgpl-3.0.txt );"
                                       "\r\n";


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
};

#endif // STATICDATA_H
