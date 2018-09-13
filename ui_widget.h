/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <mylabel.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    myLabel *pictureLabel;
    QPushButton *uploadPushButton;
    QPushButton *restartPushButton;
    QTextEdit *resultTextEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1112, 743);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        Widget->setFont(font);
        Widget->setAcceptDrops(true);
        pictureLabel = new myLabel(Widget);
        pictureLabel->setObjectName(QStringLiteral("pictureLabel"));
        pictureLabel->setGeometry(QRect(440, 360, 256, 291));
        pictureLabel->setMinimumSize(QSize(0, 0));
        pictureLabel->setMaximumSize(QSize(16777215, 16777215));
        pictureLabel->setCursor(QCursor(Qt::CrossCursor));
        pictureLabel->setAcceptDrops(true);
        uploadPushButton = new QPushButton(Widget);
        uploadPushButton->setObjectName(QStringLiteral("uploadPushButton"));
        uploadPushButton->setGeometry(QRect(20, 10, 117, 36));
        uploadPushButton->setMinimumSize(QSize(0, 0));
        uploadPushButton->setMaximumSize(QSize(333333, 16777215));
        restartPushButton = new QPushButton(Widget);
        restartPushButton->setObjectName(QStringLiteral("restartPushButton"));
        restartPushButton->setGeometry(QRect(810, 50, 256, 36));
        resultTextEdit = new QTextEdit(Widget);
        resultTextEdit->setObjectName(QStringLiteral("resultTextEdit"));
        resultTextEdit->setGeometry(QRect(830, 290, 256, 235));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        pictureLabel->setText(QApplication::translate("Widget", "\346\230\276\347\244\272\345\233\276\347\211\207", Q_NULLPTR));
        uploadPushButton->setText(QApplication::translate("Widget", "upload", Q_NULLPTR));
        restartPushButton->setText(QApplication::translate("Widget", "restart", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
