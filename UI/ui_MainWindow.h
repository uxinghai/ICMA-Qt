/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../src/Utils/BoostClass/MyTableView.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionDaori;
    QAction *actionDaochu1;
    QAction *actionJiaMi;
    QAction *actionJieMi;
    QAction *actionWenJianBaoGao;
    QAction *actionExit;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPast;
    QAction *actionReName;
    QAction *actionDelete;
    QAction *actionSelectAll;
    QAction *actionDeselect;
    QAction *actionAddTag;
    QAction *actionRemoveTag;
    QAction *actionCN;
    QAction *actionEN;
    QAction *actionPreview;
    QAction *actionStatusBar;
    QAction *actionListView;
    QAction *actionIconView;
    QAction *actionDetailView;
    QAction *actionBigFont;
    QAction *actionSmallFont;
    QAction *actionGeneralFont;
    QAction *actionFileName;
    QAction *actionFileDate;
    QAction *actionFileSize;
    QAction *actionFilePath;
    QAction *actionFileSuffix;
    QAction *actionFileType;
    QAction *actionFileCreateDate;
    QAction *actionFileModifyDate;
    QAction *actionAsc;
    QAction *actionDesc;
    QAction *actionFilter;
    QAction *actionShowHideFile;
    QAction *actionRefresh;
    QAction *actionAdvancedSearch;
    QAction *actionFileSynchronization;
    QAction *actionBatchRename;
    QAction *actionFileDuplication;
    QAction *actionDiskspaceAnalysis;
    QAction *actionDocumentComparison;
    QAction *actionUserManual;
    QAction *actionQuickStartGuide;
    QAction *actionUpdateSys;
    QAction *actionFeedback;
    QAction *actionCategorization;
    QAction *actionteStimonial;
    QAction *actionStatisticalAnalysis;
    QAction *actionRelationships;
    QAction *actionAMOLED;
    QAction *actionAqua;
    QAction *actionConsoleStyle;
    QAction *actionTransmission;
    QAction *actionJP;
    QAction *actionAutoRun;
    QAction *actionPS;
    QAction *actionEnableFileLog;
    QAction *actionMacOS;
    QAction *actionManjaroMix;
    QAction *actionMaterialDark;
    QAction *actionNeonButtons;
    QAction *actionUbuntu;
    QAction *actionAboutQT;
    QAction *actionDark;
    QAction *actionLight;
    QAction *actionShowNameCol;
    QAction *actionShowPathCol;
    QAction *actionShowSizeCol;
    QAction *actionShowTypeCol;
    QAction *actionShowCreateDateCol;
    QAction *actionShowModifyDateCol;
    QAction *actionShowLastModDateCol;
    QAction *actionShowHashCol;
    QAction *actionShowEncrCol;
    QAction *actionAutoFit;
    QAction *actionAutoFitColWidth;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QComboBox *comBoxFilter;
    QSplitter *splitter;
    QStackedWidget *stackedWidgetView;
    QWidget *TableViewPage;
    QGridLayout *gridLayout_2;
    MyTableView *tableView;
    QWidget *ListViewPage;
    QGridLayout *gridLayout_3;
    QListView *listView;
    QWidget *IconViewPage;
    QGridLayout *gridLayout_4;
    QListView *IconView;
    QLabel *lbPreview;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_6;
    QMenu *menu_8;
    QMenu *menu_3;
    QMenu *menu_7;
    QMenu *menu_S;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_A;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(852, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/icons/logo/logo1024.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        QFont font1;
        font1.setPointSize(10);
        actionAbout->setFont(font1);
        actionDaori = new QAction(MainWindow);
        actionDaori->setObjectName("actionDaori");
        actionDaori->setFont(font1);
        actionDaochu1 = new QAction(MainWindow);
        actionDaochu1->setObjectName("actionDaochu1");
        QFont font2;
        font2.setPointSize(9);
        actionDaochu1->setFont(font2);
        actionJiaMi = new QAction(MainWindow);
        actionJiaMi->setObjectName("actionJiaMi");
        actionJiaMi->setFont(font2);
        actionJieMi = new QAction(MainWindow);
        actionJieMi->setObjectName("actionJieMi");
        actionJieMi->setFont(font2);
        actionWenJianBaoGao = new QAction(MainWindow);
        actionWenJianBaoGao->setObjectName("actionWenJianBaoGao");
        actionWenJianBaoGao->setFont(font2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionExit->setFont(font2);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        actionCopy->setFont(font2);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        actionCut->setFont(font2);
        actionPast = new QAction(MainWindow);
        actionPast->setObjectName("actionPast");
        actionPast->setFont(font2);
        actionReName = new QAction(MainWindow);
        actionReName->setObjectName("actionReName");
        actionReName->setFont(font2);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
        actionDelete->setFont(font2);
        actionSelectAll = new QAction(MainWindow);
        actionSelectAll->setObjectName("actionSelectAll");
        actionSelectAll->setFont(font2);
        actionDeselect = new QAction(MainWindow);
        actionDeselect->setObjectName("actionDeselect");
        actionDeselect->setFont(font2);
        actionAddTag = new QAction(MainWindow);
        actionAddTag->setObjectName("actionAddTag");
        actionAddTag->setFont(font2);
        actionRemoveTag = new QAction(MainWindow);
        actionRemoveTag->setObjectName("actionRemoveTag");
        actionRemoveTag->setFont(font2);
        actionCN = new QAction(MainWindow);
        actionCN->setObjectName("actionCN");
        actionCN->setCheckable(true);
        actionCN->setChecked(true);
        actionCN->setFont(font2);
        actionEN = new QAction(MainWindow);
        actionEN->setObjectName("actionEN");
        actionEN->setCheckable(true);
        actionEN->setFont(font2);
        actionPreview = new QAction(MainWindow);
        actionPreview->setObjectName("actionPreview");
        actionPreview->setCheckable(true);
        actionPreview->setFont(font2);
        actionStatusBar = new QAction(MainWindow);
        actionStatusBar->setObjectName("actionStatusBar");
        actionStatusBar->setCheckable(true);
        actionStatusBar->setChecked(true);
        actionStatusBar->setFont(font2);
        actionListView = new QAction(MainWindow);
        actionListView->setObjectName("actionListView");
        actionListView->setCheckable(true);
        actionListView->setFont(font2);
        actionIconView = new QAction(MainWindow);
        actionIconView->setObjectName("actionIconView");
        actionIconView->setCheckable(true);
        actionIconView->setFont(font2);
        actionDetailView = new QAction(MainWindow);
        actionDetailView->setObjectName("actionDetailView");
        actionDetailView->setCheckable(true);
        actionDetailView->setChecked(true);
        actionDetailView->setFont(font2);
        actionBigFont = new QAction(MainWindow);
        actionBigFont->setObjectName("actionBigFont");
        actionBigFont->setFont(font2);
        actionSmallFont = new QAction(MainWindow);
        actionSmallFont->setObjectName("actionSmallFont");
        actionSmallFont->setFont(font2);
        actionGeneralFont = new QAction(MainWindow);
        actionGeneralFont->setObjectName("actionGeneralFont");
        actionGeneralFont->setFont(font2);
        actionFileName = new QAction(MainWindow);
        actionFileName->setObjectName("actionFileName");
        actionFileName->setCheckable(true);
        actionFileName->setFont(font2);
        actionFileDate = new QAction(MainWindow);
        actionFileDate->setObjectName("actionFileDate");
        actionFileDate->setCheckable(true);
        actionFileDate->setFont(font2);
        actionFileSize = new QAction(MainWindow);
        actionFileSize->setObjectName("actionFileSize");
        actionFileSize->setCheckable(true);
        actionFileSize->setFont(font2);
        actionFilePath = new QAction(MainWindow);
        actionFilePath->setObjectName("actionFilePath");
        actionFilePath->setCheckable(true);
        actionFilePath->setChecked(true);
        actionFilePath->setFont(font2);
        actionFileSuffix = new QAction(MainWindow);
        actionFileSuffix->setObjectName("actionFileSuffix");
        actionFileSuffix->setCheckable(true);
        actionFileSuffix->setFont(font2);
        actionFileType = new QAction(MainWindow);
        actionFileType->setObjectName("actionFileType");
        actionFileType->setCheckable(true);
        actionFileType->setFont(font2);
        actionFileCreateDate = new QAction(MainWindow);
        actionFileCreateDate->setObjectName("actionFileCreateDate");
        actionFileCreateDate->setCheckable(true);
        actionFileCreateDate->setFont(font2);
        actionFileModifyDate = new QAction(MainWindow);
        actionFileModifyDate->setObjectName("actionFileModifyDate");
        actionFileModifyDate->setCheckable(true);
        actionFileModifyDate->setFont(font2);
        actionAsc = new QAction(MainWindow);
        actionAsc->setObjectName("actionAsc");
        actionAsc->setCheckable(true);
        actionAsc->setChecked(true);
        actionAsc->setFont(font2);
        actionDesc = new QAction(MainWindow);
        actionDesc->setObjectName("actionDesc");
        actionDesc->setCheckable(true);
        actionDesc->setFont(font2);
        actionFilter = new QAction(MainWindow);
        actionFilter->setObjectName("actionFilter");
        actionFilter->setCheckable(true);
        actionFilter->setChecked(false);
        actionShowHideFile = new QAction(MainWindow);
        actionShowHideFile->setObjectName("actionShowHideFile");
        actionShowHideFile->setCheckable(true);
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName("actionRefresh");
        actionAdvancedSearch = new QAction(MainWindow);
        actionAdvancedSearch->setObjectName("actionAdvancedSearch");
        actionFileSynchronization = new QAction(MainWindow);
        actionFileSynchronization->setObjectName("actionFileSynchronization");
        actionBatchRename = new QAction(MainWindow);
        actionBatchRename->setObjectName("actionBatchRename");
        actionFileDuplication = new QAction(MainWindow);
        actionFileDuplication->setObjectName("actionFileDuplication");
        actionDiskspaceAnalysis = new QAction(MainWindow);
        actionDiskspaceAnalysis->setObjectName("actionDiskspaceAnalysis");
        actionDocumentComparison = new QAction(MainWindow);
        actionDocumentComparison->setObjectName("actionDocumentComparison");
        actionUserManual = new QAction(MainWindow);
        actionUserManual->setObjectName("actionUserManual");
        actionQuickStartGuide = new QAction(MainWindow);
        actionQuickStartGuide->setObjectName("actionQuickStartGuide");
        actionUpdateSys = new QAction(MainWindow);
        actionUpdateSys->setObjectName("actionUpdateSys");
        actionFeedback = new QAction(MainWindow);
        actionFeedback->setObjectName("actionFeedback");
        actionCategorization = new QAction(MainWindow);
        actionCategorization->setObjectName("actionCategorization");
        actionteStimonial = new QAction(MainWindow);
        actionteStimonial->setObjectName("actionteStimonial");
        actionStatisticalAnalysis = new QAction(MainWindow);
        actionStatisticalAnalysis->setObjectName("actionStatisticalAnalysis");
        actionRelationships = new QAction(MainWindow);
        actionRelationships->setObjectName("actionRelationships");
        actionAMOLED = new QAction(MainWindow);
        actionAMOLED->setObjectName("actionAMOLED");
        actionAMOLED->setCheckable(true);
        actionAMOLED->setChecked(true);
        actionAqua = new QAction(MainWindow);
        actionAqua->setObjectName("actionAqua");
        actionAqua->setCheckable(true);
        actionConsoleStyle = new QAction(MainWindow);
        actionConsoleStyle->setObjectName("actionConsoleStyle");
        actionConsoleStyle->setCheckable(true);
        actionTransmission = new QAction(MainWindow);
        actionTransmission->setObjectName("actionTransmission");
        actionJP = new QAction(MainWindow);
        actionJP->setObjectName("actionJP");
        actionJP->setCheckable(true);
        actionAutoRun = new QAction(MainWindow);
        actionAutoRun->setObjectName("actionAutoRun");
        actionAutoRun->setCheckable(true);
        actionPS = new QAction(MainWindow);
        actionPS->setObjectName("actionPS");
        actionEnableFileLog = new QAction(MainWindow);
        actionEnableFileLog->setObjectName("actionEnableFileLog");
        actionEnableFileLog->setCheckable(true);
        actionEnableFileLog->setChecked(true);
        actionMacOS = new QAction(MainWindow);
        actionMacOS->setObjectName("actionMacOS");
        actionMacOS->setCheckable(true);
        actionManjaroMix = new QAction(MainWindow);
        actionManjaroMix->setObjectName("actionManjaroMix");
        actionManjaroMix->setCheckable(true);
        actionMaterialDark = new QAction(MainWindow);
        actionMaterialDark->setObjectName("actionMaterialDark");
        actionMaterialDark->setCheckable(true);
        actionNeonButtons = new QAction(MainWindow);
        actionNeonButtons->setObjectName("actionNeonButtons");
        actionNeonButtons->setCheckable(true);
        actionUbuntu = new QAction(MainWindow);
        actionUbuntu->setObjectName("actionUbuntu");
        actionUbuntu->setCheckable(true);
        actionAboutQT = new QAction(MainWindow);
        actionAboutQT->setObjectName("actionAboutQT");
        actionAboutQT->setMenuRole(QAction::NoRole);
        actionDark = new QAction(MainWindow);
        actionDark->setObjectName("actionDark");
        actionDark->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/qss/res/QSS/QSS_IMG/DarkTheme.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDark->setIcon(icon1);
        actionLight = new QAction(MainWindow);
        actionLight->setObjectName("actionLight");
        actionLight->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/qss/res/QSS/QSS_IMG/LightTheme.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLight->setIcon(icon2);
        actionShowNameCol = new QAction(MainWindow);
        actionShowNameCol->setObjectName("actionShowNameCol");
        actionShowNameCol->setCheckable(true);
        actionShowNameCol->setMenuRole(QAction::NoRole);
        actionShowPathCol = new QAction(MainWindow);
        actionShowPathCol->setObjectName("actionShowPathCol");
        actionShowPathCol->setCheckable(true);
        actionShowPathCol->setMenuRole(QAction::NoRole);
        actionShowSizeCol = new QAction(MainWindow);
        actionShowSizeCol->setObjectName("actionShowSizeCol");
        actionShowSizeCol->setCheckable(true);
        actionShowSizeCol->setMenuRole(QAction::NoRole);
        actionShowTypeCol = new QAction(MainWindow);
        actionShowTypeCol->setObjectName("actionShowTypeCol");
        actionShowTypeCol->setCheckable(true);
        actionShowTypeCol->setMenuRole(QAction::NoRole);
        actionShowCreateDateCol = new QAction(MainWindow);
        actionShowCreateDateCol->setObjectName("actionShowCreateDateCol");
        actionShowCreateDateCol->setCheckable(true);
        actionShowCreateDateCol->setMenuRole(QAction::NoRole);
        actionShowModifyDateCol = new QAction(MainWindow);
        actionShowModifyDateCol->setObjectName("actionShowModifyDateCol");
        actionShowModifyDateCol->setCheckable(true);
        actionShowModifyDateCol->setMenuRole(QAction::NoRole);
        actionShowLastModDateCol = new QAction(MainWindow);
        actionShowLastModDateCol->setObjectName("actionShowLastModDateCol");
        actionShowLastModDateCol->setCheckable(true);
        actionShowLastModDateCol->setMenuRole(QAction::NoRole);
        actionShowHashCol = new QAction(MainWindow);
        actionShowHashCol->setObjectName("actionShowHashCol");
        actionShowHashCol->setCheckable(true);
        actionShowHashCol->setMenuRole(QAction::NoRole);
        actionShowEncrCol = new QAction(MainWindow);
        actionShowEncrCol->setObjectName("actionShowEncrCol");
        actionShowEncrCol->setCheckable(true);
        actionShowEncrCol->setMenuRole(QAction::NoRole);
        actionAutoFit = new QAction(MainWindow);
        actionAutoFit->setObjectName("actionAutoFit");
        actionAutoFit->setMenuRole(QAction::NoRole);
        actionAutoFitColWidth = new QAction(MainWindow);
        actionAutoFitColWidth->setObjectName("actionAutoFitColWidth");
        actionAutoFitColWidth->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setVerticalSpacing(1);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(3, 1, 3, 0);
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(0, 26));
        lineEdit->setMaximumSize(QSize(16777215, 26));
        lineEdit->setFont(font);
        lineEdit->setStyleSheet(QString::fromUtf8(""));
        lineEdit->setFrame(true);

        horizontalLayout->addWidget(lineEdit);

        comBoxFilter = new QComboBox(layoutWidget);
        comBoxFilter->addItem(QString());
        comBoxFilter->addItem(QString());
        comBoxFilter->addItem(QString());
        comBoxFilter->addItem(QString());
        comBoxFilter->addItem(QString());
        comBoxFilter->addItem(QString());
        comBoxFilter->addItem(QString());
        comBoxFilter->addItem(QString());
        comBoxFilter->setObjectName("comBoxFilter");
        comBoxFilter->setEnabled(true);
        comBoxFilter->setMinimumSize(QSize(0, 26));
        comBoxFilter->setMaximumSize(QSize(16777215, 26));
        comBoxFilter->setFont(font);
        comBoxFilter->setFrame(true);

        horizontalLayout->addWidget(comBoxFilter);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        stackedWidgetView = new QStackedWidget(splitter);
        stackedWidgetView->setObjectName("stackedWidgetView");
        TableViewPage = new QWidget();
        TableViewPage->setObjectName("TableViewPage");
        gridLayout_2 = new QGridLayout(TableViewPage);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tableView = new MyTableView(TableViewPage);
        tableView->setObjectName("tableView");
        tableView->setFont(font);
        tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableView->setShowGrid(false);
        tableView->setSortingEnabled(true);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(tableView, 0, 0, 1, 1);

        stackedWidgetView->addWidget(TableViewPage);
        ListViewPage = new QWidget();
        ListViewPage->setObjectName("ListViewPage");
        gridLayout_3 = new QGridLayout(ListViewPage);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        listView = new QListView(ListViewPage);
        listView->setObjectName("listView");
        listView->setFont(font);
        listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listView->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout_3->addWidget(listView, 0, 0, 1, 1);

        stackedWidgetView->addWidget(ListViewPage);
        IconViewPage = new QWidget();
        IconViewPage->setObjectName("IconViewPage");
        gridLayout_4 = new QGridLayout(IconViewPage);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        IconView = new QListView(IconViewPage);
        IconView->setObjectName("IconView");
        IconView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        IconView->setSelectionBehavior(QAbstractItemView::SelectRows);
        IconView->setViewMode(QListView::IconMode);

        gridLayout_4->addWidget(IconView, 0, 0, 1, 1);

        stackedWidgetView->addWidget(IconViewPage);
        splitter->addWidget(stackedWidgetView);
        lbPreview = new QLabel(splitter);
        lbPreview->setObjectName("lbPreview");
        lbPreview->setFont(font);
        lbPreview->setAlignment(Qt::AlignCenter);
        lbPreview->setWordWrap(true);
        splitter->addWidget(lbPreview);

        verticalLayout->addWidget(splitter);

        splitter_2->addWidget(layoutWidget);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setFont(font);
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setEnabled(true);
        menubar->setGeometry(QRect(0, 0, 852, 23));
        menubar->setCursor(QCursor(Qt::ArrowCursor));
        menubar->setDefaultUp(false);
        menubar->setNativeMenuBar(true);
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu->setFont(font);
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_2->setFont(font);
        menu_6 = new QMenu(menu_2);
        menu_6->setObjectName("menu_6");
        menu_6->setFont(font);
        menu_8 = new QMenu(menu_2);
        menu_8->setObjectName("menu_8");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        menu_3->setFont(font);
        menu_7 = new QMenu(menu_3);
        menu_7->setObjectName("menu_7");
        menu_7->setFont(font);
        menu_S = new QMenu(menu_3);
        menu_S->setObjectName("menu_S");
        menu_S->setFont(font);
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName("menu_4");
        menu_4->setFont(font);
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName("menu_5");
        menu_5->setFont(font);
        menu_A = new QMenu(menubar);
        menu_A->setObjectName("menu_A");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setFont(font);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menubar->addAction(menu_A->menuAction());
        menu->addAction(actionDaori);
        menu->addAction(actionDaochu1);
        menu->addSeparator();
        menu->addAction(actionJiaMi);
        menu->addAction(actionJieMi);
        menu->addSeparator();
        menu->addAction(actionWenJianBaoGao);
        menu->addSeparator();
        menu->addAction(actionExit);
        menu_2->addAction(actionCopy);
        menu_2->addAction(actionCut);
        menu_2->addAction(actionPast);
        menu_2->addAction(actionReName);
        menu_2->addAction(actionDelete);
        menu_2->addSeparator();
        menu_2->addAction(actionSelectAll);
        menu_2->addAction(actionDeselect);
        menu_2->addSeparator();
        menu_2->addAction(actionAddTag);
        menu_2->addAction(actionRemoveTag);
        menu_2->addSeparator();
        menu_2->addAction(menu_8->menuAction());
        menu_2->addAction(menu_6->menuAction());
        menu_6->addAction(actionCN);
        menu_6->addAction(actionEN);
        menu_6->addAction(actionJP);
        menu_8->addAction(actionLight);
        menu_8->addSeparator();
        menu_8->addAction(actionAqua);
        menu_8->addAction(actionMacOS);
        menu_8->addAction(actionNeonButtons);
        menu_8->addAction(actionUbuntu);
        menu_8->addSeparator();
        menu_8->addAction(actionDark);
        menu_8->addSeparator();
        menu_8->addAction(actionAMOLED);
        menu_8->addAction(actionConsoleStyle);
        menu_8->addAction(actionManjaroMix);
        menu_8->addAction(actionMaterialDark);
        menu_3->addAction(actionFilter);
        menu_3->addAction(actionPreview);
        menu_3->addAction(actionStatusBar);
        menu_3->addSeparator();
        menu_3->addAction(actionListView);
        menu_3->addAction(actionIconView);
        menu_3->addAction(actionDetailView);
        menu_3->addSeparator();
        menu_3->addAction(menu_7->menuAction());
        menu_3->addSeparator();
        menu_3->addAction(menu_S->menuAction());
        menu_3->addAction(actionShowHideFile);
        menu_3->addAction(actionRefresh);
        menu_7->addAction(actionBigFont);
        menu_7->addAction(actionSmallFont);
        menu_7->addSeparator();
        menu_7->addAction(actionGeneralFont);
        menu_S->addAction(actionFileName);
        menu_S->addAction(actionFileDate);
        menu_S->addAction(actionFileSize);
        menu_S->addAction(actionFilePath);
        menu_S->addAction(actionFileSuffix);
        menu_S->addAction(actionFileType);
        menu_S->addAction(actionFileCreateDate);
        menu_S->addAction(actionFileModifyDate);
        menu_S->addSeparator();
        menu_S->addAction(actionAsc);
        menu_S->addAction(actionDesc);
        menu_4->addAction(actionAdvancedSearch);
        menu_4->addSeparator();
        menu_4->addAction(actionFileSynchronization);
        menu_4->addAction(actionBatchRename);
        menu_4->addAction(actionFileDuplication);
        menu_4->addSeparator();
        menu_4->addAction(actionDiskspaceAnalysis);
        menu_4->addAction(actionDocumentComparison);
        menu_4->addSeparator();
        menu_4->addAction(actionTransmission);
        menu_4->addAction(actionPS);
        menu_5->addAction(actionUserManual);
        menu_5->addAction(actionQuickStartGuide);
        menu_5->addSeparator();
        menu_5->addAction(actionAutoRun);
        menu_5->addAction(actionEnableFileLog);
        menu_5->addAction(actionUpdateSys);
        menu_5->addSeparator();
        menu_5->addAction(actionAboutQT);
        menu_5->addAction(actionAbout);
        menu_5->addSeparator();
        menu_5->addAction(actionFeedback);
        menu_5->addSeparator();
        menu_A->addAction(actionCategorization);
        menu_A->addAction(actionteStimonial);
        menu_A->addSeparator();
        menu_A->addAction(actionStatisticalAnalysis);
        menu_A->addSeparator();
        menu_A->addAction(actionRelationships);
        toolBar->addAction(actionDaori);
        toolBar->addAction(actionTransmission);
        toolBar->addAction(actionPS);

        retranslateUi(MainWindow);

        stackedWidgetView->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ICMA\342\200\224\342\200\224\346\231\272\350\203\275\345\206\205\345\256\271\347\256\241\347\220\206\345\212\251\346\211\213", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216ICMA", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213ICMA\347\233\270\345\205\263\344\277\241\346\201\257.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAbout->setStatusTip(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213ICMA\347\233\270\345\205\263\344\277\241\346\201\257.", nullptr));
#endif // QT_CONFIG(statustip)
        actionDaori->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(statustip)
        actionDaori->setStatusTip(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\226\207\344\273\266\346\210\226\346\226\207\344\273\266\345\244\271.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionDaori->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDaochu1->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\351\200\211\344\270\255\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionDaochu1->setToolTip(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\211\200\351\200\211\346\213\251\347\232\204\346\211\200\346\234\211\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDaochu1->setStatusTip(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\211\200\351\200\211\346\226\207\344\273\266.", nullptr));
#endif // QT_CONFIG(statustip)
        actionJiaMi->setText(QCoreApplication::translate("MainWindow", "\345\212\240\345\257\206\351\200\211\344\270\255\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionJiaMi->setToolTip(QCoreApplication::translate("MainWindow", "\345\212\240\345\257\206\346\211\200\351\200\211\344\270\255\347\232\204\346\211\200\346\234\211\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionJieMi->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\257\206\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionJieMi->setToolTip(QCoreApplication::translate("MainWindow", "\350\247\243\345\257\206\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionWenJianBaoGao->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\226\207\344\273\266\346\212\245\345\221\212", nullptr));
#if QT_CONFIG(tooltip)
        actionWenJianBaoGao->setToolTip(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\226\207\344\273\266\346\212\245\345\221\212", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272(&X)", nullptr));
#if QT_CONFIG(tooltip)
        actionExit->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionExit->setStatusTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272ICMA.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266(&C)", nullptr));
#if QT_CONFIG(tooltip)
        actionCopy->setToolTip(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionCopy->setStatusTip(QCoreApplication::translate("MainWindow", "\345\260\206\351\200\211\344\270\255\345\206\205\345\256\271\345\244\215\345\210\266\345\210\260\345\211\252\350\264\264\346\235\277.\350\246\201\346\212\212\345\256\203\345\244\215\345\210\266\345\210\260\345\205\266\344\273\226\345\234\260\346\226\271,\350\257\267\344\275\277\347\224\250\347\262\230\350\264\264\345\212\237\350\203\275.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207(&T)", nullptr));
#if QT_CONFIG(statustip)
        actionCut->setStatusTip(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\351\200\211\344\270\255\345\206\205\345\256\271,\345\271\266\345\244\215\345\210\266\345\210\260\345\211\252\350\264\264\346\235\277.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPast->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264(&P)", nullptr));
#if QT_CONFIG(tooltip)
        actionPast->setToolTip(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionPast->setStatusTip(QCoreApplication::translate("MainWindow", "\345\260\206\345\244\215\345\210\266\346\210\226\345\211\252\345\210\207\347\232\204\345\206\205\345\256\271\346\217\222\345\205\245\346\255\244\345\244\204.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionPast->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionReName->setText(QCoreApplication::translate("MainWindow", "\351\207\215\345\221\275\345\220\215(&M)", nullptr));
#if QT_CONFIG(tooltip)
        actionReName->setToolTip(QCoreApplication::translate("MainWindow", "\351\207\215\345\221\275\345\220\215\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionReName->setStatusTip(QCoreApplication::translate("MainWindow", "\351\207\215\345\221\275\345\220\215\351\200\211\344\270\255\347\232\204\351\241\271\347\233\256.", nullptr));
#endif // QT_CONFIG(statustip)
        actionDelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244(&D)", nullptr));
#if QT_CONFIG(tooltip)
        actionDelete->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDelete->setStatusTip(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\211\200\351\200\211\351\241\271\347\233\256.", nullptr));
#endif // QT_CONFIG(statustip)
        actionSelectAll->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211(&A)", nullptr));
#if QT_CONFIG(tooltip)
        actionSelectAll->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\205\250\351\203\250", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionSelectAll->setStatusTip(QCoreApplication::translate("MainWindow", "\351\200\211\344\270\255\345\205\250\351\203\250\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionSelectAll->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDeselect->setText(QCoreApplication::translate("MainWindow", "\345\217\215\351\200\211(&I)", nullptr));
#if QT_CONFIG(tooltip)
        actionDeselect->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\215\351\200\211", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDeselect->setStatusTip(QCoreApplication::translate("MainWindow", "\345\260\206\347\233\256\345\211\215\351\200\211\344\270\255\351\241\271\345\217\226\346\266\210,\346\224\271\351\200\211\345\205\266\344\275\231\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAddTag->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\240\207\347\255\276", nullptr));
#if QT_CONFIG(tooltip)
        actionAddTag->setToolTip(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\240\207\347\255\276", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRemoveTag->setText(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\346\240\207\347\255\276", nullptr));
#if QT_CONFIG(tooltip)
        actionRemoveTag->setToolTip(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\346\240\207\347\255\276", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCN->setText(QCoreApplication::translate("MainWindow", "\344\270\255\346\226\207", nullptr));
#if QT_CONFIG(tooltip)
        actionCN->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\344\270\272\344\270\255\346\226\207\347\225\214\351\235\242", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionCN->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\344\270\255\346\226\207\347\225\214\351\235\242.", nullptr));
#endif // QT_CONFIG(statustip)
        actionEN->setText(QCoreApplication::translate("MainWindow", "\350\213\261\346\226\207", nullptr));
#if QT_CONFIG(tooltip)
        actionEN->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\344\270\272\350\213\261\346\226\207\347\225\214\351\235\242", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionEN->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\350\213\261\346\226\207\347\225\214\351\235\242.", nullptr));
#endif // QT_CONFIG(statustip)
        actionPreview->setText(QCoreApplication::translate("MainWindow", "\351\242\204\350\247\210(&P)", nullptr));
#if QT_CONFIG(tooltip)
        actionPreview->setToolTip(QCoreApplication::translate("MainWindow", "\351\242\204\350\247\210", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionPreview->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\210\226\351\232\220\350\227\217\351\242\204\350\247\210\347\252\227\345\217\243.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionPreview->setShortcut(QCoreApplication::translate("MainWindow", "Alt+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionStatusBar->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217(&B)", nullptr));
#if QT_CONFIG(tooltip)
        actionStatusBar->setToolTip(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionStatusBar->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\210\226\351\232\220\350\227\217\347\212\266\346\200\201\346\240\217.", nullptr));
#endif // QT_CONFIG(statustip)
        actionListView->setText(QCoreApplication::translate("MainWindow", "\345\210\227\350\241\250\350\247\206\345\233\276", nullptr));
#if QT_CONFIG(tooltip)
        actionListView->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\227\350\241\250\350\247\206\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionListView->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\210\227\350\241\250\345\275\242\345\274\217\346\230\276\347\244\272.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionListView->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionIconView->setText(QCoreApplication::translate("MainWindow", "\345\233\276\346\240\207\350\247\206\345\233\276", nullptr));
#if QT_CONFIG(tooltip)
        actionIconView->setToolTip(QCoreApplication::translate("MainWindow", "\345\233\276\346\240\207\350\247\206\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionIconView->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\233\276\346\240\207\345\275\242\345\274\217\346\230\276\347\244\272", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionIconView->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDetailView->setText(QCoreApplication::translate("MainWindow", "\350\257\246\347\273\206\344\277\241\346\201\257\350\247\206\345\233\276", nullptr));
#if QT_CONFIG(tooltip)
        actionDetailView->setToolTip(QCoreApplication::translate("MainWindow", "\350\257\246\347\273\206\344\277\241\346\201\257\350\247\206\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDetailView->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\233\264\350\257\246\347\273\206\347\232\204\344\277\241\346\201\257.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionDetailView->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+6", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBigFont->setText(QCoreApplication::translate("MainWindow", "\345\242\236\345\244\247(&I)", nullptr));
#if QT_CONFIG(statustip)
        actionBigFont->setStatusTip(QCoreApplication::translate("MainWindow", "\345\242\236\345\244\247\347\263\273\347\273\237\345\255\227\344\275\223\346\230\276\347\244\272.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionBigFont->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+=", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSmallFont->setText(QCoreApplication::translate("MainWindow", "\345\207\217\345\260\217(&D)", nullptr));
#if QT_CONFIG(tooltip)
        actionSmallFont->setToolTip(QCoreApplication::translate("MainWindow", "\345\207\217\345\260\217\345\255\227\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionSmallFont->setStatusTip(QCoreApplication::translate("MainWindow", "\347\274\251\345\260\217\347\263\273\347\273\237\345\255\227\344\275\223\346\230\276\347\244\272.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionSmallFont->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+-", nullptr));
#endif // QT_CONFIG(shortcut)
        actionGeneralFont->setText(QCoreApplication::translate("MainWindow", "\346\255\243\345\270\270(&N)", nullptr));
#if QT_CONFIG(tooltip)
        actionGeneralFont->setToolTip(QCoreApplication::translate("MainWindow", "\346\255\243\345\270\270\345\255\227\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionGeneralFont->setStatusTip(QCoreApplication::translate("MainWindow", "\351\207\215\347\275\256\345\233\236\351\273\230\350\256\244\347\263\273\347\273\237\346\230\276\347\244\272\357\274\21010\345\217\267\357\274\211.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionGeneralFont->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+0", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileName->setText(QCoreApplication::translate("MainWindow", "\345\220\215\347\247\260", nullptr));
#if QT_CONFIG(statustip)
        actionFileName->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\220\215\347\247\260\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFileName->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileDate->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\234\237", nullptr));
#if QT_CONFIG(statustip)
        actionFileDate->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\346\227\245\346\234\237\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFileDate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileSize->setText(QCoreApplication::translate("MainWindow", "\345\244\247\345\260\217", nullptr));
#if QT_CONFIG(statustip)
        actionFileSize->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\244\247\345\260\217\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFileSize->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFilePath->setText(QCoreApplication::translate("MainWindow", "\350\267\257\345\276\204", nullptr));
#if QT_CONFIG(statustip)
        actionFilePath->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\350\267\257\345\276\204\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFilePath->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+4", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileSuffix->setText(QCoreApplication::translate("MainWindow", "\346\211\251\345\261\225\345\220\215", nullptr));
#if QT_CONFIG(tooltip)
        actionFileSuffix->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\251\345\261\225\345\220\215", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionFileSuffix->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\346\211\251\345\261\225\345\220\215\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFileSuffix->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileType->setText(QCoreApplication::translate("MainWindow", "\347\261\273\345\236\213", nullptr));
#if QT_CONFIG(statustip)
        actionFileType->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\347\261\273\345\236\213\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFileType->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+6", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileCreateDate->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\227\245\346\234\237", nullptr));
#if QT_CONFIG(statustip)
        actionFileCreateDate->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\210\233\345\273\272\346\227\245\346\234\237\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFileCreateDate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+7", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileModifyDate->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\346\227\245\346\234\237", nullptr));
#if QT_CONFIG(statustip)
        actionFileModifyDate->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\344\277\256\346\224\271\346\227\245\346\234\237\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFileModifyDate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+8", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAsc->setText(QCoreApplication::translate("MainWindow", "\345\215\207\345\272\217(&A)", nullptr));
#if QT_CONFIG(statustip)
        actionAsc->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\215\207\345\272\217\346\226\271\345\274\217\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
        actionDesc->setText(QCoreApplication::translate("MainWindow", "\351\231\215\345\272\217(&D)", nullptr));
#if QT_CONFIG(statustip)
        actionDesc->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\351\231\215\345\272\217\346\226\271\345\274\217\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
        actionFilter->setText(QCoreApplication::translate("MainWindow", "\350\277\207\346\273\244\345\231\250(&F)", nullptr));
#if QT_CONFIG(tooltip)
        actionFilter->setToolTip(QCoreApplication::translate("MainWindow", "\350\277\207\346\273\244\345\231\250", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionFilter->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\210\226\351\232\220\350\227\217\350\277\207\346\273\244\346\240\217.", nullptr));
#endif // QT_CONFIG(statustip)
        actionShowHideFile->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\351\232\220\350\227\217\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(statustip)
        actionShowHideFile->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\210\226\351\232\220\350\227\217\351\232\220\350\227\217\346\226\207\344\273\266.", nullptr));
#endif // QT_CONFIG(statustip)
        actionRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260(&R)", nullptr));
#if QT_CONFIG(tooltip)
        actionRefresh->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionRefresh->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAdvancedSearch->setText(QCoreApplication::translate("MainWindow", "\351\253\230\347\272\247\346\220\234\347\264\242", nullptr));
#if QT_CONFIG(tooltip)
        actionAdvancedSearch->setToolTip(QCoreApplication::translate("MainWindow", "\351\253\230\347\272\247\346\220\234\347\264\242", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFileSynchronization->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\214\346\255\245", nullptr));
#if QT_CONFIG(tooltip)
        actionFileSynchronization->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\214\346\255\245", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBatchRename->setText(QCoreApplication::translate("MainWindow", "\346\211\271\351\207\217\351\207\215\345\221\275\345\220\215", nullptr));
#if QT_CONFIG(tooltip)
        actionBatchRename->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\271\351\207\217\351\207\215\345\221\275\345\220\215", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFileDuplication->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\216\273\351\207\215", nullptr));
#if QT_CONFIG(tooltip)
        actionFileDuplication->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\216\273\351\207\215", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDiskspaceAnalysis->setText(QCoreApplication::translate("MainWindow", "\347\243\201\347\233\230\347\251\272\351\227\264\345\210\206\346\236\220", nullptr));
#if QT_CONFIG(tooltip)
        actionDiskspaceAnalysis->setToolTip(QCoreApplication::translate("MainWindow", "\347\243\201\347\233\230\347\251\272\351\227\264\345\210\206\346\236\220", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDocumentComparison->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\346\257\224\350\276\203", nullptr));
#if QT_CONFIG(tooltip)
        actionDocumentComparison->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\346\257\224\350\276\203", nullptr));
#endif // QT_CONFIG(tooltip)
        actionUserManual->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\346\211\213\345\206\214", nullptr));
        actionQuickStartGuide->setText(QCoreApplication::translate("MainWindow", "\345\277\253\351\200\237\345\205\245\351\227\250\346\214\207\345\257\274", nullptr));
#if QT_CONFIG(tooltip)
        actionQuickStartGuide->setToolTip(QCoreApplication::translate("MainWindow", "\345\277\253\351\200\237\345\205\245\351\227\250", nullptr));
#endif // QT_CONFIG(tooltip)
        actionUpdateSys->setText(QCoreApplication::translate("MainWindow", "\346\243\200\346\237\245\346\233\264\346\226\260", nullptr));
#if QT_CONFIG(tooltip)
        actionUpdateSys->setToolTip(QCoreApplication::translate("MainWindow", "\346\243\200\346\237\245\346\233\264\346\226\260", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFeedback->setText(QCoreApplication::translate("MainWindow", "\345\217\215\351\246\210/\346\212\245\345\221\212\351\227\256\351\242\230", nullptr));
#if QT_CONFIG(tooltip)
        actionFeedback->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\215\351\246\210\346\210\226\346\212\245\345\221\212\351\227\256\351\242\230", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCategorization->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\210\206\347\261\273", nullptr));
#if QT_CONFIG(tooltip)
        actionCategorization->setToolTip(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\210\206\347\261\273", nullptr));
#endif // QT_CONFIG(tooltip)
        actionteStimonial->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\346\216\250\350\215\220", nullptr));
#if QT_CONFIG(tooltip)
        actionteStimonial->setToolTip(QCoreApplication::translate("MainWindow", "\346\216\250\350\215\220\345\206\205\345\256\271", nullptr));
#endif // QT_CONFIG(tooltip)
        actionStatisticalAnalysis->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\347\273\237\350\256\241\345\210\206\346\236\220", nullptr));
        actionRelationships->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\205\263\347\263\273\345\233\276\350\260\261", nullptr));
#if QT_CONFIG(tooltip)
        actionRelationships->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\205\263\347\263\273\345\233\276\350\260\261", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAMOLED->setText(QCoreApplication::translate("MainWindow", "AMOLED", nullptr));
#if QT_CONFIG(tooltip)
        actionAMOLED->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250AMOLED\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAMOLED->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250AMOLED\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAqua->setText(QCoreApplication::translate("MainWindow", "Aqua", nullptr));
#if QT_CONFIG(tooltip)
        actionAqua->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250Aqua\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAqua->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250Aqua\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionConsoleStyle->setText(QCoreApplication::translate("MainWindow", "ConsoleStyle", nullptr));
#if QT_CONFIG(tooltip)
        actionConsoleStyle->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250ConsoleStyle\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionConsoleStyle->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250ConsoleStyle\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionTransmission->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\344\274\240\350\276\223\345\267\245\345\205\267", nullptr));
#if QT_CONFIG(statustip)
        actionTransmission->setStatusTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\344\274\240\350\276\223\345\267\245\345\205\267.", nullptr));
#endif // QT_CONFIG(statustip)
        actionJP->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\226\207", nullptr));
#if QT_CONFIG(statustip)
        actionJP->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\227\245\346\226\207\347\225\214\351\235\242.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAutoRun->setText(QCoreApplication::translate("MainWindow", "\345\274\200\346\234\272\350\207\252\345\220\257\345\212\250", nullptr));
#if QT_CONFIG(tooltip)
        actionAutoRun->setToolTip(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\346\210\226\350\200\205\347\246\201\347\224\250\345\274\200\346\234\272\350\207\252\345\220\257\345\212\250.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAutoRun->setStatusTip(QCoreApplication::translate("MainWindow", "\345\205\201\350\256\270ICMA\345\234\250\346\202\250\347\232\204\350\256\241\347\256\227\346\234\272\345\274\200\346\234\272\345\220\216\350\207\252\345\220\257\345\212\250.", nullptr));
#endif // QT_CONFIG(statustip)
        actionPS->setText(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\345\244\204\347\220\206", nullptr));
#if QT_CONFIG(tooltip)
        actionPS->setToolTip(QCoreApplication::translate("MainWindow", "\345\257\271\345\233\276\345\203\217\344\275\234\345\244\204\347\220\206", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionPS->setStatusTip(QCoreApplication::translate("MainWindow", "\347\256\200\345\215\225\347\232\204\345\244\204\347\220\206\346\202\250\347\232\204\345\233\276\347\211\207.", nullptr));
#endif // QT_CONFIG(statustip)
        actionEnableFileLog->setText(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\346\227\245\345\277\227\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionEnableFileLog->setToolTip(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\346\227\245\345\277\227\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionEnableFileLog->setStatusTip(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\346\210\226\347\246\201\346\255\242\346\227\245\345\277\227\346\226\207\344\273\266\347\224\237\346\210\220\357\274\210\345\273\272\350\256\256\346\202\250\345\220\257\347\224\250\357\274\211.", nullptr));
#endif // QT_CONFIG(statustip)
        actionMacOS->setText(QCoreApplication::translate("MainWindow", "MacOS", nullptr));
#if QT_CONFIG(tooltip)
        actionMacOS->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250MacOS\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionMacOS->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250MacOS\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionManjaroMix->setText(QCoreApplication::translate("MainWindow", "ManjaroMix", nullptr));
#if QT_CONFIG(tooltip)
        actionManjaroMix->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250ManjaroMix\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionManjaroMix->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250ManjaroMix\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionMaterialDark->setText(QCoreApplication::translate("MainWindow", "MaterialDark", nullptr));
#if QT_CONFIG(tooltip)
        actionMaterialDark->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250MaterialDark\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionMaterialDark->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250MaterialDark\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionNeonButtons->setText(QCoreApplication::translate("MainWindow", "NeonButtons", nullptr));
#if QT_CONFIG(tooltip)
        actionNeonButtons->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250NeonButtons\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionNeonButtons->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250NeonButtons\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionUbuntu->setText(QCoreApplication::translate("MainWindow", "Ubuntu", nullptr));
#if QT_CONFIG(tooltip)
        actionUbuntu->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250Ubuntu\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionUbuntu->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250Ubuntu\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAboutQT->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216QT", nullptr));
#if QT_CONFIG(statustip)
        actionAboutQT->setStatusTip(QCoreApplication::translate("MainWindow", "\344\276\235\346\215\256\345\215\217\350\256\256\345\220\221\346\202\250\345\261\225\347\244\272QT\347\232\204\344\277\241\346\201\257.", nullptr));
#endif // QT_CONFIG(statustip)
        actionDark->setText(QCoreApplication::translate("MainWindow", "\346\267\261\350\211\262", nullptr));
#if QT_CONFIG(tooltip)
        actionDark->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\267\261\350\211\262\344\270\273\351\242\230", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLight->setText(QCoreApplication::translate("MainWindow", "\346\265\205\350\211\262", nullptr));
#if QT_CONFIG(tooltip)
        actionLight->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\265\205\350\211\262\344\270\273\351\242\230", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowNameCol->setText(QCoreApplication::translate("MainWindow", "\345\220\215\347\247\260", nullptr));
#if QT_CONFIG(tooltip)
        actionShowNameCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\345\220\215\347\247\260\345\210\227\345\206\205\345\256\271(\345\233\272\345\256\232\346\230\276\347\244\272).", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowPathCol->setText(QCoreApplication::translate("MainWindow", "\350\267\257\345\276\204", nullptr));
#if QT_CONFIG(tooltip)
        actionShowPathCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\350\267\257\345\276\204\345\210\227\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowSizeCol->setText(QCoreApplication::translate("MainWindow", "\345\244\247\345\260\217", nullptr));
#if QT_CONFIG(tooltip)
        actionShowSizeCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\345\244\247\345\260\217\345\210\227\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowTypeCol->setText(QCoreApplication::translate("MainWindow", "\347\261\273\345\236\213", nullptr));
#if QT_CONFIG(tooltip)
        actionShowTypeCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\347\261\273\345\236\213\345\210\227\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowCreateDateCol->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\227\266\351\227\264", nullptr));
#if QT_CONFIG(tooltip)
        actionShowCreateDateCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\345\210\233\345\273\272\346\227\266\351\227\264\345\210\227\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowModifyDateCol->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
#if QT_CONFIG(tooltip)
        actionShowModifyDateCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\344\277\256\346\224\271\346\227\266\351\227\264\345\210\227\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowLastModDateCol->setText(QCoreApplication::translate("MainWindow", "\346\234\200\350\277\221\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
#if QT_CONFIG(tooltip)
        actionShowLastModDateCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\346\234\200\350\277\221\344\277\256\346\224\271\346\227\266\351\227\264\345\210\227\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowHashCol->setText(QCoreApplication::translate("MainWindow", "\345\223\210\345\270\214\345\200\274", nullptr));
#if QT_CONFIG(tooltip)
        actionShowHashCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\345\223\210\345\270\214\345\200\274\345\210\227\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowEncrCol->setText(QCoreApplication::translate("MainWindow", "\346\230\257\345\220\246\345\212\240\345\257\206", nullptr));
#if QT_CONFIG(tooltip)
        actionShowEncrCol->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\344\273\266\346\230\257\345\220\246\345\212\240\345\257\206\345\210\227\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAutoFit->setText(QCoreApplication::translate("MainWindow", "\350\207\252\351\200\202\345\272\224\346\240\217\347\233\256\345\244\247\345\260\217(&S)", nullptr));
#if QT_CONFIG(tooltip)
        actionAutoFit->setToolTip(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\346\225\264\346\240\217\347\233\256\345\210\260\345\220\210\351\200\202\345\244\247\345\260\217.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAutoFitColWidth->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\346\225\264\345\210\227\345\256\275(&W)", nullptr));
#if QT_CONFIG(tooltip)
        actionAutoFitColWidth->setToolTip(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\346\225\264\345\210\227\345\256\275\345\210\260\345\220\210\351\200\202\347\232\204\345\244\247\345\260\217.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionAutoFitColWidth->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+\\", nullptr));
#endif // QT_CONFIG(shortcut)
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\220\234\347\202\271\344\273\200\344\271\210...", nullptr));
        comBoxFilter->setItemText(0, QCoreApplication::translate("MainWindow", "\346\211\200\346\234\211", nullptr));
        comBoxFilter->setItemText(1, QCoreApplication::translate("MainWindow", "\351\237\263\351\242\221", nullptr));
        comBoxFilter->setItemText(2, QCoreApplication::translate("MainWindow", "\345\216\213\347\274\251\346\226\207\344\273\266", nullptr));
        comBoxFilter->setItemText(3, QCoreApplication::translate("MainWindow", "\346\226\207\346\241\243", nullptr));
        comBoxFilter->setItemText(4, QCoreApplication::translate("MainWindow", "\345\217\257\346\211\247\350\241\214\346\226\207\344\273\266", nullptr));
        comBoxFilter->setItemText(5, QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\244\271", nullptr));
        comBoxFilter->setItemText(6, QCoreApplication::translate("MainWindow", "\345\233\276\347\211\207", nullptr));
        comBoxFilter->setItemText(7, QCoreApplication::translate("MainWindow", "\350\247\206\351\242\221", nullptr));

        lbPreview->setText(QCoreApplication::translate("MainWindow", "\351\242\204\350\247\210\345\233\276", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", nullptr));
        menu_6->setTitle(QCoreApplication::translate("MainWindow", "\350\257\255\350\250\200", nullptr));
        menu_8->setTitle(QCoreApplication::translate("MainWindow", "\344\270\273\351\242\230", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\350\247\206\345\233\276(&V)", nullptr));
        menu_7->setTitle(QCoreApplication::translate("MainWindow", "\345\255\227\345\217\267(&T)", nullptr));
        menu_S->setTitle(QCoreApplication::translate("MainWindow", "\346\216\222\345\272\217(&S)", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267(&T)", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", nullptr));
        menu_A->setTitle(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\212\237\350\203\275(&A)", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
