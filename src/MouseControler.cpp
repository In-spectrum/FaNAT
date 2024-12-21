#include "MouseControler.h"

#ifdef Q_OS_ANDROID

#else
#ifdef Q_OS_WIN
#include <windows.h>
#else
#ifdef Q_OS_LINUX
//#include <X11/Xlib.h>
//sudo apt-get install libxtst-dev
#include <X11/extensions/XTest.h>
#endif
#endif
#endif

void MouseControler::fCursorSetPos(int _iVar, int _iBt, int _iPress, double _dProcentX, double _dProcentY)
{
    //        qDebug() << "MouseControler::fCursorSetPos 0: "
    //                 << _iVar
    //                 << _iBt
    //                 << _iPress
    //                 << _dProcentX
    //                 << _dProcentY;

    //        return;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int a_iPosX = _dProcentX * screenGeometry.width() / 100;
    int a_iPosY = _dProcentY * screenGeometry.height() / 100;

    QCursor::setPos(a_iPosX, a_iPosY);

    if(_iVar == 1 || _iVar == 2)
    {
        fCursorCliked(_iBt, _iPress, _dProcentX, _dProcentY);
    }
    else
    {
        if(_iVar == 4)
        {
            fScrollMove(_iBt, _iPress, a_iPosX, a_iPosY);
        }
    }
}

void MouseControler::fCursorCliked(int _iBt, int _iPress, double _dProcentX, double _dProcentY)
{

    // qDebug() << "MouseControler::fCursorCliked 0: "
    //          << _iBt
    //          << _iPress
    //          << _dProcentX
    //          << _dProcentY;

#ifdef Q_OS_WIN
    if(_iBt == 1)
    {
        if(_iPress == 1)
        {
            mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            // qDebug() << "MouseControler::fCursorCliked 0: "
            //          << _iBt
            //          << _iPress
            //          << _dProcentX
            //          << _dProcentY;
        }
        else
        {
            mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
    }
    else
    {
        if(_iPress == 1)
        {
            mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);

        }
        else
        {
            mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
    }
#else
#ifdef Q_OS_LINUX

    Display *display;

    display = XOpenDisplay(0);
    if(display == NULL)
    {
        return;
    }

    //qDebug() << "MouseControler::fCursorCliked 8: " << _iBt << _iPress;

    if(_iBt == 1)
    {
        if(_iPress == 1)
        {
            // QString cmd = "xdotool mousedown 1";
            // std::string str = cmd.toStdString();
            // //qDebug() << "MouseControler::fCursorCliked 4.1: " <<
            //     system(str.c_str());

            XTestFakeButtonEvent(display, 1, True, 0);


        }
        else
        {
            // QString cmd = "xdotool mouseup 1";
            // std::string str = cmd.toStdString();
            // //qDebug() << "MouseControler::fCursorCliked 4.2: " <<
            //     system(str.c_str());

            XTestFakeButtonEvent(display, 1, False, 0);
        }
    }
    else
    {
        if(_iPress == 1)
        {
            // QString cmd = "xdotool mousedown 3";
            // std::string str = cmd.toStdString();
            // //qDebug() << "MouseControler::fCursorCliked 5.1: " <<
            //     system(str.c_str());

            XTestFakeButtonEvent(display, 3, True, 0);

        }
        else
        {
            // QString cmd = "xdotool mouseup 3";
            // std::string str = cmd.toStdString();
            // //qDebug() << "MouseControler::fCursorCliked 5.2: " <<
            //     system(str.c_str());

            XTestFakeButtonEvent(display, 3, False, 0);
        }
    }

    XFlush(display);
    XCloseDisplay(display);

#else

#endif


#endif

}

void MouseControler::fScrollMove(int _iBt, int _iPress, int _dProcentX, int _dProcentY)
{
    // qDebug() << "MouseControler::fScrollMove 0: "
    //          << _iBt
    //          << _iPress
    //          << _dProcentX
    //          << _dProcentY;



#ifdef Q_OS_WIN
    if(_iBt != 1)
        _iPress = -1;
    else
        _iPress = 1;


    _iPress *= 100;

    //qDebug() << "MouseControler::fScrollMove 2: " << _iPress;

    mouse_event(MOUSEEVENTF_WHEEL
                , (DWORD)_dProcentX
                , (DWORD)_dProcentY
                , (DWORD)_iPress
                , 0);
#else
#ifdef Q_OS_LINUX

    Display *display;

    display = XOpenDisplay(0);
    if(display == NULL)
    {
        return;
    }

    if(_iBt == 1)
    {
        // QString cmd = "xdotool click 4";
        // std::string str = cmd.toStdString();
        // system(str.c_str());

        XTestFakeButtonEvent(display, 4, True, 0);
        XTestFakeButtonEvent(display, 4, False, 0);
    }
    else
    {
        // QString cmd = "xdotool click 5";
        // std::string str = cmd.toStdString();
        // system(str.c_str());

        XTestFakeButtonEvent(display, 5, True, 0);
        XTestFakeButtonEvent(display, 5, False, 0);
    }

    XFlush(display);
    XCloseDisplay(display);

#else

#endif

#endif
}
