#ifndef GSTMEDIA_H
#define GSTMEDIA_H

#include <QImage>
#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QQuickImageProvider>
#include <QDateTime>

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <QDebug>
#include <QThread>
#include <QMutex>

#include "StaticData.h"

class myMessageT : public QObject
{
    Q_OBJECT
public:
    explicit myMessageT(QObject *p = nullptr)
    {

    }


signals:
    void sgStatus(int, QString);
};


static myMessageT *m_sMess = nullptr;

// myMessageT::myMessageT(QObject *parent) : QObject(parent)
// {

// }


class myImageProvider : public QQuickImageProvider
{
public:
    myImageProvider():QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
        a_sPath.clear();
        m_bPhoto = false;

    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){


        if(!a_sPath.isEmpty())
        {
            QPainter painter;
            painter.begin(&img);
            painter.setPen(QPen( Qt::red, 2 ));
            painter.drawLine(img.width()/2 - img.width()/50, img.height()/2, img.width()/2 + img.width()/50, img.height()/2);
            painter.drawLine(img.width()/2, img.height()/2 - img.width()/50, img.width()/2, img.height()/2 + img.width()/50);
            painter.end();

            img.save( a_sPath );

            a_sPath.clear();

            m_bPhoto = false;
        }
        else
        {
            if(m_bPhoto)
            {
                QDateTime cur_time=QDateTime::currentDateTime();
                QString name_file= ""
                                    //+ "path"
                                    + QLatin1String("/")+cur_time.toString(QLatin1String("dd_MM_yyyy"))
                                    + QLatin1String("_")+cur_time.toString(QLatin1String("hh:mm:ss_0"))
                                    + QLatin1String(".jpeg");

                QPainter painter;
                painter.begin(&img);
                painter.setPen(QPen( Qt::red, 2 ));
                painter.drawLine(img.width()/2 - img.width()/50, img.height()/2, img.width()/2 + img.width()/50, img.height()/2);
                painter.drawLine(img.width()/2, img.height()/2 - img.width()/50, img.width()/2, img.height()/2 + img.width()/50);
                painter.end();


                img.save( a_sPath );

                a_sPath.clear();

                m_bPhoto = false;
            }
        }


        return img;
    }

    QPixmap img;
    bool m_bPhoto;
    QString a_sPath;
};



class gstMediaSource : public QObject
{
    Q_OBJECT
public:
    explicit gstMediaSource(QObject *parent = nullptr, bool _Reader = true);
    ~gstMediaSource();
    int init(QString cmd, int argc, char *argv[]);

    int deInit();
    int fGet_state();

    myImageProvider *imageProvider;
signals:
    void signalFinished();
    void sgStatus(int, QString);
    void signalUpdate(int, int _iWf, int _iHf);

public slots:
    void endOfStream();
    void slStop();
    void run();


private:
    GMainLoop *loop = NULL;
    GstState status;
    GstElement *pipeline;
    GstAppSink *appsink;
    bool m_bInit = false;
    bool m_dDestroy = false;
    bool m_dStopRead = false;


public:    
    int g_framecount_1;
    int width_1, height_1 ;
    bool m_bReader = true;

    void fFrameUpdate(const uchar *data);

};

#endif // GSTMEDIA_H
