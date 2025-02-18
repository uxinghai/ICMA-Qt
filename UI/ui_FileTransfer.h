/********************************************************************************
** Form generated from reading UI file 'FileTransfer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILETRANSFER_H
#define UI_FILETRANSFER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileTrans
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *btnReceiver;
    QPushButton *btnSender;

    void setupUi(QWidget *FileTrans)
    {
        if (FileTrans->objectName().isEmpty())
            FileTrans->setObjectName("FileTrans");
        FileTrans->resize(284, 54);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/transfer/res/transfer/trans.png"), QSize(), QIcon::Normal, QIcon::Off);
        FileTrans->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(FileTrans);
        horizontalLayout->setObjectName("horizontalLayout");
        btnReceiver = new QPushButton(FileTrans);
        btnReceiver->setObjectName("btnReceiver");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnReceiver->sizePolicy().hasHeightForWidth());
        btnReceiver->setSizePolicy(sizePolicy);
        btnReceiver->setMinimumSize(QSize(130, 28));
        btnReceiver->setMaximumSize(QSize(130, 28));
        QFont font;
        font.setPointSize(11);
        btnReceiver->setFont(font);
        btnReceiver->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(btnReceiver);

        btnSender = new QPushButton(FileTrans);
        btnSender->setObjectName("btnSender");
        sizePolicy.setHeightForWidth(btnSender->sizePolicy().hasHeightForWidth());
        btnSender->setSizePolicy(sizePolicy);
        btnSender->setMinimumSize(QSize(130, 28));
        btnSender->setMaximumSize(QSize(130, 28));
        btnSender->setFont(font);
        btnSender->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(btnSender);


        retranslateUi(FileTrans);

        QMetaObject::connectSlotsByName(FileTrans);
    } // setupUi

    void retranslateUi(QWidget *FileTrans)
    {
        FileTrans->setWindowTitle(QCoreApplication::translate("FileTrans", "\344\274\240\350\276\223\345\212\251\346\211\213", nullptr));
        btnReceiver->setText(QCoreApplication::translate("FileTrans", "\346\210\221\346\230\257\346\216\245\346\224\266\346\226\271", nullptr));
        btnSender->setText(QCoreApplication::translate("FileTrans", "\346\210\221\346\230\257\345\217\221\351\200\201\346\226\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileTrans: public Ui_FileTrans {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILETRANSFER_H
