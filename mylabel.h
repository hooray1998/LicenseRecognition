#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QtDebug>
#include <QMouseEvent>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class SplitChar{
public:
    int classnum;
    int leftx;
    int topy;
    int width;
    int height;

    void init(SplitChar &temp);
};

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget*parent = 0);

    void setNewLayout();
    void setMainPicture(QPixmap p);
    void setCharsArray(SplitChar *p, int charsnum);

private:
    QPainter painter;

    QPixmap *mainPicture;
    SplitChar spchars[10];
    int charsNumber;
    QRect captureLicense[10];
    QPixmap capturePixmap[10];
    QRect mark[10];
    int wid,
        hei,
        sidewidth,
        blackwidth,
        topheight,
        lwidth,
        lheight,
        mainwidth,
        mainheight,
        mainx,
        mainy;

public slots:
    void paintEvent(QPaintEvent *);
};

#endif // MYLABEL_H
