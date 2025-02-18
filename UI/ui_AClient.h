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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AClient
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionAddFiles;
    QAction *actionSend;
    QAction *actionHelp;
    QAction *actionRemoveFile;
    QAction *actionClearList;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *mainSplitter;
    QWidget *fileListContainer;
    QVBoxLayout *verticalLayout;
    QGroupBox *fileListGroup;
    QVBoxLayout *verticalLayout_4;
    QListWidget *fileListWidget;
    QWidget *transferDetailsContainer;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *transferDetailsGroup;
    QVBoxLayout *verticalLayout_5;
    QWidget *detailsWidget;
    QGridLayout *gridLayout;
    QLabel *statusLabel;
    QLabel *statusValue;
    QLabel *currentFileLabel;
    QLabel *currentFileValue;
    QLabel *sizeLabel;
    QLabel *sizeValue;
    QLabel *speedLabel;
    QLabel *speedValue;
    QLabel *remainingTimeLabel;
    QLabel *remainingTimeValue;
    QProgressBar *progressBar;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AClient)
    {
        if (AClient->objectName().isEmpty())
            AClient->setObjectName("AClient");
        AClient->resize(800, 600);
        AClient->setMinimumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/transfer/res/transfer/fileTrans.png"), QSize(), QIcon::Normal, QIcon::Off);
        AClient->setWindowIcon(icon);
        actionConnect = new QAction(AClient);
        actionConnect->setObjectName("actionConnect");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/transfer/res/transfer/Connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon1);
        actionDisconnect = new QAction(AClient);
        actionDisconnect->setObjectName("actionDisconnect");
        actionDisconnect->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/transfer/res/transfer/disConnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon2);
        actionAddFiles = new QAction(AClient);
        actionAddFiles->setObjectName("actionAddFiles");
        actionAddFiles->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/transfer/res/transfer/addFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddFiles->setIcon(icon3);
        actionSend = new QAction(AClient);
        actionSend->setObjectName("actionSend");
        actionSend->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/transfer/res/transfer/tranStart.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSend->setIcon(icon4);
        actionHelp = new QAction(AClient);
        actionHelp->setObjectName("actionHelp");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/transfer/res/transfer/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon5);
        actionRemoveFile = new QAction(AClient);
        actionRemoveFile->setObjectName("actionRemoveFile");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/transfer/res/transfer/removeFileFromList.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemoveFile->setIcon(icon6);
        actionClearList = new QAction(AClient);
        actionClearList->setObjectName("actionClearList");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/transfer/res/transfer/clearList.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClearList->setIcon(icon7);
        centralwidget = new QWidget(AClient);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        mainSplitter = new QSplitter(centralwidget);
        mainSplitter->setObjectName("mainSplitter");
        mainSplitter->setOrientation(Qt::Horizontal);
        fileListContainer = new QWidget(mainSplitter);
        fileListContainer->setObjectName("fileListContainer");
        verticalLayout = new QVBoxLayout(fileListContainer);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        fileListGroup = new QGroupBox(fileListContainer);
        fileListGroup->setObjectName("fileListGroup");
        verticalLayout_4 = new QVBoxLayout(fileListGroup);
        verticalLayout_4->setObjectName("verticalLayout_4");
        fileListWidget = new QListWidget(fileListGroup);
        fileListWidget->setObjectName("fileListWidget");
        fileListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        fileListWidget->setDragEnabled(true);
        fileListWidget->setDragDropMode(QAbstractItemView::DragDrop);
        fileListWidget->setDefaultDropAction(Qt::CopyAction);
        fileListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        fileListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_4->addWidget(fileListWidget);


        verticalLayout->addWidget(fileListGroup);

        mainSplitter->addWidget(fileListContainer);
        transferDetailsContainer = new QWidget(mainSplitter);
        transferDetailsContainer->setObjectName("transferDetailsContainer");
        verticalLayout_2 = new QVBoxLayout(transferDetailsContainer);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        transferDetailsGroup = new QGroupBox(transferDetailsContainer);
        transferDetailsGroup->setObjectName("transferDetailsGroup");
        verticalLayout_5 = new QVBoxLayout(transferDetailsGroup);
        verticalLayout_5->setObjectName("verticalLayout_5");
        detailsWidget = new QWidget(transferDetailsGroup);
        detailsWidget->setObjectName("detailsWidget");
        gridLayout = new QGridLayout(detailsWidget);
        gridLayout->setObjectName("gridLayout");
        statusLabel = new QLabel(detailsWidget);
        statusLabel->setObjectName("statusLabel");

        gridLayout->addWidget(statusLabel, 0, 0, 1, 1);

        statusValue = new QLabel(detailsWidget);
        statusValue->setObjectName("statusValue");

        gridLayout->addWidget(statusValue, 0, 1, 1, 1);

        currentFileLabel = new QLabel(detailsWidget);
        currentFileLabel->setObjectName("currentFileLabel");

        gridLayout->addWidget(currentFileLabel, 1, 0, 1, 1);

        currentFileValue = new QLabel(detailsWidget);
        currentFileValue->setObjectName("currentFileValue");
        currentFileValue->setWordWrap(true);

        gridLayout->addWidget(currentFileValue, 1, 1, 1, 1);

        sizeLabel = new QLabel(detailsWidget);
        sizeLabel->setObjectName("sizeLabel");

        gridLayout->addWidget(sizeLabel, 2, 0, 1, 1);

        sizeValue = new QLabel(detailsWidget);
        sizeValue->setObjectName("sizeValue");

        gridLayout->addWidget(sizeValue, 2, 1, 1, 1);

        speedLabel = new QLabel(detailsWidget);
        speedLabel->setObjectName("speedLabel");

        gridLayout->addWidget(speedLabel, 3, 0, 1, 1);

        speedValue = new QLabel(detailsWidget);
        speedValue->setObjectName("speedValue");

        gridLayout->addWidget(speedValue, 3, 1, 1, 1);

        remainingTimeLabel = new QLabel(detailsWidget);
        remainingTimeLabel->setObjectName("remainingTimeLabel");

        gridLayout->addWidget(remainingTimeLabel, 4, 0, 1, 1);

        remainingTimeValue = new QLabel(detailsWidget);
        remainingTimeValue->setObjectName("remainingTimeValue");

        gridLayout->addWidget(remainingTimeValue, 4, 1, 1, 1);

        progressBar = new QProgressBar(detailsWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 5, 0, 1, 2);


        verticalLayout_5->addWidget(detailsWidget);


        verticalLayout_2->addWidget(transferDetailsGroup);

        mainSplitter->addWidget(transferDetailsContainer);

        verticalLayout_3->addWidget(mainSplitter);

        AClient->setCentralWidget(centralwidget);
        toolBar = new QToolBar(AClient);
        toolBar->setObjectName("toolBar");
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(24, 24));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        AClient->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(AClient);
        statusBar->setObjectName("statusBar");
        AClient->setStatusBar(statusBar);

        toolBar->addAction(actionConnect);
        toolBar->addAction(actionDisconnect);
        toolBar->addSeparator();
        toolBar->addAction(actionAddFiles);
        toolBar->addAction(actionSend);
        toolBar->addSeparator();
        toolBar->addAction(actionHelp);

        retranslateUi(AClient);

        QMetaObject::connectSlotsByName(AClient);
    } // setupUi

    void retranslateUi(QMainWindow *AClient)
    {
        AClient->setWindowTitle(QCoreApplication::translate("AClient", "\345\217\221\351\200\201\347\253\257", nullptr));
        actionConnect->setText(QCoreApplication::translate("AClient", "\350\277\236\346\216\245", nullptr));
#if QT_CONFIG(tooltip)
        actionConnect->setToolTip(QCoreApplication::translate("AClient", "\350\277\236\346\216\245\345\210\260\346\216\245\346\224\266\346\226\271", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDisconnect->setText(QCoreApplication::translate("AClient", "\346\226\255\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        actionDisconnect->setToolTip(QCoreApplication::translate("AClient", "\346\226\255\345\274\200\344\270\216\346\216\245\346\224\266\346\226\271\347\232\204\350\277\236\346\216\245", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAddFiles->setText(QCoreApplication::translate("AClient", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionAddFiles->setToolTip(QCoreApplication::translate("AClient", "\346\267\273\345\212\240\346\226\207\344\273\266\345\210\260\345\217\221\351\200\201\345\210\227\350\241\250", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSend->setText(QCoreApplication::translate("AClient", "\345\217\221\351\200\201", nullptr));
#if QT_CONFIG(tooltip)
        actionSend->setToolTip(QCoreApplication::translate("AClient", "\345\274\200\345\247\213\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelp->setText(QCoreApplication::translate("AClient", "\345\270\256\345\212\251", nullptr));
#if QT_CONFIG(tooltip)
        actionHelp->setToolTip(QCoreApplication::translate("AClient", "\346\237\245\347\234\213\344\275\277\347\224\250\350\257\264\346\230\216", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRemoveFile->setText(QCoreApplication::translate("AClient", "\347\247\273\351\231\244\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionRemoveFile->setToolTip(QCoreApplication::translate("AClient", "\344\273\216\345\210\227\350\241\250\344\270\255\347\247\273\351\231\244\351\200\211\344\270\255\347\232\204\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionClearList->setText(QCoreApplication::translate("AClient", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
#if QT_CONFIG(tooltip)
        actionClearList->setToolTip(QCoreApplication::translate("AClient", "\346\270\205\347\251\272\346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
#endif // QT_CONFIG(tooltip)
        fileListGroup->setTitle(QCoreApplication::translate("AClient", "\346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
        transferDetailsGroup->setTitle(QCoreApplication::translate("AClient", "\344\274\240\350\276\223\350\257\246\346\203\205", nullptr));
        statusLabel->setText(QCoreApplication::translate("AClient", "\347\212\266\346\200\201\357\274\232", nullptr));
        statusValue->setText(QCoreApplication::translate("AClient", "\346\234\252\350\277\236\346\216\245", nullptr));
        currentFileLabel->setText(QCoreApplication::translate("AClient", "\345\275\223\345\211\215\346\226\207\344\273\266\357\274\232", nullptr));
        currentFileValue->setText(QCoreApplication::translate("AClient", "\346\227\240", nullptr));
        sizeLabel->setText(QCoreApplication::translate("AClient", "\346\226\207\344\273\266\345\244\247\345\260\217\357\274\232", nullptr));
        sizeValue->setText(QCoreApplication::translate("AClient", "0 B", nullptr));
        speedLabel->setText(QCoreApplication::translate("AClient", "\344\274\240\350\276\223\351\200\237\345\272\246\357\274\232", nullptr));
        speedValue->setText(QCoreApplication::translate("AClient", "0 B/s", nullptr));
        remainingTimeLabel->setText(QCoreApplication::translate("AClient", "\345\211\251\344\275\231\346\227\266\351\227\264\357\274\232", nullptr));
        remainingTimeValue->setText(QCoreApplication::translate("AClient", "--:--:--", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("AClient", "\345\267\245\345\205\267\346\240\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AClient: public Ui_AClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACLIENT_H
