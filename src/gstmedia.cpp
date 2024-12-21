#include "gstmedia.h"

static gstMediaSource *m_pObGst = nullptr;

static QMutex m_mutexGst;

static GstFlowReturn new_preroll(GstAppSink *appsink, gpointer data)
{
    //qDebug() << "GST::new_preroll 0: ";

    g_print ("Got preroll!\n");
    //    gst_app_sink_pull_preroll(appsink);

    return GST_FLOW_OK;
}

static GstFlowReturn new_sample(GstAppSink *appsink, gstMediaSource *_pOb)
{
    //qDebug() << "GST::new_sample 0: ";

    //g_print("%s:%d\n",__FUNCTION__,__LINE__);

    if(_pOb == nullptr)
        return GST_FLOW_ERROR;


    GstSample *sample = gst_app_sink_pull_sample(appsink);
    GstCaps *caps = gst_sample_get_caps(sample);
    GstBuffer *buffer = gst_sample_get_buffer(sample);
    static GstStructure *s;
    const GstStructure *info = gst_sample_get_info(sample);
    if(_pOb->g_framecount_1==0)
    {
        g_print ("%s\n", gst_caps_to_string(caps));
        if(!caps)
        {
            g_print("Could not get image info from filter caps");
            return GST_FLOW_CUSTOM_ERROR_1;
        }

        s = gst_caps_get_structure(caps,0);
        gboolean res = gst_structure_get_int(s, "width", &_pOb->width_1);
        res |= gst_structure_get_int(s, "height", &_pOb->height_1);
        if(!res)
        {
            g_print("Could not get image width and height from filter caps");
            return GST_FLOW_CUSTOM_ERROR_2;
        }
        g_print("Image size: %d\t%d\n", _pOb->width_1, _pOb->height_1);
    }

    _pOb->g_framecount_1++;

    if(_pOb->g_framecount_1 > 10000)
        _pOb->g_framecount_1 = 0;

    GstMapInfo map;
    gst_buffer_map (buffer, &map, GST_MAP_READ);
    //    g_print("%s:%d\t%p %dx%d\n",__FUNCTION__,__LINE__,map.data,width,height);

    if(_pOb != nullptr)
    {
        _pOb->fFrameUpdate(map.data);
    }

    gst_buffer_unmap(buffer, &map);

    gst_sample_unref (sample);



    //qDebug() << "GST::new_sample 11: ";


    return GST_FLOW_OK;
}


static gboolean my_bus_callback (GstBus *bus, GstMessage *message, gpointer data)
{
    //qDebug() << "GST::my_bus_callback 0: ";

    //g_print ("Got %s message from %s\n", GST_MESSAGE_TYPE_NAME (message), GST_OBJECT_NAME (message->src));
    switch (GST_MESSAGE_TYPE (message))
    {
    case GST_MESSAGE_ERROR:
    {
        GError *err;
        gchar *debug;

        gst_message_parse_error (message, &err, &debug);

        QString e1( GST_OBJECT_NAME (message->src) );
        QString e2( err->message );

        g_print ("my_bus_callback 0: Error from %s: %s\n", GST_OBJECT_NAME (message->src), err->message);
        g_error_free (err);
        g_free (debug);

        m_mutexGst.lock();

        if(m_pObGst)
        {
            emit   m_pObGst->sgStatus(1, "Error from " + e1 + ": " + e2);

            //g_print ("my_bus_callback 1: Error from %s: %s\n", GST_OBJECT_NAME (message->src), err->message);

        }

        m_mutexGst.unlock();
    }
    break;
    case GST_MESSAGE_EOS:
    {
        gstMediaSource *self = static_cast<gstMediaSource*>(data);
        if(self){
            self->endOfStream();
        }
    }
    //quit_flag = 1;
    break;
    case GST_MESSAGE_STATE_CHANGED:
        GstState oldstate, newstate;
        gst_message_parse_state_changed(message, &oldstate, &newstate, NULL);
        //        g_print ("Element %s changed state from %s to %s.\n",
        //                 GST_OBJECT_NAME (message->src),
        //                 gst_element_state_get_name (oldstate),
        //                 gst_element_state_get_name (newstate));
        break;
    default:
        /* unhandled message */
        break;
    }

    return TRUE;
}


gstMediaSource::gstMediaSource(QObject *parent, bool _Reader) : QObject(parent),
    status(GST_STATE_NULL),pipeline(NULL),appsink(NULL)
{
    m_dStopRead = false;
    m_bReader = _Reader;

    m_mutexGst.lock();

    // if(m_sMess == nullptr)
    //     m_sMess = new myMessageT();

    // connect(m_sMess, SIGNAL( sgStatus(int, QString)), this, SIGNAL(sgStatus(int, QString))); //, Qt::QueuedConnection);


   // connect(m_sMess, &myMessage::sgStatus ,this,&gstMediaSource::sgStatus);


    if(!m_bReader)
        m_pObGst = this;
    else
        imageProvider = new myImageProvider();

    g_framecount_1 = width_1 = height_1 = 0;

    m_mutexGst.unlock();
}

gstMediaSource::~gstMediaSource()
{
    slStop();

    int a_iSl = 0;

    while (!m_dDestroy) {

        qDebug() << "gstMediaSource::~gstMediaSource 2: ";

        QThread::sleep(1);

        // a_iSl++;

        // if(m_dStop && a_iSl > 5)
        //     break;
    }

//    if(m_dStopRead && imageProvider)
//    {

//        QThread::sleep(1);
//        delete imageProvider;
//        imageProvider = nullptr;
//    }


    qDebug() << "gstMediaSource::~gstMediaSource 10: ";
}

int gstMediaSource::init(QString cmd, int argc, char *argv[])
{
    m_bInit = false;

    GError *error = NULL;
    bool ans = false;

    if(!StaticData::m_bInitGST)
        ans = gst_init_check(&argc, &argv,&error);

    if(StaticData::m_bInitGST || ans){
        g_print("GST::init 1: initing GStreamer version: %s\n",gst_version_string());
        // g_print("%s\n", cv::getBuildInformation().c_str());


        if(!StaticData::m_bInitGST)
            gst_init (&argc, &argv);

        StaticData::m_bInitGST = true;

        pipeline = gst_parse_launch (qPrintable(cmd), &error);
        if (error)
        {
            QString s(error->message);

            g_print ("could not construct pipeline: %s\n", error->message );
            g_error_free (error);

            emit sgStatus(1, "Could not construct pipeline: " + s );

            return 2;
        }
        else
        {

            if( m_bReader )
                appsink  = GST_APP_SINK(gst_bin_get_by_name (GST_BIN (pipeline), "sink"));


            GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PAUSED);
            switch(ret)
            {
            case GST_STATE_CHANGE_FAILURE:
                g_print ("failed to play the file\n");
            case GST_STATE_CHANGE_NO_PREROLL:
                g_print ("live source detected\n");
                //                    live_flag = 1;


                loop = g_main_loop_new (NULL, FALSE);

                break;
            default:
                break;
            }

            if( m_bReader )
            {
                gst_app_sink_set_emit_signals(appsink, true);
                gst_app_sink_set_drop(appsink, true);
                gst_app_sink_set_max_buffers(appsink, 1);
                GstAppSinkCallbacks callbacks = { NULL, new_preroll, NULL };
                gst_app_sink_set_callbacks (appsink, &callbacks, this,NULL);

                g_signal_connect (appsink, "new-sample", (GCallback) new_sample, this);
            }



            GstBus *bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));

            guint bus_watch_id = gst_bus_add_watch (bus, my_bus_callback, loop);

            gst_object_unref (bus);

        }

    }
    else
    {
        g_print ("could not init GSteamer: %s\n", error->message);
        g_error_free (error);

        QString s = "Could not init GSteamer: ";
        s += error->message;
        emit sgStatus(1, s );

        return 1;
    }

    m_bInit = true;

    return 0;
}

void gstMediaSource::run()
{
    if(!m_bInit)
    {
        return;
    }

    //qDebug() << "GST::run 0: ";



    if(pipeline){
        if(status == GST_STATE_NULL){
            g_print ("GST::run 1: running!\n");
            status = GST_STATE_PLAYING;

            emit sgStatus(2, "GST::run 1: running: " );

        } else if(status == GST_STATE_PLAYING){
            g_print ("GST::run 2: pausing!\n");
            status = GST_STATE_NULL;
        }

        gst_element_set_state (pipeline, status);


        if(loop)
            g_main_loop_run (loop);


    }


}

int gstMediaSource::deInit()
{
    qDebug() << "GST::deInit 0: ";

    if(pipeline){



        int ret = fGet_state();

        // switch(ret)
        // {
        // case GST_STATE_VOID_PENDING:
        //     break;
        // case GST_STATE_NULL:
        //     break;
        // case GST_STATE_READY:
        //     break;
        // case GST_STATE_PAUSED:
        //     break;
        // case GST_STATE_PLAYING:
        //     break;
        // default:
        //     break;
        // }

//        qDebug() << "GST::deInit 1.3.0: ";

//        gst_element_set_state (pipeline, GST_STATE_PAUSED);

//         qDebug() << "GST::deInit 1.3.1: ";

//        QThread::msleep(1);


        qDebug() << "GST::deInit 1.3.2: ";
        gst_element_set_state (pipeline, GST_STATE_NULL);


        qDebug() << "GST::deInit 1.3.3: ";
        gst_object_unref (pipeline);
        qDebug() << "GST::deInit 1.4: ";

        pipeline = nullptr;

        if(loop)
        {
            //qDebug() << "GST::deInit 1.0: ";

            g_main_loop_quit(loop);
            //qDebug() << "GST::deInit 1.1: ";
            g_main_loop_unref (loop);
            //qDebug() << "GST::deInit 1.2: ";

            loop = NULL;
        }

        //qDebug() << "GST::deInit pipeline OK.";
    }

    if(appsink)
    {
        gst_object_unref (appsink);
        appsink = nullptr;
    }

    qDebug() << "GST::deInit OK.";

    return 0;
}

int gstMediaSource::fGet_state(){

    GstState cur_state;
    GstStateChangeReturn state_change;

    int a_iStop = 0;

    do {

        /* 10 ms timeout. */
        state_change = gst_element_get_state(pipeline, &cur_state,
                                             NULL, 10000000);

        // qDebug() << "GST::fGet_state 1: " << state_change;

        // switch(cur_state)
        // {
        // case GST_STATE_VOID_PENDING:
        //      qDebug() << "GST::fGet_state 2.0: " << "GST_STATE_VOID_PENDING: no pending state";
        //     break;
        // case GST_STATE_NULL:
        //      qDebug() << "GST::fGet_state 2.1: " << "GST_STATE_NULL: the NULL state or initial state of an element";
        //     break;
        // case GST_STATE_READY:
        //      qDebug() << "GST::fGet_state 2.2: " << "GST_STATE_READY: the element is ready to go to PAUSED";
        //     break;
        // case GST_STATE_PAUSED:
        //      qDebug() << "GST::fGet_state 2.3: " << "GST_STATE_PAUSED: the element is PAUSED, it is ready to accept and process data. Sink elements however only accept one buffer and then block.";
        //     break;
        // case GST_STATE_PLAYING:
        //      qDebug() << "GST::fGet_state 2.4: " << "GST_STATE_PLAYING: the element is PLAYING, the GstClock is running and the data is flowing.";
        //     break;
        // default:
        //     break;
        // }



        if(state_change == GST_STATE_CHANGE_ASYNC)
            QThread::sleep(1);

        a_iStop++;

    } while ( state_change == GST_STATE_CHANGE_ASYNC && a_iStop < 4 );

    /* Translate away from GST types. */
    return (int) cur_state;

}

void gstMediaSource::endOfStream()
{
    //qDebug() << "GST::endOfStream 0: ";

    if(pipeline){
        g_print ("%s:over!\n",__FUNCTION__);
    }
}


void gstMediaSource::slStop()
{
    //qDebug() << "gstMediaSource::slStop 0: ";

    m_dStopRead = true;

    deInit();

    //qDebug() << "gstMediaSource::slStop 1.1: ";

    m_dDestroy = true;

    if(!m_bReader && m_pObGst)
        m_pObGst = nullptr;

    //qDebug() << "gstMediaSource::slStop 5: ";
}

void gstMediaSource::fFrameUpdate(const uchar *data)
{
    if(imageProvider && !m_dStopRead)
    {
        imageProvider->img =
            QPixmap::fromImage(QImage(data, width_1, height_1, QImage::Format_RGBA8888));

        emit signalUpdate(g_framecount_1, width_1, height_1);

        //qDebug() << "gstMediaSource::fFrameUpdate 5:" << g_framecount_1;
    }
}
