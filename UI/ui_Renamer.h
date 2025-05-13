/********************************************************************************
** Form generated from reading UI file 'Renamer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENAMER_H
#define UI_RENAMER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Renamer
{
public:
    QAction *actionAddFile;
    QAction *actionAddFileFormDir;
    QAction *actionClearFileList;
    QAction *actionUndoRename;
    QAction *actionFileOpenExplore;
    QAction *actionFileCopyName;
    QAction *actionFileCopyNewName;
    QAction *actionFileCopyPath;
    QAction *actionFileCopyAbsPath;
    QAction *actionRemoveList;
    QAction *actionClearList;
    QAction *actionFileOpen;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QRadioButton *radioButtonAllCase;
    QRadioButton *radioButtonRan;
    QRadioButton *radioButtonNumUp;
    QRadioButton *radioButtonNoCase;
    QRadioButton *radioButtonNo;
    QRadioButton *radioButtonFirstCase;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_2;
    QRadioButton *radioButtonSuffAllCase;
    QRadioButton *radioButtonSuffNoCase;
    QRadioButton *radioButtonSuffNo;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBoxSuffix;
    QWidget *tab_2;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBoxSouce;
    QLabel *label_4;
    QComboBox *comboBoxDest;
    QCheckBox *checkBoxCase;
    QWidget *tab_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *comboBoxPreFix;
    QComboBox *comboBoxTxt;
    QComboBox *comboBox_11;
    QCheckBox *checkBox_4;
    QSpinBox *spinBox;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QComboBox *comboBoxSuffix_2;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QComboBox *comboBox_8;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QComboBox *comboBox_9;
    QWidget *tab_4;
    QCheckBox *checkBox_5;
    QComboBox *comboBox_12;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QSpinBox *spinBox_2;
    QComboBox *comboBox_13;
    QComboBox *comboBox_14;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_15;
    QSpinBox *spinBox_3;
    QLabel *label_17;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_16;
    QSpinBox *spinBox_4;
    QLabel *label_18;
    QCheckBox *checkBox_11;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tab_5;
    QCheckBox *checkBox_12;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_19;
    QSpinBox *spinBox_5;
    QWidget *layoutWidget9;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_20;
    QSpinBox *spinBox_6;
    QWidget *layoutWidget10;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_21;
    QSpinBox *spinBox_7;
    QTableWidget *fileTableWidget;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Renamer)
    {
        if (Renamer->objectName().isEmpty())
            Renamer->setObjectName("Renamer");
        Renamer->resize(794, 605);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/Renamer/SomRename.png"), QSize(), QIcon::Normal, QIcon::Off);
        Renamer->setWindowIcon(icon);
        actionAddFile = new QAction(Renamer);
        actionAddFile->setObjectName("actionAddFile");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/transfer/res/transfer/addFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddFile->setIcon(icon1);
        QFont font;
        font.setPointSize(10);
        actionAddFile->setFont(font);
        actionAddFile->setVisible(true);
        actionAddFile->setMenuRole(QAction::NoRole);
        actionAddFileFormDir = new QAction(Renamer);
        actionAddFileFormDir->setObjectName("actionAddFileFormDir");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/transfer/res/transfer/selectFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddFileFormDir->setIcon(icon2);
        actionAddFileFormDir->setMenuRole(QAction::NoRole);
        actionClearFileList = new QAction(Renamer);
        actionClearFileList->setObjectName("actionClearFileList");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/transfer/res/transfer/clearList.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClearFileList->setIcon(icon3);
        actionClearFileList->setMenuRole(QAction::NoRole);
        actionUndoRename = new QAction(Renamer);
        actionUndoRename->setObjectName("actionUndoRename");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/res/Renamer/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndoRename->setIcon(icon4);
        actionUndoRename->setMenuRole(QAction::NoRole);
        actionFileOpenExplore = new QAction(Renamer);
        actionFileOpenExplore->setObjectName("actionFileOpenExplore");
        actionFileOpenExplore->setMenuRole(QAction::NoRole);
        actionFileCopyName = new QAction(Renamer);
        actionFileCopyName->setObjectName("actionFileCopyName");
        actionFileCopyName->setMenuRole(QAction::NoRole);
        actionFileCopyNewName = new QAction(Renamer);
        actionFileCopyNewName->setObjectName("actionFileCopyNewName");
        actionFileCopyNewName->setMenuRole(QAction::NoRole);
        actionFileCopyPath = new QAction(Renamer);
        actionFileCopyPath->setObjectName("actionFileCopyPath");
        actionFileCopyPath->setMenuRole(QAction::NoRole);
        actionFileCopyAbsPath = new QAction(Renamer);
        actionFileCopyAbsPath->setObjectName("actionFileCopyAbsPath");
        actionFileCopyAbsPath->setMenuRole(QAction::NoRole);
        actionRemoveList = new QAction(Renamer);
        actionRemoveList->setObjectName("actionRemoveList");
        actionRemoveList->setMenuRole(QAction::NoRole);
        actionClearList = new QAction(Renamer);
        actionClearList->setObjectName("actionClearList");
        actionClearList->setMenuRole(QAction::NoRole);
        actionFileOpen = new QAction(Renamer);
        actionFileOpen->setObjectName("actionFileOpen");
        actionFileOpen->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(Renamer);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(0, 180));
        tabWidget->setMaximumSize(QSize(16777215, 180));
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(6, 0, 19, 0);
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(16777215, 79));
        radioButtonAllCase = new QRadioButton(groupBox);
        radioButtonAllCase->setObjectName("radioButtonAllCase");
        radioButtonAllCase->setGeometry(QRect(10, 26, 107, 17));
        radioButtonRan = new QRadioButton(groupBox);
        radioButtonRan->setObjectName("radioButtonRan");
        radioButtonRan->setGeometry(QRect(10, 48, 62, 21));
        radioButtonNumUp = new QRadioButton(groupBox);
        radioButtonNumUp->setObjectName("radioButtonNumUp");
        radioButtonNumUp->setGeometry(QRect(123, 48, 75, 21));
        radioButtonNoCase = new QRadioButton(groupBox);
        radioButtonNoCase->setObjectName("radioButtonNoCase");
        radioButtonNoCase->setGeometry(QRect(123, 26, 107, 17));
        radioButtonNo = new QRadioButton(groupBox);
        radioButtonNo->setObjectName("radioButtonNo");
        radioButtonNo->setGeometry(QRect(236, 48, 75, 21));
        radioButtonNo->setChecked(true);
        radioButtonFirstCase = new QRadioButton(groupBox);
        radioButtonFirstCase->setObjectName("radioButtonFirstCase");
        radioButtonFirstCase->setGeometry(QRect(236, 26, 107, 17));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(350, 20, 237, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(layoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setMinimumSize(QSize(166, 0));
        comboBox->setMaximumSize(QSize(207, 16777215));

        horizontalLayout->addWidget(comboBox);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(340, 50, 78, 17));
        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(420, 50, 166, 22));
        comboBox_2->setMinimumSize(QSize(166, 0));
        comboBox_2->setMaximumSize(QSize(207, 16777215));
        comboBox_2->setEditable(true);

        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMaximumSize(QSize(16777215, 50));
        radioButtonSuffAllCase = new QRadioButton(groupBox_2);
        radioButtonSuffAllCase->setObjectName("radioButtonSuffAllCase");
        radioButtonSuffAllCase->setGeometry(QRect(10, 20, 101, 21));
        radioButtonSuffNoCase = new QRadioButton(groupBox_2);
        radioButtonSuffNoCase->setObjectName("radioButtonSuffNoCase");
        radioButtonSuffNoCase->setGeometry(QRect(120, 20, 101, 21));
        radioButtonSuffNo = new QRadioButton(groupBox_2);
        radioButtonSuffNo->setObjectName("radioButtonSuffNo");
        radioButtonSuffNo->setGeometry(QRect(230, 20, 101, 21));
        radioButtonSuffNo->setChecked(true);
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(330, 20, 226, 24));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        comboBoxSuffix = new QComboBox(layoutWidget1);
        comboBoxSuffix->addItem(QString());
        comboBoxSuffix->addItem(QString());
        comboBoxSuffix->addItem(QString());
        comboBoxSuffix->addItem(QString());
        comboBoxSuffix->addItem(QString());
        comboBoxSuffix->addItem(QString());
        comboBoxSuffix->addItem(QString());
        comboBoxSuffix->addItem(QString());
        comboBoxSuffix->setObjectName("comboBoxSuffix");
        comboBoxSuffix->setMinimumSize(QSize(140, 22));
        comboBoxSuffix->setMaximumSize(QSize(140, 22));
        comboBoxSuffix->setEditable(true);

        horizontalLayout_3->addWidget(comboBoxSuffix);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(20, 20, 492, 24));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        comboBoxSouce = new QComboBox(layoutWidget2);
        comboBoxSouce->setObjectName("comboBoxSouce");
        comboBoxSouce->setMinimumSize(QSize(166, 0));
        comboBoxSouce->setMaximumSize(QSize(166, 16777215));
        comboBoxSouce->setEditable(true);
        comboBoxSouce->setInsertPolicy(QComboBox::InsertAtBottom);
        comboBoxSouce->setDuplicatesEnabled(false);

        horizontalLayout_4->addWidget(comboBoxSouce);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        comboBoxDest = new QComboBox(layoutWidget2);
        comboBoxDest->setObjectName("comboBoxDest");
        comboBoxDest->setMinimumSize(QSize(166, 0));
        comboBoxDest->setMaximumSize(QSize(166, 16777215));
        comboBoxDest->setEditable(true);

        horizontalLayout_4->addWidget(comboBoxDest);

        checkBoxCase = new QCheckBox(layoutWidget2);
        checkBoxCase->setObjectName("checkBoxCase");
        checkBoxCase->setChecked(true);

        horizontalLayout_4->addWidget(checkBoxCase);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_5 = new QLabel(tab_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 20, 58, 17));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 70, 58, 17));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 110, 58, 17));
        comboBoxPreFix = new QComboBox(tab_3);
        comboBoxPreFix->addItem(QString());
        comboBoxPreFix->addItem(QString());
        comboBoxPreFix->addItem(QString());
        comboBoxPreFix->addItem(QString());
        comboBoxPreFix->addItem(QString());
        comboBoxPreFix->addItem(QString());
        comboBoxPreFix->setObjectName("comboBoxPreFix");
        comboBoxPreFix->setGeometry(QRect(50, 20, 166, 22));
        comboBoxPreFix->setEditable(true);
        comboBoxTxt = new QComboBox(tab_3);
        comboBoxTxt->setObjectName("comboBoxTxt");
        comboBoxTxt->setGeometry(QRect(50, 110, 101, 22));
        comboBoxTxt->setEditable(true);
        comboBox_11 = new QComboBox(tab_3);
        comboBox_11->addItem(QString());
        comboBox_11->addItem(QString());
        comboBox_11->setObjectName("comboBox_11");
        comboBox_11->setGeometry(QRect(150, 110, 55, 22));
        comboBox_11->setMinimumSize(QSize(55, 0));
        comboBox_11->setMaximumSize(QSize(55, 16777215));
        checkBox_4 = new QCheckBox(tab_3);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setGeometry(QRect(130, 70, 84, 21));
        spinBox = new QSpinBox(tab_3);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(50, 70, 71, 22));
        layoutWidget3 = new QWidget(tab_3);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(240, 20, 204, 24));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget3);
        label_8->setObjectName("label_8");

        horizontalLayout_6->addWidget(label_8);

        comboBoxSuffix_2 = new QComboBox(layoutWidget3);
        comboBoxSuffix_2->addItem(QString());
        comboBoxSuffix_2->addItem(QString());
        comboBoxSuffix_2->addItem(QString());
        comboBoxSuffix_2->addItem(QString());
        comboBoxSuffix_2->addItem(QString());
        comboBoxSuffix_2->addItem(QString());
        comboBoxSuffix_2->setObjectName("comboBoxSuffix_2");
        comboBoxSuffix_2->setMinimumSize(QSize(166, 0));
        comboBoxSuffix_2->setMaximumSize(QSize(166, 16777215));
        comboBoxSuffix_2->setEditable(true);

        horizontalLayout_6->addWidget(comboBoxSuffix_2);

        layoutWidget4 = new QWidget(tab_3);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(240, 70, 204, 24));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget4);
        label_9->setObjectName("label_9");

        horizontalLayout_7->addWidget(label_9);

        comboBox_8 = new QComboBox(layoutWidget4);
        comboBox_8->addItem(QString());
        comboBox_8->addItem(QString());
        comboBox_8->addItem(QString());
        comboBox_8->addItem(QString());
        comboBox_8->addItem(QString());
        comboBox_8->addItem(QString());
        comboBox_8->setObjectName("comboBox_8");
        comboBox_8->setMinimumSize(QSize(166, 0));
        comboBox_8->setMaximumSize(QSize(166, 16777215));
        comboBox_8->setEditable(true);

        horizontalLayout_7->addWidget(comboBox_8);

        layoutWidget5 = new QWidget(tab_3);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(240, 110, 204, 24));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget5);
        label_10->setObjectName("label_10");

        horizontalLayout_8->addWidget(label_10);

        comboBox_9 = new QComboBox(layoutWidget5);
        comboBox_9->addItem(QString());
        comboBox_9->addItem(QString());
        comboBox_9->addItem(QString());
        comboBox_9->addItem(QString());
        comboBox_9->addItem(QString());
        comboBox_9->addItem(QString());
        comboBox_9->setObjectName("comboBox_9");
        comboBox_9->setMinimumSize(QSize(166, 0));
        comboBox_9->setMaximumSize(QSize(166, 16777215));
        comboBox_9->setEditable(true);

        horizontalLayout_8->addWidget(comboBox_9);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        checkBox_5 = new QCheckBox(tab_4);
        checkBox_5->setObjectName("checkBox_5");
        checkBox_5->setGeometry(QRect(130, 70, 84, 21));
        comboBox_12 = new QComboBox(tab_4);
        comboBox_12->setObjectName("comboBox_12");
        comboBox_12->setGeometry(QRect(50, 20, 166, 22));
        comboBox_12->setEditable(true);
        label_11 = new QLabel(tab_4);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 20, 58, 17));
        label_12 = new QLabel(tab_4);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 110, 58, 17));
        label_13 = new QLabel(tab_4);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 70, 58, 17));
        spinBox_2 = new QSpinBox(tab_4);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(50, 70, 71, 22));
        comboBox_13 = new QComboBox(tab_4);
        comboBox_13->setObjectName("comboBox_13");
        comboBox_13->setGeometry(QRect(50, 110, 101, 22));
        comboBox_13->setEditable(true);
        comboBox_14 = new QComboBox(tab_4);
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->setObjectName("comboBox_14");
        comboBox_14->setGeometry(QRect(150, 110, 71, 22));
        layoutWidget6 = new QWidget(tab_4);
        layoutWidget6->setObjectName("layoutWidget6");
        layoutWidget6->setGeometry(QRect(250, 70, 169, 23));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget6);
        label_15->setObjectName("label_15");

        horizontalLayout_10->addWidget(label_15);

        spinBox_3 = new QSpinBox(layoutWidget6);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setMinimumSize(QSize(71, 0));

        horizontalLayout_10->addWidget(spinBox_3);

        label_17 = new QLabel(layoutWidget6);
        label_17->setObjectName("label_17");

        horizontalLayout_10->addWidget(label_17);

        layoutWidget7 = new QWidget(tab_4);
        layoutWidget7->setObjectName("layoutWidget7");
        layoutWidget7->setGeometry(QRect(250, 110, 290, 23));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget7);
        label_16->setObjectName("label_16");

        horizontalLayout_11->addWidget(label_16);

        spinBox_4 = new QSpinBox(layoutWidget7);
        spinBox_4->setObjectName("spinBox_4");
        spinBox_4->setMinimumSize(QSize(71, 0));

        horizontalLayout_11->addWidget(spinBox_4);

        label_18 = new QLabel(layoutWidget7);
        label_18->setObjectName("label_18");

        horizontalLayout_11->addWidget(label_18);

        checkBox_11 = new QCheckBox(layoutWidget7);
        checkBox_11->setObjectName("checkBox_11");

        horizontalLayout_11->addWidget(checkBox_11);

        widget = new QWidget(tab_4);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(260, 10, 399, 41));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_14 = new QLabel(widget);
        label_14->setObjectName("label_14");

        horizontalLayout_9->addWidget(label_14);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        checkBox_6 = new QCheckBox(widget);
        checkBox_6->setObjectName("checkBox_6");

        horizontalLayout_9->addWidget(checkBox_6);

        checkBox_7 = new QCheckBox(widget);
        checkBox_7->setObjectName("checkBox_7");

        horizontalLayout_9->addWidget(checkBox_7);

        checkBox_8 = new QCheckBox(widget);
        checkBox_8->setObjectName("checkBox_8");

        horizontalLayout_9->addWidget(checkBox_8);

        checkBox_9 = new QCheckBox(widget);
        checkBox_9->setObjectName("checkBox_9");

        horizontalLayout_9->addWidget(checkBox_9);

        checkBox_10 = new QCheckBox(widget);
        checkBox_10->setObjectName("checkBox_10");

        horizontalLayout_9->addWidget(checkBox_10);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);


        gridLayout_4->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        checkBox_12 = new QCheckBox(tab_5);
        checkBox_12->setObjectName("checkBox_12");
        checkBox_12->setGeometry(QRect(20, 20, 84, 21));
        layoutWidget8 = new QWidget(tab_5);
        layoutWidget8->setObjectName("layoutWidget8");
        layoutWidget8->setGeometry(QRect(20, 60, 131, 23));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget8);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(layoutWidget8);
        label_19->setObjectName("label_19");

        horizontalLayout_12->addWidget(label_19);

        spinBox_5 = new QSpinBox(layoutWidget8);
        spinBox_5->setObjectName("spinBox_5");
        spinBox_5->setMinimumSize(QSize(71, 0));
        spinBox_5->setValue(1);

        horizontalLayout_12->addWidget(spinBox_5);

        layoutWidget9 = new QWidget(tab_5);
        layoutWidget9->setObjectName("layoutWidget9");
        layoutWidget9->setGeometry(QRect(220, 60, 109, 23));
        horizontalLayout_13 = new QHBoxLayout(layoutWidget9);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(layoutWidget9);
        label_20->setObjectName("label_20");

        horizontalLayout_13->addWidget(label_20);

        spinBox_6 = new QSpinBox(layoutWidget9);
        spinBox_6->setObjectName("spinBox_6");
        spinBox_6->setMinimumSize(QSize(71, 0));
        spinBox_6->setValue(1);

        horizontalLayout_13->addWidget(spinBox_6);

        layoutWidget10 = new QWidget(tab_5);
        layoutWidget10->setObjectName("layoutWidget10");
        layoutWidget10->setGeometry(QRect(410, 60, 118, 23));
        horizontalLayout_14 = new QHBoxLayout(layoutWidget10);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(layoutWidget10);
        label_21->setObjectName("label_21");

        horizontalLayout_14->addWidget(label_21);

        spinBox_7 = new QSpinBox(layoutWidget10);
        spinBox_7->setObjectName("spinBox_7");
        spinBox_7->setMinimumSize(QSize(71, 0));
        spinBox_7->setValue(1);

        horizontalLayout_14->addWidget(spinBox_7);

        tabWidget->addTab(tab_5, QString());
        splitter->addWidget(tabWidget);
        fileTableWidget = new QTableWidget(splitter);
        if (fileTableWidget->columnCount() < 7)
            fileTableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        fileTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        fileTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        fileTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        fileTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        fileTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        fileTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        fileTableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        fileTableWidget->setObjectName("fileTableWidget");
        QFont font1;
        font1.setPointSize(9);
        fileTableWidget->setFont(font1);
        fileTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        fileTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        fileTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        fileTableWidget->setRowCount(0);
        splitter->addWidget(fileTableWidget);
        fileTableWidget->horizontalHeader()->setVisible(true);
        fileTableWidget->horizontalHeader()->setDefaultSectionSize(90);
        fileTableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        fileTableWidget->horizontalHeader()->setStretchLastSection(true);
        fileTableWidget->verticalHeader()->setVisible(false);
        fileTableWidget->verticalHeader()->setCascadingSectionResizes(false);
        fileTableWidget->verticalHeader()->setHighlightSections(false);
        fileTableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        fileTableWidget->verticalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        Renamer->setCentralWidget(centralwidget);
        toolBar = new QToolBar(Renamer);
        toolBar->setObjectName("toolBar");
        toolBar->setIconSize(QSize(20, 15));
        toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolBar->setFloatable(true);
        Renamer->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(Renamer);
        statusBar->setObjectName("statusBar");
        Renamer->setStatusBar(statusBar);

        toolBar->addAction(actionAddFile);
        toolBar->addAction(actionAddFileFormDir);
        toolBar->addAction(actionClearFileList);
        toolBar->addAction(actionUndoRename);

        retranslateUi(Renamer);

        tabWidget->setCurrentIndex(2);
        comboBox->setCurrentIndex(0);
        comboBoxSuffix->setCurrentIndex(-1);
        comboBoxPreFix->setCurrentIndex(-1);
        comboBoxSuffix_2->setCurrentIndex(-1);
        comboBox_8->setCurrentIndex(-1);
        comboBox_9->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Renamer);
    } // setupUi

    void retranslateUi(QMainWindow *Renamer)
    {
        Renamer->setWindowTitle(QCoreApplication::translate("Renamer", "\346\211\271\351\207\217\351\207\215\345\221\275\345\220\215\345\267\245\345\205\267", nullptr));
        actionAddFile->setText(QCoreApplication::translate("Renamer", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
        actionAddFileFormDir->setText(QCoreApplication::translate("Renamer", "\344\273\216\346\226\207\344\273\266\345\244\271\346\267\273\345\212\240", nullptr));
        actionClearFileList->setText(QCoreApplication::translate("Renamer", "\346\270\205\347\251\272\346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
        actionUndoRename->setText(QCoreApplication::translate("Renamer", "\346\222\244\351\224\200\346\224\271\345\220\215", nullptr));
        actionFileOpenExplore->setText(QCoreApplication::translate("Renamer", "\346\211\223\345\274\200\346\226\207\344\273\266\346\211\200\345\234\250\347\233\256\345\275\225(&F)", nullptr));
        actionFileCopyName->setText(QCoreApplication::translate("Renamer", "\345\244\215\345\210\266\346\226\207\344\273\266\345\220\215", nullptr));
        actionFileCopyNewName->setText(QCoreApplication::translate("Renamer", "\345\244\215\345\210\266\346\226\260\346\226\207\344\273\266\345\220\215", nullptr));
        actionFileCopyPath->setText(QCoreApplication::translate("Renamer", "\345\244\215\345\210\266\350\267\257\345\276\204", nullptr));
        actionFileCopyAbsPath->setText(QCoreApplication::translate("Renamer", "\345\244\215\345\210\266\346\226\207\344\273\266\347\273\235\345\257\271\350\267\257\345\276\204", nullptr));
        actionRemoveList->setText(QCoreApplication::translate("Renamer", "\347\247\273\351\231\244(&R)", nullptr));
        actionClearList->setText(QCoreApplication::translate("Renamer", "\346\270\205\347\251\272(&C)", nullptr));
        actionFileOpen->setText(QCoreApplication::translate("Renamer", "\346\211\223\345\274\200(&O)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Renamer", "\346\226\207\344\273\266\345\220\215", nullptr));
        radioButtonAllCase->setText(QCoreApplication::translate("Renamer", "\345\205\250\351\203\250\345\244\247\345\206\231", nullptr));
        radioButtonRan->setText(QCoreApplication::translate("Renamer", "\351\232\217\346\234\272\346\225\260", nullptr));
        radioButtonNumUp->setText(QCoreApplication::translate("Renamer", "\346\225\260\345\255\227\351\200\222\345\242\236", nullptr));
        radioButtonNoCase->setText(QCoreApplication::translate("Renamer", "\345\205\250\351\203\250\345\260\217\345\206\231", nullptr));
        radioButtonNo->setText(QCoreApplication::translate("Renamer", "\344\277\235\346\214\201\344\270\215\345\217\230", nullptr));
        radioButtonFirstCase->setText(QCoreApplication::translate("Renamer", "\351\246\226\345\255\227\346\257\215\345\244\247\345\206\231", nullptr));
        label->setText(QCoreApplication::translate("Renamer", "      \350\275\254\346\215\242\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Renamer", "\344\270\215\351\200\211\346\213\251", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Renamer", "\347\256\200\344\275\223\350\275\254\347\271\201\344\275\223", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Renamer", "\347\271\201\344\275\223\350\275\254\347\256\200\344\275\223", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Renamer", "\344\270\200\344\272\214\344\270\211\350\275\254123", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Renamer", "123\350\275\254\344\270\200\344\272\214\344\270\211", nullptr));

        label_2->setText(QCoreApplication::translate("Renamer", "\346\226\207\344\273\266\345\220\215\346\224\271\344\270\272\357\274\232", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Renamer", "\346\213\223\345\261\225\345\220\215", nullptr));
        radioButtonSuffAllCase->setText(QCoreApplication::translate("Renamer", "\345\205\250\351\203\250\345\244\247\345\206\231", nullptr));
        radioButtonSuffNoCase->setText(QCoreApplication::translate("Renamer", "\345\205\250\351\203\250\345\260\217\345\206\231", nullptr));
        radioButtonSuffNo->setText(QCoreApplication::translate("Renamer", "\344\277\235\346\214\201\344\270\215\345\217\230", nullptr));
        label_3->setText(QCoreApplication::translate("Renamer", "\346\213\223\345\261\225\345\220\215\346\224\271\344\270\272\357\274\232", nullptr));
        comboBoxSuffix->setItemText(0, QCoreApplication::translate("Renamer", "mkv", nullptr));
        comboBoxSuffix->setItemText(1, QCoreApplication::translate("Renamer", "mp4", nullptr));
        comboBoxSuffix->setItemText(2, QCoreApplication::translate("Renamer", "pdf", nullptr));
        comboBoxSuffix->setItemText(3, QCoreApplication::translate("Renamer", "txt", nullptr));
        comboBoxSuffix->setItemText(4, QCoreApplication::translate("Renamer", "jpg", nullptr));
        comboBoxSuffix->setItemText(5, QCoreApplication::translate("Renamer", "png", nullptr));
        comboBoxSuffix->setItemText(6, QCoreApplication::translate("Renamer", "zip", nullptr));
        comboBoxSuffix->setItemText(7, QCoreApplication::translate("Renamer", "uvz", nullptr));

        comboBoxSuffix->setCurrentText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Renamer", "\346\225\264\344\275\223", nullptr));
        label_4->setText(QCoreApplication::translate("Renamer", "\346\233\277\346\215\242\344\270\272\357\274\232", nullptr));
        checkBoxCase->setText(QCoreApplication::translate("Renamer", "\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Renamer", "\346\233\277\346\215\242", nullptr));
        label_5->setText(QCoreApplication::translate("Renamer", "\345\211\215\347\274\200:", nullptr));
        label_6->setText(QCoreApplication::translate("Renamer", "\344\275\215\347\275\256:", nullptr));
        label_7->setText(QCoreApplication::translate("Renamer", "\346\226\207\346\234\254:", nullptr));
        comboBoxPreFix->setItemText(0, QCoreApplication::translate("Renamer", "<date>", nullptr));
        comboBoxPreFix->setItemText(1, QCoreApplication::translate("Renamer", "<time>", nullptr));
        comboBoxPreFix->setItemText(2, QCoreApplication::translate("Renamer", "<cdate>", nullptr));
        comboBoxPreFix->setItemText(3, QCoreApplication::translate("Renamer", "<ctime>", nullptr));
        comboBoxPreFix->setItemText(4, QCoreApplication::translate("Renamer", "<mdate>", nullptr));
        comboBoxPreFix->setItemText(5, QCoreApplication::translate("Renamer", "<mtime>", nullptr));

        comboBoxPreFix->setCurrentText(QString());
        comboBoxTxt->setCurrentText(QString());
        comboBox_11->setItemText(0, QCoreApplication::translate("Renamer", "\345\211\215\351\235\242", nullptr));
        comboBox_11->setItemText(1, QCoreApplication::translate("Renamer", "\345\220\216\351\235\242", nullptr));

        checkBox_4->setText(QCoreApplication::translate("Renamer", "\344\273\216\345\217\263\345\276\200\345\267\246", nullptr));
        label_8->setText(QCoreApplication::translate("Renamer", "\345\220\216\347\274\200:", nullptr));
        comboBoxSuffix_2->setItemText(0, QCoreApplication::translate("Renamer", "<date>", nullptr));
        comboBoxSuffix_2->setItemText(1, QCoreApplication::translate("Renamer", "<time>", nullptr));
        comboBoxSuffix_2->setItemText(2, QCoreApplication::translate("Renamer", "<cdate>", nullptr));
        comboBoxSuffix_2->setItemText(3, QCoreApplication::translate("Renamer", "<ctime>", nullptr));
        comboBoxSuffix_2->setItemText(4, QCoreApplication::translate("Renamer", "<mdate>", nullptr));
        comboBoxSuffix_2->setItemText(5, QCoreApplication::translate("Renamer", "<mtime>", nullptr));

        comboBoxSuffix_2->setCurrentText(QString());
        label_9->setText(QCoreApplication::translate("Renamer", "\346\267\273\345\212\240 ", nullptr));
        comboBox_8->setItemText(0, QCoreApplication::translate("Renamer", "<date>", nullptr));
        comboBox_8->setItemText(1, QCoreApplication::translate("Renamer", "<time>", nullptr));
        comboBox_8->setItemText(2, QCoreApplication::translate("Renamer", "<cdate>", nullptr));
        comboBox_8->setItemText(3, QCoreApplication::translate("Renamer", "<ctime>", nullptr));
        comboBox_8->setItemText(4, QCoreApplication::translate("Renamer", "<mdate>", nullptr));
        comboBox_8->setItemText(5, QCoreApplication::translate("Renamer", "<mtime>", nullptr));

        comboBox_8->setCurrentText(QString());
        label_10->setText(QCoreApplication::translate("Renamer", "\346\267\273\345\212\240 ", nullptr));
        comboBox_9->setItemText(0, QCoreApplication::translate("Renamer", "<date>", nullptr));
        comboBox_9->setItemText(1, QCoreApplication::translate("Renamer", "<time>", nullptr));
        comboBox_9->setItemText(2, QCoreApplication::translate("Renamer", "<cdate>", nullptr));
        comboBox_9->setItemText(3, QCoreApplication::translate("Renamer", "<ctime>", nullptr));
        comboBox_9->setItemText(4, QCoreApplication::translate("Renamer", "<mdate>", nullptr));
        comboBox_9->setItemText(5, QCoreApplication::translate("Renamer", "<mtime>", nullptr));

        comboBox_9->setCurrentText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("Renamer", "\346\267\273\345\212\240", nullptr));
        checkBox_5->setText(QCoreApplication::translate("Renamer", "\344\273\216\345\217\263\345\276\200\345\267\246", nullptr));
        label_11->setText(QCoreApplication::translate("Renamer", "\346\226\207\346\234\254\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("Renamer", "\346\226\207\346\234\254:", nullptr));
        label_13->setText(QCoreApplication::translate("Renamer", "\344\275\215\347\275\256:", nullptr));
        comboBox_14->setItemText(0, QCoreApplication::translate("Renamer", "\345\276\200\342\206\222", nullptr));
        comboBox_14->setItemText(1, QCoreApplication::translate("Renamer", "\345\276\200\342\206\220", nullptr));
        comboBox_14->setItemText(2, QCoreApplication::translate("Renamer", "\345\276\200\342\206\222\345\210\260\345\272\225", nullptr));
        comboBox_14->setItemText(3, QCoreApplication::translate("Renamer", "\345\276\200\342\206\220\345\210\260\345\272\225", nullptr));

        label_15->setText(QCoreApplication::translate("Renamer", "   \345\210\240\351\231\244", nullptr));
        label_17->setText(QCoreApplication::translate("Renamer", "\344\270\252\345\255\227\347\254\246", nullptr));
        label_16->setText(QCoreApplication::translate("Renamer", "   \345\210\240\351\231\244  ", nullptr));
        label_18->setText(QCoreApplication::translate("Renamer", "\344\270\252\345\255\227\347\254\246", nullptr));
        checkBox_11->setText(QCoreApplication::translate("Renamer", "\345\214\205\345\220\253\345\205\263\351\224\256\350\257\215\346\234\254\350\272\253", nullptr));
        label_14->setText(QCoreApplication::translate("Renamer", "\345\210\240\351\231\244", nullptr));
        checkBox_6->setText(QCoreApplication::translate("Renamer", "\347\251\272\346\240\274", nullptr));
        checkBox_7->setText(QCoreApplication::translate("Renamer", "\346\225\260\345\255\227", nullptr));
        checkBox_8->setText(QCoreApplication::translate("Renamer", "\345\260\217\345\206\231\345\255\227\346\257\215", nullptr));
        checkBox_9->setText(QCoreApplication::translate("Renamer", "\345\244\247\345\206\231\345\255\227\346\257\215", nullptr));
        checkBox_10->setText(QCoreApplication::translate("Renamer", "\347\211\271\346\256\212\345\255\227\347\254\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("Renamer", "\345\210\240\351\231\244", nullptr));
        checkBox_12->setText(QCoreApplication::translate("Renamer", "\345\272\217\345\217\267", nullptr));
        label_19->setText(QCoreApplication::translate("Renamer", "\350\265\267\345\247\213\345\200\274\357\274\232", nullptr));
        label_20->setText(QCoreApplication::translate("Renamer", "\345\242\236\351\207\217:", nullptr));
        label_21->setText(QCoreApplication::translate("Renamer", "\344\275\215\346\225\260\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("Renamer", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem = fileTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Renamer", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = fileTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Renamer", "\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = fileTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Renamer", "\346\226\260\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = fileTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Renamer", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = fileTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Renamer", "\346\213\223\345\261\225\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = fileTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Renamer", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = fileTableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Renamer", "\350\267\257\345\276\204", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("Renamer", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Renamer: public Ui_Renamer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENAMER_H
