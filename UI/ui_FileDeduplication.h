/********************************************************************************
** Form generated from reading UI file 'FileDeduplication.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEDEDUPLICATION_H
#define UI_FILEDEDUPLICATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileDeduplication
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lePath;
    QPushButton *btnBrowse;
    QGroupBox *optionsGroup;
    QGridLayout *gridLayout;
    QCheckBox *subfolderCheck;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *keepFirstCheck;
    QCheckBox *handCheck;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QPushButton *btnScan;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *toolBtnAllSelect;
    QToolButton *toolBtnCancelSelect;
    QToolButton *toolBtnReverse;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *resultTable;
    QHBoxLayout *horizontalLayout_2;
    QLabel *statusLabel;
    QProgressBar *progressBar;
    QPushButton *btnDelete;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *FileDeduplication)
    {
        if (FileDeduplication->objectName().isEmpty())
            FileDeduplication->setObjectName("FileDeduplication");
        FileDeduplication->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/deduplicate.png"), QSize(), QIcon::Normal, QIcon::Off);
        FileDeduplication->setWindowIcon(icon);
        actionExit = new QAction(FileDeduplication);
        actionExit->setObjectName("actionExit");
        actionAbout = new QAction(FileDeduplication);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(FileDeduplication);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lePath = new QLineEdit(centralwidget);
        lePath->setObjectName("lePath");

        horizontalLayout->addWidget(lePath);

        btnBrowse = new QPushButton(centralwidget);
        btnBrowse->setObjectName("btnBrowse");

        horizontalLayout->addWidget(btnBrowse);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        optionsGroup = new QGroupBox(centralwidget);
        optionsGroup->setObjectName("optionsGroup");
        gridLayout = new QGridLayout(optionsGroup);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(5, 3, 3, 0);
        subfolderCheck = new QCheckBox(optionsGroup);
        subfolderCheck->setObjectName("subfolderCheck");
        subfolderCheck->setChecked(true);

        gridLayout->addWidget(subfolderCheck, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        keepFirstCheck = new QCheckBox(optionsGroup);
        keepFirstCheck->setObjectName("keepFirstCheck");
        keepFirstCheck->setChecked(true);
        keepFirstCheck->setAutoExclusive(true);

        horizontalLayout_3->addWidget(keepFirstCheck);

        handCheck = new QCheckBox(optionsGroup);
        handCheck->setObjectName("handCheck");
        handCheck->setAutoExclusive(true);

        horizontalLayout_3->addWidget(handCheck);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_2 = new QLabel(optionsGroup);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        gridLayout_2->addWidget(optionsGroup, 1, 0, 1, 1);

        btnScan = new QPushButton(centralwidget);
        btnScan->setObjectName("btnScan");

        gridLayout_2->addWidget(btnScan, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        toolBtnAllSelect = new QToolButton(centralwidget);
        toolBtnAllSelect->setObjectName("toolBtnAllSelect");
        toolBtnAllSelect->setAutoRaise(true);

        horizontalLayout_4->addWidget(toolBtnAllSelect);

        toolBtnCancelSelect = new QToolButton(centralwidget);
        toolBtnCancelSelect->setObjectName("toolBtnCancelSelect");
        toolBtnCancelSelect->setAutoRaise(true);

        horizontalLayout_4->addWidget(toolBtnCancelSelect);

        toolBtnReverse = new QToolButton(centralwidget);
        toolBtnReverse->setObjectName("toolBtnReverse");
        toolBtnReverse->setAutoRaise(true);

        horizontalLayout_4->addWidget(toolBtnReverse);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        resultTable = new QTableWidget(centralwidget);
        if (resultTable->columnCount() < 5)
            resultTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        resultTable->setObjectName("resultTable");
        resultTable->setAlternatingRowColors(true);
        resultTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        resultTable->setColumnCount(5);
        resultTable->horizontalHeader()->setDefaultSectionSize(120);
        resultTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        resultTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout_2->addWidget(resultTable, 4, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        horizontalLayout_2->addWidget(statusLabel);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(0, 15));
        progressBar->setMaximumSize(QSize(16777215, 15));
        progressBar->setValue(0);

        horizontalLayout_2->addWidget(progressBar);

        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setEnabled(false);

        horizontalLayout_2->addWidget(btnDelete);


        gridLayout_2->addLayout(horizontalLayout_2, 5, 0, 1, 1);

        FileDeduplication->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(FileDeduplication);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        FileDeduplication->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionAbout);
        menu->addAction(actionExit);

        retranslateUi(FileDeduplication);

        QMetaObject::connectSlotsByName(FileDeduplication);
    } // setupUi

    void retranslateUi(QMainWindow *FileDeduplication)
    {
        FileDeduplication->setWindowTitle(QCoreApplication::translate("FileDeduplication", "\346\226\207\344\273\266\345\216\273\351\207\215\345\267\245\345\205\267", nullptr));
        actionExit->setText(QCoreApplication::translate("FileDeduplication", "\351\200\200\345\207\272", nullptr));
        actionAbout->setText(QCoreApplication::translate("FileDeduplication", "\345\205\263\344\272\216", nullptr));
        lePath->setPlaceholderText(QCoreApplication::translate("FileDeduplication", "\350\257\267\351\200\211\346\213\251\350\246\201\346\211\253\346\217\217\347\232\204\346\226\207\344\273\266\345\244\271\350\267\257\345\276\204...", nullptr));
        btnBrowse->setText(QCoreApplication::translate("FileDeduplication", "\346\265\217\350\247\210...", nullptr));
        optionsGroup->setTitle(QCoreApplication::translate("FileDeduplication", "\346\211\253\346\217\217\351\200\211\351\241\271", nullptr));
#if QT_CONFIG(tooltip)
        subfolderCheck->setToolTip(QCoreApplication::translate("FileDeduplication", "\345\213\276\351\200\211\346\255\244\351\241\271\350\241\250\347\244\272\346\211\253\346\217\217\346\227\266\345\220\214\346\227\266\346\211\253\346\217\217\345\205\266\345\255\220\346\226\207\344\273\266\345\244\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        subfolderCheck->setText(QCoreApplication::translate("FileDeduplication", "\345\214\205\345\220\253\345\255\220\346\226\207\344\273\266\345\244\271", nullptr));
#if QT_CONFIG(tooltip)
        keepFirstCheck->setToolTip(QCoreApplication::translate("FileDeduplication", "\345\213\276\351\200\211\346\255\244\351\241\271\350\241\250\347\244\272\345\210\240\351\231\244\344\272\244\346\226\260\347\232\204\351\207\215\345\244\215\351\241\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        keepFirstCheck->setText(QCoreApplication::translate("FileDeduplication", "\344\277\235\347\225\231\346\234\200\346\227\251\347\232\204\346\226\207\344\273\266", nullptr));
        handCheck->setText(QCoreApplication::translate("FileDeduplication", "\346\211\213\345\212\250\351\200\211\346\213\251", nullptr));
        label_2->setText(QCoreApplication::translate("FileDeduplication", "\345\223\210\345\270\214\345\200\274\344\270\200\350\207\264\350\241\250\347\244\272\346\226\207\344\273\266\345\256\214\345\205\250\347\233\270\345\220\214", nullptr));
        btnScan->setText(QCoreApplication::translate("FileDeduplication", "\345\274\200\345\247\213\346\211\253\346\217\217", nullptr));
        toolBtnAllSelect->setText(QCoreApplication::translate("FileDeduplication", "\345\205\250\351\200\211", nullptr));
        toolBtnCancelSelect->setText(QCoreApplication::translate("FileDeduplication", "\345\217\226\346\266\210\345\205\250\351\200\211", nullptr));
        toolBtnReverse->setText(QCoreApplication::translate("FileDeduplication", "\345\217\215\351\200\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem = resultTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("FileDeduplication", "\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = resultTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("FileDeduplication", "\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = resultTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("FileDeduplication", "\346\226\207\344\273\266\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = resultTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("FileDeduplication", "\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = resultTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("FileDeduplication", "\345\223\210\345\270\214\345\200\274", nullptr));
        statusLabel->setText(QCoreApplication::translate("FileDeduplication", "\345\260\261\347\273\252", nullptr));
        btnDelete->setText(QCoreApplication::translate("FileDeduplication", "\345\210\240\351\231\244\351\207\215\345\244\215\346\226\207\344\273\266", nullptr));
        menu->setTitle(QCoreApplication::translate("FileDeduplication", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileDeduplication: public Ui_FileDeduplication {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEDEDUPLICATION_H
