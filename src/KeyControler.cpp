#include "KeyControler.h"


#ifdef Q_OS_WIN

#include <windows.h>

int KeyControler::fKeyWin(unsigned int _iKey)
{
    //qDebug() << "StaticData::fKeyWin 0: " << _iKey;

    for(int i = 0; i < sizeof(KeyTbl) / sizeof(KeyTbl[0]); i++)
    {
        //qDebug() << "StaticData::fKeyWin 3: " << QKeySequence(KeyTbl[i]).toString() << KeyTbl[i] ;

        if(KeyTbl[i] == _iKey )
        {
            //qDebug() << "StaticData::fKeyWin 4: " << i ;
            return i;
        }
    }

    return -1;
}

bool KeyControler::fCtrlV( unsigned int _iVar, unsigned int _iKay)
{
    int a_iKeyWin = fKeyWin(_iKay);

    if( a_iKeyWin < 0 )
    {
        //нажато Control + V
        if( _iVar == 1
            && ( (GetKeyState(17) >> 8) & 0xFF ) == 0xff
            && ((char)_iKay == 'V' || (char)_iKay == 'v')
            )
        {
            qDebug() << "KeyControler::fCtrlV 4.5: " << "Control + V";
            return true;
        }
    }

    return false;
}
#else
#ifdef Q_OS_LINUX

//#include <X11/Xlib.h>
//#include <X11/keysym.h>
//sudo apt-get install libxtst-dev
#include <X11/extensions/XTest.h>

static bool fGetKeyState(KeySym keySym)
{
    Display *display;

    display = XOpenDisplay(0);
    if(display == NULL)
    {
        return false;
    }

    char szKey[32];
    int iKeyCodeToFind = XKeysymToKeycode(display, keySym);

    XQueryKeymap(display, szKey);
    XCloseDisplay(display);

    return szKey[iKeyCodeToFind / 8] & (1 << (iKeyCodeToFind % 8));

    return false;
}


int KeyControler::fKeyLinux(unsigned int _iKey)
{
    //qDebug() << "StaticData::fKeyLinux 0: " << _iKey;

    for(int i = 1; i < sizeof(KeyTblLinux) / sizeof(KeyTblLinux[0]); i+=2)
    {
        //qDebug() << "StaticData::fKeyLinux 3: " << QKeySequence(KeyTblLinux[i]).toString() << KeyLinux[i] ;

        if(KeyTblLinux[i] == _iKey )
        {
            //qDebug() << "StaticData::fKeyLinux 4: " << i ;
            return i;
        }
    }

    return -1;
}

bool KeyControler::fCtrlV( unsigned int _iVar, unsigned int _iKay)
{
    //qDebug() << "KeyControler::fCtrlV 0: " << _iVar << _iKay;

    //нажато Control + V
    if( _iVar == 1
        && (fGetKeyState(XK_Control_L) || fGetKeyState(XK_Control_R) )
        && ((char)_iKay == 'V' || (char)_iKay == 'v')
        )
    {
        qDebug() << "KeyControler::fCtrlV 4.5: " << "Control + V";
        return true;
    }

    return false;
}

#else

#endif

#endif
