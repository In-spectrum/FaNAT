#include "fileWrite.h"

FileWrite::FileWrite(QString _sUserId, QObject *parent) :
    QThread(parent)
{
    //qDebug() << "FileWrite::FileWrite 0: " << _sUserId;

    m_sUserId = _sUserId;
    m_fWrite = nullptr;

    //qDebug() << "FileWrite::FileWrite 200: ";
}


void FileWrite::run()
{

    exec();

    m_sUserId = "";

    if(m_fWrite)
    {
        if(m_fWrite->isOpen())
        {
            m_fWrite->close();
        }

        delete m_fWrite;
        m_fWrite = nullptr;
    }


    //qDebug() << "FileWrite::run 200: " << " thWrite end";
}

void FileWrite::slControl(QString _sId, int _iVar, QByteArray _baIn)
{
    //qDebug() << "FileWrite::slControl 0: " << _sId << _iVar << _sData;

    if(_iVar != 0 && m_sUserId != _sId)
        return;

    switch (_iVar) {
    case 0:
        m_sUserId = "";
        exit(0);

        break;
    case 1:
    {
        if(_sId == m_sUserId)
        {
            fFileWrite(_baIn);
        }

    }
    break;
    case 2:
    {

    }
    break;
    default:
        break;
    }

}

void FileWrite::slTimer()
{
    m_mutexFileWrite.lock();

    if(m_fWrite)
    {
        m_iTimeFileWrite++;

        if(m_iTimeFileWrite > 8)
        {
            m_iTimeFileWrite = 0;

            if(m_fWrite->isOpen())
                m_fWrite->close();

            delete m_fWrite;
            m_fWrite = nullptr;

            m_sUserId = "";

            emit sgControl("2", 16, "-1", "");

            exit(0);

            //qDebug() << "FileWrite::slTimer 3.2: " << "close FileWrite.";
        }

    }

    m_mutexFileWrite.unlock();
}

void FileWrite::fFileWrite(QByteArray _baIn)
{
    m_mutexFileWrite.lock();

    m_iTimeFileWrite = 0;

    //qDebug() << "FileWrite::fFileWrite 0: " << _baIn.length() << _baIn.toHex(':') << "--------------------------";

    //qDebug() << "FileWrite::fSendFile 0: " << _baIn.length() << _baIn.toHex(':');

    if(_baIn.length() < 4)
        return;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "FileWrite::fSendFile 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "FileWrite::fSendFile 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "FileWrite::fSendFile 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "FileWrite::fSendFile 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return;

    int a_iData_5 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos - 1 ) );

    //qDebug() << "FileWrite::fSendFile 2.3: " << a_iData_4;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos + 1)
        return;

    int a_iData_6 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos - 1 ) );

    bool a_bOk;
    a_iData_6 = _baIn.mid(3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos - 1, 4).toHex().toUInt(&a_bOk, 16);

    //qDebug() << "FileWrite::fSendFile 2.3: " << a_iData_4;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3 + 1)
        return;




//    qDebug() << "FileWrite::fSendFile 2.3: "
//             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos)
//                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos + 3 + 1 )) )
        return;

   // qDebug() << "FileWrite::fSendFile 3: ";

    QByteArray a_baForId;
    a_iPlasPos = 0;

    for(int i = 3; i < 3 + a_iData_1 + a_iPlasPos; i++)
    {
        a_baForId.append(_baIn[i]);
    }

    QByteArray a_baFromId;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iPlasPos; i++)
    {
        a_baFromId.append(_baIn[i]);
    }


    //FilePath

    QByteArray a_baFilePath;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i++)
    {
        a_baFilePath.append(_baIn[i]);
    }

    //FileSize

    QByteArray a_baFileSize;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos; i++)
    {
        a_baFileSize.append(_baIn[i]);
    }



    //Poss

    QByteArray a_baPoss;
    a_iPlasPos++;

    for(int i = 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos;
            i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos;
        i++)
    {
        a_baPoss.append(_baIn[i]);
    }

    //Data

    QByteArray a_baData;
    a_iPlasPos += 4;

    for(int i = 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iPlasPos;
            i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iData_5 + a_iData_6 + a_iPlasPos;
        i++)
    {
        a_baData.append(_baIn[i]);
    }

    //////


    //////////////////
    bool m_bOk;
    unsigned int a_iPoss = a_baPoss.toHex().toUInt(&m_bOk, 16);
    unsigned int a_iFileSize = a_baFileSize.toHex().toUInt(&m_bOk, 16);

//    qDebug() << "FileWrite::fFileWrite 6.1: " << a_baPoss.toHex(':') << a_iPoss;
//    qDebug() << "FileWrite::fFileWrite 6.2: " << a_baFileSize.toHex(':') << a_iFileSize;

    if( QString::fromStdString(a_baFilePath.toStdString()) == "stopCopy" )
    {
        //qDebug() << "FileWrite::fFileWrite 7: " << m_fWrite->fileName() << QString::fromStdString(a_baFilePath.toStdString());

        m_iTimeFileWrite = 10;

        emit sgControl("2", 16, "0", "" );
    }
    else
    if(a_iFileSize == 0 && a_baData.length() == 0)
    {
        emit sgControl("0", 16, "-1", "");
        exit(0);
    }
    else
    {

        if(m_fWrite)
        {
            if(!m_fWrite->isOpen())
            {
                delete m_fWrite;
                m_fWrite = nullptr;

                m_iTimeFileWrite = 0;
            }
        }

        if(!m_fWrite)
        {
            QStringList a_saT = QString::fromStdString(a_baFilePath.toStdString()).split('/');

            if(a_saT.length() < 2)
                a_saT = QString::fromStdString(a_baFilePath.toStdString()).split("\\");

            //qDebug() << "FileWrite::fFileWrite 5.0: " << a_saT.length() << a_saT;

            if(a_saT.length() >= 2)
            {
                m_fWrite = new QFile( StaticData::m_sPathData + "/" + a_saT.at(a_saT.length() - 1) );

                if (!m_fWrite->open(QIODevice::WriteOnly))
                {
                    //qDebug() << "FileWrite::fFileWrite 5.1: " << "can't open: " << m_fWrite->fileName();

                    emit sgControl("4", 16, "-1", ("can't write:\n" + m_fWrite->fileName()).toUtf8() );
                }
            }
            else
            {
                emit sgControl("4", 16, "-1", ("bad path:\n" + QString::fromStdString(a_baFilePath.toStdString()).toUtf8() ) );
                //qDebug() << "FileWrite::fFileWrite 5.2: " << "bad path: " << QString::fromStdString(a_baFilePath.toStdString());
            }

        }

        if(m_fWrite->isOpen())
        {
            m_iTimeFileWrite = 0;

            qint64 a_iWr = m_fWrite->write(a_baData);

            emit sgControl("1", 16, QString::number((100.*(a_iWr + a_iPoss)/a_iFileSize), 'f', 2), "" );

            if(a_iWr + a_iPoss >= a_iFileSize)
            {
                m_sUserId = "";

                //qDebug() << "FileWrite::fFileWrite 7.0: " << "write all file" << QString::fromStdString(a_baFilePath.toStdString());

                m_fWrite->close();
                delete m_fWrite;
                m_fWrite = nullptr;

                emit sgControl("3", 16, "0", "" );

                exit(0);
            }
            else
            {
//                qDebug() << "FileWrite::fFileWrite 7.1: " << "file"
//                         << QString::fromStdString(a_baFilePath.toStdString())
//                         << "writed " << a_baPoss.toHex().toUInt(&m_bOk, 16) << "Bt.";

                emit sgControl("1", 16, "-1"
                               ,  MyProtocol::fGetFile( QString::fromStdString(a_baFromId.toStdString())
                                                        , QString::fromStdString(a_baForId.toStdString())
                                                        , QString::fromStdString(a_baFilePath.toStdString())
                                                        , a_iWr + a_iPoss )
                               );
            }

        }
    }



   m_mutexFileWrite.unlock();
}
