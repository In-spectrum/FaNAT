#ifndef KEYCONTROLERH_H
#define KEYCONTROLERH_H

#include <QtGlobal>
#include <QDebug>
#include <QGuiApplication>
#include <QThread>
#include <QKeySequence>



#ifdef Q_OS_ANDROID

#else
#ifdef Q_OS_LINUX
#include <X11/keysym.h>
// the next lines are taken on 10/2009 from X.org (X11/XF86keysym.h), defining some special
// multimedia keys. They are included here as not every system has them.

#define XF86XK_MonBrightnessUp     0x1008FF02
#define XF86XK_MonBrightnessDown   0x1008FF03
#define XF86XK_KbdLightOnOff       0x1008FF04
#define XF86XK_KbdBrightnessUp     0x1008FF05
#define XF86XK_KbdBrightnessDown   0x1008FF06
#define XF86XK_Standby             0x1008FF10
#define XF86XK_AudioLowerVolume	   0x1008FF11
#define XF86XK_AudioMute           0x1008FF12
#define XF86XK_AudioRaiseVolume    0x1008FF13
#define XF86XK_AudioPlay           0x1008FF14
#define XF86XK_AudioStop           0x1008FF15
#define XF86XK_AudioPrev           0x1008FF16
#define XF86XK_AudioNext           0x1008FF17
#define XF86XK_HomePage            0x1008FF18
#define XF86XK_Mail                0x1008FF19
#define XF86XK_Start               0x1008FF1A
#define XF86XK_Search              0x1008FF1B
#define XF86XK_AudioRecord         0x1008FF1C
#define XF86XK_Calculator          0x1008FF1D
#define XF86XK_Memo                0x1008FF1E
#define XF86XK_ToDoList            0x1008FF1F
#define XF86XK_Calendar            0x1008FF20
#define XF86XK_PowerDown           0x1008FF21
#define XF86XK_ContrastAdjust      0x1008FF22
#define XF86XK_Back                0x1008FF26
#define XF86XK_Forward             0x1008FF27
#define XF86XK_Stop                0x1008FF28
#define XF86XK_Refresh             0x1008FF29
#define XF86XK_PowerOff            0x1008FF2A
#define XF86XK_WakeUp              0x1008FF2B
#define XF86XK_Eject               0x1008FF2C
#define XF86XK_ScreenSaver         0x1008FF2D
#define XF86XK_WWW                 0x1008FF2E
#define XF86XK_Sleep               0x1008FF2F
#define XF86XK_Favorites           0x1008FF30
#define XF86XK_AudioPause          0x1008FF31
#define XF86XK_AudioMedia          0x1008FF32
#define XF86XK_MyComputer          0x1008FF33
#define XF86XK_LightBulb           0x1008FF35
#define XF86XK_Shop                0x1008FF36
#define XF86XK_History             0x1008FF37
#define XF86XK_OpenURL             0x1008FF38
#define XF86XK_AddFavorite         0x1008FF39
#define XF86XK_HotLinks            0x1008FF3A
#define XF86XK_BrightnessAdjust    0x1008FF3B
#define XF86XK_Finance             0x1008FF3C
#define XF86XK_Community           0x1008FF3D
#define XF86XK_AudioRewind         0x1008FF3E
#define XF86XK_BackForward         0x1008FF3F
#define XF86XK_Launch0             0x1008FF40
#define XF86XK_Launch1             0x1008FF41
#define XF86XK_Launch2             0x1008FF42
#define XF86XK_Launch3             0x1008FF43
#define XF86XK_Launch4             0x1008FF44
#define XF86XK_Launch5             0x1008FF45
#define XF86XK_Launch6             0x1008FF46
#define XF86XK_Launch7             0x1008FF47
#define XF86XK_Launch8             0x1008FF48
#define XF86XK_Launch9             0x1008FF49
#define XF86XK_LaunchA             0x1008FF4A
#define XF86XK_LaunchB             0x1008FF4B
#define XF86XK_LaunchC             0x1008FF4C
#define XF86XK_LaunchD             0x1008FF4D
#define XF86XK_LaunchE             0x1008FF4E
#define XF86XK_LaunchF             0x1008FF4F
#define XF86XK_ApplicationLeft     0x1008FF50
#define XF86XK_ApplicationRight    0x1008FF51
#define XF86XK_Book                0x1008FF52
#define XF86XK_CD                  0x1008FF53
#define XF86XK_Calculater          0x1008FF54
#define XF86XK_Clear               0x1008FF55
#define XF86XK_ClearGrab           0x1008FE21
#define XF86XK_Close               0x1008FF56
#define XF86XK_Copy                0x1008FF57
#define XF86XK_Cut                 0x1008FF58
#define XF86XK_Display             0x1008FF59
#define XF86XK_DOS                 0x1008FF5A
#define XF86XK_Documents           0x1008FF5B
#define XF86XK_Excel               0x1008FF5C
#define XF86XK_Explorer            0x1008FF5D
#define XF86XK_Game                0x1008FF5E
#define XF86XK_Go                  0x1008FF5F
#define XF86XK_iTouch              0x1008FF60
#define XF86XK_LogOff              0x1008FF61
#define XF86XK_Market              0x1008FF62
#define XF86XK_Meeting             0x1008FF63
#define XF86XK_MenuKB              0x1008FF65
#define XF86XK_MenuPB              0x1008FF66
#define XF86XK_MySites             0x1008FF67
#define XF86XK_News                0x1008FF69
#define XF86XK_OfficeHome          0x1008FF6A
#define XF86XK_Option              0x1008FF6C
#define XF86XK_Paste               0x1008FF6D
#define XF86XK_Phone               0x1008FF6E
#define XF86XK_Reply               0x1008FF72
#define XF86XK_Reload              0x1008FF73
#define XF86XK_RotateWindows       0x1008FF74
#define XF86XK_RotationPB          0x1008FF75
#define XF86XK_RotationKB          0x1008FF76
#define XF86XK_Save                0x1008FF77
#define XF86XK_Send                0x1008FF7B
#define XF86XK_Spell               0x1008FF7C
#define XF86XK_SplitScreen         0x1008FF7D
#define XF86XK_Support             0x1008FF7E
#define XF86XK_TaskPane            0x1008FF7F
#define XF86XK_Terminal            0x1008FF80
#define XF86XK_Tools               0x1008FF81
#define XF86XK_Travel              0x1008FF82
#define XF86XK_Video               0x1008FF87
#define XF86XK_Word                0x1008FF89
#define XF86XK_Xfer                0x1008FF8A
#define XF86XK_ZoomIn              0x1008FF8B
#define XF86XK_ZoomOut             0x1008FF8C
#define XF86XK_Away                0x1008FF8D
#define XF86XK_Messenger           0x1008FF8E
#define XF86XK_WebCam              0x1008FF8F
#define XF86XK_MailForward         0x1008FF90
#define XF86XK_Pictures            0x1008FF91
#define XF86XK_Music               0x1008FF92
#define XF86XK_Battery             0x1008FF93
#define XF86XK_Bluetooth           0x1008FF94
#define XF86XK_WLAN                0x1008FF95
#define XF86XK_UWB                 0x1008FF96
#define XF86XK_AudioForward        0x1008FF97
#define XF86XK_AudioRepeat         0x1008FF98
#define XF86XK_AudioRandomPlay     0x1008FF99
#define XF86XK_Subtitle            0x1008FF9A
#define XF86XK_AudioCycleTrack     0x1008FF9B
#define XF86XK_Time                0x1008FF9F
#define XF86XK_Select              0x1008FFA0
#define XF86XK_View                0x1008FFA1
#define XF86XK_TopMenu             0x1008FFA2
#define XF86XK_Suspend             0x1008FFA7
#define XF86XK_Hibernate           0x1008FFA8


// end of XF86keysyms.h

// Special keys used by Qtopia, mapped into the X11 private keypad range.
#define QTOPIAXK_Select         0x11000601
#define QTOPIAXK_Yes            0x11000602
#define QTOPIAXK_No             0x11000603
#define QTOPIAXK_Cancel         0x11000604
#define QTOPIAXK_Printer        0x11000605
#define QTOPIAXK_Execute        0x11000606
#define QTOPIAXK_Sleep          0x11000607
#define QTOPIAXK_Play           0x11000608
#define QTOPIAXK_Zoom           0x11000609
#define QTOPIAXK_Context1       0x1100060A
#define QTOPIAXK_Context2       0x1100060B
#define QTOPIAXK_Context3       0x1100060C
#define QTOPIAXK_Context4       0x1100060D
#define QTOPIAXK_Call           0x1100060E
#define QTOPIAXK_Hangup         0x1100060F
#define QTOPIAXK_Flip           0x11000610



static const uint KeyLinux[] = { // Keyboard mapping table

    Qt::Key_unknown,    0,  //
    Qt::Key_unknown,    0,  //   1                | Left mouse button
    Qt::Key_unknown,    0,  //   2                | Right mouse button
    Qt::Key_Cancel,     XK_Cancel,   //   3                 | Control-Break processing
    Qt::Key_unknown,    0,  //   4                | Middle mouse button
    Qt::Key_unknown,    0,  //   5               | X1 mouse button
    Qt::Key_unknown,    0,  //   6               | X2 mouse button
    Qt::Key_unknown,    0,  //   7      -- unassigned --
    Qt::Key_Backspace,  XK_BackSpace,   //   8                   | BackSpace key
    Qt::Key_Tab,        XK_Tab,   //   9                    | Tab key
    Qt::Key_unknown,    0,  //  10      -- reserved --
    Qt::Key_unknown,    0,  //  11      -- reserved --
    Qt::Key_Clear,      XK_Clear,   //  12                  | Clear key
    Qt::Key_Return,     XK_Return,   //  13                 | Enter key
    Qt::Key_unknown,    0,  //  14   0x0E
    Qt::Key_unknown,    0,  //  15   0x0F   -- unassigned --
    Qt::Key_Shift,      XK_Shift_L,   //  16                  | Shift key
    Qt::Key_Control,    XK_Control_L,   //  17                | Ctrl key
    Qt::Key_unknown,    0,  // Qt::Key_Alt,        //  18                   | Alt key
    Qt::Key_Pause,      XK_Pause,   //  19                  | Pause key
    Qt::Key_CapsLock,   XK_Caps_Lock,   //  20                | Caps-Lock
    Qt::Key_unknown,    0,  //  21    | IME Kana or Hangul mode
    Qt::Key_unknown,    0,  //  22      -- unassigned --
    Qt::Key_unknown,    0,  //  23                  | IME Junja mode
    Qt::Key_unknown,    0,  //  24                  | IME final mode
    Qt::Key_unknown,    0,  //  25       / VK_KANJI | IME Hanja or Kanji mode
    Qt::Key_unknown,    0,  //  26      -- unassigned --
    Qt::Key_Escape,     XK_Escape,   //  27                 | Esc key
    Qt::Key_unknown,    0,  //  28                | IME convert
    Qt::Key_unknown,    0,  //  29             | IME non-convert
    Qt::Key_unknown,    0,  //  30                 | IME accept
    Qt::Key_Mode_switch, XK_Mode_switch,   //  31             | IME mode change request
    Qt::Key_Space,      XK_space,   //  32                  | Spacebar
    Qt::Key_PageUp,     XK_Page_Up,   //  33                  | Page Up key
    Qt::Key_PageDown,   XK_Page_Down,   //  34                   | Page Down key
    Qt::Key_End,        XK_End,   //  35                    | End key
    Qt::Key_Home,       XK_Home,   //  36                   | Home key
    Qt::Key_Left,       XK_Left,   //  37                   | Left arrow key
    Qt::Key_Up,         XK_Up,   //  38                     | Up arrow key
    Qt::Key_Right,      XK_Right,   //  39                  | Right arrow key
    Qt::Key_Down,       XK_Down,   //  40                   | Down arrow key
    Qt::Key_Select,     XK_Select,   //  41                 | Select key
    Qt::Key_Printer,    0,   //  42                  | Print key
    Qt::Key_Execute,    XK_Execute,   //  43                | Execute key
    Qt::Key_Print,      XK_Print,   //  44               | Print Screen key
    Qt::Key_Insert,     XK_Insert,   //  45                 | Ins key
    Qt::Key_Delete,     XK_Delete,   //  46                 | Del key  //65439
    Qt::Key_Help,       XK_Help,   //  47                   | Help key //65386
    0,                  //  48                    | 0 key
    0,                  //  49                 | 1 key
    0,                  //  50               | 2 key
    0,                  //  51               | 3 key
    0,                  //  52                | 4 key
    0,                  //  53              | 5 key
    0,                  //  54                | 6 key
    0,                  //  55                 | 7 key
    0,                  //  56                 | 8 key
    0,                  //  57                | 9 key
    Qt::Key_unknown,    0,   //  58      -- unassigned --
    Qt::Key_unknown,    0,   //  59      -- unassigned --
    Qt::Key_unknown,    0,   //  60      -- unassigned --
    Qt::Key_unknown,    0,   //  61      -- unassigned --
    Qt::Key_unknown,    0,   //  62      -- unassigned --
    Qt::Key_unknown,    0,   //  63      -- unassigned --
    Qt::Key_unknown,    0,   //  64      -- unassigned --
    0,                  0,   //  65           | A key
    0,                  0,   //  66               | B key
    0,                  0,   //  67                  | C key
    0,                  0,   //  68                  | D key
    0,                  0,   //  69                 | E key
    0,                  0,   //  70                | F key
    0,                  0,   //  71                 | G key
    0,                  0,   //  72                 | H key
    0,                  0,   //  73                 | I key
    0,                  0,   //  74                 | J key
    0,                  0,   //  75                 | K key
    0,                  0,   //  76                 | L key
    0,                  0,   //  77                 | M key
    0,                  0,   //  78                 | N key
    0,                  0,   //  79                | O key
    0,                  0,   //  80                 | P key
    0,                  0,   //  81                | Q key
    0,                  0,   //  82                 | R key
    0,                  0,   //  83                 | S key
    0,                  0,   //  84                 | T key
    0,                  0,   //  85                 | U key
    0,                  0,   //  86                 | V key
    0,                  0,   //  87                 | W key
    0,                  0,   //  88                | X key
    0,                  0,   //  89                | Y key
    0,                  0,   //  90                 | Z key
    Qt::Key_Meta,       XK_Meta_L,   //  91                   | Left Windows  - MS Natural kbd
    Qt::Key_Meta,       XK_Meta_R,   //  92                   | Right Windows - MS Natural kbd
    Qt::Key_Menu,       XK_Menu,   //  93                   | Application key-MS Natural kbd
    Qt::Key_unknown,    0,   //  94      -- reserved --
    Qt::Key_Sleep,      0,   //  95      VK_SLEEP
    Qt::Key_0,          XK_0,   //  96                | Numeric keypad 0 key
    Qt::Key_1,          XK_1,   //  97                | Numeric keypad 1 key
    Qt::Key_2,          XK_2,   //  98                | Numeric keypad 2 key
    Qt::Key_3,          XK_3,   //  99                | Numeric keypad 3 key
    Qt::Key_4,          XK_4,   // 100                | Numeric keypad 4 key
    Qt::Key_5,          XK_5,   // 101                | Numeric keypad 5 key
    Qt::Key_6,          XK_6,   // 102                | Numeric keypad 6 key
    Qt::Key_7,          XK_7,   // 103                | Numeric keypad 7 key
    Qt::Key_8,          XK_8,   // 104                | Numeric keypad 8 key
    Qt::Key_9,          XK_9,   // 105                | Numeric keypad 9 key
    Qt::Key_Asterisk,   XK_asterisk,   // 106               | Multiply key
    Qt::Key_Plus,       XK_plus,   // 107                    | Add key
    Qt::Key_Comma,      XK_comma,   // 108              | Separator key
    Qt::Key_Minus,      XK_minus,   // 109               | Subtract key
    Qt::Key_Period,     XK_period,   // 110                | Decimal key
    Qt::Key_Slash,      XK_slash,   // 111                 | Divide key
    Qt::Key_F1,         XK_F1,   // 112                     | F1 key
    Qt::Key_F2,         XK_F2,   // 113                     | F2 key
    Qt::Key_F3,         XK_F3,   // 114                     | F3 key
    Qt::Key_F4,         XK_F4,   // 115                     | F4 key
    Qt::Key_F5,         XK_F5,   // 116                     | F5 key
    Qt::Key_F6,         XK_F6,   // 117                     | F6 key
    Qt::Key_F7,         XK_F7,   // 118                     | F7 key
    Qt::Key_F8,         XK_F8,   // 119                     | F8 key
    Qt::Key_F9,         XK_F9,   // 120                     | F9 key
    Qt::Key_F10,        XK_F10,   // 121                    | F10 key
    Qt::Key_F11,        XK_F11,   // 122                    | F11 key
    Qt::Key_F12,        XK_F12,   // 123                    | F12 key
    Qt::Key_F13,        XK_F13,   // 124                    | F13 key
    Qt::Key_F14,        XK_F14,   // 125                    | F14 key
    Qt::Key_F15,        XK_F15,   // 126                    | F15 key
    Qt::Key_F16,        XK_F16,   // 127                    | F16 key
    Qt::Key_F17,        XK_F17,   // 128                    | F17 key
    Qt::Key_F18,        XK_F18,   // 129                    | F18 key
    Qt::Key_F19,        XK_F19,   // 130                    | F19 key
    Qt::Key_F20,        XK_F20,   // 131                    | F20 key
    Qt::Key_F21,        XK_F21,   // 132                    | F21 key
    Qt::Key_F22,        XK_F22,   // 133                    | F22 key
    Qt::Key_F23,        XK_F23,   // 134                    | F23 key
    Qt::Key_F24,        XK_F24,   // 135                    | F24 key
    Qt::Key_unknown,    0,  // 136      -- unassigned --
    Qt::Key_unknown,    0,  // 137      -- unassigned --
    Qt::Key_unknown,    0,  // 138      -- unassigned --
    Qt::Key_unknown,    0,  // 139      -- unassigned --
    Qt::Key_unknown,    0,  // 140      -- unassigned --
    Qt::Key_unknown,    0,  // 141      -- unassigned --
    Qt::Key_unknown,    0,  // 142      -- unassigned --
    Qt::Key_unknown,    0,  // 143      -- unassigned --
    Qt::Key_NumLock,    0,  // 144                | Num Lock key
    Qt::Key_ScrollLock, 0,  // 145                 | Scroll Lock key
    // Fujitsu/OASYS kbd --------------------
    0, 0,  //Qt::Key_Jisho, // 146           | 'Dictionary' key /
    //              VK_OEM_NEC_EQUAL  = key on numpad on NEC PC-9800 kbd
    Qt::Key_Massyo,     XK_Massyo,   // 147         | 'Unregister word' key
    Qt::Key_Touroku,    XK_Touroku,   // 148         | 'Register word' key
    0, 0,  //Qt::Key_Oyayubi_Left,//149       | 'Left OYAYUBI' key
    0, 0,  //Qt::Key_Oyayubi_Right,//150      | 'Right OYAYUBI' key
    Qt::Key_unknown,    0,  // 151      -- unassigned --
    Qt::Key_unknown,    0,  // 152      -- unassigned --
    Qt::Key_unknown,    0,  // 153      -- unassigned --
    Qt::Key_unknown,    0,  // 154      -- unassigned --
    Qt::Key_unknown,    0,  // 155      -- unassigned --
    Qt::Key_unknown,    0,  // 156      -- unassigned --
    Qt::Key_unknown,    0,  // 157      -- unassigned --
    Qt::Key_unknown,    0,  // 158      -- unassigned --
    Qt::Key_unknown,    0,  // 159      -- unassigned --
    Qt::Key_Shift,      XK_Shift_L,   // 160                 | Left Shift key
    Qt::Key_Shift,      XK_Shift_R,   // 161                 | Right Shift key
    Qt::Key_Control,    XK_Control_L,   // 162         | Left Ctrl key
    Qt::Key_Control,    XK_Control_R,   // 163               | Right Ctrl key
    Qt::Key_Alt,        XK_Alt_L,   // 164                  | Left Menu key
    Qt::Key_Alt,        XK_Alt_R,   // 165                  | Right Menu key
    Qt::Key_Back,       0,   // 166           | Browser Back key
    Qt::Key_Forward,    0,   // 167        | Browser Forward key
    Qt::Key_Refresh,    0,   // 168        | Browser Refresh key
    Qt::Key_Stop,       0,   // 169           | Browser Stop key
    Qt::Key_Search,     XK_Find,   // 170         | Browser Search key
    Qt::Key_Favorites,  0,   // 171      | Browser Favorites key
    Qt::Key_HomePage,   0,   // 172           | Browser Start and Home key
    Qt::Key_VolumeMute, 0,   // 173            | Volume Mute key
    Qt::Key_VolumeDown, 0,   // 174            | Volume Down key
    Qt::Key_VolumeUp,   0,   // 175              | Volume Up key
    Qt::Key_MediaNext,  0,   // 176       | Next Track key
    Qt::Key_MediaPrevious, 0,   //177     | Previous Track key
    Qt::Key_MediaStop,  0,   // 178             | Stop Media key
    Qt::Key_MediaPlay,  0,   // 179       | Play/Pause Media key
    Qt::Key_LaunchMail, 0,   // 180            | Start Mail key
    Qt::Key_LaunchMedia, 0,   // 181       Select Media key
    Qt::Key_Launch0,    0,   // 182            | Start Application 1 key
    Qt::Key_Launch1,    0,   // 183            | Start Application 2 key
    Qt::Key_unknown,    0,   // 184      -- reserved --
    Qt::Key_unknown,    0,   // 185      -- reserved --
    0,                  0,   // 186                  | ';:' for US
    0,                  0,   // 187               | '+' any country
    0,                  0,   // 188              | ',' any country
    0,                  0,   // 189              | '-' any country
    0,                  0,   // 190             | '.' any country
    0,                  0,   // 191                  | '/?' for US
    0,                  0,   // 192                  | '`~' for US
    Qt::Key_unknown,    0,   // 193      -- reserved --
    Qt::Key_unknown,    0,   // 194      -- reserved --
    Qt::Key_unknown,    0,   // 195      -- reserved --
    Qt::Key_unknown,    0,   // 196      -- reserved --
    Qt::Key_unknown,    0,   // 197      -- reserved --
    Qt::Key_unknown,    0,   // 198      -- reserved --
    Qt::Key_unknown,    0,   // 199      -- reserved --
    Qt::Key_unknown,    0,   // 200      -- reserved --
    Qt::Key_unknown,    0,   // 201      -- reserved --
    Qt::Key_unknown,    0,   // 202      -- reserved --
    Qt::Key_unknown,    0,   // 203      -- reserved --
    Qt::Key_unknown,    0,   // 204      -- reserved --
    Qt::Key_unknown,    0,   // 205      -- reserved --
    Qt::Key_unknown,    0,   // 206      -- reserved --
    Qt::Key_unknown,    0,   // 207      -- reserved --
    Qt::Key_unknown,    0,   // 208      -- reserved --
    Qt::Key_unknown,    0,   // 209      -- reserved --
    Qt::Key_unknown,    0,   // 210      -- reserved --
    Qt::Key_unknown,    0,   // 211      -- reserved --
    Qt::Key_unknown,    0,   // 212      -- reserved --
    Qt::Key_unknown,    0,   // 213      -- reserved --
    Qt::Key_unknown,    0,   // 214      -- reserved --
    Qt::Key_unknown,    0,   // 215      -- reserved --
    Qt::Key_unknown,    0,   // 216      -- unassigned --
    Qt::Key_unknown,    0,   // 217      -- unassigned --
    Qt::Key_unknown,    0,   // 218      -- unassigned --
    0,                  0,   // 219                  | '[{' for US
    0,                  0,   // 220                  | '\|' for US
    0,                  0,    // 221                  | ']}' for US
    0,                  0,   // 222                  | ''"' for US
    0,                  0,   // 223
    Qt::Key_unknown,    0,   // 224      -- reserved --
    Qt::Key_unknown,    0,   // 225                 | 'AX' key on Japanese AX kbd
    Qt::Key_unknown,    0,   // 226                | "<>" or "\|" on RT 102-key kbd
    Qt::Key_unknown,    0,   // 227               | Help key on ICO
    Qt::Key_unknown,    0,   // 228                 | 00 key on ICO
    Qt::Key_unknown,    0,   // 229             | IME Process key
    Qt::Key_unknown,    0,   // 230              |
    Qt::Key_unknown,    0,   // 231                 | Unicode char as keystrokes
    Qt::Key_unknown,    0,   // 232      -- unassigned --
    // Nokia/Ericsson definitions ---------------
    Qt::Key_unknown,    0,   // 233      VK_OEM_RESET
    Qt::Key_unknown,    0,   // 234      VK_OEM_JUMP
    Qt::Key_unknown,    0,   // 235      VK_OEM_PA1
    Qt::Key_unknown,    0,   // 236      VK_OEM_PA2
    Qt::Key_unknown,    0,   // 237      VK_OEM_PA3
    Qt::Key_unknown,    0,   // 238      VK_OEM_WSCTRL
    Qt::Key_unknown,    0,   // 239      VK_OEM_CUSEL
    Qt::Key_unknown,    0,   // 240      VK_OEM_ATTN
    Qt::Key_unknown,    0,   // 241      VK_OEM_FINISH
    Qt::Key_unknown,    0,   // 242      VK_OEM_COPY
    Qt::Key_unknown,    0,   // 243      VK_OEM_AUTO
    Qt::Key_unknown,    0,   // 244      VK_OEM_ENLW
    Qt::Key_unknown,    0,   // 245      VK_OEM_BACKTAB
    Qt::Key_unknown,    0,   // 246                   | Attn key
    Qt::Key_unknown,    0,   // 247                  | CrSel key
    Qt::Key_unknown,    0,   // 248                  | ExSel key
    Qt::Key_unknown,    0,   // 249                  | Erase EOF key
    Qt::Key_Play,       0,   // 250                   | Play key
    Qt::Key_Zoom,       0,   // 251                   | Zoom key
    Qt::Key_unknown,    0,   // 252                 | Reserved
    Qt::Key_unknown,    0,   // 253                    | PA1 key
    Qt::Key_Clear,      XK_Clear,   // 254              | Clear key
    0,                  0
};

// keyboard mapping table
static const unsigned int KeyTblLinux[] = {

    // misc keys

    XK_Escape,                  Qt::Key_Escape, //1
    XK_Tab,                     Qt::Key_Tab,    //3
    XK_ISO_Left_Tab,            Qt::Key_Backtab,    //5
    XK_BackSpace,               Qt::Key_Backspace,  //  7
    XK_Return,                  Qt::Key_Return, //9
    XK_Insert,                  Qt::Key_Insert,
    XK_Delete,                  Qt::Key_Delete,
    XK_Clear,                   Qt::Key_Delete,
    XK_Pause,                   Qt::Key_Pause,
    XK_Print,                   Qt::Key_Print,
    XK_space,                   Qt::Key_Space,
    0x1007ff00,                 Qt::Key_SysReq,         // hardcoded X386 SysReq

    // cursor movement

    XK_Home,                    Qt::Key_Home,   //25
    XK_End,                     Qt::Key_End,
    XK_Left,                    Qt::Key_Left,
    XK_Up,                      Qt::Key_Up,
    XK_Right,                   Qt::Key_Right,
    XK_Down,                    Qt::Key_Down,
    XK_Prior,                   Qt::Key_PageUp,
    XK_Next,                    Qt::Key_PageDown,

    // modifiers

    XK_Shift_L,                 Qt::Key_Shift,  //41
    XK_Shift_R,                 Qt::Key_Shift,
    XK_Shift_Lock,              Qt::Key_Shift,
    XK_Control_L,               Qt::Key_Control,
    XK_Control_R,               Qt::Key_Control,
    XK_Meta_L,                  Qt::Key_Meta,
    XK_Meta_R,                  Qt::Key_Meta,
    XK_Alt_L,                   Qt::Key_Alt,
    XK_Alt_R,                   Qt::Key_Alt,
    XK_Caps_Lock,               Qt::Key_CapsLock,
    XK_Num_Lock,                Qt::Key_NumLock,
    XK_Scroll_Lock,             Qt::Key_ScrollLock,
    XK_Super_L,                 Qt::Key_Super_L,
    XK_Super_R,                 Qt::Key_Super_R,
    XK_Menu,                    Qt::Key_Menu,
    XK_Hyper_L,                 Qt::Key_Hyper_L,
    XK_Hyper_R,                 Qt::Key_Hyper_R,
    XK_Help,                    Qt::Key_Help,
    0x1000FF74,                 Qt::Key_Backtab,        // hardcoded HP backtab
    0x1005FF10,                 Qt::Key_F11,            // hardcoded Sun F36 (labeled F11)
    0x1005FF11,                 Qt::Key_F12,            // hardcoded Sun F37 (labeled F12)

    // numeric and function keypad keys

    XK_KP_Space,                Qt::Key_Space,  //83
    XK_KP_Tab,                  Qt::Key_Tab,
    XK_KP_Enter,                Qt::Key_Enter,
    XK_KP_Home,                 Qt::Key_Home,
    XK_KP_Left,                 Qt::Key_Left,
    XK_KP_Up,                   Qt::Key_Up,
    XK_KP_Right,                Qt::Key_Right,
    XK_KP_Down,                 Qt::Key_Down,
    XK_KP_Prior,                Qt::Key_PageUp,
    XK_KP_Next,                 Qt::Key_PageDown,
    XK_KP_End,                  Qt::Key_End,
    XK_KP_Begin,                Qt::Key_Clear,
    XK_KP_Insert,               Qt::Key_Insert,
    XK_KP_Delete,               Qt::Key_Delete,
    XK_KP_Equal,                Qt::Key_Equal,
    XK_KP_Multiply,             Qt::Key_Asterisk,
    XK_KP_Add,                  Qt::Key_Plus,
    XK_KP_Separator,            Qt::Key_Comma,
    XK_KP_Subtract,             Qt::Key_Minus,
    XK_KP_Decimal,              Qt::Key_Period,
    XK_KP_Divide,               Qt::Key_Slash,

    // International input method support keys

    // International & multi-key character composition
    XK_ISO_Level3_Shift,        Qt::Key_AltGr,  //125
    XK_Multi_key,		Qt::Key_Multi_key,
    XK_Codeinput,		Qt::Key_Codeinput,
    XK_SingleCandidate,		Qt::Key_SingleCandidate,
    XK_MultipleCandidate,	Qt::Key_MultipleCandidate,
    XK_PreviousCandidate,	Qt::Key_PreviousCandidate,

    // Misc Functions
    XK_Mode_switch,		Qt::Key_Mode_switch,    //137
    XK_script_switch,		Qt::Key_Mode_switch,    //139

    // Japanese keyboard support
    XK_Kanji,			Qt::Key_Kanji,  //121
    XK_Muhenkan,		Qt::Key_Muhenkan,
    //XK_Henkan_Mode,		Qt::Key_Henkan_Mode,
    XK_Henkan_Mode,		Qt::Key_Henkan,
    XK_Henkan,			Qt::Key_Henkan,
    XK_Romaji,			Qt::Key_Romaji,
    XK_Hiragana,		Qt::Key_Hiragana,
    XK_Katakana,		Qt::Key_Katakana,
    XK_Hiragana_Katakana,	Qt::Key_Hiragana_Katakana,
    XK_Zenkaku,			Qt::Key_Zenkaku,
    XK_Hankaku,			Qt::Key_Hankaku,
    XK_Zenkaku_Hankaku,		Qt::Key_Zenkaku_Hankaku,
    XK_Touroku,			Qt::Key_Touroku,
    XK_Massyo,			Qt::Key_Massyo,
    XK_Kana_Lock,		Qt::Key_Kana_Lock,
    XK_Kana_Shift,		Qt::Key_Kana_Shift,
    XK_Eisu_Shift,		Qt::Key_Eisu_Shift,
    XK_Eisu_toggle,		Qt::Key_Eisu_toggle,
    //XK_Kanji_Bangou,		Qt::Key_Kanji_Bangou,
    //XK_Zen_Koho,		Qt::Key_Zen_Koho,
    //XK_Mae_Koho,		Qt::Key_Mae_Koho,
    XK_Kanji_Bangou,		Qt::Key_Codeinput,
    XK_Zen_Koho,		Qt::Key_MultipleCandidate,
    XK_Mae_Koho,		Qt::Key_PreviousCandidate,

#ifdef XK_KOREAN
    // Korean keyboard support
    XK_Hangul,			Qt::Key_Hangul, //181
    XK_Hangul_Start,		Qt::Key_Hangul_Start,
    XK_Hangul_End,		Qt::Key_Hangul_End,
    XK_Hangul_Hanja,		Qt::Key_Hangul_Hanja,
    XK_Hangul_Jamo,		Qt::Key_Hangul_Jamo,
    XK_Hangul_Romaja,		Qt::Key_Hangul_Romaja,
    //XK_Hangul_Codeinput,	Qt::Key_Hangul_Codeinput,
    XK_Hangul_Codeinput,	Qt::Key_Codeinput,
    XK_Hangul_Jeonja,		Qt::Key_Hangul_Jeonja,
    XK_Hangul_Banja,		Qt::Key_Hangul_Banja,
    XK_Hangul_PreHanja,		Qt::Key_Hangul_PreHanja,
    XK_Hangul_PostHanja,	Qt::Key_Hangul_PostHanja,
    //XK_Hangul_SingleCandidate,Qt::Key_Hangul_SingleCandidate,
    //XK_Hangul_MultipleCandidate,Qt::Key_Hangul_MultipleCandidate,
    //XK_Hangul_PreviousCandidate,Qt::Key_Hangul_PreviousCandidate,
    XK_Hangul_SingleCandidate,	Qt::Key_SingleCandidate, //203
    XK_Hangul_MultipleCandidate,Qt::Key_MultipleCandidate,
    XK_Hangul_PreviousCandidate,Qt::Key_PreviousCandidate,
    XK_Hangul_Special,		Qt::Key_Hangul_Special,
    //XK_Hangul_switch,		Qt::Key_Hangul_switch,
    XK_Hangul_switch,		Qt::Key_Mode_switch,
#endif  // XK_KOREAN

    // dead keys
    XK_dead_grave,              Qt::Key_Dead_Grave, //215
    XK_dead_acute,              Qt::Key_Dead_Acute,
    XK_dead_circumflex,         Qt::Key_Dead_Circumflex,
    XK_dead_tilde,              Qt::Key_Dead_Tilde,
    XK_dead_macron,             Qt::Key_Dead_Macron,
    XK_dead_breve,              Qt::Key_Dead_Breve,
    XK_dead_abovedot,           Qt::Key_Dead_Abovedot,
    XK_dead_diaeresis,          Qt::Key_Dead_Diaeresis,
    XK_dead_abovering,          Qt::Key_Dead_Abovering,
    XK_dead_doubleacute,        Qt::Key_Dead_Doubleacute,
    XK_dead_caron,              Qt::Key_Dead_Caron,
    XK_dead_cedilla,            Qt::Key_Dead_Cedilla,
    XK_dead_ogonek,             Qt::Key_Dead_Ogonek,
    XK_dead_iota,               Qt::Key_Dead_Iota,
    XK_dead_voiced_sound,       Qt::Key_Dead_Voiced_Sound,
    XK_dead_semivoiced_sound,   Qt::Key_Dead_Semivoiced_Sound,
    XK_dead_belowdot,           Qt::Key_Dead_Belowdot,
    XK_dead_hook,               Qt::Key_Dead_Hook,
    XK_dead_horn,               Qt::Key_Dead_Horn,

    // Special keys from X.org - This include multimedia keys,
    // wireless/bluetooth/uwb keys, special launcher keys, etc.
    XF86XK_Back,                Qt::Key_Back,   //258
    XF86XK_Forward,             Qt::Key_Forward,
    XF86XK_Stop,                Qt::Key_Stop,
    XF86XK_Refresh,             Qt::Key_Refresh,
    XF86XK_Favorites,           Qt::Key_Favorites,
    XF86XK_AudioMedia,          Qt::Key_LaunchMedia,
    XF86XK_OpenURL,             Qt::Key_OpenUrl,
    XF86XK_HomePage,            Qt::Key_HomePage,
    XF86XK_Search,              Qt::Key_Search,
    XF86XK_AudioLowerVolume,    Qt::Key_VolumeDown,
    XF86XK_AudioMute,           Qt::Key_VolumeMute,
    XF86XK_AudioRaiseVolume,    Qt::Key_VolumeUp,
    XF86XK_AudioPlay,           Qt::Key_MediaPlay,
    XF86XK_AudioStop,           Qt::Key_MediaStop,
    XF86XK_AudioPrev,           Qt::Key_MediaPrevious,
    XF86XK_AudioNext,           Qt::Key_MediaNext,
    XF86XK_AudioRecord,         Qt::Key_MediaRecord,
    XF86XK_Mail,                Qt::Key_LaunchMail,
    XF86XK_MyComputer,          Qt::Key_Launch0,  // ### Qt 5: remap properly
    XF86XK_Calculator,          Qt::Key_Launch1,
    XF86XK_Memo,                Qt::Key_Memo,
    XF86XK_ToDoList,            Qt::Key_ToDoList,
    XF86XK_Calendar,            Qt::Key_Calendar,
    XF86XK_PowerDown,           Qt::Key_PowerDown,
    XF86XK_ContrastAdjust,      Qt::Key_ContrastAdjust,
    XF86XK_Standby,             Qt::Key_Standby,
    XF86XK_MonBrightnessUp,     Qt::Key_MonBrightnessUp,
    XF86XK_MonBrightnessDown,   Qt::Key_MonBrightnessDown,
    XF86XK_KbdLightOnOff,       Qt::Key_KeyboardLightOnOff,
    XF86XK_KbdBrightnessUp,     Qt::Key_KeyboardBrightnessUp,
    XF86XK_KbdBrightnessDown,   Qt::Key_KeyboardBrightnessDown,
    XF86XK_PowerOff,            Qt::Key_PowerOff,
    XF86XK_WakeUp,              Qt::Key_WakeUp,
    XF86XK_Eject,               Qt::Key_Eject,
    XF86XK_ScreenSaver,         Qt::Key_ScreenSaver,
    XF86XK_WWW,                 Qt::Key_WWW,
    XF86XK_Sleep,               Qt::Key_Sleep,
    XF86XK_LightBulb,           Qt::Key_LightBulb,
    XF86XK_Shop,                Qt::Key_Shop,
    XF86XK_History,             Qt::Key_History,
    XF86XK_AddFavorite,         Qt::Key_AddFavorite,
    XF86XK_HotLinks,            Qt::Key_HotLinks,
    XF86XK_BrightnessAdjust,    Qt::Key_BrightnessAdjust,
    XF86XK_Finance,             Qt::Key_Finance,
    XF86XK_Community,           Qt::Key_Community,
    XF86XK_AudioRewind,         Qt::Key_AudioRewind,
    XF86XK_BackForward,         Qt::Key_BackForward,
    XF86XK_ApplicationLeft,     Qt::Key_ApplicationLeft,
    XF86XK_ApplicationRight,    Qt::Key_ApplicationRight,
    XF86XK_Book,                Qt::Key_Book,
    XF86XK_CD,                  Qt::Key_CD,
    XF86XK_Calculater,          Qt::Key_Calculator,
    XF86XK_Clear,               Qt::Key_Clear,
    XF86XK_ClearGrab,           Qt::Key_ClearGrab,
    XF86XK_Close,               Qt::Key_Close,
    XF86XK_Copy,                Qt::Key_Copy,
    XF86XK_Cut,                 Qt::Key_Cut,    //370
    XF86XK_Display,             Qt::Key_Display,
    XF86XK_DOS,                 Qt::Key_DOS,
    XF86XK_Documents,           Qt::Key_Documents,
    XF86XK_Excel,               Qt::Key_Excel,
    XF86XK_Explorer,            Qt::Key_Explorer,
    XF86XK_Game,                Qt::Key_Game,
    XF86XK_Go,                  Qt::Key_Go,
    XF86XK_iTouch,              Qt::Key_iTouch,
    XF86XK_LogOff,              Qt::Key_LogOff,
    XF86XK_Market,              Qt::Key_Market,
    XF86XK_Meeting,             Qt::Key_Meeting,
    XF86XK_MenuKB,              Qt::Key_MenuKB,
    XF86XK_MenuPB,              Qt::Key_MenuPB,
    XF86XK_MySites,             Qt::Key_MySites,
    XF86XK_News,                Qt::Key_News,
    XF86XK_OfficeHome,          Qt::Key_OfficeHome,
    XF86XK_Option,              Qt::Key_Option,
    XF86XK_Paste,               Qt::Key_Paste,
    XF86XK_Phone,               Qt::Key_Phone,
    XF86XK_Reply,               Qt::Key_Reply, //410
    XF86XK_Reload,              Qt::Key_Reload,
    XF86XK_RotateWindows,       Qt::Key_RotateWindows,
    XF86XK_RotationPB,          Qt::Key_RotationPB,
    XF86XK_RotationKB,          Qt::Key_RotationKB,
    XF86XK_Save,                Qt::Key_Save,
    XF86XK_Send,                Qt::Key_Send,
    XF86XK_Spell,               Qt::Key_Spell,
    XF86XK_SplitScreen,         Qt::Key_SplitScreen,
    XF86XK_Support,             Qt::Key_Support,
    XF86XK_TaskPane,            Qt::Key_TaskPane,
    XF86XK_Terminal,            Qt::Key_Terminal,
    XF86XK_Tools,               Qt::Key_Tools,
    XF86XK_Travel,              Qt::Key_Travel,
    XF86XK_Video,               Qt::Key_Video,
    XF86XK_Word,                Qt::Key_Word,
    XF86XK_Xfer,                Qt::Key_Xfer,
    XF86XK_ZoomIn,              Qt::Key_ZoomIn,
    XF86XK_ZoomOut,             Qt::Key_ZoomOut,
    XF86XK_Away,                Qt::Key_Away,
    XF86XK_Messenger,           Qt::Key_Messenger,
    XF86XK_WebCam,              Qt::Key_WebCam,
    XF86XK_MailForward,         Qt::Key_MailForward,
    XF86XK_Pictures,            Qt::Key_Pictures,
    XF86XK_Music,               Qt::Key_Music,
    XF86XK_Battery,             Qt::Key_Battery,
    XF86XK_Bluetooth,           Qt::Key_Bluetooth,
    XF86XK_WLAN,                Qt::Key_WLAN,
    XF86XK_UWB,                 Qt::Key_UWB,
    XF86XK_AudioForward,        Qt::Key_AudioForward,
    XF86XK_AudioRepeat,         Qt::Key_AudioRepeat,
    XF86XK_AudioRandomPlay,     Qt::Key_AudioRandomPlay,
    XF86XK_Subtitle,            Qt::Key_Subtitle,
    XF86XK_AudioCycleTrack,     Qt::Key_AudioCycleTrack,
    XF86XK_Time,                Qt::Key_Time,
    XF86XK_Select,              Qt::Key_Select,
    XF86XK_View,                Qt::Key_View,
    XF86XK_TopMenu,             Qt::Key_TopMenu,
    XF86XK_Bluetooth,           Qt::Key_Bluetooth,
    XF86XK_Suspend,             Qt::Key_Suspend,
    XF86XK_Hibernate,           Qt::Key_Hibernate,
    XF86XK_Launch0,             Qt::Key_Launch2, // ### Qt 5: remap properly
    XF86XK_Launch1,             Qt::Key_Launch3,
    XF86XK_Launch2,             Qt::Key_Launch4,
    XF86XK_Launch3,             Qt::Key_Launch5,
    XF86XK_Launch4,             Qt::Key_Launch6,
    XF86XK_Launch5,             Qt::Key_Launch7,
    XF86XK_Launch6,             Qt::Key_Launch8,
    XF86XK_Launch7,             Qt::Key_Launch9,
    XF86XK_Launch8,             Qt::Key_LaunchA,
    XF86XK_Launch9,             Qt::Key_LaunchB, //510
    XF86XK_LaunchA,             Qt::Key_LaunchC,
    XF86XK_LaunchB,             Qt::Key_LaunchD,
    XF86XK_LaunchC,             Qt::Key_LaunchE,
    XF86XK_LaunchD,             Qt::Key_LaunchF,
    XF86XK_LaunchE,             Qt::Key_LaunchG,
    XF86XK_LaunchF,             Qt::Key_LaunchH, //522

    // Qtopia keys
    QTOPIAXK_Select,            Qt::Key_Select, //524
    QTOPIAXK_Yes,               Qt::Key_Yes,
    QTOPIAXK_No,                Qt::Key_No,
    QTOPIAXK_Cancel,            Qt::Key_Cancel,
    QTOPIAXK_Printer,           Qt::Key_Printer,
    QTOPIAXK_Execute,           Qt::Key_Execute,
    QTOPIAXK_Sleep,             Qt::Key_Sleep,
    QTOPIAXK_Play,              Qt::Key_Play,
    QTOPIAXK_Zoom,              Qt::Key_Zoom,
    QTOPIAXK_Context1,          Qt::Key_Context1,
    QTOPIAXK_Context2,          Qt::Key_Context2,
    QTOPIAXK_Context3,          Qt::Key_Context3,
    QTOPIAXK_Context4,          Qt::Key_Context4,
    QTOPIAXK_Call,              Qt::Key_Call,
    QTOPIAXK_Hangup,            Qt::Key_Hangup,
    QTOPIAXK_Flip,              Qt::Key_Flip, //554

    //XK_KP_F1,                 Qt::Key_F1,
    //XK_KP_F2,                 Qt::Key_F2,
    //XK_KP_F3,                 Qt::Key_F3,
    //XK_KP_F4,                 Qt::Key_F4,

    XK_F1,                       Qt::Key_F1, //556
    XK_F2,                       Qt::Key_F2,
    XK_F3,                       Qt::Key_F3,
    XK_F4,                       Qt::Key_F4,
    XK_F5,                       Qt::Key_F5,
    XK_F6,                       Qt::Key_F6,
    XK_F7,                       Qt::Key_F7,
    XK_F8,                       Qt::Key_F8,
    XK_F9,                       Qt::Key_F9,
    XK_F10,                      Qt::Key_F10,
    XK_F11,                      Qt::Key_F11,
    XK_F12,                      Qt::Key_F12,
    XK_F13,                      Qt::Key_F13,
    XK_F14,                      Qt::Key_F14,
    XK_F15,                      Qt::Key_F15,
    XK_F16,                      Qt::Key_F16,
    XK_F17,                      Qt::Key_F17,
    XK_F18,                      Qt::Key_F18,
    XK_F19,                      Qt::Key_F19,
    XK_F20,                      Qt::Key_F20,
    XK_F21,                      Qt::Key_F21,
    XK_F22,                      Qt::Key_F22,
    XK_F23,                      Qt::Key_F23,
    XK_F24,                      Qt::Key_F24, //602

    XK_A,                        Qt::Key_A, //604
    XK_B,                        Qt::Key_B,
    XK_C,                        Qt::Key_C,
    XK_D,                        Qt::Key_D, //610
    XK_E,                        Qt::Key_E,
    XK_F,                        Qt::Key_F,
    XK_G,                        Qt::Key_G,
    XK_H,                        Qt::Key_H,
    XK_I,                        Qt::Key_I,
    XK_J,                        Qt::Key_J,
    XK_K,                        Qt::Key_K,
    XK_L,                        Qt::Key_L,
    XK_M,                        Qt::Key_M,
    XK_N,                        Qt::Key_N,
    XK_O,                        Qt::Key_O,
    XK_P,                        Qt::Key_P,
    XK_R,                        Qt::Key_R,
    XK_S,                        Qt::Key_S,
    XK_T,                        Qt::Key_T,
    XK_U,                        Qt::Key_U,
    XK_V,                        Qt::Key_V,
    XK_W,                        Qt::Key_W,
    XK_X,                        Qt::Key_X,
    XK_Y,                        Qt::Key_Y,
    XK_Z,                        Qt::Key_Z, //652

    0,                          0   //654
};

#endif
#endif


static const uint KeyTbl[] = { // Keyboard mapping table

    Qt::Key_unknown,    //   0   0x00
    Qt::Key_unknown,    //   1   0x01   VK_LBUTTON          | Left mouse button
    Qt::Key_unknown,    //   2   0x02   VK_RBUTTON          | Right mouse button
    Qt::Key_Cancel,     //   3   0x03   VK_CANCEL           | Control-Break processing
    Qt::Key_unknown,    //   4   0x04   VK_MBUTTON          | Middle mouse button
    Qt::Key_unknown,    //   5   0x05   VK_XBUTTON1         | X1 mouse button
    Qt::Key_unknown,    //   6   0x06   VK_XBUTTON2         | X2 mouse button
    Qt::Key_unknown,    //   7   0x07   -- unassigned --
    Qt::Key_Backspace,  //   8   0x08   VK_BACK             | BackSpace key
    Qt::Key_Tab,        //   9   0x09   VK_TAB              | Tab key
    Qt::Key_unknown,    //  10   0x0A   -- reserved --
    Qt::Key_unknown,    //  11   0x0B   -- reserved --
    Qt::Key_Clear,      //  12   0x0C   VK_CLEAR            | Clear key
    Qt::Key_Return,     //  13   0x0D   VK_RETURN           | Enter key
    Qt::Key_unknown,    //  14   0x0E   -- unassigned --
    Qt::Key_unknown,    //  15   0x0F   -- unassigned --
    Qt::Key_Shift,      //  16   0x10   VK_SHIFT            | Shift key
    Qt::Key_Control,    //  17   0x11   VK_CONTROL          | Ctrl key
    Qt::Key_unknown, // Qt::Key_Alt,        //  18   0x12   VK_MENU             | Alt key
    Qt::Key_Pause,      //  19   0x13   VK_PAUSE            | Pause key
    Qt::Key_CapsLock,   //  20   0x14   VK_CAPITAL          | Caps-Lock
    Qt::Key_unknown,    //  21   0x15   VK_KANA / VK_HANGUL | IME Kana or Hangul mode
    Qt::Key_unknown,    //  22   0x16   -- unassigned --
    Qt::Key_unknown,    //  23   0x17   VK_JUNJA            | IME Junja mode
    Qt::Key_unknown,    //  24   0x18   VK_FINAL            | IME final mode
    Qt::Key_unknown,    //  25   0x19   VK_HANJA / VK_KANJI | IME Hanja or Kanji mode
    Qt::Key_unknown,    //  26   0x1A   -- unassigned --
    Qt::Key_Escape,     //  27   0x1B   VK_ESCAPE           | Esc key
    Qt::Key_unknown,    //  28   0x1C   VK_CONVERT          | IME convert
    Qt::Key_unknown,    //  29   0x1D   VK_NONCONVERT       | IME non-convert
    Qt::Key_unknown,    //  30   0x1E   VK_ACCEPT           | IME accept
    Qt::Key_Mode_switch,//  31   0x1F   VK_MODECHANGE       | IME mode change request
    Qt::Key_Space,      //  32   0x20   VK_SPACE            | Spacebar
    Qt::Key_PageUp,     //  33   0x21   VK_PRIOR            | Page Up key
    Qt::Key_PageDown,   //  34   0x22   VK_NEXT             | Page Down key
    Qt::Key_End,        //  35   0x23   VK_END              | End key
    Qt::Key_Home,       //  36   0x24   VK_HOME             | Home key
    Qt::Key_Left,       //  37   0x25   VK_LEFT             | Left arrow key
    Qt::Key_Up,         //  38   0x26   VK_UP               | Up arrow key
    Qt::Key_Right,      //  39   0x27   VK_RIGHT            | Right arrow key
    Qt::Key_Down,       //  40   0x28   VK_DOWN             | Down arrow key
    Qt::Key_Select,     //  41   0x29   VK_SELECT           | Select key
    Qt::Key_Printer,    //  42   0x2A   VK_PRINT            | Print key
    Qt::Key_Execute,    //  43   0x2B   VK_EXECUTE          | Execute key
    Qt::Key_Print,      //  44   0x2C   VK_SNAPSHOT         | Print Screen key
    Qt::Key_Insert,     //  45   0x2D   VK_INSERT           | Ins key
    Qt::Key_Delete,     //  46   0x2E   VK_DELETE           | Del key  //65439
    Qt::Key_Help,       //  47   0x2F   VK_HELP             | Help key //65386
    0,                  //  48   0x30   (VK_0)              | 0 key
    0,                  //  49   0x31   (VK_1)              | 1 key
    0,                  //  50   0x32   (VK_2)              | 2 key
    0,                  //  51   0x33   (VK_3)              | 3 key
    0,                  //  52   0x34   (VK_4)              | 4 key
    0,                  //  53   0x35   (VK_5)              | 5 key
    0,                  //  54   0x36   (VK_6)              | 6 key
    0,                  //  55   0x37   (VK_7)              | 7 key
    0,                  //  56   0x38   (VK_8)              | 8 key
    0,                  //  57   0x39   (VK_9)              | 9 key
    Qt::Key_unknown,    //  58   0x3A   -- unassigned --
    Qt::Key_unknown,    //  59   0x3B   -- unassigned --
    Qt::Key_unknown,    //  60   0x3C   -- unassigned --
    Qt::Key_unknown,    //  61   0x3D   -- unassigned --
    Qt::Key_unknown,    //  62   0x3E   -- unassigned --
    Qt::Key_unknown,    //  63   0x3F   -- unassigned --
    Qt::Key_unknown,    //  64   0x40   -- unassigned --
    Qt::Key_A,                  //  65   0x41   (VK_A)              | A key
    Qt::Key_B,                  //  66   0x42   (VK_B)              | B key
    Qt::Key_C,                  //  67   0x43   (VK_C)              | C key
    Qt::Key_D,                  //  68   0x44   (VK_D)              | D key
    Qt::Key_E,                  //  69   0x45   (VK_E)              | E key
    Qt::Key_F,                  //  70   0x46   (VK_F)              | F key
    Qt::Key_G,                  //  71   0x47   (VK_G)              | G key
    Qt::Key_H,                  //  72   0x48   (VK_H)              | H key
    Qt::Key_I,                  //  73   0x49   (VK_I)              | I key
    Qt::Key_J,                  //  74   0x4A   (VK_J)              | J key
    Qt::Key_K,                  //  75   0x4B   (VK_K)              | K key
    Qt::Key_L,                  //  76   0x4C   (VK_L)              | L key
    Qt::Key_M,                  //  77   0x4D   (VK_M)              | M key
    Qt::Key_N,                  //  78   0x4E   (VK_N)              | N key
    Qt::Key_O,                  //  79   0x4F   (VK_O)              | O key
    Qt::Key_P,                  //  80   0x50   (VK_P)              | P key
    Qt::Key_Q,                  //  81   0x51   (VK_Q)              | Q key
    Qt::Key_R,                  //  82   0x52   (VK_R)              | R key
    Qt::Key_S,                  //  83   0x53   (VK_S)              | S key
    Qt::Key_T,                  //  84   0x54   (VK_T)              | T key
    Qt::Key_U,                  //  85   0x55   (VK_U)              | U key
    Qt::Key_V,                  //  86   0x56   (VK_V)              | V key
    Qt::Key_W,                  //  87   0x57   (VK_W)              | W key
    Qt::Key_X,                  //  88   0x58   (VK_X)              | X key
    Qt::Key_Y,                  //  89   0x59   (VK_Y)              | Y key
    Qt::Key_Z,                  //  90   0x5A   (VK_Z)              | Z key
    Qt::Key_Meta,       //  91   0x5B   VK_LWIN             | Left Windows  - MS Natural kbd
    Qt::Key_Meta,       //  92   0x5C   VK_RWIN             | Right Windows - MS Natural kbd
    Qt::Key_Menu,       //  93   0x5D   VK_APPS             | Application key-MS Natural kbd
    Qt::Key_unknown,    //  94   0x5E   -- reserved --
    Qt::Key_Sleep,      //  95   0x5F   VK_SLEEP
    Qt::Key_0,          //  96   0x60   VK_NUMPAD0          | Numeric keypad 0 key
    Qt::Key_1,          //  97   0x61   VK_NUMPAD1          | Numeric keypad 1 key
    Qt::Key_2,          //  98   0x62   VK_NUMPAD2          | Numeric keypad 2 key
    Qt::Key_3,          //  99   0x63   VK_NUMPAD3          | Numeric keypad 3 key
    Qt::Key_4,          // 100   0x64   VK_NUMPAD4          | Numeric keypad 4 key
    Qt::Key_5,          // 101   0x65   VK_NUMPAD5          | Numeric keypad 5 key
    Qt::Key_6,          // 102   0x66   VK_NUMPAD6          | Numeric keypad 6 key
    Qt::Key_7,          // 103   0x67   VK_NUMPAD7          | Numeric keypad 7 key
    Qt::Key_8,          // 104   0x68   VK_NUMPAD8          | Numeric keypad 8 key
    Qt::Key_9,          // 105   0x69   VK_NUMPAD9          | Numeric keypad 9 key
    Qt::Key_Asterisk,   // 106   0x6A   VK_MULTIPLY         | Multiply key
    Qt::Key_Plus,       // 107   0x6B   VK_ADD              | Add key
    Qt::Key_Comma,      // 108   0x6C   VK_SEPARATOR        | Separator key
    Qt::Key_Minus,      // 109   0x6D   VK_SUBTRACT         | Subtract key
    Qt::Key_Period,     // 110   0x6E   VK_DECIMAL          | Decimal key
    Qt::Key_Slash,      // 111   0x6F   VK_DIVIDE           | Divide key
    Qt::Key_F1,         // 112   0x70   VK_F1               | F1 key
    Qt::Key_F2,         // 113   0x71   VK_F2               | F2 key
    Qt::Key_F3,         // 114   0x72   VK_F3               | F3 key
    Qt::Key_F4,         // 115   0x73   VK_F4               | F4 key
    Qt::Key_F5,         // 116   0x74   VK_F5               | F5 key
    Qt::Key_F6,         // 117   0x75   VK_F6               | F6 key
    Qt::Key_F7,         // 118   0x76   VK_F7               | F7 key
    Qt::Key_F8,         // 119   0x77   VK_F8               | F8 key
    Qt::Key_F9,         // 120   0x78   VK_F9               | F9 key
    Qt::Key_F10,        // 121   0x79   VK_F10              | F10 key
    Qt::Key_F11,        // 122   0x7A   VK_F11              | F11 key
    Qt::Key_F12,        // 123   0x7B   VK_F12              | F12 key
    Qt::Key_F13,        // 124   0x7C   VK_F13              | F13 key
    Qt::Key_F14,        // 125   0x7D   VK_F14              | F14 key
    Qt::Key_F15,        // 126   0x7E   VK_F15              | F15 key
    Qt::Key_F16,        // 127   0x7F   VK_F16              | F16 key
    Qt::Key_F17,        // 128   0x80   VK_F17              | F17 key
    Qt::Key_F18,        // 129   0x81   VK_F18              | F18 key
    Qt::Key_F19,        // 130   0x82   VK_F19              | F19 key
    Qt::Key_F20,        // 131   0x83   VK_F20              | F20 key
    Qt::Key_F21,        // 132   0x84   VK_F21              | F21 key
    Qt::Key_F22,        // 133   0x85   VK_F22              | F22 key
    Qt::Key_F23,        // 134   0x86   VK_F23              | F23 key
    Qt::Key_F24,        // 135   0x87   VK_F24              | F24 key
    Qt::Key_unknown,    // 136   0x88   -- unassigned --
    Qt::Key_unknown,    // 137   0x89   -- unassigned --
    Qt::Key_unknown,    // 138   0x8A   -- unassigned --
    Qt::Key_unknown,    // 139   0x8B   -- unassigned --
    Qt::Key_unknown,    // 140   0x8C   -- unassigned --
    Qt::Key_unknown,    // 141   0x8D   -- unassigned --
    Qt::Key_unknown,    // 142   0x8E   -- unassigned --
    Qt::Key_unknown,    // 143   0x8F   -- unassigned --
    Qt::Key_NumLock,    // 144   0x90   VK_NUMLOCK          | Num Lock key
    Qt::Key_ScrollLock, // 145   0x91   VK_SCROLL           | Scroll Lock key
    // Fujitsu/OASYS kbd --------------------
    0, //Qt::Key_Jisho, // 146   0x92   VK_OEM_FJ_JISHO     | 'Dictionary' key /
    //              VK_OEM_NEC_EQUAL  = key on numpad on NEC PC-9800 kbd
    Qt::Key_Massyo,     // 147   0x93   VK_OEM_FJ_MASSHOU   | 'Unregister word' key
    Qt::Key_Touroku,    // 148   0x94   VK_OEM_FJ_TOUROKU   | 'Register word' key
    0, //Qt::Key_Oyayubi_Left,//149   0x95  VK_OEM_FJ_LOYA  | 'Left OYAYUBI' key
    0, //Qt::Key_Oyayubi_Right,//150  0x96  VK_OEM_FJ_ROYA  | 'Right OYAYUBI' key
    Qt::Key_unknown,    // 151   0x97   -- unassigned --
    Qt::Key_unknown,    // 152   0x98   -- unassigned --
    Qt::Key_unknown,    // 153   0x99   -- unassigned --
    Qt::Key_unknown,    // 154   0x9A   -- unassigned --
    Qt::Key_unknown,    // 155   0x9B   -- unassigned --
    Qt::Key_unknown,    // 156   0x9C   -- unassigned --
    Qt::Key_unknown,    // 157   0x9D   -- unassigned --
    Qt::Key_unknown,    // 158   0x9E   -- unassigned --
    Qt::Key_unknown,    // 159   0x9F   -- unassigned --
    Qt::Key_Shift,      // 160   0xA0   VK_LSHIFT           | Left Shift key
    Qt::Key_Shift,      // 161   0xA1   VK_RSHIFT           | Right Shift key
    Qt::Key_Control,    // 162   0xA2   VK_LCONTROL         | Left Ctrl key
    Qt::Key_Control,    // 163   0xA3   VK_RCONTROL         | Right Ctrl key
    Qt::Key_Alt,        // 164   0xA4   VK_LMENU            | Left Menu key
    Qt::Key_Alt,        // 165   0xA5   VK_RMENU            | Right Menu key
    Qt::Key_Back,       // 166   0xA6   VK_BROWSER_BACK     | Browser Back key
    Qt::Key_Forward,    // 167   0xA7   VK_BROWSER_FORWARD  | Browser Forward key
    Qt::Key_Refresh,    // 168   0xA8   VK_BROWSER_REFRESH  | Browser Refresh key
    Qt::Key_Stop,       // 169   0xA9   VK_BROWSER_STOP     | Browser Stop key
    Qt::Key_Search,     // 170   0xAA   VK_BROWSER_SEARCH   | Browser Search key
    Qt::Key_Favorites,  // 171   0xAB   VK_BROWSER_FAVORITES| Browser Favorites key
    Qt::Key_HomePage,   // 172   0xAC   VK_BROWSER_HOME     | Browser Start and Home key
    Qt::Key_VolumeMute, // 173   0xAD   VK_VOLUME_MUTE      | Volume Mute key
    Qt::Key_VolumeDown, // 174   0xAE   VK_VOLUME_DOWN      | Volume Down key
    Qt::Key_VolumeUp,   // 175   0xAF   VK_VOLUME_UP        | Volume Up key
    Qt::Key_MediaNext,  // 176   0xB0   VK_MEDIA_NEXT_TRACK | Next Track key
    Qt::Key_MediaPrevious, //177 0xB1   VK_MEDIA_PREV_TRACK | Previous Track key
    Qt::Key_MediaStop,  // 178   0xB2   VK_MEDIA_STOP       | Stop Media key
    Qt::Key_MediaPlay,  // 179   0xB3   VK_MEDIA_PLAY_PAUSE | Play/Pause Media key
    Qt::Key_LaunchMail, // 180   0xB4   VK_LAUNCH_MAIL      | Start Mail key
    Qt::Key_LaunchMedia,// 181   0xB5   VK_LAUNCH_MEDIA_SELECT Select Media key
    Qt::Key_Launch0,    // 182   0xB6   VK_LAUNCH_APP1      | Start Application 1 key
    Qt::Key_Launch1,    // 183   0xB7   VK_LAUNCH_APP2      | Start Application 2 key
    Qt::Key_unknown,    // 184   0xB8   -- reserved --
    Qt::Key_unknown,    // 185   0xB9   -- reserved --
    0,                  // 186   0xBA   VK_OEM_1            | ';:' for US
    0,                  // 187   0xBB   VK_OEM_PLUS         | '+' any country
    0,                  // 188   0xBC   VK_OEM_COMMA        | ',' any country
    0,                  // 189   0xBD   VK_OEM_MINUS        | '-' any country
    0,                  // 190   0xBE   VK_OEM_PERIOD       | '.' any country
    0,                  // 191   0xBF   VK_OEM_2            | '/?' for US
    0,                  // 192   0xC0   VK_OEM_3            | '`~' for US
    Qt::Key_unknown,    // 193   0xC1   -- reserved --
    Qt::Key_unknown,    // 194   0xC2   -- reserved --
    Qt::Key_unknown,    // 195   0xC3   -- reserved --
    Qt::Key_unknown,    // 196   0xC4   -- reserved --
    Qt::Key_unknown,    // 197   0xC5   -- reserved --
    Qt::Key_unknown,    // 198   0xC6   -- reserved --
    Qt::Key_unknown,    // 199   0xC7   -- reserved --
    Qt::Key_unknown,    // 200   0xC8   -- reserved --
    Qt::Key_unknown,    // 201   0xC9   -- reserved --
    Qt::Key_unknown,    // 202   0xCA   -- reserved --
    Qt::Key_unknown,    // 203   0xCB   -- reserved --
    Qt::Key_unknown,    // 204   0xCC   -- reserved --
    Qt::Key_unknown,    // 205   0xCD   -- reserved --
    Qt::Key_unknown,    // 206   0xCE   -- reserved --
    Qt::Key_unknown,    // 207   0xCF   -- reserved --
    Qt::Key_unknown,    // 208   0xD0   -- reserved --
    Qt::Key_unknown,    // 209   0xD1   -- reserved --
    Qt::Key_unknown,    // 210   0xD2   -- reserved --
    Qt::Key_unknown,    // 211   0xD3   -- reserved --
    Qt::Key_unknown,    // 212   0xD4   -- reserved --
    Qt::Key_unknown,    // 213   0xD5   -- reserved --
    Qt::Key_unknown,    // 214   0xD6   -- reserved --
    Qt::Key_unknown,    // 215   0xD7   -- reserved --
    Qt::Key_unknown,    // 216   0xD8   -- unassigned --
    Qt::Key_unknown,    // 217   0xD9   -- unassigned --
    Qt::Key_unknown,    // 218   0xDA   -- unassigned --
    0,                  // 219   0xDB   VK_OEM_4            | '[{' for US
    0,                  // 220   0xDC   VK_OEM_5            | '\|' for US
    0,                  // 221   0xDD   VK_OEM_6            | ']}' for US
    0,                  // 222   0xDE   VK_OEM_7            | ''"' for US
    0,                  // 223   0xDF   VK_OEM_8
    Qt::Key_unknown,    // 224   0xE0   -- reserved --
    Qt::Key_unknown,    // 225   0xE1   VK_OEM_AX           | 'AX' key on Japanese AX kbd
    Qt::Key_unknown,    // 226   0xE2   VK_OEM_102          | "<>" or "\|" on RT 102-key kbd
    Qt::Key_unknown,    // 227   0xE3   VK_ICO_HELP         | Help key on ICO
    Qt::Key_unknown,    // 228   0xE4   VK_ICO_00           | 00 key on ICO
    Qt::Key_unknown,    // 229   0xE5   VK_PROCESSKEY       | IME Process key
    Qt::Key_unknown,    // 230   0xE6   VK_ICO_CLEAR        |
    Qt::Key_unknown,    // 231   0xE7   VK_PACKET           | Unicode char as keystrokes
    Qt::Key_unknown,    // 232   0xE8   -- unassigned --
    // Nokia/Ericsson definitions ---------------
    Qt::Key_unknown,    // 233   0xE9   VK_OEM_RESET
    Qt::Key_unknown,    // 234   0xEA   VK_OEM_JUMP
    Qt::Key_unknown,    // 235   0xEB   VK_OEM_PA1
    Qt::Key_unknown,    // 236   0xEC   VK_OEM_PA2
    Qt::Key_unknown,    // 237   0xED   VK_OEM_PA3
    Qt::Key_unknown,    // 238   0xEE   VK_OEM_WSCTRL
    Qt::Key_unknown,    // 239   0xEF   VK_OEM_CUSEL
    Qt::Key_unknown,    // 240   0xF0   VK_OEM_ATTN
    Qt::Key_unknown,    // 241   0xF1   VK_OEM_FINISH
    Qt::Key_unknown,    // 242   0xF2   VK_OEM_COPY
    Qt::Key_unknown,    // 243   0xF3   VK_OEM_AUTO
    Qt::Key_unknown,    // 244   0xF4   VK_OEM_ENLW
    Qt::Key_unknown,    // 245   0xF5   VK_OEM_BACKTAB
    Qt::Key_unknown,    // 246   0xF6   VK_ATTN             | Attn key
    Qt::Key_unknown,    // 247   0xF7   VK_CRSEL            | CrSel key
    Qt::Key_unknown,    // 248   0xF8   VK_EXSEL            | ExSel key
    Qt::Key_unknown,    // 249   0xF9   VK_EREOF            | Erase EOF key
    Qt::Key_Play,       // 250   0xFA   VK_PLAY             | Play key
    Qt::Key_Zoom,       // 251   0xFB   VK_ZOOM             | Zoom key
    Qt::Key_unknown,    // 252   0xFC   VK_NONAME           | Reserved
    Qt::Key_unknown,    // 253   0xFD   VK_PA1              | PA1 key
    Qt::Key_Clear,      // 254   0xFE   VK_OEM_CLEAR        | Clear key
    0
};


static int m_iKeyPressed = 0;

class KeyControler
{

public:

    static bool fCtrlV( unsigned int _iVar, unsigned int _iKay);

    static int fKeyWin(unsigned int _iKey);
    static int fKeyLinux(unsigned int _iKey);
};

#endif // KEYCONTROLERH_H
