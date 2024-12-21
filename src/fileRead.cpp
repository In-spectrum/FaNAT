#include "fileRead.h"

FileRead::FileRead(QString _sUserId, QObject *parent) :
    QThread(parent)
{
    //qDebug() << "FileRead::FileRead 0: " << _sUserId;

    m_sUserId = _sUserId;
    m_fRead = nullptr;

    //qDebug() << "FileRead::FileRead 200: ";
}


void FileRead::run()
{

    exec();

    if(m_fRead)
    {
        if(m_fRead->isOpen())
        {
            m_fRead->close();
        }

        delete m_fRead;
        m_fRead = nullptr;
    }


    //qDebug() << "FileRead::run 200: " << " thread end";
}

void FileRead::slControl(QString _sId, int _iVar, QByteArray _baIn)
{
    //qDebug() << "FileRead::slControl 0: " << _sId << _iVar << _sData;

    switch (_iVar) {
    case 0:
        m_sUserId = "";
        exit(0);

        break;
    case 1:
    {
        if(_sId == m_sUserId)
        {
            fFileRead(_baIn);
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

void FileRead::slTimer()
{
    m_mutexFileRead.lock();

    if(m_fRead)
    {
        m_iTimeFileRead++;

        if(m_iTimeFileRead > 8)
        {
            m_iTimeFileRead = 0;

            if(m_fRead->isOpen())
                m_fRead->close();

            delete m_fRead;
            m_fRead = nullptr;

            m_sUserId = "";
            exit(0);

            //qDebug() << "FileRead::slTimer 3.2: " << "close fileRead.";
        }

    }

    m_mutexFileRead.unlock();
}

void FileRead::fFileRead(QByteArray _baIn)
{
    m_mutexFileRead.lock();

    //qDebug() << "FileRead::fFileRead 0: " << _baIn.length() << _baIn.toHex(':') << "--------------------------";

    if(_baIn.length() < 4)
        return;

    int a_iPlasPos = 0;

    int a_iData_1 = static_cast<quint8>( _baIn.at(2) ); //SZ-1

    //qDebug() << "FileRead::fFileRead 2.0: " << a_iData_1;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iPlasPos + 1)
        return;

    int a_iData_2 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iPlasPos - 1) );

    //qDebug() << "FileRead::fFileRead 2.1: " << a_iData_2;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iPlasPos + 1)
        return;

    int a_iData_3 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iPlasPos - 1 ) );

    //qDebug() << "FileRead::fFileRead 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos + 1)
        return;

    int a_iData_4 = static_cast<quint8>( _baIn.at( 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos - 1 ) );

    //qDebug() << "FileRead::fFileRead 2.2: " << a_iData_3;

    a_iPlasPos++;
    if(_baIn.length() < 2 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1)
        return;

//    qDebug() << "FileRead::fFileRead 2.3: "
//             <<  MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
//                                       , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 ));


    if( !MyProtocol::fCRC_isOk(_baIn.mid(1,  1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos)
                               , _baIn.at( 1 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos + 1 )) )
        return;


    //qDebug() << "FileRead::fFileRead 3: ";

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

    //Poss

    QByteArray a_baPoss;
    a_iPlasPos++;

    for(int i =  3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iPlasPos; i < 3 + a_iData_1 + a_iData_2 + a_iData_3 + a_iData_4 + a_iPlasPos; i++)
    {
        a_baPoss.append(_baIn[i]);
    }


    //////////////////
    bool m_bOk;
    //qDebug() << "FileRead::fFileRead 4: " << QString::fromStdString(a_baFilePath.toStdString()) << a_baPoss.toHex().toUInt(&m_bOk, 16);

    if(QString::fromStdString(a_baFilePath.toStdString()) == "stopCopy" )
    {
        emit sgControl("2", 11, "0",
                       MyProtocol::fSendFile( QString::fromStdString(a_baFromId.toStdString())
                                               , QString::fromStdString(a_baForId.toStdString())
                                               , "stopCopy"
                                               , 0
                                               , 0
                                               , "") );

        m_mutexFileRead.unlock();

        m_sUserId = "";
        exit(0);

        return;
    }

    if(m_fRead)
    {
        if(!m_fRead->isOpen())
        {
            delete m_fRead;
            m_fRead = nullptr;

            m_iTimeFileRead = 0;
        }
    }


    if(!m_fRead)
    {
        m_fRead = new QFile( QString::fromStdString(a_baFilePath.toStdString()) );

        if(!m_fRead->exists())
        {
            //qDebug() << "FileRead::fFileRead 5.0: " << "filed file" << m_fRead->fileName();

            emit sgControl("0", 11, "-1",
                           MyProtocol::fSendFile( QString::fromStdString(a_baFromId.toStdString())
                                                   , QString::fromStdString(a_baForId.toStdString())
                                                   , QString::fromStdString(a_baFilePath.toStdString())
                                                   , 0
                                                   , 0
                                                   , "") );

            m_sUserId = "";
            exit(0);
        }
        else
        {
            if (!m_fRead->open(QIODevice::ReadOnly))
            {
                //qDebug() << "FileRead::fFileRead 5.1: " << "can't open " << m_fRead->fileName();
            }
            else
            {
                m_iFileSize = m_fRead->size();
                // qDebug() << "FileRead::fFileRead 5.1: " << "file " << m_fRead->fileName() << m_iFileSize;
            }
        }


    }

    if(m_fRead && m_fRead->isOpen())
    {
        QByteArray a_baFileData;
        char a_ch;
        bool a_bOk;
        unsigned int a_iPoss = a_baPoss.toHex().toUInt(&a_bOk, 16);
        unsigned int a_iFileRead = 0;

        m_iTimeFileRead = 0;        

        m_fRead->seek( a_iPoss );

        for(unsigned int i = a_iPoss; i < m_iFileSize; i++ )
        {
             m_fRead->read(&a_ch, sizeof(char));

             a_baFileData.append(a_ch);

             a_iFileRead++;

             if(a_iFileRead == 100 * 256)
                 break;
        }



        if(a_baFileData.length())
        {
            //qDebug() << "FileRead::fFileRead 7: " << (a_iPoss + a_iFileRead)  << a_iFileRead;


            if(a_iPoss + a_iFileRead >= m_iFileSize)
            {
                emit sgControl("1", 11, "100",
                               MyProtocol::fSendFile( QString::fromStdString(a_baFromId.toStdString())
                                                       , QString::fromStdString(a_baForId.toStdString())
                                                       , QString::fromStdString(a_baFilePath.toStdString())
                                                       , m_iFileSize
                                                       , a_iPoss// + a_iFileRead
                                                       , a_baFileData) );


            }
            else
            {
                emit sgControl("1", 11, QString::number((100.*a_iPoss/m_iFileSize), 'f', 2),
                               MyProtocol::fSendFile( QString::fromStdString(a_baFromId.toStdString())
                                                       , QString::fromStdString(a_baForId.toStdString())
                                                       , QString::fromStdString(a_baFilePath.toStdString())
                                                       , m_iFileSize
                                                       , a_iPoss// + a_iFileRead
                                                       , a_baFileData) );
            }
        }

        if(a_iPoss + a_iFileRead >= m_iFileSize)
        {
            //qDebug() << "FileRead::fFileRead 6: " << "readed all file" << m_fRead->fileName();

            m_fRead->close();
            delete m_fRead;
            m_fRead = nullptr;

            emit sgControl("3", 11, "0", "" );

            m_sUserId = "";
            exit(0);
        }
    }


   m_mutexFileRead.unlock();
}
