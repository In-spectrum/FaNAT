#include "myfilter.h"

MyFilter::MyFilter( QObject* parent )
    : QAbstractVideoFilter( parent )
{
}

QVideoFilterRunnable* MyFilter::createFilterRunnable()
{
    return new MyFilterRunnable( this );
}

int MyFilter::frameRead() const
{
    return m_iFrameNum;
}

void MyFilter::frameWrite(const int _iVar)
{
    if(_iVar == m_iFrameNum)
        return;

    m_iFrameNum = _iVar;
    emit frameNumChanged();
}

MyFilterRunnable::MyFilterRunnable( MyFilter* filter ) :
    m_Filter( filter )
{
}



QVideoFrame MyFilterRunnable::run( QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags )
{
    Q_UNUSED( flags )

    if ( !input )
    {
        return QVideoFrame();
    }

    StaticData::m_iTimeForStream = 0;


    if(m_Filter->frameRead() + 1 > 100)
        m_Filter->frameWrite( 1 );
    else
        m_Filter->frameWrite( m_Filter->frameRead() + 1);


    //qDebug() << "MyFilterRunnable::run 1: " << m_Filter->frameRead();



    return *input;
}

