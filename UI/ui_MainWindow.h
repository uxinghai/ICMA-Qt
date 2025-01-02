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
#include <QtWidgets/QGroupBox>
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
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionabout;
    QAction *actiondaori;
    QAction *actiondaochu1;
    QAction *actionjiami;
    QAction *actionjiemi;
    QAction *actionshengchengwenjianbaogao;
    QAction *actiontuichu;
    QAction *actioncopy;
    QAction *actioncut;
    QAction *actionpast;
    QAction *actionreName;
    QAction *actiondelete;
    QAction *actionselect_all;
    QAction *actiondeselect;
    QAction *actionadd_tag;
    QAction *actionremove_tag;
    QAction *actionCN;
    QAction *actionEN;
    QAction *actionpreview;
    QAction *actionstatusbar;
    QAction *actionlistView;
    QAction *actioniconView;
    QAction *actiondetaileview;
    QAction *actionbig;
    QAction *actionsmall;
    QAction *actiongeneral;
    QAction *actionname;
    QAction *actiondate;
    QAction *actionsize;
    QAction *actionpath;
    QAction *actionsufix;
    QAction *actiontype;
    QAction *actioncreatDate;
    QAction *actionmodifyDate;
    QAction *actionasc;
    QAction *actiondesc;
    QAction *actionfilter;
    QAction *actionshowOrhide;
    QAction *actionrefreash;
    QAction *actionAdvancedSearch;
    QAction *actionfilesynchronization;
    QAction *actionBatchRename;
    QAction *actionFile_de_duplication;
    QAction *actionDiskspaceAnalysis;
    QAction *actionDocumentComparison;
    QAction *actionuser_manual;
    QAction *actionQuickStartGuide;
    QAction *action_update;
    QAction *actionFeedback;
    QAction *actioncategorization;
    QAction *actiontestimonial;
    QAction *actionstatisticalAnalysis;
    QAction *actionrelationships;
    QAction *actionlight;
    QAction *actiondark;
    QAction *actionauto;
    QAction *actionnewWindow;
    QAction *actiontransmission;
    QAction *actionJP;
    QAction *actionautoRun;
    QAction *actionPS;
    QAction *actionenableFileLog;
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
    QTableView *tableView;
    QWidget *ListViewPage;
    QGridLayout *gridLayout_3;
    QListView *listView;
    QWidget *IconViewPage;
    QGridLayout *gridLayout_4;
    QListView *IconView;
    QLabel *lbPreview;
    QWidget *widget;
    QGridLayout *gridLayout_5;
    QGroupBox *GroupRecommand;
    QGroupBox *GroupStatistical;
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
        font.setPointSize(10);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/icons/logo/logo1024.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName("actionabout");
        QFont font1;
        font1.setPointSize(9);
        actionabout->setFont(font1);
        actiondaori = new QAction(MainWindow);
        actiondaori->setObjectName("actiondaori");
        actiondaori->setFont(font);
        actiondaochu1 = new QAction(MainWindow);
        actiondaochu1->setObjectName("actiondaochu1");
        actiondaochu1->setFont(font1);
        actionjiami = new QAction(MainWindow);
        actionjiami->setObjectName("actionjiami");
        actionjiami->setFont(font1);
        actionjiemi = new QAction(MainWindow);
        actionjiemi->setObjectName("actionjiemi");
        actionjiemi->setFont(font1);
        actionshengchengwenjianbaogao = new QAction(MainWindow);
        actionshengchengwenjianbaogao->setObjectName("actionshengchengwenjianbaogao");
        actionshengchengwenjianbaogao->setFont(font1);
        actiontuichu = new QAction(MainWindow);
        actiontuichu->setObjectName("actiontuichu");
        actiontuichu->setFont(font1);
        actioncopy = new QAction(MainWindow);
        actioncopy->setObjectName("actioncopy");
        actioncopy->setFont(font1);
        actioncut = new QAction(MainWindow);
        actioncut->setObjectName("actioncut");
        actioncut->setFont(font1);
        actionpast = new QAction(MainWindow);
        actionpast->setObjectName("actionpast");
        actionpast->setFont(font1);
        actionreName = new QAction(MainWindow);
        actionreName->setObjectName("actionreName");
        actionreName->setFont(font1);
        actiondelete = new QAction(MainWindow);
        actiondelete->setObjectName("actiondelete");
        actiondelete->setFont(font1);
        actionselect_all = new QAction(MainWindow);
        actionselect_all->setObjectName("actionselect_all");
        actionselect_all->setFont(font1);
        actiondeselect = new QAction(MainWindow);
        actiondeselect->setObjectName("actiondeselect");
        actiondeselect->setFont(font1);
        actionadd_tag = new QAction(MainWindow);
        actionadd_tag->setObjectName("actionadd_tag");
        actionadd_tag->setFont(font1);
        actionremove_tag = new QAction(MainWindow);
        actionremove_tag->setObjectName("actionremove_tag");
        actionremove_tag->setFont(font1);
        actionCN = new QAction(MainWindow);
        actionCN->setObjectName("actionCN");
        actionCN->setCheckable(true);
        actionCN->setChecked(true);
        actionCN->setFont(font1);
        actionEN = new QAction(MainWindow);
        actionEN->setObjectName("actionEN");
        actionEN->setCheckable(true);
        actionEN->setFont(font1);
        actionpreview = new QAction(MainWindow);
        actionpreview->setObjectName("actionpreview");
        actionpreview->setCheckable(true);
        actionpreview->setFont(font1);
        actionstatusbar = new QAction(MainWindow);
        actionstatusbar->setObjectName("actionstatusbar");
        actionstatusbar->setCheckable(true);
        actionstatusbar->setChecked(true);
        actionstatusbar->setFont(font1);
        actionlistView = new QAction(MainWindow);
        actionlistView->setObjectName("actionlistView");
        actionlistView->setCheckable(true);
        actionlistView->setFont(font1);
        actioniconView = new QAction(MainWindow);
        actioniconView->setObjectName("actioniconView");
        actioniconView->setCheckable(true);
        actioniconView->setFont(font1);
        actiondetaileview = new QAction(MainWindow);
        actiondetaileview->setObjectName("actiondetaileview");
        actiondetaileview->setCheckable(true);
        actiondetaileview->setChecked(true);
        actiondetaileview->setFont(font1);
        actionbig = new QAction(MainWindow);
        actionbig->setObjectName("actionbig");
        actionbig->setFont(font1);
        actionsmall = new QAction(MainWindow);
        actionsmall->setObjectName("actionsmall");
        actionsmall->setFont(font1);
        actiongeneral = new QAction(MainWindow);
        actiongeneral->setObjectName("actiongeneral");
        actiongeneral->setFont(font1);
        actionname = new QAction(MainWindow);
        actionname->setObjectName("actionname");
        actionname->setCheckable(true);
        actionname->setFont(font1);
        actiondate = new QAction(MainWindow);
        actiondate->setObjectName("actiondate");
        actiondate->setCheckable(true);
        actiondate->setFont(font1);
        actionsize = new QAction(MainWindow);
        actionsize->setObjectName("actionsize");
        actionsize->setCheckable(true);
        actionsize->setFont(font1);
        actionpath = new QAction(MainWindow);
        actionpath->setObjectName("actionpath");
        actionpath->setCheckable(true);
        actionpath->setChecked(true);
        actionpath->setFont(font1);
        actionsufix = new QAction(MainWindow);
        actionsufix->setObjectName("actionsufix");
        actionsufix->setCheckable(true);
        actionsufix->setFont(font1);
        actiontype = new QAction(MainWindow);
        actiontype->setObjectName("actiontype");
        actiontype->setCheckable(true);
        actiontype->setFont(font1);
        actioncreatDate = new QAction(MainWindow);
        actioncreatDate->setObjectName("actioncreatDate");
        actioncreatDate->setCheckable(true);
        actioncreatDate->setFont(font1);
        actionmodifyDate = new QAction(MainWindow);
        actionmodifyDate->setObjectName("actionmodifyDate");
        actionmodifyDate->setCheckable(true);
        actionmodifyDate->setFont(font1);
        actionasc = new QAction(MainWindow);
        actionasc->setObjectName("actionasc");
        actionasc->setCheckable(true);
        actionasc->setChecked(true);
        actionasc->setFont(font1);
        actiondesc = new QAction(MainWindow);
        actiondesc->setObjectName("actiondesc");
        actiondesc->setCheckable(true);
        actiondesc->setFont(font1);
        actionfilter = new QAction(MainWindow);
        actionfilter->setObjectName("actionfilter");
        actionfilter->setCheckable(true);
        actionfilter->setChecked(false);
        actionshowOrhide = new QAction(MainWindow);
        actionshowOrhide->setObjectName("actionshowOrhide");
        actionshowOrhide->setCheckable(true);
        actionrefreash = new QAction(MainWindow);
        actionrefreash->setObjectName("actionrefreash");
        actionAdvancedSearch = new QAction(MainWindow);
        actionAdvancedSearch->setObjectName("actionAdvancedSearch");
        actionfilesynchronization = new QAction(MainWindow);
        actionfilesynchronization->setObjectName("actionfilesynchronization");
        actionBatchRename = new QAction(MainWindow);
        actionBatchRename->setObjectName("actionBatchRename");
        actionFile_de_duplication = new QAction(MainWindow);
        actionFile_de_duplication->setObjectName("actionFile_de_duplication");
        actionDiskspaceAnalysis = new QAction(MainWindow);
        actionDiskspaceAnalysis->setObjectName("actionDiskspaceAnalysis");
        actionDocumentComparison = new QAction(MainWindow);
        actionDocumentComparison->setObjectName("actionDocumentComparison");
        actionuser_manual = new QAction(MainWindow);
        actionuser_manual->setObjectName("actionuser_manual");
        actionQuickStartGuide = new QAction(MainWindow);
        actionQuickStartGuide->setObjectName("actionQuickStartGuide");
        action_update = new QAction(MainWindow);
        action_update->setObjectName("action_update");
        actionFeedback = new QAction(MainWindow);
        actionFeedback->setObjectName("actionFeedback");
        actioncategorization = new QAction(MainWindow);
        actioncategorization->setObjectName("actioncategorization");
        actiontestimonial = new QAction(MainWindow);
        actiontestimonial->setObjectName("actiontestimonial");
        actionstatisticalAnalysis = new QAction(MainWindow);
        actionstatisticalAnalysis->setObjectName("actionstatisticalAnalysis");
        actionrelationships = new QAction(MainWindow);
        actionrelationships->setObjectName("actionrelationships");
        actionlight = new QAction(MainWindow);
        actionlight->setObjectName("actionlight");
        actionlight->setCheckable(true);
        actionlight->setChecked(true);
        actiondark = new QAction(MainWindow);
        actiondark->setObjectName("actiondark");
        actiondark->setCheckable(true);
        actionauto = new QAction(MainWindow);
        actionauto->setObjectName("actionauto");
        actionauto->setCheckable(true);
        actionnewWindow = new QAction(MainWindow);
        actionnewWindow->setObjectName("actionnewWindow");
        actiontransmission = new QAction(MainWindow);
        actiontransmission->setObjectName("actiontransmission");
        actionJP = new QAction(MainWindow);
        actionJP->setObjectName("actionJP");
        actionJP->setCheckable(true);
        actionautoRun = new QAction(MainWindow);
        actionautoRun->setObjectName("actionautoRun");
        actionautoRun->setCheckable(true);
        actionPS = new QAction(MainWindow);
        actionPS->setObjectName("actionPS");
        actionenableFileLog = new QAction(MainWindow);
        actionenableFileLog->setObjectName("actionenableFileLog");
        actionenableFileLog->setCheckable(true);
        actionenableFileLog->setChecked(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, -1, 0, 3);
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(0, 26));
        lineEdit->setMaximumSize(QSize(16777215, 26));
        lineEdit->setFont(font1);
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
        comBoxFilter->setFont(font1);
        comBoxFilter->setFrame(true);

        horizontalLayout->addWidget(comBoxFilter);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        stackedWidgetView = new QStackedWidget(splitter);
        stackedWidgetView->setObjectName("stackedWidgetView");
        TableViewPage = new QWidget();
        TableViewPage->setObjectName("TableViewPage");
        gridLayout_2 = new QGridLayout(TableViewPage);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(TableViewPage);
        tableView->setObjectName("tableView");
        tableView->setFont(font1);

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
        listView->setFont(font1);

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
        IconView->setViewMode(QListView::ViewMode::IconMode);

        gridLayout_4->addWidget(IconView, 0, 0, 1, 1);

        stackedWidgetView->addWidget(IconViewPage);
        splitter->addWidget(stackedWidgetView);
        lbPreview = new QLabel(splitter);
        lbPreview->setObjectName("lbPreview");
        lbPreview->setFont(font1);
        lbPreview->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lbPreview->setWordWrap(true);
        splitter->addWidget(lbPreview);

        verticalLayout->addWidget(splitter);

        splitter_2->addWidget(layoutWidget);
        widget = new QWidget(splitter_2);
        widget->setObjectName("widget");
        widget->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        widget->setAutoFillBackground(false);
        gridLayout_5 = new QGridLayout(widget);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setHorizontalSpacing(0);
        gridLayout_5->setVerticalSpacing(3);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        GroupRecommand = new QGroupBox(widget);
        GroupRecommand->setObjectName("GroupRecommand");
        GroupRecommand->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_5->addWidget(GroupRecommand, 0, 0, 1, 1);

        GroupStatistical = new QGroupBox(widget);
        GroupStatistical->setObjectName("GroupStatistical");
        GroupStatistical->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_5->addWidget(GroupStatistical, 1, 0, 1, 1);

        splitter_2->addWidget(widget);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setFont(font1);
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setEnabled(true);
        menubar->setGeometry(QRect(0, 0, 852, 26));
        menubar->setCursor(QCursor(Qt::ArrowCursor));
        menubar->setDefaultUp(false);
        menubar->setNativeMenuBar(true);
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu->setFont(font1);
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_2->setFont(font1);
        menu_6 = new QMenu(menu_2);
        menu_6->setObjectName("menu_6");
        menu_6->setFont(font1);
        menu_8 = new QMenu(menu_2);
        menu_8->setObjectName("menu_8");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        menu_3->setFont(font1);
        menu_7 = new QMenu(menu_3);
        menu_7->setObjectName("menu_7");
        menu_7->setFont(font1);
        menu_S = new QMenu(menu_3);
        menu_S->setObjectName("menu_S");
        menu_S->setFont(font1);
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName("menu_4");
        menu_4->setFont(font1);
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName("menu_5");
        menu_5->setFont(font1);
        menu_A = new QMenu(menubar);
        menu_A->setObjectName("menu_A");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menubar->addAction(menu_A->menuAction());
        menu->addAction(actionnewWindow);
        menu->addSeparator();
        menu->addAction(actiondaori);
        menu->addAction(actiondaochu1);
        menu->addSeparator();
        menu->addAction(actionjiami);
        menu->addAction(actionjiemi);
        menu->addSeparator();
        menu->addAction(actionshengchengwenjianbaogao);
        menu->addSeparator();
        menu->addAction(actiontuichu);
        menu_2->addAction(actioncopy);
        menu_2->addAction(actioncut);
        menu_2->addAction(actionpast);
        menu_2->addAction(actionreName);
        menu_2->addAction(actiondelete);
        menu_2->addSeparator();
        menu_2->addAction(actionselect_all);
        menu_2->addAction(actiondeselect);
        menu_2->addSeparator();
        menu_2->addAction(actionadd_tag);
        menu_2->addAction(actionremove_tag);
        menu_2->addSeparator();
        menu_2->addAction(menu_8->menuAction());
        menu_2->addAction(menu_6->menuAction());
        menu_6->addAction(actionCN);
        menu_6->addAction(actionEN);
        menu_6->addAction(actionJP);
        menu_8->addAction(actionlight);
        menu_8->addAction(actiondark);
        menu_8->addSeparator();
        menu_8->addAction(actionauto);
        menu_3->addAction(actionfilter);
        menu_3->addAction(actionpreview);
        menu_3->addAction(actionstatusbar);
        menu_3->addSeparator();
        menu_3->addAction(actionlistView);
        menu_3->addAction(actioniconView);
        menu_3->addAction(actiondetaileview);
        menu_3->addSeparator();
        menu_3->addAction(menu_7->menuAction());
        menu_3->addSeparator();
        menu_3->addAction(menu_S->menuAction());
        menu_3->addAction(actionshowOrhide);
        menu_3->addAction(actionrefreash);
        menu_7->addAction(actionbig);
        menu_7->addAction(actionsmall);
        menu_7->addSeparator();
        menu_7->addAction(actiongeneral);
        menu_S->addAction(actionname);
        menu_S->addAction(actiondate);
        menu_S->addAction(actionsize);
        menu_S->addAction(actionpath);
        menu_S->addAction(actionsufix);
        menu_S->addAction(actiontype);
        menu_S->addAction(actioncreatDate);
        menu_S->addAction(actionmodifyDate);
        menu_S->addSeparator();
        menu_S->addAction(actionasc);
        menu_S->addAction(actiondesc);
        menu_4->addAction(actionAdvancedSearch);
        menu_4->addSeparator();
        menu_4->addAction(actionfilesynchronization);
        menu_4->addAction(actionBatchRename);
        menu_4->addAction(actionFile_de_duplication);
        menu_4->addSeparator();
        menu_4->addAction(actionDiskspaceAnalysis);
        menu_4->addAction(actionDocumentComparison);
        menu_4->addSeparator();
        menu_4->addAction(actiontransmission);
        menu_4->addAction(actionPS);
        menu_5->addAction(actionuser_manual);
        menu_5->addAction(actionQuickStartGuide);
        menu_5->addSeparator();
        menu_5->addAction(actionautoRun);
        menu_5->addAction(actionenableFileLog);
        menu_5->addAction(action_update);
        menu_5->addSeparator();
        menu_5->addAction(actionabout);
        menu_5->addAction(actionFeedback);
        menu_5->addSeparator();
        menu_A->addAction(actioncategorization);
        menu_A->addAction(actiontestimonial);
        menu_A->addSeparator();
        menu_A->addAction(actionstatisticalAnalysis);
        menu_A->addSeparator();
        menu_A->addAction(actionrelationships);
        toolBar->addAction(actiondaori);
        toolBar->addAction(actiontransmission);
        toolBar->addAction(actionPS);

        retranslateUi(MainWindow);

        stackedWidgetView->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ICMA\342\200\224\342\200\224\346\231\272\350\203\275\345\206\205\345\256\271\347\256\241\347\220\206\345\212\251\346\211\213", nullptr));
        actionabout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216ICMA", nullptr));
#if QT_CONFIG(tooltip)
        actionabout->setToolTip(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\350\275\257\344\273\266\344\273\213\347\273\215\344\277\241\346\201\257", nullptr));
#endif // QT_CONFIG(tooltip)
        actiondaori->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(statustip)
        actiondaori->setStatusTip(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\226\207\344\273\266\346\210\226\346\226\207\344\273\266\345\244\271.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actiondaori->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actiondaochu1->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\351\200\211\344\270\255\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actiondaochu1->setToolTip(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\211\200\351\200\211\346\213\251\347\232\204\346\211\200\346\234\211\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actiondaochu1->setStatusTip(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\211\200\351\200\211\346\226\207\344\273\266.", nullptr));
#endif // QT_CONFIG(statustip)
        actionjiami->setText(QCoreApplication::translate("MainWindow", "\345\212\240\345\257\206\351\200\211\344\270\255\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionjiami->setToolTip(QCoreApplication::translate("MainWindow", "\345\212\240\345\257\206\346\211\200\351\200\211\344\270\255\347\232\204\346\211\200\346\234\211\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionjiemi->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\257\206\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionjiemi->setToolTip(QCoreApplication::translate("MainWindow", "\350\247\243\345\257\206\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionshengchengwenjianbaogao->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\226\207\344\273\266\346\212\245\345\221\212", nullptr));
#if QT_CONFIG(tooltip)
        actionshengchengwenjianbaogao->setToolTip(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\226\207\344\273\266\346\212\245\345\221\212", nullptr));
#endif // QT_CONFIG(tooltip)
        actiontuichu->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272(&X)", nullptr));
#if QT_CONFIG(tooltip)
        actiontuichu->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actiontuichu->setStatusTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272ICMA.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actiontuichu->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actioncopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266(&C)", nullptr));
#if QT_CONFIG(tooltip)
        actioncopy->setToolTip(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actioncopy->setStatusTip(QCoreApplication::translate("MainWindow", "\345\260\206\351\200\211\344\270\255\345\206\205\345\256\271\345\244\215\345\210\266\345\210\260\345\211\252\350\264\264\346\235\277.\350\246\201\346\212\212\345\256\203\345\244\215\345\210\266\345\210\260\345\205\266\344\273\226\345\234\260\346\226\271,\350\257\267\344\275\277\347\224\250\347\262\230\350\264\264\345\212\237\350\203\275.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actioncopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actioncut->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207(&T)", nullptr));
#if QT_CONFIG(statustip)
        actioncut->setStatusTip(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\351\200\211\344\270\255\345\206\205\345\256\271,\345\271\266\345\244\215\345\210\266\345\210\260\345\211\252\350\264\264\346\235\277.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actioncut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionpast->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264(&P)", nullptr));
#if QT_CONFIG(tooltip)
        actionpast->setToolTip(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionpast->setStatusTip(QCoreApplication::translate("MainWindow", "\345\260\206\345\244\215\345\210\266\346\210\226\345\211\252\345\210\207\347\232\204\345\206\205\345\256\271\346\217\222\345\205\245\346\255\244\345\244\204.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionpast->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionreName->setText(QCoreApplication::translate("MainWindow", "\351\207\215\345\221\275\345\220\215(&M)", nullptr));
#if QT_CONFIG(tooltip)
        actionreName->setToolTip(QCoreApplication::translate("MainWindow", "\351\207\215\345\221\275\345\220\215\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionreName->setStatusTip(QCoreApplication::translate("MainWindow", "\351\207\215\345\221\275\345\220\215\351\200\211\344\270\255\347\232\204\351\241\271\347\233\256.", nullptr));
#endif // QT_CONFIG(statustip)
        actiondelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244(&D)", nullptr));
#if QT_CONFIG(tooltip)
        actiondelete->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actiondelete->setStatusTip(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\211\200\351\200\211\351\241\271\347\233\256.", nullptr));
#endif // QT_CONFIG(statustip)
        actionselect_all->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211(&A)", nullptr));
#if QT_CONFIG(tooltip)
        actionselect_all->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\205\250\351\203\250", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionselect_all->setStatusTip(QCoreApplication::translate("MainWindow", "\351\200\211\344\270\255\345\205\250\351\203\250\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionselect_all->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actiondeselect->setText(QCoreApplication::translate("MainWindow", "\345\217\215\351\200\211(&I)", nullptr));
#if QT_CONFIG(tooltip)
        actiondeselect->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\215\351\200\211", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actiondeselect->setStatusTip(QCoreApplication::translate("MainWindow", "\345\260\206\347\233\256\345\211\215\351\200\211\344\270\255\351\241\271\345\217\226\346\266\210,\346\224\271\351\200\211\345\205\266\344\275\231\345\206\205\345\256\271.", nullptr));
#endif // QT_CONFIG(statustip)
        actionadd_tag->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\240\207\347\255\276", nullptr));
#if QT_CONFIG(tooltip)
        actionadd_tag->setToolTip(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\240\207\347\255\276", nullptr));
#endif // QT_CONFIG(tooltip)
        actionremove_tag->setText(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\346\240\207\347\255\276", nullptr));
#if QT_CONFIG(tooltip)
        actionremove_tag->setToolTip(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\346\240\207\347\255\276", nullptr));
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
        actionpreview->setText(QCoreApplication::translate("MainWindow", "\351\242\204\350\247\210(&P)", nullptr));
#if QT_CONFIG(tooltip)
        actionpreview->setToolTip(QCoreApplication::translate("MainWindow", "\351\242\204\350\247\210", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionpreview->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\210\226\351\232\220\350\227\217\351\242\204\350\247\210\347\252\227\345\217\243.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionpreview->setShortcut(QCoreApplication::translate("MainWindow", "Alt+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionstatusbar->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217(&B)", nullptr));
#if QT_CONFIG(tooltip)
        actionstatusbar->setToolTip(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionstatusbar->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\210\226\351\232\220\350\227\217\347\212\266\346\200\201\346\240\217.", nullptr));
#endif // QT_CONFIG(statustip)
        actionlistView->setText(QCoreApplication::translate("MainWindow", "\345\210\227\350\241\250\350\247\206\345\233\276", nullptr));
#if QT_CONFIG(tooltip)
        actionlistView->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\227\350\241\250\350\247\206\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionlistView->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\210\227\350\241\250\345\275\242\345\274\217\346\230\276\347\244\272.", nullptr));
#endif // QT_CONFIG(statustip)
        actioniconView->setText(QCoreApplication::translate("MainWindow", "\345\233\276\346\240\207\350\247\206\345\233\276", nullptr));
#if QT_CONFIG(tooltip)
        actioniconView->setToolTip(QCoreApplication::translate("MainWindow", "\345\233\276\346\240\207\350\247\206\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actioniconView->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\233\276\346\240\207\345\275\242\345\274\217\346\230\276\347\244\272", nullptr));
#endif // QT_CONFIG(statustip)
        actiondetaileview->setText(QCoreApplication::translate("MainWindow", "\350\257\246\347\273\206\344\277\241\346\201\257\350\247\206\345\233\276", nullptr));
#if QT_CONFIG(tooltip)
        actiondetaileview->setToolTip(QCoreApplication::translate("MainWindow", "\350\257\246\347\273\206\344\277\241\346\201\257\350\247\206\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actiondetaileview->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\233\264\350\257\246\347\273\206\347\232\204\344\277\241\346\201\257.", nullptr));
#endif // QT_CONFIG(statustip)
        actionbig->setText(QCoreApplication::translate("MainWindow", "\345\242\236\345\244\247(&I)", nullptr));
#if QT_CONFIG(statustip)
        actionbig->setStatusTip(QCoreApplication::translate("MainWindow", "\345\242\236\345\244\247\347\263\273\347\273\237\345\255\227\344\275\223\346\230\276\347\244\272.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionbig->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+=", nullptr));
#endif // QT_CONFIG(shortcut)
        actionsmall->setText(QCoreApplication::translate("MainWindow", "\345\207\217\345\260\217(&D)", nullptr));
#if QT_CONFIG(tooltip)
        actionsmall->setToolTip(QCoreApplication::translate("MainWindow", "\345\207\217\345\260\217\345\255\227\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionsmall->setStatusTip(QCoreApplication::translate("MainWindow", "\347\274\251\345\260\217\347\263\273\347\273\237\345\255\227\344\275\223\346\230\276\347\244\272.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionsmall->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+-", nullptr));
#endif // QT_CONFIG(shortcut)
        actiongeneral->setText(QCoreApplication::translate("MainWindow", "\346\255\243\345\270\270(&N)", nullptr));
#if QT_CONFIG(tooltip)
        actiongeneral->setToolTip(QCoreApplication::translate("MainWindow", "\346\255\243\345\270\270\345\255\227\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actiongeneral->setStatusTip(QCoreApplication::translate("MainWindow", "\351\207\215\347\275\256\345\233\236\351\273\230\350\256\244\347\263\273\347\273\237\346\230\276\347\244\272\357\274\21010\345\217\267\357\274\211.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actiongeneral->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+0", nullptr));
#endif // QT_CONFIG(shortcut)
        actionname->setText(QCoreApplication::translate("MainWindow", "\345\220\215\347\247\260", nullptr));
#if QT_CONFIG(statustip)
        actionname->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\220\215\347\247\260\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionname->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+1", nullptr));
#endif // QT_CONFIG(shortcut)
        actiondate->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\234\237", nullptr));
#if QT_CONFIG(statustip)
        actiondate->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\346\227\245\346\234\237\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actiondate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionsize->setText(QCoreApplication::translate("MainWindow", "\345\244\247\345\260\217", nullptr));
#if QT_CONFIG(statustip)
        actionsize->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\244\247\345\260\217\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionsize->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionpath->setText(QCoreApplication::translate("MainWindow", "\350\267\257\345\276\204", nullptr));
#if QT_CONFIG(statustip)
        actionpath->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\350\267\257\345\276\204\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionpath->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+4", nullptr));
#endif // QT_CONFIG(shortcut)
        actionsufix->setText(QCoreApplication::translate("MainWindow", "\346\211\251\345\261\225\345\220\215", nullptr));
#if QT_CONFIG(tooltip)
        actionsufix->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\251\345\261\225\345\220\215", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionsufix->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\346\211\251\345\261\225\345\220\215\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionsufix->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+5", nullptr));
#endif // QT_CONFIG(shortcut)
        actiontype->setText(QCoreApplication::translate("MainWindow", "\347\261\273\345\236\213", nullptr));
#if QT_CONFIG(statustip)
        actiontype->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\347\261\273\345\236\213\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actiontype->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+6", nullptr));
#endif // QT_CONFIG(shortcut)
        actioncreatDate->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\227\245\346\234\237", nullptr));
#if QT_CONFIG(statustip)
        actioncreatDate->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\210\233\345\273\272\346\227\245\346\234\237\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actioncreatDate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+7", nullptr));
#endif // QT_CONFIG(shortcut)
        actionmodifyDate->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\346\227\245\346\234\237", nullptr));
#if QT_CONFIG(statustip)
        actionmodifyDate->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\344\277\256\346\224\271\346\227\245\346\234\237\344\270\272\345\255\227\346\256\265\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionmodifyDate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+8", nullptr));
#endif // QT_CONFIG(shortcut)
        actionasc->setText(QCoreApplication::translate("MainWindow", "\345\215\207\345\272\217(&A)", nullptr));
#if QT_CONFIG(statustip)
        actionasc->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\345\215\207\345\272\217\346\226\271\345\274\217\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
        actiondesc->setText(QCoreApplication::translate("MainWindow", "\351\231\215\345\272\217(&D)", nullptr));
#if QT_CONFIG(statustip)
        actiondesc->setStatusTip(QCoreApplication::translate("MainWindow", "\344\273\245\351\231\215\345\272\217\346\226\271\345\274\217\346\216\222\345\272\217.", nullptr));
#endif // QT_CONFIG(statustip)
        actionfilter->setText(QCoreApplication::translate("MainWindow", "\350\277\207\346\273\244\345\231\250(&F)", nullptr));
#if QT_CONFIG(tooltip)
        actionfilter->setToolTip(QCoreApplication::translate("MainWindow", "\350\277\207\346\273\244\345\231\250", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionfilter->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\210\226\351\232\220\350\227\217\350\277\207\346\273\244\346\240\217.", nullptr));
#endif // QT_CONFIG(statustip)
        actionshowOrhide->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272/\351\232\220\350\227\217\351\232\220\350\227\217\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(statustip)
        actionshowOrhide->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\210\226\351\232\220\350\227\217\351\232\220\350\227\217\346\226\207\344\273\266.", nullptr));
#endif // QT_CONFIG(statustip)
        actionrefreash->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260(&R)", nullptr));
#if QT_CONFIG(tooltip)
        actionrefreash->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAdvancedSearch->setText(QCoreApplication::translate("MainWindow", "\351\253\230\347\272\247\346\220\234\347\264\242", nullptr));
#if QT_CONFIG(tooltip)
        actionAdvancedSearch->setToolTip(QCoreApplication::translate("MainWindow", "\351\253\230\347\272\247\346\220\234\347\264\242", nullptr));
#endif // QT_CONFIG(tooltip)
        actionfilesynchronization->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\214\346\255\245", nullptr));
#if QT_CONFIG(tooltip)
        actionfilesynchronization->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\214\346\255\245", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBatchRename->setText(QCoreApplication::translate("MainWindow", "\346\211\271\351\207\217\351\207\215\345\221\275\345\220\215", nullptr));
#if QT_CONFIG(tooltip)
        actionBatchRename->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\271\351\207\217\351\207\215\345\221\275\345\220\215", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFile_de_duplication->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\216\273\351\207\215", nullptr));
#if QT_CONFIG(tooltip)
        actionFile_de_duplication->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\216\273\351\207\215", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDiskspaceAnalysis->setText(QCoreApplication::translate("MainWindow", "\347\243\201\347\233\230\347\251\272\351\227\264\345\210\206\346\236\220", nullptr));
#if QT_CONFIG(tooltip)
        actionDiskspaceAnalysis->setToolTip(QCoreApplication::translate("MainWindow", "\347\243\201\347\233\230\347\251\272\351\227\264\345\210\206\346\236\220", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDocumentComparison->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\346\257\224\350\276\203", nullptr));
#if QT_CONFIG(tooltip)
        actionDocumentComparison->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\346\257\224\350\276\203", nullptr));
#endif // QT_CONFIG(tooltip)
        actionuser_manual->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\346\211\213\345\206\214", nullptr));
        actionQuickStartGuide->setText(QCoreApplication::translate("MainWindow", "\345\277\253\351\200\237\345\205\245\351\227\250\346\214\207\345\257\274", nullptr));
#if QT_CONFIG(tooltip)
        actionQuickStartGuide->setToolTip(QCoreApplication::translate("MainWindow", "\345\277\253\351\200\237\345\205\245\351\227\250", nullptr));
#endif // QT_CONFIG(tooltip)
        action_update->setText(QCoreApplication::translate("MainWindow", "\346\243\200\346\237\245\346\233\264\346\226\260", nullptr));
#if QT_CONFIG(tooltip)
        action_update->setToolTip(QCoreApplication::translate("MainWindow", "\346\243\200\346\237\245\346\233\264\346\226\260", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFeedback->setText(QCoreApplication::translate("MainWindow", "\345\217\215\351\246\210/\346\212\245\345\221\212\351\227\256\351\242\230", nullptr));
#if QT_CONFIG(tooltip)
        actionFeedback->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\215\351\246\210\346\210\226\346\212\245\345\221\212\351\227\256\351\242\230", nullptr));
#endif // QT_CONFIG(tooltip)
        actioncategorization->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\210\206\347\261\273", nullptr));
#if QT_CONFIG(tooltip)
        actioncategorization->setToolTip(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\210\206\347\261\273", nullptr));
#endif // QT_CONFIG(tooltip)
        actiontestimonial->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\346\216\250\350\215\220", nullptr));
#if QT_CONFIG(tooltip)
        actiontestimonial->setToolTip(QCoreApplication::translate("MainWindow", "\346\216\250\350\215\220\345\206\205\345\256\271", nullptr));
#endif // QT_CONFIG(tooltip)
        actionstatisticalAnalysis->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\347\273\237\350\256\241\345\210\206\346\236\220", nullptr));
        actionrelationships->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\205\263\347\263\273\345\233\276\350\260\261", nullptr));
#if QT_CONFIG(tooltip)
        actionrelationships->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\205\263\347\263\273\345\233\276\350\260\261", nullptr));
#endif // QT_CONFIG(tooltip)
        actionlight->setText(QCoreApplication::translate("MainWindow", "\346\265\205\350\211\262\344\270\273\351\242\230(&L)", nullptr));
#if QT_CONFIG(statustip)
        actionlight->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\265\205\350\211\262\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actiondark->setText(QCoreApplication::translate("MainWindow", "\346\267\261\350\211\262\344\270\273\351\242\230(&D)", nullptr));
#if QT_CONFIG(statustip)
        actiondark->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\267\261\350\211\262\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionauto->setText(QCoreApplication::translate("MainWindow", "\350\267\237\351\232\217\347\263\273\347\273\237", nullptr));
#if QT_CONFIG(tooltip)
        actionauto->setToolTip(QCoreApplication::translate("MainWindow", "\350\267\237\351\232\217\347\263\273\347\273\237", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionauto->setStatusTip(QCoreApplication::translate("MainWindow", "\350\267\237\351\232\217\346\202\250\347\232\204\347\263\273\347\273\237\350\207\252\345\212\250\345\210\207\346\215\242\344\270\273\351\242\230.", nullptr));
#endif // QT_CONFIG(statustip)
        actionnewWindow->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\344\270\200\344\270\252\347\252\227\345\217\243(&N)", nullptr));
#if QT_CONFIG(tooltip)
        actionnewWindow->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\344\270\200\344\270\252\347\252\227\345\217\243", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionnewWindow->setStatusTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\200\344\270\252\346\226\260\347\232\204\347\252\227\345\217\243.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionnewWindow->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actiontransmission->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\344\274\240\350\276\223\345\267\245\345\205\267", nullptr));
#if QT_CONFIG(statustip)
        actiontransmission->setStatusTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\344\274\240\350\276\223\345\267\245\345\205\267.", nullptr));
#endif // QT_CONFIG(statustip)
        actionJP->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\226\207", nullptr));
#if QT_CONFIG(statustip)
        actionJP->setStatusTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\227\245\346\226\207\347\225\214\351\235\242.", nullptr));
#endif // QT_CONFIG(statustip)
        actionautoRun->setText(QCoreApplication::translate("MainWindow", "\345\274\200\346\234\272\350\207\252\345\220\257\345\212\250", nullptr));
#if QT_CONFIG(tooltip)
        actionautoRun->setToolTip(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\346\210\226\350\200\205\347\246\201\347\224\250\345\274\200\346\234\272\350\207\252\345\220\257\345\212\250.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionautoRun->setStatusTip(QCoreApplication::translate("MainWindow", "\346\230\257\345\220\246\345\205\201\350\256\270ICMA\345\234\250\346\202\250\347\232\204\350\256\241\347\256\227\346\234\272\345\274\200\346\234\272\345\220\216\350\207\252\345\220\257\345\212\250.", nullptr));
#endif // QT_CONFIG(statustip)
        actionPS->setText(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\345\244\204\347\220\206", nullptr));
#if QT_CONFIG(tooltip)
        actionPS->setToolTip(QCoreApplication::translate("MainWindow", "\345\257\271\345\233\276\345\203\217\344\275\234\345\244\204\347\220\206", nullptr));
#endif // QT_CONFIG(tooltip)
        actionenableFileLog->setText(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\346\227\245\345\277\227\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionenableFileLog->setToolTip(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\346\227\245\345\277\227\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionenableFileLog->setStatusTip(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\346\210\226\347\246\201\346\255\242\346\227\245\345\277\227\346\226\207\344\273\266\347\224\237\346\210\220\357\274\210\345\273\272\350\256\256\346\202\250\345\220\257\347\224\250\357\274\211.", nullptr));
#endif // QT_CONFIG(statustip)
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
        GroupRecommand->setTitle(QCoreApplication::translate("MainWindow", "\346\216\250\350\215\220", nullptr));
        GroupStatistical->setTitle(QCoreApplication::translate("MainWindow", "\347\273\237\350\256\241\345\210\206\346\236\220", nullptr));
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
