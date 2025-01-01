#include <QApplication>
#include <csignal>
#include "control.h"

#include <iostream>

static void sigHandler(int s)
{
    //qDebug() << "sigHandler 0: " << s;
    std::signal(s, SIG_DFL);
    qApp->quit();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << StaticData::m_sNameApp << StaticData::m_sVersion;
    std::cout << StaticData::m_sSupport.toStdString() << std::endl;

    std::signal(SIGINT,  sigHandler);
    std::signal(SIGTERM, sigHandler);

    QStringList a_Ar;
    a_Ar.append( a.arguments() );

    // a_Ar.append("-ds");
    // a_Ar.append("1");

    // a_Ar.append("-kds");
    // a_Ar.append("xxxxxxxx45");

    // a_Ar.append("-spas");
    // a_Ar.append("22227");

    // a_Ar.append("-sip");
    // a_Ar.append("156.34.212.11");

    // a_Ar.append("-ptcp");
    // a_Ar.append("1237");

    // a_Ar.append("-prtsp");
    // a_Ar.append("8504");

    // a_Ar.append("-prtmp");
    // a_Ar.append("1935");

    // a_Ar.append("-log");
    // a_Ar.append("nico");

    // a_Ar.append("-pas");
    // a_Ar.append("1242");

    Control m_pC( a_Ar );

    //    char a_cTemp;

    //    while (true)
    //    {
    //        std::cin >> a_cTemp;
    //        std::cout << a_cTemp << endl;
    //    }


    return a.exec();
}
