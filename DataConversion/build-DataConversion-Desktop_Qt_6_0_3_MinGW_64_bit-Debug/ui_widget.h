/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *writeButton;
    QTextEdit *textEdit;
    QPushButton *readButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(563, 291);
        writeButton = new QPushButton(Widget);
        writeButton->setObjectName(QString::fromUtf8("writeButton"));
        writeButton->setGeometry(QRect(220, 220, 101, 41));
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(120, 90, 321, 31));
        readButton = new QPushButton(Widget);
        readButton->setObjectName(QString::fromUtf8("readButton"));
        readButton->setGeometry(QRect(460, 90, 91, 31));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 20, 181, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(10, 90, 101, 31));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";"));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(10, 150, 101, 31));
        label_3->setFont(font);
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";"));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setEnabled(true);
        label_4->setGeometry(QRect(180, 150, 181, 31));
        label_4->setFont(font);
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";"));
        label_4->setAlignment(Qt::AlignCenter);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        writeButton->setText(QCoreApplication::translate("Widget", "\350\275\254\346\215\242", nullptr));
        readButton->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\261\241\346\263\245\346\225\260\346\215\256\346\226\207\344\273\266\350\275\254\346\215\242", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\272\220\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\350\275\254\346\215\242\347\212\266\346\200\201 :", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\346\227\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
