#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"workthread.h"

#include <QSplitter>
#include <QFileSystemModel>
#include <QListView>
#include <QApplication>
#include <QDesktopWidget>

#include <QProcess>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <QThread>
#include <QHBoxLayout>
#include <QLabel>

//drag
#include<QDragEnterEvent>
#include<QMimeData>
#include<QDropEvent>
#include<QUrl>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void initStyle();
    void uploadStartPath();
    void showResult();

protected:
    void contextMenuEvent();
    void resizeEvent(QResizeEvent *event);
    void dragEnterEvent(QDragEnterEvent*event);//拖动进入事件
    void dropEvent(QDropEvent*event);

signals:
    void IniCmdThread_sign();
    void read_sign();
    void write_sign(QString);
    void stopread_sign();
    void sendcomd_sign(QString);

private slots:
    void getdata_slot(QString);
    void stopRead();

    void readCurPicture(QModelIndex index);
    void on_uploadPushButton_clicked();
    void on_restartPushButton_clicked();

private:
    Ui::Widget *ui;
    QProcess* myChildProcess;
    QThread m_thread;

    QSplitter *splitter;
    QFileSystemModel *model;
    QListView *list;
};

#endif // WIDGET_H
