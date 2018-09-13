#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    splitter = new QSplitter(this);
    model = new QFileSystemModel;
    list = new QListView(splitter);
    list->setModel(model);
    splitter->show();

    initStyle();

    connect(list,SIGNAL(clicked(QModelIndex)),this,SLOT(readCurPicture(QModelIndex)));

}

Widget::~Widget()
{
    delete ui;
}
void Widget::initStyle()
{
    //加载样式表
    QFile file(":/other/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}
void Widget::readCurPicture(QModelIndex index)
{
    QString filepath = model->filePath(index);
    if(filepath.contains(".jpg")||filepath.contains(".png"))
        ui->pictureLabel->setMainPicture(QPixmap(filepath));


}

void Widget::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"resize size"<<this->width()<<this->height();

    //RESIZE all widget;
    int wid = this->width();
    int hei = this->height();

    ui->uploadPushButton->setGeometry(0,0,wid/5,50);
    splitter->setGeometry(0,50,wid/5,hei-50);

    ui->pictureLabel->setGeometry(wid/5,0,wid*3/5,hei);

    ui->restartPushButton->setGeometry(wid*4/5,0,wid/5,50);
    ui->resultTextEdit->setGeometry(wid*4/5,50,wid/5,hei-50);
}
void Widget::on_uploadPushButton_clicked()
{
   QString folder = QFileDialog::getExistingDirectory(this,"选择图片加载位置",QDir::rootPath());
   if(!folder.isNull()&&!folder.isEmpty())
   {
        model->setRootPath(folder);
        list->setRootIndex(model->index(folder));
   }
}

void Widget::showResult()
{
    ui->resultTextEdit->clear();
}
