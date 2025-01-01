QT = core widgets network
equals(QT_MAJOR_VERSION, 6){
    message("qt6.1 v:" $$QT_MAJOR_VERSION)
    QT += core5compat
}

CONFIG += c++17 cmdline


SOURCES += \
        MyProtocol.cpp \
        ComandLine.cpp \
        control.cpp \
        fileRead.cpp \
        fileWrite.cpp \
        main.cpp \
        newclient.cpp \
        parsersocketdata.cpp \
        settingsapp.cpp


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    MyProtocol.h \
    ComandLine.h \
    StaticData.h \
    control.h \
    fileRead.h \
    fileWrite.h \
    newclient.h \
    parsersocketdata.h \
    settingsapp.h


unix:!macx:{

    LIBS += -L/usr/local/lib

}

win32{

   LIBS += -luser32
}

