#ifndef PING_H
#define PING_H

#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QSysInfo>
#include <QProcess>

#include "StaticData.h"

class Ping : public QThread
{
    Q_OBJECT


public:
    bool m_bRun = false;
    bool m_bPing = true;


    Ping(QWidget* parent = nullptr)
    {
        m_bRun = true;
    }


private:

    void run() override {

        //qDebug() << "Ping::run(): 0";


        while (m_bRun)
        {
          //qDebug() << "Ping::run() 2:";
          fPing();
          QThread::sleep(1);
        }

        qDebug() << "Ping::run(): end";
    }

    void fPing()
    {
        //qDebug() << "Ping::fPing() 0: " << m_bPing;

        if(!m_bPing)
          return;

        m_bPing = false;

         QStringList parameters ;
         parameters << StaticData::m_sServerIP;

         #if defined(WIN32)
            parameters << "-n" << "1";
            //parameters << "-t3";
         #else
            parameters << "-c 1";
            parameters << "-w 3";
            parameters << "-q";
         #endif

        //qDebug() << "Ping::fPing() 1: " << parameters;

        //uint64_t a_iT56 = QDateTime::currentMSecsSinceEpoch();

        int exitCode = QProcess::execute("ping", parameters);
        if (exitCode==0) {

            //qDebug() << "fPing 2.1: true";
            emit signalConnectStatus(1, true);

        } else {

            emit signalConnectStatus(1, false);

            //fPingConnect();
        }

        //qDebug() << "Ping::fPing() 8: " << (QDateTime::currentMSecsSinceEpoch() - a_iT56);

    }

    bool fPingConnect()
    {
        bool a_bConnect = true;

        QStringList parameters ;
        parameters << "google.com";

        #if defined(WIN32)
                parameters << "-n" << "1";
        #else
                parameters << "-c 1";
        #endif


        int exitCode = QProcess::execute("ping", parameters);
        if (exitCode==0) {

             emit signalConnectStatus(2, true);

        } else {
             a_bConnect = false;

            emit signalConnectStatus(2, false);

        }

        return a_bConnect;
    }


public:
    signals:
    void signalConnectStatus(ushort, bool);

public slots:
  void slotStop()
  {
      qDebug() << "Ping::slotStop 0:";
      m_bRun = false;
  }

  void slotPingRun(bool _bVar)
  {
      //qDebug() << "Ping::slotPingRun 0:" << _bVar;

      m_bPing = _bVar;
  }

};

#endif // PING_H
