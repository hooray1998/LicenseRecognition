
#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include<QThread.h>
#include<QString.h>
#include<Qthread.h>
#include <QDebug>
#define QDBG qDebug()<<__FILE__<<__FUNCTION__<<"():"<<__LINE__

class QProcess;
class workThread : public QObject
{
    Q_OBJECT
public:
    explicit workThread(QObject *parent = 0);
    ~workThread();

public:
   QProcess* myChildProcess;


public slots:
    void readSlot();
    void writeSlot(QString str);
    void IniCmdThreadSlot();
signals:
    void senddata_sign(QString);

};

#endif // WORKTHREAD_H
