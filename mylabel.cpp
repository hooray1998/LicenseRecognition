#include "mylabel.h"
#include <QPainter>
myLabel::myLabel(QWidget *parent) :
    QLabel(parent)
{

    setMouseTracking(true);

    mainPicture = NULL;
    charsNumber = 0;
}

void myLabel::setNewLayout()
{

    wid = this->width();
    hei = this->height();

    //set main Picture
    mainwidth = wid*7/9;
    mainheight = hei/4;
    mainx = (wid-mainwidth)/2;
    mainy = hei/8;

    //set splitChars
    if(charsNumber!=0)
    {
        topheight= hei*1/7;
        lwidth = wid*4/(MAX_CHAR_NUM*5);
        lheight = 2 * lwidth;
        blackwidth = lwidth/4;
        sidewidth= ( wid - charsNumber*(lwidth+blackwidth)+blackwidth)/2;

        int tempx = sidewidth;
        int tempy = topheight + mainy + mainheight;
        for(int i=0;i<charsNumber;i++)
        {
            mark[i].setRect(tempx,tempy,lwidth,lheight);
            tempx += blackwidth+lwidth;
        }
    }


}


void myLabel::paintEvent(QPaintEvent *)
{
        painter.begin(this);          //进行重绘;


        //painting main picture
        if(mainPicture!=NULL)
        {
            painter.drawPixmap(mainx,mainy,mainPicture->scaled(QSize(mainwidth,mainheight)));
            for(int i=0;i<charsNumber;i++)
            {
                captureLicense[i].setRect(charsRects[i].x(),charsRects[i].y(),charsRects[i].width(),charsRects[i].height());
                qDebug()<<captureLicense[i];
                capturePixmap[i] =labelPicture.copy(captureLicense[i]);
            }
            for(int i=0;i<charsNumber;i++)
            {
                painter.drawPixmap(mark[i],capturePixmap[i].scaled(mark[i].size()));
                painter.drawText(mark[i].x(),mark[i].y()+mark[i].height(),mark[i].width(),mark[i].height(), 0, spchars[i].classnum+QString("\n%1%").arg(spchars[i].rightRate));
            }

        }

        painter.end();  //重绘结束;

}

void myLabel::setMainPicture(QPixmap p)
{
    mainPicture = new QPixmap(p);
    qDebug()<<mainPicture->width()<<"width";
    charsNumber = 0;
    setNewLayout();
    update();
}

void myLabel::setCharsArray(SplitChar *p, int charsnum)
{
    labelPicture = QWidget::grab(this->rect());

    int pwid = mainPicture->width();
    int phei = mainPicture->height();

    for(int i=0;i<charsnum;i++)
    {
        spchars[i].init(p[i]);
        int realx = mainx + 1.0*mainwidth*p[i].leftx/(1.0*pwid);
        int realy = mainy + 1.0*mainheight*p[i].topy/(1.0*phei);
        int realwidth = 1.0*mainwidth*p[i].width/(1.0*pwid);
        int realheight = 1.0*mainheight*p[i].height/(1.0*phei);
        qDebug()<<realx<<realy<<realwidth<<realheight<<"%%%"<<1.0*mainwidth*p[i].width/(1.0*pwid)<<"mainwidth"<<mainwidth;

        charsRects[i].setRect(realx, realy, realwidth, realheight);

    }
    charsNumber = charsnum;

    setNewLayout();
    update();
}

void SplitChar::init(SplitChar &temp)
{
    classnum = temp.classnum;
    rightRate = temp.rightRate;
    leftx = temp.leftx;
    topy = temp.topy;
    width = temp.width;
    height = temp.height;
}
