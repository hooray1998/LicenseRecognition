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

    sidewidth= wid*1/15;
    blackwidth = wid*1/38;
    topheight= hei*2/5;
    if(charsNumber!=0)
    {
        lwidth = (wid - 2*sidewidth - (charsNumber-1)*blackwidth)/charsNumber;
        lheight = hei*1/4;
    }
    mainwidth = wid*7/9;
    mainheight = hei/4;
    mainx = (wid-mainwidth)/2;
    mainy = hei/8;



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


        //painting main picture
        if(mainPicture!=NULL)
        {
            painter.drawPixmap(mainx,mainy,mainPicture->scaled(QSize(mainwidth,mainheight)));
            for(int i=0;i<charsNumber;i++)
            {
                captureLicense[i].setRect(spchars[i].leftx,spchars[i].topy,spchars[i].width,spchars[i].height);
                //capturePixmap[i] = mainPicture.copy(captureLicense[i]);
                painter.drawPixmap(mark[i],capturePixmap[i].scaled(mark[i].size()));
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
    for(int i=0;i<charsnum;i++)
    {
        spchars[i].init(p[i]);
    }
    charsNumber = charsnum;

    setNewLayout();
    update();
}

void SplitChar::init(SplitChar &temp)
{
    classnum = temp.classnum;
    leftx = temp.leftx;
    topy = temp.topy;
    width = temp.width;
    height = temp.height;
}
