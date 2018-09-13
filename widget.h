#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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
public slots:
    void readCurPicture(QModelIndex index);
private slots:
    void on_uploadPushButton_clicked();

private:
    Ui::Widget *ui;
    QWidget *secwidget;
    QHBoxLayout*seclay;
    QLabel*seclabel;

    QSplitter *splitter;
    QFileSystemModel *model;
    QListView *list;
};

#endif // WIDGET_H
