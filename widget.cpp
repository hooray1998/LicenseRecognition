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

    QString folder2 = "E:/QtCoding/workThread/t";
        model->setRootPath(folder2);
        list->setRootIndex(model->index(folder2));
    initStyle();

    connect(list,SIGNAL(clicked(QModelIndex)),this,SLOT(readCurPicture(QModelIndex)));


    //run darknet

    workThread *work=new workThread;
    work->moveToThread(&m_thread);
    connect(this, SIGNAL(IniCmdThread_sign()), work, SLOT(IniCmdThreadSlot()));
    connect(&m_thread,SIGNAL(&QThread::finished()), work,SLOT(&QObject::deleteLater()));

    connect(this, SIGNAL(write_sign(QString)), work, SLOT(writeSlot(QString)));
    connect(this, SIGNAL(read_sign()), work, SLOT(readSlot()));
    connect(work,SIGNAL(senddata_sign(QString)),this,SLOT(getdata_slot(QString)));
    connect(this,SIGNAL(sendcomd_sign(QString)),work,SLOT(writeSlot(QString)));


    m_thread.start();
    emit IniCmdThread_sign();
    emit read_sign();

    //end run DARKNET
}

Widget::~Widget()
{
    delete ui;
    emit sendcomd_sign("exit\r\n");
    m_thread.quit();
    m_thread.wait();
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

    QFont font(NULL, 12);
    ui->resultTextEdit->setFont(font);
}
void Widget::readCurPicture(QModelIndex index)
{
    QString filepath = model->filePath(index);
    if(filepath.contains(".jpg")||filepath.contains(".png")||filepath.contains(".bmp"))
    {
        ui->pictureLabel->setMainPicture(QPixmap(filepath));
        QString str_comd = filepath + '\r' + '\n';
        emit sendcomd_sign(str_comd);
    }



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

    ui->pictureLabel->setNewLayout();
    ui->pictureLabel->update();

    //字体随之变化
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


///////////////////////////////////////////////
/// \brief Widget::getdata_slot
/// \param info
///         run Darknet
/// /////////////////////

void Widget::getdata_slot(QString info)
{
        if(info.contains("Predicted"))
        {
            QString  resultfile = QDir::currentPath()+"/"+QString("prediction_result.txt");
            QFile *file = new QFile(resultfile);

            bool ok = file->open(QIODevice::Text|QIODevice::ReadOnly);
            if(!ok) qDebug("no open ");

            QTextStream in(file);
            SplitChar tempArrays[MAX_CHAR_NUM];
            int num=0;
            while(!in.atEnd())
            {
                //QDBG<<in.readLine();
                in>>tempArrays[num].classnum>>tempArrays[num].rightRate>>tempArrays[num].leftx>>tempArrays[num].topy>>tempArrays[num].width>>tempArrays[num].height;
                num++;

            }
            num--;///

            ui->resultTextEdit->append(QString("charsNum is %1").arg(num));

            file->close();
            delete file;
            file = NULL;

            ui->pictureLabel->setCharsArray(tempArrays,num);

            //QDBG << info;
            ui->resultTextEdit->append(info);

        }
        else if (info.indexOf("\r\n")!=0)
        {

            //QDBG << info;
            ui->resultTextEdit->append(info);
        }
}

void Widget::stopRead()
{

}

void Widget::on_restartPushButton_clicked()
{

    m_thread.terminate();
    m_thread.start();
    emit IniCmdThread_sign();
    emit read_sign();
}
