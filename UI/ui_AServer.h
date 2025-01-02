/********************************************************************************
** Form generated from reading UI file 'AServer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASERVER_H
#define UI_ASERVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AServer
{
public:
    QAction *actionListen;
    QAction *actionDisConnect;
    QAction *actionHelp;
    QAction *actionSetSavePath;
    QAction *actionOpenFile;
    QAction *actionOpenPath;
    QAction *actionCopyAbsoultPath;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *FileListView;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QWidget *TransDetail_2;
    QFormLayout *formLayout;
    QLabel *lb1;
    QLabel *lbStatus;
    QLabel *lb2;
    QLabel *lbCurFile;
    QLabel *lb3;
    QLabel *lbSize;
    QLabel *lb4;
    QLabel *lbSpeed;
    QLabel *lb5;
    QLabel *lbRemaingTime;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *AServer)
    {
        if (AServer->objectName().isEmpty())
            AServer->setObjectName("AServer");
        AServer->resize(640, 450);
        AServer->setMinimumSize(QSize(640, 450));
        AServer->setMaximumSize(QSize(640, 450));
        QFont font;
        font.setPointSize(11);
        AServer->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/transfer/res/transfer/fileTrans.png"), QSize(), QIcon::Normal, QIcon::Off);
        AServer->setWindowIcon(icon);
        actionListen = new QAction(AServer);
        actionListen->setObjectName("actionListen");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/transfer/res/transfer/Connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionListen->setIcon(icon1);
        actionListen->setFont(font);
        actionListen->setMenuRole(QAction::MenuRole::NoRole);
        actionDisConnect = new QAction(AServer);
        actionDisConnect->setObjectName("actionDisConnect");
        actionDisConnect->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/transfer/res/transfer/disConnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisConnect->setIcon(icon2);
        actionDisConnect->setFont(font);
        actionDisConnect->setMenuRole(QAction::MenuRole::NoRole);
        actionHelp = new QAction(AServer);
        actionHelp->setObjectName("actionHelp");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/transfer/res/transfer/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon3);
        actionHelp->setFont(font);
        actionHelp->setMenuRole(QAction::MenuRole::NoRole);
        actionSetSavePath = new QAction(AServer);
        actionSetSavePath->setObjectName("actionSetSavePath");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/transfer/res/transfer/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetSavePath->setIcon(icon4);
        actionSetSavePath->setFont(font);
        actionSetSavePath->setMenuRole(QAction::MenuRole::NoRole);
        actionOpenFile = new QAction(AServer);
        actionOpenFile->setObjectName("actionOpenFile");
        actionOpenFile->setMenuRole(QAction::MenuRole::NoRole);
        actionOpenPath = new QAction(AServer);
        actionOpenPath->setObjectName("actionOpenPath");
        actionOpenPath->setMenuRole(QAction::MenuRole::NoRole);
        actionCopyAbsoultPath = new QAction(AServer);
        actionCopyAbsoultPath->setObjectName("actionCopyAbsoultPath");
        actionCopyAbsoultPath->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(AServer);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setFont(font);
        splitter->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 24));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        FileListView = new QListWidget(layoutWidget);
        FileListView->setObjectName("FileListView");
        FileListView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        FileListView->setFrameShape(QFrame::Shape::Box);
        FileListView->setFrameShadow(QFrame::Shadow::Plain);

        verticalLayout->addWidget(FileListView);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(16777215, 24));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        TransDetail_2 = new QWidget(layoutWidget1);
        TransDetail_2->setObjectName("TransDetail_2");
        TransDetail_2->setMinimumSize(QSize(250, 0));
        TransDetail_2->setFont(font);
        TransDetail_2->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    border: 1px solid;\n"
"}\n"
"\n"
"QLabel {\n"
"    border: none;  /* \347\241\256\344\277\235 QLabel \347\232\204\350\276\271\346\241\206\344\270\215\350\242\253\344\277\256\346\224\271 */\n"
"}\n"
""));
        formLayout = new QFormLayout(TransDetail_2);
        formLayout->setObjectName("formLayout");
        lb1 = new QLabel(TransDetail_2);
        lb1->setObjectName("lb1");
        lb1->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, lb1);

        lbStatus = new QLabel(TransDetail_2);
        lbStatus->setObjectName("lbStatus");
        lbStatus->setFont(font);

        formLayout->setWidget(0, QFormLayout::FieldRole, lbStatus);

        lb2 = new QLabel(TransDetail_2);
        lb2->setObjectName("lb2");
        lb2->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, lb2);

        lbCurFile = new QLabel(TransDetail_2);
        lbCurFile->setObjectName("lbCurFile");
        lbCurFile->setFont(font);

        formLayout->setWidget(1, QFormLayout::FieldRole, lbCurFile);

        lb3 = new QLabel(TransDetail_2);
        lb3->setObjectName("lb3");
        lb3->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, lb3);

        lbSize = new QLabel(TransDetail_2);
        lbSize->setObjectName("lbSize");
        lbSize->setFont(font);

        formLayout->setWidget(2, QFormLayout::FieldRole, lbSize);

        lb4 = new QLabel(TransDetail_2);
        lb4->setObjectName("lb4");
        lb4->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, lb4);

        lbSpeed = new QLabel(TransDetail_2);
        lbSpeed->setObjectName("lbSpeed");
        lbSpeed->setFont(font);

        formLayout->setWidget(3, QFormLayout::FieldRole, lbSpeed);

        lb5 = new QLabel(TransDetail_2);
        lb5->setObjectName("lb5");
        lb5->setFont(font);

        formLayout->setWidget(4, QFormLayout::LabelRole, lb5);

        lbRemaingTime = new QLabel(TransDetail_2);
        lbRemaingTime->setObjectName("lbRemaingTime");
        lbRemaingTime->setFont(font);

        formLayout->setWidget(4, QFormLayout::FieldRole, lbRemaingTime);


        verticalLayout_2->addWidget(TransDetail_2);

        splitter->addWidget(layoutWidget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        AServer->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(AServer);
        statusbar->setObjectName("statusbar");
        AServer->setStatusBar(statusbar);
        toolBar = new QToolBar(AServer);
        toolBar->setObjectName("toolBar");
        toolBar->setMovable(false);
        toolBar->setAllowedAreas(Qt::ToolBarArea::TopToolBarArea);
        toolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
        AServer->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionListen);
        toolBar->addAction(actionDisConnect);
        toolBar->addAction(actionSetSavePath);
        toolBar->addAction(actionHelp);

        retranslateUi(AServer);

        QMetaObject::connectSlotsByName(AServer);
    } // setupUi

    void retranslateUi(QMainWindow *AServer)
    {
        AServer->setWindowTitle(QCoreApplication::translate("AServer", "\346\216\245\346\224\266\346\226\271", nullptr));
        actionListen->setText(QCoreApplication::translate("AServer", "\347\233\221\345\220\254", nullptr));
#if QT_CONFIG(tooltip)
        actionListen->setToolTip(QCoreApplication::translate("AServer", "\347\255\211\345\276\205\346\226\271\351\200\201\346\226\271\344\274\240\350\276\223.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDisConnect->setText(QCoreApplication::translate("AServer", "\346\226\255\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        actionDisConnect->setToolTip(QCoreApplication::translate("AServer", "\346\226\255\345\274\200\344\270\216\345\217\221\351\200\201\346\226\271\347\232\204\350\277\236\346\216\245.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelp->setText(QCoreApplication::translate("AServer", "\345\270\256\345\212\251", nullptr));
#if QT_CONFIG(tooltip)
        actionHelp->setToolTip(QCoreApplication::translate("AServer", "\346\237\245\347\234\213\344\275\277\347\224\250\350\257\264\346\230\216.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSetSavePath->setText(QCoreApplication::translate("AServer", "\350\256\276\347\275\256\346\216\245\346\224\266\350\267\257\345\276\204", nullptr));
#if QT_CONFIG(tooltip)
        actionSetSavePath->setToolTip(QCoreApplication::translate("AServer", "\345\217\221\351\200\201\346\226\271\345\217\221\351\200\201\346\235\245\347\232\204\346\226\207\344\273\266\345\255\230\345\234\250\346\255\244\350\267\257\345\276\204\344\270\213.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpenFile->setText(QCoreApplication::translate("AServer", "\346\211\223\345\274\200(&o)", nullptr));
#if QT_CONFIG(tooltip)
        actionOpenFile->setToolTip(QCoreApplication::translate("AServer", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpenPath->setText(QCoreApplication::translate("AServer", "\346\211\223\345\274\200\350\267\257\345\276\204", nullptr));
#if QT_CONFIG(tooltip)
        actionOpenPath->setToolTip(QCoreApplication::translate("AServer", "\346\211\223\345\274\200\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCopyAbsoultPath->setText(QCoreApplication::translate("AServer", "\345\244\215\345\210\266\345\256\214\346\225\264\350\267\257\345\276\204\345\222\214\346\226\207\344\273\266\345\220\215", nullptr));
#if QT_CONFIG(tooltip)
        actionCopyAbsoultPath->setToolTip(QCoreApplication::translate("AServer", "\345\244\215\345\210\266AboslutePath", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("AServer", "\346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
        label_3->setText(QCoreApplication::translate("AServer", "\344\274\240\350\276\223\350\257\246\346\203\205", nullptr));
        lb1->setText(QCoreApplication::translate("AServer", "\347\212\266\346\200\201\357\274\232", nullptr));
        lbStatus->setText(QCoreApplication::translate("AServer", "\347\255\211\345\276\205\344\270\255...", nullptr));
        lb2->setText(QCoreApplication::translate("AServer", "\345\275\223\345\211\215\346\226\207\344\273\266\357\274\232", nullptr));
        lbCurFile->setText(QCoreApplication::translate("AServer", "\347\255\211\345\276\205\344\270\255...", nullptr));
        lb3->setText(QCoreApplication::translate("AServer", "\345\244\247\345\260\217\357\274\232", nullptr));
        lbSize->setText(QCoreApplication::translate("AServer", "\347\255\211\345\276\205\344\270\255...", nullptr));
        lb4->setText(QCoreApplication::translate("AServer", "\351\200\237\345\272\246\357\274\232", nullptr));
        lbSpeed->setText(QCoreApplication::translate("AServer", "\347\255\211\345\276\205\344\270\255...", nullptr));
        lb5->setText(QCoreApplication::translate("AServer", "\351\242\204\350\256\241\345\211\251\344\275\231\346\227\266\351\227\264\357\274\232", nullptr));
        lbRemaingTime->setText(QCoreApplication::translate("AServer", "\347\255\211\345\276\205\344\270\255...", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("AServer", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AServer: public Ui_AServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASERVER_H
