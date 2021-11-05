/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButtonToComputer;
    QListView *computerListView;
    QListView *DeviceListView;
    QPushButton *pushButtonToDevice;
    QLabel *label;
    QLabel *label_2;
    QToolButton *toolButtonDir;
    QTextEdit *textEdit;
    QComboBox *comboBoxSerial;
    QToolButton *toolButtonSerialRefresh;
    QPushButton *pushButtonStop;
    QLabel *label_3;
    QComboBox *comboBoxSpeed;
    QLabel *label_4;
    QLabel *label_7;
    QFrame *frame;
    QComboBox *comboBoxBits;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBoxStop;
    QLabel *label_10;
    QComboBox *comboBoxStopParity;
    QComboBox *comboBoxControl;
    QFrame *frame_2;
    QLabel *label_8;
    QLineEdit *lineEditDir;
    QLineEdit *lineEditBaseName;
    QCheckBox *checkBoxReceiveFile;
    QLabel *label_9;
    QComboBox *comboBoxFilter;
    QComboBox *comboBoxProtocol;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMinimumSize(QSize(0, 600));
        Widget->setMaximumSize(QSize(800, 800));
        pushButtonToComputer = new QPushButton(Widget);
        pushButtonToComputer->setObjectName(QString::fromUtf8("pushButtonToComputer"));
        pushButtonToComputer->setGeometry(QRect(330, 140, 113, 32));
        computerListView = new QListView(Widget);
        computerListView->setObjectName(QString::fromUtf8("computerListView"));
        computerListView->setGeometry(QRect(500, 140, 281, 192));
        computerListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        DeviceListView = new QListView(Widget);
        DeviceListView->setObjectName(QString::fromUtf8("DeviceListView"));
        DeviceListView->setGeometry(QRect(20, 140, 256, 192));
        DeviceListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        pushButtonToDevice = new QPushButton(Widget);
        pushButtonToDevice->setObjectName(QString::fromUtf8("pushButtonToDevice"));
        pushButtonToDevice->setGeometry(QRect(330, 180, 113, 32));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 120, 60, 16));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(500, 120, 91, 16));
        toolButtonDir = new QToolButton(Widget);
        toolButtonDir->setObjectName(QString::fromUtf8("toolButtonDir"));
        toolButtonDir->setGeometry(QRect(750, 20, 26, 22));
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 370, 761, 211));
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        textEdit->setFont(font);
        comboBoxSerial = new QComboBox(Widget);
        comboBoxSerial->setObjectName(QString::fromUtf8("comboBoxSerial"));
        comboBoxSerial->setGeometry(QRect(60, 10, 261, 32));
        toolButtonSerialRefresh = new QToolButton(Widget);
        toolButtonSerialRefresh->setObjectName(QString::fromUtf8("toolButtonSerialRefresh"));
        toolButtonSerialRefresh->setGeometry(QRect(330, 15, 26, 21));
        pushButtonStop = new QPushButton(Widget);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setGeometry(QRect(330, 220, 113, 32));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 17, 41, 20));
        comboBoxSpeed = new QComboBox(Widget);
        comboBoxSpeed->setObjectName(QString::fromUtf8("comboBoxSpeed"));
        comboBoxSpeed->setGeometry(QRect(10, 60, 91, 32));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 40, 41, 20));
        label_7 = new QLabel(Widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(310, 40, 51, 20));
        frame = new QFrame(Widget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 0, 371, 111));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        comboBoxBits = new QComboBox(frame);
        comboBoxBits->setObjectName(QString::fromUtf8("comboBoxBits"));
        comboBoxBits->setGeometry(QRect(90, 60, 61, 32));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(100, 40, 41, 20));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(160, 40, 41, 20));
        comboBoxStop = new QComboBox(frame);
        comboBoxStop->setObjectName(QString::fromUtf8("comboBoxStop"));
        comboBoxStop->setGeometry(QRect(150, 60, 61, 32));
        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(220, 40, 41, 20));
        comboBoxStopParity = new QComboBox(frame);
        comboBoxStopParity->setObjectName(QString::fromUtf8("comboBoxStopParity"));
        comboBoxStopParity->setGeometry(QRect(210, 60, 81, 32));
        comboBoxControl = new QComboBox(frame);
        comboBoxControl->setObjectName(QString::fromUtf8("comboBoxControl"));
        comboBoxControl->setGeometry(QRect(290, 60, 81, 32));
        frame_2 = new QFrame(Widget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(380, 0, 411, 111));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 20, 101, 20));
        lineEditDir = new QLineEdit(frame_2);
        lineEditDir->setObjectName(QString::fromUtf8("lineEditDir"));
        lineEditDir->setGeometry(QRect(110, 20, 251, 21));
        lineEditBaseName = new QLineEdit(frame_2);
        lineEditBaseName->setObjectName(QString::fromUtf8("lineEditBaseName"));
        lineEditBaseName->setGeometry(QRect(130, 50, 231, 21));
        checkBoxReceiveFile = new QCheckBox(frame_2);
        checkBoxReceiveFile->setObjectName(QString::fromUtf8("checkBoxReceiveFile"));
        checkBoxReceiveFile->setGeometry(QRect(10, 50, 111, 20));
        label_9 = new QLabel(Widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 350, 60, 16));
        comboBoxFilter = new QComboBox(Widget);
        comboBoxFilter->setObjectName(QString::fromUtf8("comboBoxFilter"));
        comboBoxFilter->setGeometry(QRect(330, 260, 111, 32));
        comboBoxProtocol = new QComboBox(Widget);
        comboBoxProtocol->setObjectName(QString::fromUtf8("comboBoxProtocol"));
        comboBoxProtocol->setGeometry(QRect(330, 300, 111, 32));
        frame->raise();
        frame_2->raise();
        pushButtonToComputer->raise();
        computerListView->raise();
        DeviceListView->raise();
        pushButtonToDevice->raise();
        label->raise();
        label_2->raise();
        toolButtonDir->raise();
        textEdit->raise();
        comboBoxSerial->raise();
        toolButtonSerialRefresh->raise();
        pushButtonStop->raise();
        label_3->raise();
        comboBoxSpeed->raise();
        label_4->raise();
        label_7->raise();
        label_9->raise();
        comboBoxFilter->raise();
        comboBoxProtocol->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Serial transfer utility", nullptr));
        pushButtonToComputer->setText(QCoreApplication::translate("Widget", "-->", nullptr));
        pushButtonToDevice->setText(QCoreApplication::translate("Widget", "<--", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Device:", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "Computer:", nullptr));
        toolButtonDir->setText(QCoreApplication::translate("Widget", "...", nullptr));
        toolButtonSerialRefresh->setText(QCoreApplication::translate("Widget", "...", nullptr));
        pushButtonStop->setText(QCoreApplication::translate("Widget", "Stop", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "Port:", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "Speed:", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "Control:", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "Bits:", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "Stop:", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "Parity:", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "Base directory:", nullptr));
        checkBoxReceiveFile->setText(QCoreApplication::translate("Widget", "Receive to  file:", nullptr));
        label_9->setText(QCoreApplication::translate("Widget", "Console:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
