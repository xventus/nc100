/********************************************************************************
** Form generated from reading UI file 'formheddump.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMHEDDUMP_H
#define UI_FORMHEDDUMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormHedDump
{
public:
    QPushButton *pushButtonClose;
    QTextEdit *textEdit;

    void setupUi(QWidget *FormHedDump)
    {
        if (FormHedDump->objectName().isEmpty())
            FormHedDump->setObjectName(QString::fromUtf8("FormHedDump"));
        FormHedDump->resize(751, 372);
        pushButtonClose = new QPushButton(FormHedDump);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(620, 330, 113, 32));
        textEdit = new QTextEdit(FormHedDump);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 731, 311));
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier")});
        font.setPointSize(14);
        textEdit->setFont(font);
        textEdit->setReadOnly(true);

        retranslateUi(FormHedDump);

        QMetaObject::connectSlotsByName(FormHedDump);
    } // setupUi

    void retranslateUi(QWidget *FormHedDump)
    {
        FormHedDump->setWindowTitle(QCoreApplication::translate("FormHedDump", "Form", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("FormHedDump", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormHedDump: public Ui_FormHedDump {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMHEDDUMP_H
