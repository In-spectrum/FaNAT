#include "ComandLine.h"

ComandLine::ComandLine(QString _sUserId, int _iVar, QObject *parent) :
    QThread(parent)
{
    //qDebug() << "ComandLine::ComandLine 0: ";

    m_sUserId = _sUserId;
    m_iVar = _iVar;
    process = nullptr;
    qRegisterMetaType<QProcess::ProcessError>("QProcess::ProcessError");
}

void ComandLine::run()
{
    //qDebug() << "ComandLine::run 0: ";

    m_bRun = true;
    process = nullptr;

    //slControl(1, (("$ping -n 10 ") + StaticData::m_sServerIP ).toUtf8() );

    while (m_bRun) {

        if(!m_blData.isEmpty())
        {
            fParser(QString::fromStdString(m_blData.at(0).toStdString()));

            m_blData.removeFirst();

            m_iTimeStop = 0;
        }

        QThread::sleep(1);

        if(process)
        {
            m_iTimeStop++;

            if(m_iTimeStop > 8)
            {
                slStop();
                //qDebug() << "ComandLine::run 3.2: " << "close.";
            }

        }
    }

    //exec();


    fProgressStop();

    //qDebug() << "ComandLine::run 200: " << m_sUserId << " thread end";
}

void ComandLine::slStop()
{
    //qDebug() << "ComandLine::slStop 0: ";
    m_bRun = false;

    //exit(0);
}


void ComandLine::slControl(QString _sId, int _iVar, QByteArray _baIn)
{
    //qDebug() << "ComandLine::slControl 0: " << _iVar << _baIn.toHex(':') << QString::fromStdString(_baIn.toStdString());

    if(_iVar != 0 && m_sUserId != _sId)
        return;

    switch (_iVar) {
    case 0:
        m_sUserId = "";
        fProgressStop();
        slStop();
        break;
    case 1:
        m_blData.append(_baIn);
        break;
    case 2:
        m_sUserId = "";
        fProgressStop();
        slStop();
        break;
    default:
        break;
    }

}

void ComandLine::fParser(QString _sIn)
{
    //qDebug() << "ComandLine::fParser 0: " << _sIn;

    if(_sIn == "stopRun")
    {
        fProgressStop();

        return;
    }

    _sIn = _sIn.replace("      ", " ");
    _sIn = _sIn.replace("     ", " ");
    _sIn = _sIn.replace("    ", " ");
    _sIn = _sIn.replace("   ", " ");
    _sIn = _sIn.replace("  ", " ");


    QStringList a_sData = _sIn.split(' ');
    QStringList a_sPar;

    bool a_bApp = false;
    bool a_bSudo = false;
    bool a_bPassSSH = false;
    bool a_bGrep = false;
    bool a_bPassAdd = false;
    QString a_sSudoPar = "";

    for(QString s : a_sData)
    {
        if(s.length() > 0)
        {
            if(!a_bApp)
            {
                if(s.length() > 1)
                {
                    a_bApp = true;

                    if(s == "sudo")
                    {
                        a_bSudo = true;
                        fProgram("/bin/sh");
                    }
                    else {
                        if(s == "sshpass")
                        {
                            a_bPassSSH = true;
                            fProgram("/bin/sh");

                            a_sSudoPar = s;
                        }
                        else {
                            if(_sIn.indexOf("grep") > 0 )
                            {
                                a_bGrep = true;
                                fProgram("/bin/sh");

                                a_sSudoPar = s;
                            }
                            else {
                                fProgram(s);
                            }
                        }
                    }
                }
            }
            else
            {
                if(a_bSudo && !a_bPassAdd)
                {
                    a_bPassAdd = true;

                    a_sPar.append("-c");

                    a_sSudoPar = "echo";
                    a_sSudoPar.append(" ");
                    a_sSudoPar.append(s);
                    a_sSudoPar.append(" |");
                    a_sSudoPar.append(" sudo");
                    a_sSudoPar.append(" -S");

                }
                else
                {
                    if( (a_bPassSSH || a_bGrep ) && !a_bPassAdd)
                    {
                        a_bPassAdd = true;

                        a_sPar.append("-c");

                        a_sSudoPar.append(" ");
                        a_sSudoPar.append(s);
                    }
                    else
                    {
                        if(a_bSudo || a_bPassSSH || a_bGrep)
                        {
                            a_sSudoPar.append(" ");
                            a_sSudoPar.append(s);

                            if(a_bPassSSH && s == "scp" && _sIn.indexOf("StrictHostKeyChecking") < 0)
                            {
                                a_sSudoPar.append(" -o");
                                a_sSudoPar.append(" StrictHostKeyChecking=accept-new");
                            }
                        }
                        else
                            a_sPar.append(s);
                    }
                }
            }
        }
    }

    if(a_sSudoPar.length() > 0)
    {
        //if(a_sSudoPar.indexOf("-y"))
        a_sPar.append(a_sSudoPar);
    }

    fPerforming(a_sPar);
}

void ComandLine::fProgram(QString  _sData)
{
    //qDebug() << "ComandLine::fProgramm 0: " << _sData;

    fProgressStop();

    m_sComande = _sData;

    process = new QProcess();

    QObject::connect(process, &QProcess::errorOccurred, this, &ComandLine::slErrP);


    process->setWorkingDirectory( StaticData::m_sProcessWorkingDirector );
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->setReadChannel(QProcess::StandardOutput);
    process->setProgram(m_sComande);
}

void ComandLine::slErrP(QProcess::ProcessError exitStatus)
{
    //    qDebug() << "ComandLine::slErrP 3: " << "Error: " << exitStatus;
    //    qDebug() << "ComandLine::slErrP 3.2: " << "Error: " << process->errorString();

    emit sgControl(m_sUserId, 14, "0"
                   ,  QString("error: '" + m_sComande +"' is not recognized as an internal or external command, operable program OR " + process->errorString()).toUtf8() );

    slStop();
}


bool ComandLine::fPerforming(QStringList  _slData)
{
    //qDebug() << "ComandLine::fPerforming 0: " << _slData;

    if(process == nullptr)
    {
        emit sgControl(m_sUserId, 14, "3"
                       ,  QString("is not recognized as an internal or external command.").toUtf8() );

        slStop();

        return false;
    }

    if( fCustomProcess(_slData) )
        return false;


    if(_slData.length() > 0)
        process->setArguments(_slData);


//    qDebug() << "ComandLine::fPerforming 2: "
//             << process->workingDirectory()
//             << process->program() << process->arguments();

    process->start();


    emit sgControl(m_sUserId, 14, "1",
                   QString("Working directory: " + process->workingDirectory() + "\r\n").toUtf8());


    QString a_sInfo = "";

    if (process->waitForStarted(-1))
    {
        while(process->waitForReadyRead(-1))
        {
            //qDebug() << "ComandLine::fPerforming 3.0: ";

            //process->moveToThread(this);

            while(process->canReadLine())
            {
                //qDebug() << "ComandLine::fPerforming 3.1: ";

                QByteArray a_baT = process->readLine();

                if(m_iVar == 2)
                {
                    QTextCodec *a_cod = QTextCodec::codecForName("cp866");
                    //assert(a_cod);
                    //qDebug() << "ComandLine::fPerforming 3: " << m_sUserId << a_cod->toUnicode( a_baT ) ;
                    a_baT = a_cod->toUnicode( a_baT ).toUtf8();
                }

                uint64_t a_iSend = 0;

                while (1) {
                    //qDebug() << "ComandLine::fPerforming 3.6: " << a_iSend;

                    if(a_iSend + 255 <= a_baT.length())
                    {
                        emit sgControl(m_sUserId, 14, "1", a_baT.mid(a_iSend, 255));
                    }
                    else
                    {
                        emit sgControl(m_sUserId, 14, "1", a_baT.mid(a_iSend, a_baT.length() - a_iSend ));
                    }

                    a_iSend += 255;

                    //qDebug() << "ComandLine::fPerforming 3.7: " << a_iSend;

                    if(a_iSend + 255 >= a_baT.length())
                        break;
                }



                //emit sgControl(m_sUserId, 14, "1", a_baT);

                //qDebug() << "ComandLine::fPerforming 3.9: " << m_bRun;

                if(!m_bRun)
                    process->kill();
            }

            //qDebug() << "ComandLine::fPerforming 3.10: " << m_bRun;

            if(!m_bRun)
                process->kill();
        }
    }
    // else
    // {
    //     qDebug() << "ComandLine::fPerforming 5.1: " << process->readAllStandardOutput();
    // }

    //qDebug() << "ComandLine::fPerforming 6.0: ";

    slStop();

    //qDebug() << "ComandLine::fPerforming 6.1: ";

    process->waitForFinished();

    //qDebug() << "ComandLine::fPerforming 6.2: ";

    if (process->exitCode() != 0) {

        emit sgControl(m_sUserId, 14, "0",  QString("error: " + process->errorString() + m_sLineFin).toUtf8() );

        qDebug() << "ComandLine::fPerforming 7: " << m_sUserId << "error" << process->errorString();

        return false;
    }

    //qDebug() << "ComandLine::fPerforming 9: ";

    emit sgControl(m_sUserId, 14, "2",  m_sLineFin.toUtf8() );

    //qDebug() << "ComandLine::fPerforming 200: " << m_sUserId;

    return true;
}

void ComandLine::fProgressStop()
{
    //qDebug() << "ComandLine::fProgressStop 0: ";

    if(process)
    {
        if(process->isReadable())
            process->kill();

        //delete process;

        //process = nullptr;
    }

}

void ComandLine::fSetWorkingDirectory(QString _sPath)
{
    //qDebug() << "ComandLine::fSetWorkingDirectory 0: " << _sPath;

    QString a_sDir = StaticData::m_sProcessWorkingDirector;

    if(_sPath.length() > 0)
    {
        if(_sPath.at(0) == '~')
            a_sDir = QDir::homePath();
        else
            if(_sPath.at(0) == '/')
                a_sDir += _sPath;
            else
                a_sDir += ( "/" + _sPath );
    }

    QDir a_dDir( a_sDir );

    if(a_dDir.exists())
    {
        a_sDir = a_dDir.absolutePath();
        //qDebug() << "ComandLine::fSetWorkingDirectory 5: " << a_sDir << a_dDir.absolutePath();
    }
    else
    {
        a_sDir = StaticData::m_sProcessWorkingDirector;

        QDir a_dDir( _sPath );
        if(a_dDir.exists())
        {
            a_sDir = a_dDir.absolutePath();
            //qDebug() << "ComandLine::fSetWorkingDirectory 7: " << a_sDir << a_dDir.absolutePath();
        }
    }

    StaticData::m_sProcessWorkingDirector =  a_sDir;

    //qDebug() << "ComandLine::fSetWorkingDirectory 6: " << a_sDir;
}

void ComandLine::fFolderList(QString _sVar)
{
    QDir dir( StaticData::m_sProcessWorkingDirector );

    if(_sVar == "-a")
    {
        for (const QString &filename : dir.entryList(QDir::Dirs | QDir::Hidden) )
            emit sgControl(m_sUserId, 14, "1",
                           QString("[" + filename + "]\r\n").toUtf8());

        for (const QString &filename : dir.entryList(QDir::Files | QDir::Hidden) )
            emit sgControl(m_sUserId, 14, "1",
                           QString("" + filename + "\r\n").toUtf8());
    }
    else
    {
        for (const QString &filename : dir.entryList(QDir::AllDirs) )
            emit sgControl(m_sUserId, 14, "1",
                           QString("[" + filename + "]\r\n").toUtf8());

        for (const QString &filename : dir.entryList(QDir::Files) )
            emit sgControl(m_sUserId, 14, "1",
                           QString("" + filename + "\r\n").toUtf8());
    }

}

bool ComandLine::fCustomProcess(QStringList  _slData)
{
    if(process == nullptr)
    {
        return false;
    }

    if(process->program() == "cd")
    {
        //qDebug() << "ComandLine::fCustomProcess 1: ";

        if(_slData.length() > 0)
            fSetWorkingDirectory(_slData.at(0));
        else
            fSetWorkingDirectory( "" );

        emit sgControl(m_sUserId, 14, "1",
                       QString("Working directory: " + StaticData::m_sProcessWorkingDirector + "\r\n").toUtf8());

        slStop();

        emit sgControl(m_sUserId, 14, "2",  m_sLineFin.toUtf8() );

        return true;
    }
    else
    {
        if(process->program() == "ls")
        {
            if(_slData.length() > 0)
                fFolderList(_slData.at(0));
            else
                fFolderList("");

            slStop();

            emit sgControl(m_sUserId, 14, "2",  m_sLineFin.toUtf8() );

            return true;
        }
    }

    return false;
}
