/********************************************************************************
** Form generated from reading UI file 'FaceTest.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACETEST_H
#define UI_FACETEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceTest
{
public:
    QAction *actionCloseCamera;
    QAction *actionOpenCamera;
    QAction *actionSlip;
    QAction *actionDetect;
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
    QLabel *lbCamera;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FaceTest)
    {
        if (FaceTest->objectName().isEmpty())
            FaceTest->setObjectName("FaceTest");
        FaceTest->resize(800, 600);
        FaceTest->setMinimumSize(QSize(800, 600));
        FaceTest->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setPointSize(11);
        FaceTest->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/faceTest.png"), QSize(), QIcon::Normal, QIcon::Off);
        FaceTest->setWindowIcon(icon);
        actionCloseCamera = new QAction(FaceTest);
        actionCloseCamera->setObjectName("actionCloseCamera");
        actionCloseCamera->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ps/res/ps/cameraClose.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCloseCamera->setIcon(icon1);
        actionOpenCamera = new QAction(FaceTest);
        actionOpenCamera->setObjectName("actionOpenCamera");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ps/res/ps/camera_C.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenCamera->setIcon(icon2);
        actionOpenCamera->setMenuRole(QAction::NoRole);
        actionOpenCamera->setIconVisibleInMenu(true);
        actionSlip = new QAction(FaceTest);
        actionSlip->setObjectName("actionSlip");
        actionSlip->setCheckable(true);
        actionSlip->setChecked(true);
        actionSlip->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ps/res/ps/cameraSlip.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSlip->setIcon(icon3);
        actionSlip->setMenuRole(QAction::NoRole);
        actionDetect = new QAction(FaceTest);
        actionDetect->setObjectName("actionDetect");
        actionDetect->setIcon(icon);
        actionDetect->setVisible(false);
        actionDetect->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(FaceTest);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        lbCamera = new QLabel(centralwidget);
        lbCamera->setObjectName("lbCamera");
        lbCamera->setMinimumSize(QSize(500, 0));
        lbCamera->setFrameShape(QFrame::NoFrame);
        lbCamera->setScaledContents(true);
        lbCamera->setAlignment(Qt::AlignCenter);
        lbCamera->setTextInteractionFlags(Qt::NoTextInteraction);

        mainLayout->addWidget(lbCamera);

        FaceTest->setCentralWidget(centralwidget);
        toolBar = new QToolBar(FaceTest);
        toolBar->setObjectName("toolBar");
        toolBar->setFont(font);
        toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea|Qt::TopToolBarArea);
        toolBar->setIconSize(QSize(24, 24));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolBar->setFloatable(false);
        FaceTest->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(FaceTest);
        statusBar->setObjectName("statusBar");
        FaceTest->setStatusBar(statusBar);

        toolBar->addAction(actionOpenCamera);
        toolBar->addAction(actionDetect);
        toolBar->addAction(actionCloseCamera);
        toolBar->addSeparator();
        toolBar->addAction(actionSlip);
        toolBar->addSeparator();

        retranslateUi(FaceTest);

        QMetaObject::connectSlotsByName(FaceTest);
    } // setupUi

    void retranslateUi(QMainWindow *FaceTest)
    {
        FaceTest->setWindowTitle(QCoreApplication::translate("FaceTest", "\344\272\272\350\204\270\344\277\241\346\201\257\346\243\200\346\265\213", nullptr));
        actionCloseCamera->setText(QCoreApplication::translate("FaceTest", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", nullptr));
#if QT_CONFIG(tooltip)
        actionCloseCamera->setToolTip(QCoreApplication::translate("FaceTest", "\346\211\223\345\274\200/\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpenCamera->setText(QCoreApplication::translate("FaceTest", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
        actionSlip->setText(QCoreApplication::translate("FaceTest", "\351\225\234\345\203\217", nullptr));
        actionDetect->setText(QCoreApplication::translate("FaceTest", "\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
        lbCamera->setText(QString());
        toolBar->setWindowTitle(QCoreApplication::translate("FaceTest", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FaceTest: public Ui_FaceTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACETEST_H
