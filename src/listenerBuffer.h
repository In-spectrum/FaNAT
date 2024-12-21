#ifndef LISTENERBUFFER_H
#define LISTENERBUFFER_H

#include <QThread>
#include <QDebug>

class ListenerBuffer : public QThread
{
    Q_OBJECT


public:
    bool m_bRun = false;


    ListenerBuffer(QObject* parent = nullptr)
    {
        m_bRun = true;
    }


private:

    void run() override {

        //qDebug() << "ListenerBuffer::run(): 0";


        while (m_bRun)
        {
          //qDebug() << "ListenerBuffer::run() 2:";
          fListenerBuffer();
          QThread::sleep(1);
        }

        //qDebug() << "ListenerBuffer::run(): end";
    }

    void fListenerBuffer()
    {
        //qDebug() << "ListenerBuffer::fListenerBuffer() 0: ";

        emit sgBufferData();
    }

signals:
    void sgBufferData();

public slots:
  void slStop()
  {
      //qDebug() << "ListenerBuffer::slotStop 0:";
      m_bRun = false;
  }

};

#endif // LISTENERBUFFER_H
