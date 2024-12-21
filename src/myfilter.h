#ifndef MYFILTER_H
#define MYFILTER_H


#include <QObject>
#include <QAbstractVideoFilter>
#include <QVideoFilterRunnable>
#include <QDebug>

#include "StaticData.h"

class MyFilter : public QAbstractVideoFilter
{
    Q_OBJECT
    Q_PROPERTY(int frameNum READ frameRead WRITE frameWrite NOTIFY frameNumChanged)

public:
    MyFilter( QObject* parent = nullptr );
    QVideoFilterRunnable* createFilterRunnable() Q_DECL_OVERRIDE;

    int frameRead() const;
    void frameWrite(const int _iVar);

signals:
    void frameNumChanged();


private:
    int m_iFrameNum = 0;

};

class MyFilterRunnable : public QVideoFilterRunnable
{
public:
    MyFilterRunnable( MyFilter* filter );
    QVideoFrame run( QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags ) Q_DECL_OVERRIDE;

protected:
    MyFilter* m_Filter;

};

#endif // MYFILTER_H
