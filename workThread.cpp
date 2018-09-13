
#include "workThread.h"
#include <QCoreApplication>
#include <QProcess>
#include <QDebug.h>
#include <QString>
#include <QTime>

workThread::workThread(QObject *parent) : QObject(parent)
{
}

workThread::~workThread()
{
    myChildProcess->close();

    delete myChildProcess;

    myChildProcess=NULL;
    qDebug() << "end myChildProcess " << "\r\n";
}

void workThread::readSlot()
{
    //QDBG << myChildProcess->canReadLine();
    while(myChildProcess->canReadLine())
    {
        char output[1024];
        int ret = myChildProcess->readLine(output,1023);
        QString tmpstr = QString::fromLocal8Bit(output);
        emit senddata_sign(tmpstr);

        /*

*/
    }
}

void workThread::writeSlot(QString strWrite)
{

    QDBG << strWrite.toStdString().c_str();
    emit senddata_sign(strWrite.toStdString().c_str());
    char*ch;
    QByteArray ba = strWrite.toLatin1();
    ch=ba.data();
    myChildProcess->write(ch);
    myChildProcess->waitForBytesWritten(2000);

}

void workThread::IniCmdThreadSlot()
{
   QDBG << "IniCmdThread_slot()";
    emit senddata_sign("IniCmdThread_slot()");
   myChildProcess = new QProcess(this);
   myChildProcess->setProcessChannelMode(QProcess::MergedChannels);
   QObject::connect(myChildProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readSlot()));

    QString program = QDir::currentPath()+"/"+QString("darknet_no_gpu.exe");
    QStringList args;
    args<<"detector"<<"test"<<"ittdata/obj.data"<<"ittdata/yolo-park.cfg"<<"ittdata/yolo-park_final.weights"<<"-ext_output";
    //cmd->startDetached(program,args);

   myChildProcess->start(program,args);
   if (!myChildProcess->waitForStarted())
   {
       QDBG << "Make failed:" << myChildProcess->errorString();
       QString tmpstr = "Make failed:" + myChildProcess->errorString();
        emit senddata_sign(tmpstr);
   }
   else
   {
       QDBG << "Child Process Started.123 " << myChildProcess->readAll();
       QString tmpstr ="Child Process Started.123 " + myChildProcess->readAll();
       emit senddata_sign(tmpstr);
   }

}
