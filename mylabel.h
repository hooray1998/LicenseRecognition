#ifndef MYLABEL_H
#define MYLABEL_H

#define MAX_CHAR_NUM 10

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
    QString classnum;
    int rightRate;
    int leftx;
    int topy;
    int width;
    int height;

    void init(SplitChar &temp);
    bool equal(SplitChar &another);
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
    SplitChar spchars[MAX_CHAR_NUM];
    QRect charsRects[MAX_CHAR_NUM];
    int charsNumber;
    QRect captureLicense[MAX_CHAR_NUM];
    QPixmap capturePixmap[MAX_CHAR_NUM];
    QRect mark[MAX_CHAR_NUM];
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

    QPixmap labelPicture;//label快照

public slots:
    void paintEvent(QPaintEvent *);
};

#endif // MYLABEL_H
