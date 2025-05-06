/********************************************************************************
** Form generated from reading UI file 'DiskAnalyzer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISKANALYZER_H
#define UI_DISKANALYZER_H

#include <QtCharts/QChartView>
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiskAnalyzer
{
public:
    QAction *actionScan;
    QAction *actionSwitchTo2D;
    QAction *actionSwitchTo3D;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *driveComboBox;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QTreeWidget *driveInfoWidget;
    QTreeView *directoryTreeView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTableView *fileTableView;
    QStackedWidget *chartStackedWidget;
    QWidget *pageChart2D;
    QVBoxLayout *verticalLayout_2;
    QChartView *chartView2D;
    QWidget *pageChart3D;
    QVBoxLayout *verticalLayout_3;
    QWidget *chartView3D;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *xAxisComboBox;
    QLabel *label_3;
    QComboBox *yAxisComboBox;
    QSpacerItem *horizontalSpacer_2;
    QWidget *barChartView;

    void setupUi(QMainWindow *DiskAnalyzer)
    {
        if (DiskAnalyzer->objectName().isEmpty())
            DiskAnalyzer->setObjectName("DiskAnalyzer");
        DiskAnalyzer->resize(1000, 700);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        DiskAnalyzer->setWindowIcon(icon);
        actionScan = new QAction(DiskAnalyzer);
        actionScan->setObjectName("actionScan");
        actionSwitchTo2D = new QAction(DiskAnalyzer);
        actionSwitchTo2D->setObjectName("actionSwitchTo2D");
        actionSwitchTo3D = new QAction(DiskAnalyzer);
        actionSwitchTo3D->setObjectName("actionSwitchTo3D");
        centralwidget = new QWidget(DiskAnalyzer);
        centralwidget->setObjectName("centralwidget");
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 20));
        label->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_3->addWidget(label);

        driveComboBox = new QComboBox(centralwidget);
        driveComboBox->setObjectName("driveComboBox");
        driveComboBox->setMinimumSize(QSize(0, 20));
        driveComboBox->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_3->addWidget(driveComboBox);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        driveInfoWidget = new QTreeWidget(splitter);
        driveInfoWidget->setObjectName("driveInfoWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(driveInfoWidget->sizePolicy().hasHeightForWidth());
        driveInfoWidget->setSizePolicy(sizePolicy);
        splitter->addWidget(driveInfoWidget);
        directoryTreeView = new QTreeView(splitter);
        directoryTreeView->setObjectName("directoryTreeView");
        splitter->addWidget(directoryTreeView);
        splitter_2->addWidget(splitter);
        tabWidget = new QTabWidget(splitter_2);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        fileTableView = new QTableView(tab);
        fileTableView->setObjectName("fileTableView");

        gridLayout_2->addWidget(fileTableView, 0, 0, 1, 1);

        chartStackedWidget = new QStackedWidget(tab);
        chartStackedWidget->setObjectName("chartStackedWidget");
        pageChart2D = new QWidget();
        pageChart2D->setObjectName("pageChart2D");
        verticalLayout_2 = new QVBoxLayout(pageChart2D);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        chartView2D = new QChartView(pageChart2D);
        chartView2D->setObjectName("chartView2D");
        chartView2D->setMinimumSize(QSize(0, 150));

        verticalLayout_2->addWidget(chartView2D);

        chartStackedWidget->addWidget(pageChart2D);
        pageChart3D = new QWidget();
        pageChart3D->setObjectName("pageChart3D");
        verticalLayout_3 = new QVBoxLayout(pageChart3D);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        chartView3D = new QWidget(pageChart3D);
        chartView3D->setObjectName("chartView3D");

        verticalLayout_3->addWidget(chartView3D);

        chartStackedWidget->addWidget(pageChart3D);

        gridLayout_2->addWidget(chartStackedWidget, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout = new QGridLayout(tab_2);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(tab_2);
        widget->setObjectName("widget");
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 20));
        label_2->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(label_2);

        xAxisComboBox = new QComboBox(groupBox);
        xAxisComboBox->addItem(QString());
        xAxisComboBox->addItem(QString());
        xAxisComboBox->addItem(QString());
        xAxisComboBox->addItem(QString());
        xAxisComboBox->addItem(QString());
        xAxisComboBox->setObjectName("xAxisComboBox");
        xAxisComboBox->setMinimumSize(QSize(0, 20));
        xAxisComboBox->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(xAxisComboBox);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 20));
        label_3->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(label_3);

        yAxisComboBox = new QComboBox(groupBox);
        yAxisComboBox->addItem(QString());
        yAxisComboBox->addItem(QString());
        yAxisComboBox->addItem(QString());
        yAxisComboBox->addItem(QString());
        yAxisComboBox->addItem(QString());
        yAxisComboBox->setObjectName("yAxisComboBox");
        yAxisComboBox->setMinimumSize(QSize(0, 20));
        yAxisComboBox->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(yAxisComboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout_5->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        barChartView = new QWidget(groupBox);
        barChartView->setObjectName("barChartView");

        gridLayout_5->addWidget(barChartView, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        splitter_2->addWidget(tabWidget);

        gridLayout_3->addWidget(splitter_2, 1, 0, 1, 1);

        DiskAnalyzer->setCentralWidget(centralwidget);

        retranslateUi(DiskAnalyzer);

        tabWidget->setCurrentIndex(1);
        yAxisComboBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(DiskAnalyzer);
    } // setupUi

    void retranslateUi(QMainWindow *DiskAnalyzer)
    {
        DiskAnalyzer->setWindowTitle(QCoreApplication::translate("DiskAnalyzer", "\347\243\201\347\233\230\345\210\206\346\236\220\345\267\245\345\205\267", nullptr));
        actionScan->setText(QCoreApplication::translate("DiskAnalyzer", "\346\211\253\346\217\217", nullptr));
        actionSwitchTo2D->setText(QCoreApplication::translate("DiskAnalyzer", "2D\345\233\276", nullptr));
        actionSwitchTo3D->setText(QCoreApplication::translate("DiskAnalyzer", "3D\345\233\276", nullptr));
        label->setText(QCoreApplication::translate("DiskAnalyzer", "\351\200\211\346\213\251\347\233\230\347\254\246:", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = driveInfoWidget->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("DiskAnalyzer", "\344\275\277\347\224\250\347\216\207", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("DiskAnalyzer", "\345\217\257\347\224\250\347\251\272\351\227\264", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("DiskAnalyzer", "\345\267\262\347\224\250\347\251\272\351\227\264", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("DiskAnalyzer", "\346\200\273\345\256\271\351\207\217", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("DiskAnalyzer", "\347\233\230\347\254\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("DiskAnalyzer", "\346\226\207\344\273\266\347\261\273\345\236\213\345\215\240\346\257\224\345\210\206\345\270\203\345\233\276", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DiskAnalyzer", "\345\217\257\350\247\206\345\214\226", nullptr));
        label_2->setText(QCoreApplication::translate("DiskAnalyzer", "X\350\275\264", nullptr));
        xAxisComboBox->setItemText(0, QCoreApplication::translate("DiskAnalyzer", "\347\233\230\347\254\246", nullptr));
        xAxisComboBox->setItemText(1, QCoreApplication::translate("DiskAnalyzer", "\346\200\273\345\256\271\351\207\217", nullptr));
        xAxisComboBox->setItemText(2, QCoreApplication::translate("DiskAnalyzer", "\345\267\262\347\224\250\347\251\272\351\227\264", nullptr));
        xAxisComboBox->setItemText(3, QCoreApplication::translate("DiskAnalyzer", "\345\217\257\347\224\250\347\251\272\351\227\264", nullptr));
        xAxisComboBox->setItemText(4, QCoreApplication::translate("DiskAnalyzer", "\344\275\277\347\224\250\347\216\207", nullptr));

        label_3->setText(QCoreApplication::translate("DiskAnalyzer", "Y\350\275\264", nullptr));
        yAxisComboBox->setItemText(0, QCoreApplication::translate("DiskAnalyzer", "\347\233\230\347\254\246", nullptr));
        yAxisComboBox->setItemText(1, QCoreApplication::translate("DiskAnalyzer", "\346\200\273\345\256\271\351\207\217", nullptr));
        yAxisComboBox->setItemText(2, QCoreApplication::translate("DiskAnalyzer", "\345\267\262\347\224\250\347\251\272\351\227\264", nullptr));
        yAxisComboBox->setItemText(3, QCoreApplication::translate("DiskAnalyzer", "\345\217\257\347\224\250\347\251\272\351\227\264", nullptr));
        yAxisComboBox->setItemText(4, QCoreApplication::translate("DiskAnalyzer", "\344\275\277\347\224\250\347\216\207", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("DiskAnalyzer", "\347\243\201\347\233\230\347\251\272\351\227\264\345\217\257\350\247\206\345\214\226\344\272\214\347\273\264\345\233\276\346\237\261\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiskAnalyzer: public Ui_DiskAnalyzer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISKANALYZER_H
