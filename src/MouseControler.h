#ifndef MOUSECONTROLER_H
#define MOUSECONTROLER_H



#include <QDebug>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QScreen>
#include <QRect>

#include <QCursor>

#include "StaticData.h"


class MouseControler
{
public:

    static void fCursorSetPos(int _iVar, int _iBt, int _iPress, double _dProcentX, double _dProcentY);

    static void fCursorCliked(int _iBt, int _iPress, double _dProcentX, double _dProcentY);

    static void fScrollMove(int _iBt, int _iPress, int _dProcentX, int _dProcentY);
};

#endif // MOUSECONTROLER_H
