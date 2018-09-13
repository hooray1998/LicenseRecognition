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

    //layout

        wid = this->width();
        hei = this->height();

        sidewidth= wid*1/9;
        blackwidth = wid*1/38;
        topheight= hei*1/8;
        lwidth = (wid - 2*sidewidth - (charsNumber-1)*blackwidth)/charsNumber;
        lheight = hei*1/4;
        mainwidth = wid*2/3;
        mainheight = hei*1/5;
        mainx = (wid-mainwidth)/2;
        mainy = (50+topheight+lheight);



        int tempx = sidewidth;
        int tempy = topheight;
        for(int i=0;i<charsNumber;i++)
        {
            mark[i].setRect(tempx,tempy,lwidth,lheight);
            tempx += blackwidth+lwidth;
        }

}


void myLabel::paintEvent(QPaintEvent *)
{
        painter.begin(this);          //进行重绘;

        QPixmap *qp = new QPixmap("E:/bz.jpg");
        painter.drawPixmap(rect(),qp->scaled(this->size()));

        painter.end();  //重绘结束;

}

void myLabel::setMainPicture(QPixmap p)
{
    mainPicture = new QPixmap(p);
}

void myLabel::setCharsArray(SplitChar *p, int charsnum)
{
    for(int i=0;i<charsnum;i++)
    {
        spchars[i].init(p[i]);
    }
    charsNumber = charsnum;
}



void SplitChar::init(SplitChar &temp)
{
    classnum = temp.classnum;
    leftx = temp.leftx;
    topy = temp.topy;
    width = temp.width;
    height = temp.height;
}
