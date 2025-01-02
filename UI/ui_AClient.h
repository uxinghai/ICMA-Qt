/********************************************************************************
** Form generated from reading UI file 'AClient.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACLIENT_H
#define UI_ACLIENT_H

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

class Ui_AClient
{
public:
    QAction *actionSend;
    QAction *actionDisConnect;
    QAction *actionHelp;
    QAction *actionAdd;
    QAction *actionRemove;
    QAction *actionClearList;
    QAction *actionConnect;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *FileListWidget;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QWidget *TransDetail;
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

    void setupUi(QMainWindow *AClient)
    {
        if (AClient->objectName().isEmpty())
            AClient->setObjectName("AClient");
        AClient->resize(640, 450);
        AClient->setMinimumSize(QSize(640, 450));
        AClient->setMaximumSize(QSize(660, 450));
        QFont font;
        font.setPointSize(11);
        AClient->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/transfer/res/transfer/fileTrans.png"), QSize(), QIcon::Normal, QIcon::Off);
        AClient->setWindowIcon(icon);
        AClient->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        actionSend = new QAction(AClient);
        actionSend->setObjectName("actionSend");
        actionSend->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/transfer/res/transfer/tranStart.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSend->setIcon(icon1);
        actionSend->setFont(font);
        actionSend->setMenuRole(QAction::MenuRole::NoRole);
        actionDisConnect = new QAction(AClient);
        actionDisConnect->setObjectName("actionDisConnect");
        actionDisConnect->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/transfer/res/transfer/disConnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisConnect->setIcon(icon2);
        actionDisConnect->setFont(font);
        actionDisConnect->setMenuRole(QAction::MenuRole::NoRole);
        actionHelp = new QAction(AClient);
        actionHelp->setObjectName("actionHelp");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/transfer/res/transfer/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon3);
        actionHelp->setFont(font);
        actionHelp->setMenuRole(QAction::MenuRole::NoRole);
        actionAdd = new QAction(AClient);
        actionAdd->setObjectName("actionAdd");
        actionAdd->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/transfer/res/transfer/addFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd->setIcon(icon4);
        actionAdd->setFont(font);
        actionAdd->setMenuRole(QAction::MenuRole::NoRole);
        actionRemove = new QAction(AClient);
        actionRemove->setObjectName("actionRemove");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/transfer/res/transfer/removeFileFromList.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemove->setIcon(icon5);
        actionRemove->setMenuRole(QAction::MenuRole::NoRole);
        actionClearList = new QAction(AClient);
        actionClearList->setObjectName("actionClearList");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/transfer/res/transfer/clearList.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClearList->setIcon(icon6);
        actionClearList->setMenuRole(QAction::MenuRole::NoRole);
        actionConnect = new QAction(AClient);
        actionConnect->setObjectName("actionConnect");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/transfer/res/transfer/Connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon7);
        actionConnect->setFont(font);
        actionConnect->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(AClient);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 24));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        FileListWidget = new QListWidget(layoutWidget);
        FileListWidget->setObjectName("FileListWidget");
        FileListWidget->setMaximumSize(QSize(350, 16777215));
        FileListWidget->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        FileListWidget->setFrameShape(QFrame::Shape::NoFrame);
        FileListWidget->setFrameShadow(QFrame::Shadow::Plain);
        FileListWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        FileListWidget->setDragEnabled(false);
        FileListWidget->setDragDropMode(QAbstractItemView::DragDropMode::NoDragDrop);
        FileListWidget->setDefaultDropAction(Qt::DropAction::IgnoreAction);
        FileListWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        FileListWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        FileListWidget->setProperty("isWrapping", QVariant(false));

        verticalLayout->addWidget(FileListWidget);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(16777215, 24));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        TransDetail = new QWidget(layoutWidget1);
        TransDetail->setObjectName("TransDetail");
        TransDetail->setMinimumSize(QSize(250, 0));
        TransDetail->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    border: 1px solid;\n"
"}\n"
"\n"
"QLabel {\n"
"    border: none;  /* \347\241\256\344\277\235 QLabel \347\232\204\350\276\271\346\241\206\344\270\215\350\242\253\344\277\256\346\224\271 */\n"
"}\n"
""));
        formLayout = new QFormLayout(TransDetail);
        formLayout->setObjectName("formLayout");
        formLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        formLayout->setHorizontalSpacing(5);
        formLayout->setVerticalSpacing(5);
        formLayout->setContentsMargins(-1, -1, -1, 0);
        lb1 = new QLabel(TransDetail);
        lb1->setObjectName("lb1");
        lb1->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, lb1);

        lbStatus = new QLabel(TransDetail);
        lbStatus->setObjectName("lbStatus");
        lbStatus->setFont(font);

        formLayout->setWidget(0, QFormLayout::FieldRole, lbStatus);

        lb2 = new QLabel(TransDetail);
        lb2->setObjectName("lb2");
        lb2->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, lb2);

        lbCurFile = new QLabel(TransDetail);
        lbCurFile->setObjectName("lbCurFile");
        lbCurFile->setFont(font);

        formLayout->setWidget(1, QFormLayout::FieldRole, lbCurFile);

        lb3 = new QLabel(TransDetail);
        lb3->setObjectName("lb3");
        lb3->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, lb3);

        lbSize = new QLabel(TransDetail);
        lbSize->setObjectName("lbSize");
        lbSize->setFont(font);

        formLayout->setWidget(2, QFormLayout::FieldRole, lbSize);

        lb4 = new QLabel(TransDetail);
        lb4->setObjectName("lb4");
        lb4->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, lb4);

        lbSpeed = new QLabel(TransDetail);
        lbSpeed->setObjectName("lbSpeed");
        lbSpeed->setFont(font);

        formLayout->setWidget(3, QFormLayout::FieldRole, lbSpeed);

        lb5 = new QLabel(TransDetail);
        lb5->setObjectName("lb5");
        lb5->setFont(font);

        formLayout->setWidget(4, QFormLayout::LabelRole, lb5);

        lbRemaingTime = new QLabel(TransDetail);
        lbRemaingTime->setObjectName("lbRemaingTime");
        lbRemaingTime->setFont(font);

        formLayout->setWidget(4, QFormLayout::FieldRole, lbRemaingTime);


        verticalLayout_2->addWidget(TransDetail);

        splitter->addWidget(layoutWidget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        AClient->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(AClient);
        statusbar->setObjectName("statusbar");
        AClient->setStatusBar(statusbar);
        toolBar = new QToolBar(AClient);
        toolBar->setObjectName("toolBar");
        toolBar->setMovable(false);
        toolBar->setAllowedAreas(Qt::ToolBarArea::TopToolBarArea);
        toolBar->setIconSize(QSize(25, 25));
        toolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
        AClient->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionConnect);
        toolBar->addAction(actionDisConnect);
        toolBar->addAction(actionAdd);
        toolBar->addAction(actionSend);
        toolBar->addAction(actionHelp);

        retranslateUi(AClient);

        QMetaObject::connectSlotsByName(AClient);
    } // setupUi

    void retranslateUi(QMainWindow *AClient)
    {
        AClient->setWindowTitle(QCoreApplication::translate("AClient", "\345\217\221\351\200\201\346\226\271", nullptr));
        actionSend->setText(QCoreApplication::translate("AClient", "\345\217\221\351\200\201", nullptr));
#if QT_CONFIG(tooltip)
        actionSend->setToolTip(QCoreApplication::translate("AClient", "\345\274\200\345\247\213\345\217\221\351\200\201.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDisConnect->setText(QCoreApplication::translate("AClient", "\346\226\255\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        actionDisConnect->setToolTip(QCoreApplication::translate("AClient", "\346\226\255\345\274\200\344\270\216\346\216\245\346\224\266\346\226\271\347\232\204\350\277\236\346\216\245.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelp->setText(QCoreApplication::translate("AClient", "\345\270\256\345\212\251", nullptr));
#if QT_CONFIG(tooltip)
        actionHelp->setToolTip(QCoreApplication::translate("AClient", "\346\237\245\347\234\213\344\275\277\347\224\250\350\257\264\346\230\216.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAdd->setText(QCoreApplication::translate("AClient", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionAdd->setToolTip(QCoreApplication::translate("AClient", "\346\267\273\345\212\240\346\226\207\344\273\266\345\210\260\345\210\227\350\241\250.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRemove->setText(QCoreApplication::translate("AClient", "\347\247\273\351\231\244\350\277\231\346\235\241", nullptr));
        actionClearList->setText(QCoreApplication::translate("AClient", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
        actionConnect->setText(QCoreApplication::translate("AClient", "\350\277\236\346\216\245", nullptr));
#if QT_CONFIG(tooltip)
        actionConnect->setToolTip(QCoreApplication::translate("AClient", "\350\277\236\346\216\245\345\210\260\346\216\245\346\224\266\346\226\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("AClient", "\346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
        label_2->setText(QCoreApplication::translate("AClient", "\344\274\240\350\276\223\350\257\246\346\203\205", nullptr));
        lb1->setText(QCoreApplication::translate("AClient", "\347\212\266\346\200\201\357\274\232", nullptr));
        lbStatus->setText(QCoreApplication::translate("AClient", "\347\255\211\345\276\205\344\270\255...", nullptr));
        lb2->setText(QCoreApplication::translate("AClient", "\345\275\223\345\211\215\346\226\207\344\273\266\357\274\232", nullptr));
        lbCurFile->setText(QCoreApplication::translate("AClient", "\347\255\211\345\276\205\344\270\255...", nullptr));
        lb3->setText(QCoreApplication::translate("AClient", "\345\244\247\345\260\217\357\274\232", nullptr));
        lbSize->setText(QCoreApplication::translate("AClient", "\347\255\211\345\276\205\344\270\255...", nullptr));
        lb4->setText(QCoreApplication::translate("AClient", "\351\200\237\345\272\246\357\274\232", nullptr));
        lbSpeed->setText(QCoreApplication::translate("AClient", "\347\255\211\345\276\205\344\270\255...", nullptr));
        lb5->setText(QCoreApplication::translate("AClient", "\351\242\204\350\256\241\345\211\251\344\275\231\346\227\266\351\227\264\357\274\232", nullptr));
        lbRemaingTime->setText(QCoreApplication::translate("AClient", "\347\255\211\345\276\205\344\270\255...", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("AClient", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AClient: public Ui_AClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACLIENT_H
