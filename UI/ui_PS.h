/********************************************************************************
** Form generated from reading UI file 'PS.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PS_H
#define UI_PS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../src/Widgets/photoShop/MyGraphicsView.h"

QT_BEGIN_NAMESPACE

class Ui_PS
{
public:
    QGridLayout *gridLayout_21;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout1;
    MyGraphicsView *GraphicsView;
    QWidget *widget_4;
    QGridLayout *gridLayout_7;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QToolBox *toolBox;
    QWidget *crop;
    QGridLayout *gridLayout_3;
    QListWidget *cropList;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label2;
    QLineEdit *leSizeW2;
    QLabel *label_11;
    QLineEdit *leSizeH2;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_12;
    QWidget *size;
    QGridLayout *gridLayout_10;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *leSizeW;
    QLabel *label_8;
    QLineEdit *leSizeH;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_10;
    QListWidget *sizeList;
    QCheckBox *lockedWHRatio;
    QWidget *adjust;
    QGridLayout *gridLayout_17;
    QLabel *label_2;
    QSpinBox *spinBoxBrightness;
    QLabel *label_3;
    QDoubleSpinBox *spinBoxContrast;
    QLabel *label_4;
    QDoubleSpinBox *spinBoxSaturation;
    QLabel *label_5;
    QSpinBox *spinBoxContrary;
    QSlider *contrarySlider;
    QSlider *saturationSlider;
    QSlider *contrastSlider;
    QSlider *brightnessSlider;
    QPushButton *sureAdjust;
    QWidget *page_3;
    QGridLayout *gridLayout;
    QSlider *rotaSlider;
    QToolButton *btnFlipVertical;
    QToolButton *btnRotateLeft;
    QToolButton *btnFlipHorizontal;
    QToolButton *btnRotateRight;
    QPushButton *sureTransform;
    QWidget *Filter;
    QGridLayout *gridLayout_5;
    QListWidget *FilterList;
    QPushButton *sureFilter;
    QWidget *algrothime;
    QGridLayout *gridLayout_4;
    QRadioButton *radioBilateral;
    QRadioButton *radioMedian;
    QRadioButton *radioBlur;
    QRadioButton *radioGaussion;
    QLabel *label4;
    QHBoxLayout *horizontalLayout;
    QSlider *kernelValue;
    QSpinBox *spinBoxKernel;
    QPushButton *sureAlgo;
    QWidget *AITool;
    QGridLayout *gridLayout_8;
    QListWidget *AIList;
    QWidget *page_2;
    QGroupBox *otherTool;
    QGridLayout *gridLayout_6;
    QToolButton *FaceTestToolBtn;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout1;
    QSpacerItem *horizontalSpacer1;
    QToolButton *btnUndo;
    QToolButton *btnReset;
    QToolButton *btnComparison;
    QSpacerItem *horizontalSpacer2;
    QHBoxLayout *horizontalLayout2;
    QPushButton *btnOpenImg;
    QPushButton *btnDireSave;
    QPushButton *btnSaveAs;

    void setupUi(QWidget *PS)
    {
        if (PS->objectName().isEmpty())
            PS->setObjectName("PS");
        PS->setEnabled(true);
        PS->resize(964, 698);
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        PS->setFont(font);
        PS->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/icons/logo/imgEditor.png"), QSize(), QIcon::Normal, QIcon::Off);
        PS->setWindowIcon(icon);
        PS->setStyleSheet(QString::fromUtf8("\n"
"        QPushButton {\n"
"        background-color: #4a90e2;\n"
"        color: white;\n"
"        border: none;\n"
"        padding: 8px 16px;\n"
"        border-radius: 4px;\n"
"        }\n"
"        QPushButton:hover {\n"
"        background-color: #357abd;\n"
"        }\n"
"        QPushButton:pressed {\n"
"        background-color: #2a5d8c;\n"
"        }\n"
"        QSlider::groove:horizontal {\n"
"        border: 1px solid #999999;\n"
"        height: 8px;\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1,\n"
"        stop:1 #c4c4c4);\n"
"        margin: 2px 0;\n"
"        }\n"
"        QSlider::groove:vertical {\n"
"        border: 1px solid #999999;\n"
"        width: 8px; /* \346\224\271\344\270\272 width\357\274\214\351\200\202\345\220\210\345\236\202\347\233\264\346\226\271\345\220\221 */\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1,\n"
"        stop:1 #c4c4c4);\n"
"        margin: 0 2px; /* \350\260\203\346\225\264\345\236\202\347\233"
                        "\264\346\226\271\345\220\221\347\232\204\351\227\264\350\267\235 */\n"
"        }\n"
"\n"
"        QSlider::handle:horizontal {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #52a8ec,\n"
"        stop:1 #4a90e2);\n"
"        border: 1px solid #5c5c5c;\n"
"        width: 18px;\n"
"        margin: -2px 0;\n"
"        border-radius: 3px;\n"
"        }\n"
"\n"
"        QSlider::handle:vertical {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #52a8ec,\n"
"        stop:1 #4a90e2);\n"
"        border: 1px solid #5c5c5c;\n"
"        height: 18px; /* \345\257\271\345\272\224\345\236\202\347\233\264\346\226\271\345\220\221\347\232\204\346\273\221\345\235\227\345\244\247\345\260\217 */\n"
"        margin: 0 -2px; /* \350\260\203\346\225\264\345\236\202\347\233\264\346\273\221\345\235\227\347\232\204\350\276\271\350\267\235 */\n"
"        border-radius: 3px;\n"
"        }\n"
"\n"
"        QDoubleSpinBox {\n"
"        padding: 4px;\n"
"        border: 1px solid #aaa;\n"
"    "
                        "    border-radius: 4px;\n"
"        }\n"
"        QGroupBox {\n"
"        font-weight: bold;\n"
"        border: 1px solid #ccc;\n"
"        border-radius: 6px;\n"
"        margin-top: 6px;\n"
"        padding-top: 10px;\n"
"        }\n"
"        QGroupBox::title {\n"
"        subcontrol-origin: margin;\n"
"        left: 10px;\n"
"        padding: 0 3px 0 3px;\n"
"        }\n"
"      "));
        gridLayout_21 = new QGridLayout(PS);
        gridLayout_21->setSpacing(5);
        gridLayout_21->setObjectName("gridLayout_21");
        gridLayout_21->setContentsMargins(5, 5, 5, 5);
        splitter = new QSplitter(PS);
        splitter->setObjectName("splitter");
        splitter->setAcceptDrops(true);
        splitter->setStyleSheet(QString::fromUtf8("  /*--------------------------\350\260\203\346\225\264\344\270\255\347\232\204\345\234\206\350\247\222\346\240\267\345\274\217------------------*/\n"
"                                QSpinBox, QDoubleSpinBox {\n"
"                                border: 1px solid #E0E0E0;\n"
"                                border-radius: 10px; /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"                                padding: 5px 10px;\n"
"                                background: white;\n"
"                                min-width: 37px;\n"
"                                min-height: 15px;\n"
"                                max-width: 37px;\n"
"                                max-height: 15px;\n"
"                                }"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(false);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout1 = new QVBoxLayout(layoutWidget);
        verticalLayout1->setObjectName("verticalLayout1");
        verticalLayout1->setContentsMargins(0, 0, 0, 0);
        GraphicsView = new MyGraphicsView(layoutWidget);
        GraphicsView->setObjectName("GraphicsView");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GraphicsView->sizePolicy().hasHeightForWidth());
        GraphicsView->setSizePolicy(sizePolicy);
        GraphicsView->setMinimumSize(QSize(600, 0));
        GraphicsView->setFont(font);
        GraphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
        GraphicsView->setAcceptDrops(true);
        GraphicsView->setStyleSheet(QString::fromUtf8("\n"
"                      border: 2px solid #ccc;\n"
"                      border-radius: 8px;\n"
"                    "));
        GraphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        GraphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        GraphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        GraphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        verticalLayout1->addWidget(GraphicsView);

        splitter->addWidget(layoutWidget);
        widget_4 = new QWidget(splitter);
        widget_4->setObjectName("widget_4");
        widget_4->setAcceptDrops(true);
        gridLayout_7 = new QGridLayout(widget_4);
        gridLayout_7->setSpacing(5);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(widget_4);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        toolBox = new QToolBox(page);
        toolBox->setObjectName("toolBox");
        toolBox->setEnabled(false);
        sizePolicy.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
        toolBox->setSizePolicy(sizePolicy);
        toolBox->setMaximumSize(QSize(16777215, 16777215));
        toolBox->setFont(font);
        toolBox->setStyleSheet(QString::fromUtf8("\n"
"                              /*--------------------------\350\260\203\346\225\264\344\270\255\347\232\204\346\273\221\345\212\250\346\235\241\346\240\267\345\274\217------------------*/\n"
"                              QSlider {\n"
"                              min-height: 20px;\n"
"                              max-height: 20px;\n"
"                              }\n"
"\n"
"                              QSlider::groove:horizontal {\n"
"                              border: none;\n"
"                              height: 2px; /* \351\231\215\344\275\216\350\275\250\351\201\223\351\253\230\345\272\246\344\275\277\345\205\266\346\233\264\347\273\206\350\205\273 */\n"
"                              background: #E0E0E0;\n"
"                              margin: 0px;\n"
"                              border-radius: 1px;\n"
"                              }\n"
"\n"
"                              QSlider::sub-page:horizontal {\n"
"                              background: #6C5CE7;\n"
"                          "
                        "    border-radius: 1px;\n"
"                              }\n"
"\n"
"                              QSlider::add-page:horizontal {\n"
"                              background: #E0E0E0;\n"
"                              border-radius: 1px;\n"
"                              }\n"
"\n"
"                              QSlider::handle:horizontal {\n"
"                              background: white;\n"
"                              border: 1px solid #6C5CE7; /* \350\276\271\346\241\206 */\n"
"                              width: 12px; /* \345\234\206\347\220\203\345\260\272\345\257\270 */\n"
"                              height: 12px;\n"
"                              margin: -5px 0; /* \345\236\202\347\233\264\344\275\215\347\275\256 */\n"
"                              border-radius: 6px;\n"
"                              }\n"
"\n"
"                              /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\240\267\345\274\217 */\n"
"                              QSlider::handle:"
                        "horizontal:hover {\n"
"                              background: white;\n"
"                              border: 1px solid #6C5CE7; /* \347\250\215\345\276\256\345\212\240\347\262\227\350\276\271\346\241\206 */\n"
"                              width: 14px; /* \347\250\215\345\276\256\345\242\236\345\244\247 */\n"
"                              height: 14px;\n"
"                              margin: -6px 0;\n"
"                              border-radius: 6px;\n"
"                              }\n"
"\n"
"                              /* \351\274\240\346\240\207\346\214\211\344\270\213\346\227\266\347\232\204\346\240\267\345\274\217 */\n"
"                              QSlider::handle:horizontal:pressed {\n"
"                              background: #6C5CE7; /* \346\214\211\344\270\213\346\227\266\345\217\230\346\210\220\345\256\236\345\277\203 */\n"
"                              border: 1px solid #6C5CE7;\n"
"                              width: 12px;\n"
"                              height: 12px;\n"
"    "
                        "                          margin: -5px 0;\n"
"                              border-radius: 6px;\n"
"                              }\n"
"                            "));
        toolBox->setFrameShape(QFrame::Box);
        toolBox->setFrameShadow(QFrame::Plain);
        crop = new QWidget();
        crop->setObjectName("crop");
        crop->setGeometry(QRect(0, 0, 345, 239));
        gridLayout_3 = new QGridLayout(crop);
        gridLayout_3->setObjectName("gridLayout_3");
        cropList = new QListWidget(crop);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        new QListWidgetItem(cropList);
        cropList->setObjectName("cropList");
        cropList->setFont(font);
        cropList->setFrameShape(QFrame::NoFrame);

        gridLayout_3->addWidget(cropList, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(5);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label2 = new QLabel(crop);
        label2->setObjectName("label2");
        label2->setFont(font);

        horizontalLayout_11->addWidget(label2);

        leSizeW2 = new QLineEdit(crop);
        leSizeW2->setObjectName("leSizeW2");
        leSizeW2->setEnabled(false);
        leSizeW2->setMaximumSize(QSize(45, 25));

        horizontalLayout_11->addWidget(leSizeW2);

        label_11 = new QLabel(crop);
        label_11->setObjectName("label_11");

        horizontalLayout_11->addWidget(label_11);

        leSizeH2 = new QLineEdit(crop);
        leSizeH2->setObjectName("leSizeH2");
        leSizeH2->setEnabled(false);
        leSizeH2->setMaximumSize(QSize(45, 25));

        horizontalLayout_11->addWidget(leSizeH2);

        label_12 = new QLabel(crop);
        label_12->setObjectName("label_12");

        horizontalLayout_11->addWidget(label_12);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_12);


        gridLayout_3->addLayout(horizontalLayout_11, 1, 0, 1, 1);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ps/res/ps/crop.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(crop, icon1, QString::fromUtf8("\350\243\201\345\211\252"));
        size = new QWidget();
        size->setObjectName("size");
        size->setGeometry(QRect(0, 0, 345, 303));
        gridLayout_10 = new QGridLayout(size);
        gridLayout_10->setObjectName("gridLayout_10");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(5);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        leSizeW = new QLineEdit(size);
        leSizeW->setObjectName("leSizeW");
        leSizeW->setMaximumSize(QSize(16777215, 25));
        leSizeW->setMaxLength(4);

        horizontalLayout_6->addWidget(leSizeW);

        label_8 = new QLabel(size);
        label_8->setObjectName("label_8");

        horizontalLayout_6->addWidget(label_8);

        leSizeH = new QLineEdit(size);
        leSizeH->setObjectName("leSizeH");
        leSizeH->setMaximumSize(QSize(16777215, 25));
        leSizeH->setMaxLength(4);

        horizontalLayout_6->addWidget(leSizeH);

        label_9 = new QLabel(size);
        label_9->setObjectName("label_9");

        horizontalLayout_6->addWidget(label_9);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);


        gridLayout_10->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        sizeList = new QListWidget(size);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        new QListWidgetItem(sizeList);
        sizeList->setObjectName("sizeList");
        sizeList->setFont(font);
        sizeList->setFrameShape(QFrame::NoFrame);

        gridLayout_10->addWidget(sizeList, 0, 0, 1, 1);

        lockedWHRatio = new QCheckBox(size);
        lockedWHRatio->setObjectName("lockedWHRatio");
        lockedWHRatio->setChecked(true);

        gridLayout_10->addWidget(lockedWHRatio, 2, 0, 1, 1);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ps/res/ps/size.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(size, icon2, QString::fromUtf8("\346\224\271\345\260\272\345\257\270"));
        adjust = new QWidget();
        adjust->setObjectName("adjust");
        adjust->setGeometry(QRect(0, 0, 345, 287));
        adjust->setStyleSheet(QString::fromUtf8(""));
        gridLayout_17 = new QGridLayout(adjust);
        gridLayout_17->setObjectName("gridLayout_17");
        label_2 = new QLabel(adjust);
        label_2->setObjectName("label_2");

        gridLayout_17->addWidget(label_2, 0, 0, 1, 1);

        spinBoxBrightness = new QSpinBox(adjust);
        spinBoxBrightness->setObjectName("spinBoxBrightness");
        spinBoxBrightness->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBoxBrightness->sizePolicy().hasHeightForWidth());
        spinBoxBrightness->setSizePolicy(sizePolicy1);
        spinBoxBrightness->setMinimumSize(QSize(59, 27));
        spinBoxBrightness->setMaximumSize(QSize(59, 27));
        spinBoxBrightness->setFont(font);
        spinBoxBrightness->setStyleSheet(QString::fromUtf8(""));
        spinBoxBrightness->setWrapping(false);
        spinBoxBrightness->setFrame(false);
        spinBoxBrightness->setAlignment(Qt::AlignCenter);
        spinBoxBrightness->setReadOnly(false);
        spinBoxBrightness->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxBrightness->setAccelerated(false);
        spinBoxBrightness->setProperty("showGroupSeparator", QVariant(false));
        spinBoxBrightness->setMinimum(-50);
        spinBoxBrightness->setMaximum(50);

        gridLayout_17->addWidget(spinBoxBrightness, 0, 1, 1, 1);

        label_3 = new QLabel(adjust);
        label_3->setObjectName("label_3");

        gridLayout_17->addWidget(label_3, 2, 0, 1, 1);

        spinBoxContrast = new QDoubleSpinBox(adjust);
        spinBoxContrast->setObjectName("spinBoxContrast");
        spinBoxContrast->setEnabled(false);
        sizePolicy1.setHeightForWidth(spinBoxContrast->sizePolicy().hasHeightForWidth());
        spinBoxContrast->setSizePolicy(sizePolicy1);
        spinBoxContrast->setMinimumSize(QSize(59, 27));
        spinBoxContrast->setMaximumSize(QSize(59, 27));
        spinBoxContrast->setFont(font);
        spinBoxContrast->setFrame(false);
        spinBoxContrast->setAlignment(Qt::AlignCenter);
        spinBoxContrast->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxContrast->setDecimals(1);
        spinBoxContrast->setMinimum(0.100000000000000);
        spinBoxContrast->setMaximum(3.000000000000000);
        spinBoxContrast->setSingleStep(0.100000000000000);
        spinBoxContrast->setStepType(QAbstractSpinBox::DefaultStepType);
        spinBoxContrast->setValue(1.000000000000000);

        gridLayout_17->addWidget(spinBoxContrast, 2, 1, 1, 1);

        label_4 = new QLabel(adjust);
        label_4->setObjectName("label_4");

        gridLayout_17->addWidget(label_4, 4, 0, 1, 1);

        spinBoxSaturation = new QDoubleSpinBox(adjust);
        spinBoxSaturation->setObjectName("spinBoxSaturation");
        spinBoxSaturation->setEnabled(false);
        sizePolicy1.setHeightForWidth(spinBoxSaturation->sizePolicy().hasHeightForWidth());
        spinBoxSaturation->setSizePolicy(sizePolicy1);
        spinBoxSaturation->setMinimumSize(QSize(59, 27));
        spinBoxSaturation->setMaximumSize(QSize(59, 27));
        spinBoxSaturation->setFont(font);
        spinBoxSaturation->setFrame(false);
        spinBoxSaturation->setAlignment(Qt::AlignCenter);
        spinBoxSaturation->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxSaturation->setAccelerated(false);
        spinBoxSaturation->setKeyboardTracking(true);
        spinBoxSaturation->setProperty("showGroupSeparator", QVariant(false));
        spinBoxSaturation->setMaximum(2.000000000000000);
        spinBoxSaturation->setSingleStep(0.010000000000000);
        spinBoxSaturation->setStepType(QAbstractSpinBox::DefaultStepType);
        spinBoxSaturation->setValue(1.000000000000000);

        gridLayout_17->addWidget(spinBoxSaturation, 4, 1, 1, 1);

        label_5 = new QLabel(adjust);
        label_5->setObjectName("label_5");

        gridLayout_17->addWidget(label_5, 6, 0, 1, 1);

        spinBoxContrary = new QSpinBox(adjust);
        spinBoxContrary->setObjectName("spinBoxContrary");
        spinBoxContrary->setEnabled(false);
        sizePolicy1.setHeightForWidth(spinBoxContrary->sizePolicy().hasHeightForWidth());
        spinBoxContrary->setSizePolicy(sizePolicy1);
        spinBoxContrary->setMinimumSize(QSize(59, 27));
        spinBoxContrary->setMaximumSize(QSize(59, 27));
        spinBoxContrary->setFont(font);
        spinBoxContrary->setStyleSheet(QString::fromUtf8(""));
        spinBoxContrary->setWrapping(false);
        spinBoxContrary->setFrame(false);
        spinBoxContrary->setAlignment(Qt::AlignCenter);
        spinBoxContrary->setReadOnly(false);
        spinBoxContrary->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxContrary->setAccelerated(false);
        spinBoxContrary->setProperty("showGroupSeparator", QVariant(false));
        spinBoxContrary->setMinimum(0);
        spinBoxContrary->setMaximum(100);
        spinBoxContrary->setSingleStep(0);

        gridLayout_17->addWidget(spinBoxContrary, 6, 1, 1, 1);

        contrarySlider = new QSlider(adjust);
        contrarySlider->setObjectName("contrarySlider");
        contrarySlider->setCursor(QCursor(Qt::ArrowCursor));
        contrarySlider->setFocusPolicy(Qt::StrongFocus);
        contrarySlider->setMinimum(0);
        contrarySlider->setMaximum(255);
        contrarySlider->setSingleStep(3);
        contrarySlider->setPageStep(0);
        contrarySlider->setValue(0);
        contrarySlider->setTracking(true);
        contrarySlider->setOrientation(Qt::Horizontal);

        gridLayout_17->addWidget(contrarySlider, 7, 0, 1, 2);

        saturationSlider = new QSlider(adjust);
        saturationSlider->setObjectName("saturationSlider");
        saturationSlider->setCursor(QCursor(Qt::ArrowCursor));
        saturationSlider->setFocusPolicy(Qt::StrongFocus);
        saturationSlider->setMinimum(0);
        saturationSlider->setMaximum(200);
        saturationSlider->setPageStep(0);
        saturationSlider->setValue(100);
        saturationSlider->setTracking(true);
        saturationSlider->setOrientation(Qt::Horizontal);

        gridLayout_17->addWidget(saturationSlider, 5, 0, 1, 2);

        contrastSlider = new QSlider(adjust);
        contrastSlider->setObjectName("contrastSlider");
        contrastSlider->setCursor(QCursor(Qt::ArrowCursor));
        contrastSlider->setMinimum(1);
        contrastSlider->setMaximum(30);
        contrastSlider->setPageStep(1);
        contrastSlider->setValue(10);
        contrastSlider->setTracking(true);
        contrastSlider->setOrientation(Qt::Horizontal);

        gridLayout_17->addWidget(contrastSlider, 3, 0, 1, 2);

        brightnessSlider = new QSlider(adjust);
        brightnessSlider->setObjectName("brightnessSlider");
        brightnessSlider->setCursor(QCursor(Qt::ArrowCursor));
        brightnessSlider->setStyleSheet(QString::fromUtf8(""));
        brightnessSlider->setMinimum(-50);
        brightnessSlider->setMaximum(50);
        brightnessSlider->setPageStep(1);
        brightnessSlider->setTracking(true);
        brightnessSlider->setOrientation(Qt::Horizontal);
        brightnessSlider->setTickPosition(QSlider::NoTicks);
        brightnessSlider->setTickInterval(1);

        gridLayout_17->addWidget(brightnessSlider, 1, 0, 1, 2);

        sureAdjust = new QPushButton(adjust);
        sureAdjust->setObjectName("sureAdjust");
        sureAdjust->setMaximumSize(QSize(16777215, 35));

        gridLayout_17->addWidget(sureAdjust, 8, 0, 1, 2);

        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ps/res/ps/change.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(adjust, icon3, QString::fromUtf8("\350\260\203\346\225\264"));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setGeometry(QRect(0, 0, 345, 135));
        gridLayout = new QGridLayout(page_3);
        gridLayout->setObjectName("gridLayout");
        rotaSlider = new QSlider(page_3);
        rotaSlider->setObjectName("rotaSlider");
        rotaSlider->setMaximum(360);
        rotaSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(rotaSlider, 3, 0, 1, 2);

        btnFlipVertical = new QToolButton(page_3);
        btnFlipVertical->setObjectName("btnFlipVertical");
        btnFlipVertical->setMaximumSize(QSize(16777215, 35));
        btnFlipVertical->setFocusPolicy(Qt::NoFocus);
        btnFlipVertical->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("\n"
"                                        :/ps/res/ps/slip1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnFlipVertical->setIcon(icon4);
        btnFlipVertical->setIconSize(QSize(64, 64));
        btnFlipVertical->setPopupMode(QToolButton::DelayedPopup);
        btnFlipVertical->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnFlipVertical->setAutoRaise(false);
        btnFlipVertical->setArrowType(Qt::NoArrow);

        gridLayout->addWidget(btnFlipVertical, 1, 1, 1, 1);

        btnRotateLeft = new QToolButton(page_3);
        btnRotateLeft->setObjectName("btnRotateLeft");
        btnRotateLeft->setMaximumSize(QSize(16777215, 35));
        btnRotateLeft->setFocusPolicy(Qt::NoFocus);
        btnRotateLeft->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("\n"
"                                        :/ps/res/ps/rotaLeft.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRotateLeft->setIcon(icon5);
        btnRotateLeft->setIconSize(QSize(64, 64));
        btnRotateLeft->setPopupMode(QToolButton::DelayedPopup);
        btnRotateLeft->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnRotateLeft->setAutoRaise(false);
        btnRotateLeft->setArrowType(Qt::NoArrow);

        gridLayout->addWidget(btnRotateLeft, 0, 0, 1, 1);

        btnFlipHorizontal = new QToolButton(page_3);
        btnFlipHorizontal->setObjectName("btnFlipHorizontal");
        btnFlipHorizontal->setMaximumSize(QSize(16777215, 35));
        btnFlipHorizontal->setFocusPolicy(Qt::NoFocus);
        btnFlipHorizontal->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("\n"
"                                        :/ps/res/ps/slip0.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnFlipHorizontal->setIcon(icon6);
        btnFlipHorizontal->setIconSize(QSize(64, 64));
        btnFlipHorizontal->setPopupMode(QToolButton::DelayedPopup);
        btnFlipHorizontal->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnFlipHorizontal->setAutoRaise(false);
        btnFlipHorizontal->setArrowType(Qt::NoArrow);

        gridLayout->addWidget(btnFlipHorizontal, 1, 0, 1, 1);

        btnRotateRight = new QToolButton(page_3);
        btnRotateRight->setObjectName("btnRotateRight");
        btnRotateRight->setMaximumSize(QSize(16777215, 35));
        btnRotateRight->setFocusPolicy(Qt::NoFocus);
        btnRotateRight->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("\n"
"                                        :/ps/res/ps/rotaRight.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRotateRight->setIcon(icon7);
        btnRotateRight->setIconSize(QSize(64, 64));
        btnRotateRight->setPopupMode(QToolButton::DelayedPopup);
        btnRotateRight->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnRotateRight->setAutoRaise(false);
        btnRotateRight->setArrowType(Qt::NoArrow);

        gridLayout->addWidget(btnRotateRight, 0, 1, 1, 1);

        sureTransform = new QPushButton(page_3);
        sureTransform->setObjectName("sureTransform");

        gridLayout->addWidget(sureTransform, 4, 0, 1, 2);

        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/ps/res/ps/rota2.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(page_3, icon8, QString::fromUtf8("\346\227\213\350\275\254\345\217\230\346\215\242"));
        Filter = new QWidget();
        Filter->setObjectName("Filter");
        Filter->setGeometry(QRect(0, 0, 345, 249));
        gridLayout_5 = new QGridLayout(Filter);
        gridLayout_5->setObjectName("gridLayout_5");
        FilterList = new QListWidget(Filter);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        new QListWidgetItem(FilterList);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(FilterList);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        FilterList->setObjectName("FilterList");
        FilterList->setAutoFillBackground(false);
        FilterList->setFrameShape(QFrame::NoFrame);
        FilterList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        FilterList->setAlternatingRowColors(false);
        FilterList->setSelectionRectVisible(false);

        gridLayout_5->addWidget(FilterList, 0, 0, 1, 1);

        sureFilter = new QPushButton(Filter);
        sureFilter->setObjectName("sureFilter");

        gridLayout_5->addWidget(sureFilter, 1, 0, 1, 1);

        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/ps/res/ps/filter.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(Filter, icon9, QString::fromUtf8("\347\211\271\346\225\210\346\273\244\351\225\234"));
        algrothime = new QWidget();
        algrothime->setObjectName("algrothime");
        algrothime->setGeometry(QRect(0, 0, 345, 182));
        gridLayout_4 = new QGridLayout(algrothime);
        gridLayout_4->setObjectName("gridLayout_4");
        radioBilateral = new QRadioButton(algrothime);
        radioBilateral->setObjectName("radioBilateral");

        gridLayout_4->addWidget(radioBilateral, 2, 1, 1, 1);

        radioMedian = new QRadioButton(algrothime);
        radioMedian->setObjectName("radioMedian");

        gridLayout_4->addWidget(radioMedian, 2, 0, 1, 1);

        radioBlur = new QRadioButton(algrothime);
        radioBlur->setObjectName("radioBlur");
        radioBlur->setChecked(true);

        gridLayout_4->addWidget(radioBlur, 1, 0, 1, 1);

        radioGaussion = new QRadioButton(algrothime);
        radioGaussion->setObjectName("radioGaussion");

        gridLayout_4->addWidget(radioGaussion, 1, 1, 1, 1);

        label4 = new QLabel(algrothime);
        label4->setObjectName("label4");
        label4->setFont(font);
        label4->setStyleSheet(QString::fromUtf8(""));
        label4->setWordWrap(true);

        gridLayout_4->addWidget(label4, 3, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        kernelValue = new QSlider(algrothime);
        kernelValue->setObjectName("kernelValue");
        kernelValue->setEnabled(false);
        kernelValue->setMinimum(1);
        kernelValue->setMaximum(20);
        kernelValue->setPageStep(1);
        kernelValue->setOrientation(Qt::Horizontal);
        kernelValue->setTickPosition(QSlider::NoTicks);
        kernelValue->setTickInterval(1);

        horizontalLayout->addWidget(kernelValue);

        spinBoxKernel = new QSpinBox(algrothime);
        spinBoxKernel->setObjectName("spinBoxKernel");
        spinBoxKernel->setEnabled(false);
        spinBoxKernel->setMaximumSize(QSize(59, 27));
        spinBoxKernel->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxKernel->setMinimum(1);
        spinBoxKernel->setMaximum(20);

        horizontalLayout->addWidget(spinBoxKernel);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 2);

        sureAlgo = new QPushButton(algrothime);
        sureAlgo->setObjectName("sureAlgo");

        gridLayout_4->addWidget(sureAlgo, 4, 0, 1, 2);

        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/ps/res/ps/algorithm.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(algrothime, icon10, QString::fromUtf8("\350\277\207\346\273\244\347\256\227\346\263\225"));
        AITool = new QWidget();
        AITool->setObjectName("AITool");
        AITool->setGeometry(QRect(0, 0, 345, 210));
        gridLayout_8 = new QGridLayout(AITool);
        gridLayout_8->setObjectName("gridLayout_8");
        AIList = new QListWidget(AITool);
        new QListWidgetItem(AIList);
        new QListWidgetItem(AIList);
        new QListWidgetItem(AIList);
        new QListWidgetItem(AIList);
        AIList->setObjectName("AIList");
        AIList->setFrameShape(QFrame::NoFrame);
        AIList->setSelectionMode(QAbstractItemView::NoSelection);

        gridLayout_8->addWidget(AIList, 0, 0, 1, 1);

        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/ps/res/ps/AITool.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(AITool, icon11, QString::fromUtf8("\346\231\272\350\203\275\345\267\245\345\205\267"));

        gridLayout_2->addWidget(toolBox, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        gridLayout_7->addWidget(stackedWidget, 0, 0, 1, 1);

        otherTool = new QGroupBox(widget_4);
        otherTool->setObjectName("otherTool");
        otherTool->setAcceptDrops(true);
        gridLayout_6 = new QGridLayout(otherTool);
        gridLayout_6->setObjectName("gridLayout_6");
        FaceTestToolBtn = new QToolButton(otherTool);
        FaceTestToolBtn->setObjectName("FaceTestToolBtn");
        FaceTestToolBtn->setAcceptDrops(true);
        FaceTestToolBtn->setAutoRaise(true);

        gridLayout_6->addWidget(FaceTestToolBtn, 0, 0, 1, 1);


        gridLayout_7->addWidget(otherTool, 1, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_9, 3, 0, 1, 1);

        splitter->addWidget(widget_4);

        gridLayout_21->addWidget(splitter, 1, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, -1, -1, -1);
        horizontalLayout1 = new QHBoxLayout();
        horizontalLayout1->setObjectName("horizontalLayout1");
        horizontalSpacer1 = new QSpacerItem(70, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout1->addItem(horizontalSpacer1);

        btnUndo = new QToolButton(PS);
        btnUndo->setObjectName("btnUndo");
        btnUndo->setEnabled(false);
        btnUndo->setMaximumSize(QSize(16777215, 33));
        btnUndo->setFont(font);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/ps/res/ps/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnUndo->setIcon(icon12);
        btnUndo->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnUndo->setAutoRaise(true);

        horizontalLayout1->addWidget(btnUndo);

        btnReset = new QToolButton(PS);
        btnReset->setObjectName("btnReset");
        btnReset->setEnabled(false);
        btnReset->setMaximumSize(QSize(16777215, 33));
        btnReset->setFont(font);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/ps/res/ps/resetImg.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnReset->setIcon(icon13);
        btnReset->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnReset->setAutoRaise(true);

        horizontalLayout1->addWidget(btnReset);

        btnComparison = new QToolButton(PS);
        btnComparison->setObjectName("btnComparison");
        btnComparison->setEnabled(false);
        btnComparison->setMaximumSize(QSize(16777215, 33));
        btnComparison->setFont(font);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/ps/res/ps/CloseEye.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnComparison->setIcon(icon14);
        btnComparison->setCheckable(true);
        btnComparison->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnComparison->setAutoRaise(true);

        horizontalLayout1->addWidget(btnComparison);

        horizontalSpacer2 = new QSpacerItem(10, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout1->addItem(horizontalSpacer2);


        horizontalLayout_10->addLayout(horizontalLayout1);

        horizontalLayout2 = new QHBoxLayout();
        horizontalLayout2->setObjectName("horizontalLayout2");
        btnOpenImg = new QPushButton(PS);
        btnOpenImg->setObjectName("btnOpenImg");
        btnOpenImg->setMinimumSize(QSize(0, 0));
        btnOpenImg->setMaximumSize(QSize(16777215, 35));
        btnOpenImg->setFont(font);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/ps/res/ps/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpenImg->setIcon(icon15);
        btnOpenImg->setIconSize(QSize(32, 32));

        horizontalLayout2->addWidget(btnOpenImg);

        btnDireSave = new QPushButton(PS);
        btnDireSave->setObjectName("btnDireSave");
        btnDireSave->setEnabled(false);
        btnDireSave->setMaximumSize(QSize(16777215, 35));
        btnDireSave->setFont(font);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/ps/res/ps/changeImg.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDireSave->setIcon(icon16);
        btnDireSave->setIconSize(QSize(32, 32));

        horizontalLayout2->addWidget(btnDireSave);

        btnSaveAs = new QPushButton(PS);
        btnSaveAs->setObjectName("btnSaveAs");
        btnSaveAs->setEnabled(false);
        btnSaveAs->setMaximumSize(QSize(16777215, 35));
        btnSaveAs->setFont(font);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/ps/res/ps/saveAS.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSaveAs->setIcon(icon17);
        btnSaveAs->setIconSize(QSize(32, 32));

        horizontalLayout2->addWidget(btnSaveAs);


        horizontalLayout_10->addLayout(horizontalLayout2);


        gridLayout_21->addLayout(horizontalLayout_10, 0, 0, 1, 1);


        retranslateUi(PS);

        stackedWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(1);
        toolBox->layout()->setSpacing(7);


        QMetaObject::connectSlotsByName(PS);
    } // setupUi

    void retranslateUi(QWidget *PS)
    {
        PS->setWindowTitle(QCoreApplication::translate("PS", "\347\256\200\346\230\223\345\233\276\345\203\217\347\274\226\350\276\221\345\231\250", nullptr));

        const bool __sortingEnabled = cropList->isSortingEnabled();
        cropList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = cropList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("PS", "\350\207\252\347\224\261\350\243\201\345\211\252", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = cropList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("PS", "1:1", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = cropList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("PS", "3:4", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = cropList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("PS", "2:3", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = cropList->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("PS", "9:16", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = cropList->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("PS", "4:3", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = cropList->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("PS", "3:2", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = cropList->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("PS", "16:9", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = cropList->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("PS", "\344\270\200\345\257\270", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = cropList->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("PS", "\345\244\247\344\270\200\345\257\270", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = cropList->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("PS", "\344\270\244\345\257\270", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = cropList->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("PS", "\345\205\254\344\274\227\345\217\267\351\246\226\345\233\276", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = cropList->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("PS", "\345\260\217\347\272\242\344\271\246\351\205\215\345\233\276", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = cropList->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("PS", "\347\253\226\347\211\210\350\247\206\351\242\221\345\260\201\351\235\242", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = cropList->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("PS", "\346\250\252\347\211\210\350\247\206\351\242\221\345\260\201\351\235\242", nullptr));
        cropList->setSortingEnabled(__sortingEnabled);

        label2->setText(QCoreApplication::translate("PS", "\345\275\223\345\211\215\345\260\272\345\257\270\357\274\232", nullptr));
        label_11->setText(QCoreApplication::translate("PS", "<html><head/><body><p>\303\227</p></body></html>", nullptr));
        label_12->setText(QCoreApplication::translate("PS", "px", nullptr));
        toolBox->setItemText(toolBox->indexOf(crop), QCoreApplication::translate("PS", "\350\243\201\345\211\252", nullptr));
        label_8->setText(QCoreApplication::translate("PS", "<html><head/><body><p>\303\227</p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("PS", "px", nullptr));

        const bool __sortingEnabled1 = sizeList->isSortingEnabled();
        sizeList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem15 = sizeList->item(0);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("PS", "\350\207\252\345\256\232\344\271\211", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = sizeList->item(1);
        ___qlistwidgetitem16->setText(QCoreApplication::translate("PS", "\345\225\206\345\223\201\344\270\273\345\233\276 1000*1000px", nullptr));
        QListWidgetItem *___qlistwidgetitem17 = sizeList->item(2);
        ___qlistwidgetitem17->setText(QCoreApplication::translate("PS", "\347\253\226\347\211\210\344\270\273\345\233\276 800*1200px", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = sizeList->item(3);
        ___qlistwidgetitem18->setText(QCoreApplication::translate("PS", "\346\267\230\345\256\235 800*800px", nullptr));
        QListWidgetItem *___qlistwidgetitem19 = sizeList->item(4);
        ___qlistwidgetitem19->setText(QCoreApplication::translate("PS", "Logo\350\256\276\350\256\241 500*500px", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = sizeList->item(5);
        ___qlistwidgetitem20->setText(QCoreApplication::translate("PS", "\344\272\254\344\270\234 500*500px", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = sizeList->item(6);
        ___qlistwidgetitem21->setText(QCoreApplication::translate("PS", "\351\245\277\344\272\206\344\271\210 480*480px", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = sizeList->item(7);
        ___qlistwidgetitem22->setText(QCoreApplication::translate("PS", "\346\212\226\351\237\263 600*800px", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = sizeList->item(8);
        ___qlistwidgetitem23->setText(QCoreApplication::translate("PS", "\347\276\216\345\233\242 600*600px", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = sizeList->item(9);
        ___qlistwidgetitem24->setText(QCoreApplication::translate("PS", "\344\270\200\345\257\270 295*413px", nullptr));
        QListWidgetItem *___qlistwidgetitem25 = sizeList->item(10);
        ___qlistwidgetitem25->setText(QCoreApplication::translate("PS", "\345\244\247\344\270\200\345\257\270 390*567px", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = sizeList->item(11);
        ___qlistwidgetitem26->setText(QCoreApplication::translate("PS", "\344\270\244\345\257\270 413*579px", nullptr));
        QListWidgetItem *___qlistwidgetitem27 = sizeList->item(12);
        ___qlistwidgetitem27->setText(QCoreApplication::translate("PS", "QQ\345\244\264\345\203\217 150*150px", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = sizeList->item(13);
        ___qlistwidgetitem28->setText(QCoreApplication::translate("PS", "\345\276\256\344\277\241\345\244\264\345\203\2171 200*200px", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = sizeList->item(14);
        ___qlistwidgetitem29->setText(QCoreApplication::translate("PS", "\345\276\256\344\277\241\345\244\264\345\203\2172 300*300px", nullptr));
        sizeList->setSortingEnabled(__sortingEnabled1);

        lockedWHRatio->setText(QCoreApplication::translate("PS", "\351\224\201\345\256\232\345\256\275\351\253\230\346\257\224\344\276\213", nullptr));
        toolBox->setItemText(toolBox->indexOf(size), QCoreApplication::translate("PS", "\346\224\271\345\260\272\345\257\270", nullptr));
        label_2->setText(QCoreApplication::translate("PS", "\344\272\256\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("PS", "\345\257\271\346\257\224\345\272\246", nullptr));
        label_4->setText(QCoreApplication::translate("PS", "\351\245\261\345\222\214\345\272\246", nullptr));
        label_5->setText(QCoreApplication::translate("PS", "\345\217\215\347\233\270", nullptr));
        spinBoxContrary->setSuffix(QCoreApplication::translate("PS", "%", nullptr));
        sureAdjust->setText(QCoreApplication::translate("PS", "\345\272\224\347\224\250", nullptr));
        toolBox->setItemText(toolBox->indexOf(adjust), QCoreApplication::translate("PS", "\350\260\203\346\225\264", nullptr));
#if QT_CONFIG(tooltip)
        btnFlipVertical->setToolTip(QCoreApplication::translate("PS", "\345\236\202\347\233\264\347\277\273\350\275\254", nullptr));
#endif // QT_CONFIG(tooltip)
        btnFlipVertical->setText(QCoreApplication::translate("PS", "\345\236\202\347\233\264\347\277\273\350\275\254", nullptr));
#if QT_CONFIG(tooltip)
        btnRotateLeft->setToolTip(QCoreApplication::translate("PS", "\345\267\246\346\227\213\350\275\25490\345\272\246", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRotateLeft->setText(QCoreApplication::translate("PS", "\345\220\221\345\267\246\346\227\213\350\275\25490\302\260", nullptr));
#if QT_CONFIG(tooltip)
        btnFlipHorizontal->setToolTip(QCoreApplication::translate("PS", "\346\260\264\345\271\263\351\225\234\345\203\217\347\277\273\350\275\254", nullptr));
#endif // QT_CONFIG(tooltip)
        btnFlipHorizontal->setText(QCoreApplication::translate("PS", "\346\260\264\345\271\263\347\277\273\350\275\254", nullptr));
#if QT_CONFIG(tooltip)
        btnRotateRight->setToolTip(QCoreApplication::translate("PS", "\345\217\263\346\227\213\350\275\25490\345\272\246", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRotateRight->setText(QCoreApplication::translate("PS", "\345\220\221\345\217\263\346\227\213\350\275\25490\302\260", nullptr));
        sureTransform->setText(QCoreApplication::translate("PS", "\345\272\224\347\224\250", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_3), QCoreApplication::translate("PS", "\346\227\213\350\275\254\345\217\230\346\215\242", nullptr));

        const bool __sortingEnabled2 = FilterList->isSortingEnabled();
        FilterList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem30 = FilterList->item(0);
        ___qlistwidgetitem30->setText(QCoreApplication::translate("PS", "\345\244\247\345\270\210\351\273\221\347\231\275", nullptr));
        QListWidgetItem *___qlistwidgetitem31 = FilterList->item(1);
        ___qlistwidgetitem31->setText(QCoreApplication::translate("PS", "\345\244\215\345\217\244\350\203\266\347\211\207", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = FilterList->item(2);
        ___qlistwidgetitem32->setText(QCoreApplication::translate("PS", "\351\223\205\347\254\224\347\264\240\346\217\217", nullptr));
        QListWidgetItem *___qlistwidgetitem33 = FilterList->item(3);
        ___qlistwidgetitem33->setText(QCoreApplication::translate("PS", "\345\275\251\350\211\262\351\223\205\347\254\224\347\224\273", nullptr));
        QListWidgetItem *___qlistwidgetitem34 = FilterList->item(4);
        ___qlistwidgetitem34->setText(QCoreApplication::translate("PS", "\345\215\241\351\200\232\345\212\250\346\274\253", nullptr));
        QListWidgetItem *___qlistwidgetitem35 = FilterList->item(5);
        ___qlistwidgetitem35->setText(QCoreApplication::translate("PS", "\345\223\245\347\211\271\346\262\271\347\224\273", nullptr));
        QListWidgetItem *___qlistwidgetitem36 = FilterList->item(6);
        ___qlistwidgetitem36->setText(QCoreApplication::translate("PS", "\345\275\251\350\211\262\347\263\226\345\235\227\346\262\271\347\224\273", nullptr));
        QListWidgetItem *___qlistwidgetitem37 = FilterList->item(7);
        ___qlistwidgetitem37->setText(QCoreApplication::translate("PS", "\345\221\220\345\226\212\346\262\271\347\224\273", nullptr));
        QListWidgetItem *___qlistwidgetitem38 = FilterList->item(8);
        ___qlistwidgetitem38->setText(QCoreApplication::translate("PS", "\347\245\236\345\245\210\345\267\235\345\206\262\346\265\252\351\207\214\346\262\271\347\224\273", nullptr));
        QListWidgetItem *___qlistwidgetitem39 = FilterList->item(9);
        ___qlistwidgetitem39->setText(QCoreApplication::translate("PS", "\345\245\207\345\274\202\346\262\271\347\224\273", nullptr));
        QListWidgetItem *___qlistwidgetitem40 = FilterList->item(10);
        ___qlistwidgetitem40->setText(QCoreApplication::translate("PS", "\350\226\260\350\241\243\350\215\211\346\262\271\347\224\273", nullptr));
        FilterList->setSortingEnabled(__sortingEnabled2);

        sureFilter->setText(QCoreApplication::translate("PS", "\345\272\224\347\224\250", nullptr));
        toolBox->setItemText(toolBox->indexOf(Filter), QCoreApplication::translate("PS", "\347\211\271\346\225\210\346\273\244\351\225\234", nullptr));
        radioBilateral->setText(QCoreApplication::translate("PS", "\345\217\214\350\276\271\350\277\207\346\273\244", nullptr));
        radioMedian->setText(QCoreApplication::translate("PS", "\344\270\255\345\200\274\350\277\207\346\273\244", nullptr));
        radioBlur->setText(QCoreApplication::translate("PS", "\345\235\207\345\200\274\350\277\207\346\273\244", nullptr));
        radioGaussion->setText(QCoreApplication::translate("PS", "\351\253\230\346\226\257\350\277\207\346\273\244", nullptr));
        label4->setText(QCoreApplication::translate("PS", "Note: \346\224\271\345\217\230\347\256\227\346\263\225\345\220\216\345\276\256\350\260\203\346\273\221\345\235\227\343\200\202", nullptr));
        sureAlgo->setText(QCoreApplication::translate("PS", "\345\272\224\347\224\250", nullptr));
        toolBox->setItemText(toolBox->indexOf(algrothime), QCoreApplication::translate("PS", "\350\277\207\346\273\244\347\256\227\346\263\225", nullptr));

        const bool __sortingEnabled3 = AIList->isSortingEnabled();
        AIList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem41 = AIList->item(0);
        ___qlistwidgetitem41->setText(QCoreApplication::translate("PS", "\346\231\272\350\203\275\347\276\216\345\214\226", nullptr));
        QListWidgetItem *___qlistwidgetitem42 = AIList->item(1);
        ___qlistwidgetitem42->setText(QCoreApplication::translate("PS", "\351\273\221\347\231\275\345\233\276\345\203\217\344\270\212\350\211\262", nullptr));
        QListWidgetItem *___qlistwidgetitem43 = AIList->item(2);
        ___qlistwidgetitem43->setText(QCoreApplication::translate("PS", "\344\272\272\347\211\251\345\212\250\346\274\253\345\214\226", nullptr));
        QListWidgetItem *___qlistwidgetitem44 = AIList->item(3);
        ___qlistwidgetitem44->setText(QCoreApplication::translate("PS", "\350\203\214\346\231\257\346\266\210\351\231\244", nullptr));
        AIList->setSortingEnabled(__sortingEnabled3);

        toolBox->setItemText(toolBox->indexOf(AITool), QCoreApplication::translate("PS", "\346\231\272\350\203\275\345\267\245\345\205\267", nullptr));
        otherTool->setTitle(QCoreApplication::translate("PS", "\345\205\266\344\273\226\345\267\245\345\205\267", nullptr));
#if QT_CONFIG(tooltip)
        FaceTestToolBtn->setToolTip(QCoreApplication::translate("PS", "\345\234\250\347\272\277\346\243\200\346\265\213\344\272\272\350\204\270\351\235\242\351\203\250\350\277\224\345\233\236\344\270\200\347\263\273\345\210\227\347\232\204\344\272\272\350\204\270\344\277\241\346\201\257", nullptr));
#endif // QT_CONFIG(tooltip)
        FaceTestToolBtn->setText(QCoreApplication::translate("PS", "\344\272\272\350\204\270\344\277\241\346\201\257\346\243\200\346\265\213", nullptr));
#if QT_CONFIG(tooltip)
        btnUndo->setToolTip(QCoreApplication::translate("PS", "\346\222\244\351\224\200\344\270\212\344\270\200\346\255\245\346\223\215\344\275\234", nullptr));
#endif // QT_CONFIG(tooltip)
        btnUndo->setText(QCoreApplication::translate("PS", "\346\222\244\351\224\200", nullptr));
#if QT_CONFIG(shortcut)
        btnUndo->setShortcut(QCoreApplication::translate("PS", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        btnReset->setToolTip(QCoreApplication::translate("PS", "\350\277\230\345\216\237\345\210\260\345\210\235\345\247\213\345\233\276\345\203\217", nullptr));
#endif // QT_CONFIG(tooltip)
        btnReset->setText(QCoreApplication::translate("PS", "\350\277\230\345\216\237", nullptr));
#if QT_CONFIG(shortcut)
        btnReset->setShortcut(QCoreApplication::translate("PS", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        btnComparison->setToolTip(QCoreApplication::translate("PS", "\344\270\216\345\216\237\345\233\276\350\277\233\350\241\214\345\257\271\346\257\224", nullptr));
#endif // QT_CONFIG(tooltip)
        btnComparison->setText(QCoreApplication::translate("PS", "\345\257\271\346\257\224", nullptr));
        btnOpenImg->setText(QCoreApplication::translate("PS", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
#if QT_CONFIG(tooltip)
        btnDireSave->setToolTip(QCoreApplication::translate("PS", "\344\273\245\346\233\277\346\215\242\345\216\237\346\235\245\345\233\276\347\211\207\347\232\204\345\275\242\345\274\217\344\277\235\345\255\230", nullptr));
#endif // QT_CONFIG(tooltip)
        btnDireSave->setText(QCoreApplication::translate("PS", "\344\277\235\345\255\230\346\233\277\346\215\242", nullptr));
#if QT_CONFIG(shortcut)
        btnDireSave->setShortcut(QCoreApplication::translate("PS", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        btnSaveAs->setToolTip(QCoreApplication::translate("PS", "\345\217\246\345\255\230\345\210\260\346\214\207\345\256\232\344\275\215\347\275\256", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSaveAs->setText(QCoreApplication::translate("PS", "\345\217\246\345\255\230\344\270\272", nullptr));
#if QT_CONFIG(shortcut)
        btnSaveAs->setShortcut(QCoreApplication::translate("PS", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class PS: public Ui_PS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PS_H
