QT += quick gui multimedia core
equals(QT_MAJOR_VERSION, 6){
    message("qt6.1 v:" $$QT_MAJOR_VERSION)
    QT += core5compat
}


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += c++1z

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

RESOURCES += \
    image.qrc

equals(QT_MAJOR_VERSION, 6){
    message("qt6.2 v:" $$QT_MAJOR_VERSION)

    RESOURCES += \
        qml6.qrc
}

equals(QT_MAJOR_VERSION, 5){
   message("qt5 v:" $$QT_MAJOR_VERSION)


    RESOURCES += \
        qml5.qrc

    HEADERS += \
       myfilter.h

    SOURCES += \
       myfilter.cpp
}


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = \tmp/$${TARGET}/bin
else: unix:!android: target.path = \opt/$${TARGET}/bin
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
    ping.h \
    settingsapp.h


unix:!macx:{


}

unix:!android:{

     HEADERS += \
        KeyControler.h

    SOURCES += \
        KeyControler.cpp

    LIBS += -lXtst -lX11
}


win32{

    HEADERS += \
       KeyControler.h

    SOURCES += \
       KeyControler.cpp

   LIBS += -luser32
}
