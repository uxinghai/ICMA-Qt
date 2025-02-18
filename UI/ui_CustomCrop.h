/********************************************************************************
** Form generated from reading UI file 'CustomCrop.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMCROP_H
#define UI_CUSTOMCROP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "../src/Widgets/photoShop/ImgCropper/Tool/ImageCropperLabel.h"

QT_BEGIN_NAMESPACE

class Ui_CustomCrop
{
public:
    QGridLayout *gridLayout;
    ImageCropperLabel *imgCropperLabel;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *btnSavePreview;
    QPushButton *btnQuit;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_2;
    QLabel *label_10;
    QCheckBox *checkEnableOpacity;
    QSlider *sliderOpacity;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_9;
    QLabel *labelPreviewImage;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label_4;
    QComboBox *comboOutputShape;
    QLabel *label_5;
    QComboBox *comboCropperShape;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QToolButton *btnChooseDragSquareColor;
    QLabel *label_12;
    QLineEdit *editDragSquareEdge;
    QLabel *label_14;
    QLabel *label_13;
    QLabel *labelDragSquareColor;
    QCheckBox *checkShowDragSquare;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QLineEdit *editCropperFixedHeight;
    QLabel *label_7;
    QLineEdit *editCropperFixedWidth;
    QLabel *label_8;
    QComboBox *editCropperMinWidth;
    QLabel *label_9;
    QComboBox *editCropperMinHeight;
    QGroupBox *groupBox_5;
    QFormLayout *formLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_18;
    QCheckBox *checkShowRectBorder;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_16;
    QLabel *labelRectBorderColor;
    QToolButton *btnChooseRectBorderColor;

    void setupUi(QWidget *CustomCrop)
    {
        if (CustomCrop->objectName().isEmpty())
            CustomCrop->setObjectName("CustomCrop");
        CustomCrop->resize(926, 632);
        CustomCrop->setMinimumSize(QSize(879, 532));
        CustomCrop->setMaximumSize(QSize(999, 700));
        gridLayout = new QGridLayout(CustomCrop);
        gridLayout->setObjectName("gridLayout");
        imgCropperLabel = new ImageCropperLabel(CustomCrop);
        imgCropperLabel->setObjectName("imgCropperLabel");
        imgCropperLabel->setMinimumSize(QSize(600, 500));
        imgCropperLabel->setFrameShape(QFrame::Box);
        imgCropperLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout->addWidget(imgCropperLabel, 0, 0, 1, 1);

        widget = new QWidget(CustomCrop);
        widget->setObjectName("widget");
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setHorizontalSpacing(3);
        gridLayout_2->setVerticalSpacing(5);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        btnSavePreview = new QPushButton(widget);
        btnSavePreview->setObjectName("btnSavePreview");

        horizontalLayout_13->addWidget(btnSavePreview);

        btnQuit = new QPushButton(widget);
        btnQuit->setObjectName("btnQuit");

        horizontalLayout_13->addWidget(btnQuit);


        gridLayout_2->addLayout(horizontalLayout_13, 7, 0, 1, 1);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName("groupBox_3");
        formLayout_2 = new QFormLayout(groupBox_3);
        formLayout_2->setObjectName("formLayout_2");
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_10);

        checkEnableOpacity = new QCheckBox(groupBox_3);
        checkEnableOpacity->setObjectName("checkEnableOpacity");
        checkEnableOpacity->setChecked(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, checkEnableOpacity);

        sliderOpacity = new QSlider(groupBox_3);
        sliderOpacity->setObjectName("sliderOpacity");
        sliderOpacity->setMaximum(100);
        sliderOpacity->setValue(60);
        sliderOpacity->setOrientation(Qt::Horizontal);

        formLayout_2->setWidget(1, QFormLayout::SpanningRole, sliderOpacity);


        gridLayout_2->addWidget(groupBox_3, 3, 0, 1, 1);

        groupBox_6 = new QGroupBox(widget);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayout_9 = new QGridLayout(groupBox_6);
        gridLayout_9->setSpacing(0);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(0, 0, 0, 5);
        labelPreviewImage = new QLabel(groupBox_6);
        labelPreviewImage->setObjectName("labelPreviewImage");
        labelPreviewImage->setMinimumSize(QSize(96, 96));
        labelPreviewImage->setMaximumSize(QSize(96, 96));
        labelPreviewImage->setFrameShape(QFrame::Panel);
        labelPreviewImage->setFrameShadow(QFrame::Sunken);
        labelPreviewImage->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(labelPreviewImage, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_6, 0, 0, 1, 1);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        comboOutputShape = new QComboBox(groupBox);
        comboOutputShape->addItem(QString());
        comboOutputShape->addItem(QString());
        comboOutputShape->setObjectName("comboOutputShape");

        formLayout->setWidget(0, QFormLayout::FieldRole, comboOutputShape);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        comboCropperShape = new QComboBox(groupBox);
        comboCropperShape->addItem(QString());
        comboCropperShape->addItem(QString());
        comboCropperShape->addItem(QString());
        comboCropperShape->addItem(QString());
        comboCropperShape->addItem(QString());
        comboCropperShape->addItem(QString());
        comboCropperShape->setObjectName("comboCropperShape");

        formLayout->setWidget(1, QFormLayout::FieldRole, comboCropperShape);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName("gridLayout_4");
        btnChooseDragSquareColor = new QToolButton(groupBox_4);
        btnChooseDragSquareColor->setObjectName("btnChooseDragSquareColor");

        gridLayout_4->addWidget(btnChooseDragSquareColor, 2, 3, 1, 1);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName("label_12");

        gridLayout_4->addWidget(label_12, 0, 0, 1, 1);

        editDragSquareEdge = new QLineEdit(groupBox_4);
        editDragSquareEdge->setObjectName("editDragSquareEdge");

        gridLayout_4->addWidget(editDragSquareEdge, 1, 1, 1, 3);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName("label_14");

        gridLayout_4->addWidget(label_14, 2, 0, 1, 2);

        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName("label_13");

        gridLayout_4->addWidget(label_13, 1, 0, 1, 1);

        labelDragSquareColor = new QLabel(groupBox_4);
        labelDragSquareColor->setObjectName("labelDragSquareColor");

        gridLayout_4->addWidget(labelDragSquareColor, 2, 2, 1, 1);

        checkShowDragSquare = new QCheckBox(groupBox_4);
        checkShowDragSquare->setObjectName("checkShowDragSquare");
        checkShowDragSquare->setChecked(true);

        gridLayout_4->addWidget(checkShowDragSquare, 0, 1, 1, 2);


        gridLayout_2->addWidget(groupBox_4, 4, 0, 1, 1);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName("gridLayout_3");
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        editCropperFixedHeight = new QLineEdit(groupBox_2);
        editCropperFixedHeight->setObjectName("editCropperFixedHeight");
        editCropperFixedHeight->setEnabled(false);

        gridLayout_3->addWidget(editCropperFixedHeight, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_7, 0, 2, 1, 1);

        editCropperFixedWidth = new QLineEdit(groupBox_2);
        editCropperFixedWidth->setObjectName("editCropperFixedWidth");
        editCropperFixedWidth->setEnabled(false);

        gridLayout_3->addWidget(editCropperFixedWidth, 0, 3, 1, 2);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);

        editCropperMinWidth = new QComboBox(groupBox_2);
        editCropperMinWidth->addItem(QString());
        editCropperMinWidth->addItem(QString());
        editCropperMinWidth->addItem(QString());
        editCropperMinWidth->addItem(QString());
        editCropperMinWidth->addItem(QString());
        editCropperMinWidth->addItem(QString());
        editCropperMinWidth->addItem(QString());
        editCropperMinWidth->addItem(QString());
        editCropperMinWidth->setObjectName("editCropperMinWidth");
        editCropperMinWidth->setEditable(true);

        gridLayout_3->addWidget(editCropperMinWidth, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_9, 1, 2, 1, 1);

        editCropperMinHeight = new QComboBox(groupBox_2);
        editCropperMinHeight->addItem(QString());
        editCropperMinHeight->addItem(QString());
        editCropperMinHeight->addItem(QString());
        editCropperMinHeight->addItem(QString());
        editCropperMinHeight->addItem(QString());
        editCropperMinHeight->addItem(QString());
        editCropperMinHeight->addItem(QString());
        editCropperMinHeight->addItem(QString());
        editCropperMinHeight->setObjectName("editCropperMinHeight");
        editCropperMinHeight->setEditable(true);

        gridLayout_3->addWidget(editCropperMinHeight, 1, 3, 1, 2);


        gridLayout_2->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName("groupBox_5");
        formLayout_3 = new QFormLayout(groupBox_5);
        formLayout_3->setObjectName("formLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName("label_18");

        horizontalLayout->addWidget(label_18);

        checkShowRectBorder = new QCheckBox(groupBox_5);
        checkShowRectBorder->setObjectName("checkShowRectBorder");
        checkShowRectBorder->setChecked(true);

        horizontalLayout->addWidget(checkShowRectBorder);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName("label_16");

        horizontalLayout_2->addWidget(label_16);

        labelRectBorderColor = new QLabel(groupBox_5);
        labelRectBorderColor->setObjectName("labelRectBorderColor");

        horizontalLayout_2->addWidget(labelRectBorderColor);

        btnChooseRectBorderColor = new QToolButton(groupBox_5);
        btnChooseRectBorderColor->setObjectName("btnChooseRectBorderColor");

        horizontalLayout_2->addWidget(btnChooseRectBorderColor);


        formLayout_3->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);


        gridLayout_2->addWidget(groupBox_5, 5, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 1, 1, 1);


        retranslateUi(CustomCrop);

        QMetaObject::connectSlotsByName(CustomCrop);
    } // setupUi

    void retranslateUi(QWidget *CustomCrop)
    {
        CustomCrop->setWindowTitle(QCoreApplication::translate("CustomCrop", "\350\207\252\347\224\261\350\243\201\345\211\252\342\200\224\342\200\224\351\253\230\347\272\247\350\243\201\345\211\252", nullptr));
        imgCropperLabel->setText(QCoreApplication::translate("CustomCrop", "TextLabel", nullptr));
        btnSavePreview->setText(QCoreApplication::translate("CustomCrop", "\347\241\256\345\256\232", nullptr));
        btnQuit->setText(QCoreApplication::translate("CustomCrop", "\345\217\226\346\266\210", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CustomCrop", "\345\244\226\350\247\202\350\256\276\347\275\256", nullptr));
        label_10->setText(QCoreApplication::translate("CustomCrop", "\345\220\257\347\224\250\344\270\215\351\200\217\346\230\216\345\272\246\357\274\232", nullptr));
        checkEnableOpacity->setText(QString());
        groupBox_6->setTitle(QCoreApplication::translate("CustomCrop", "\351\242\204\350\247\210", nullptr));
        labelPreviewImage->setText(QCoreApplication::translate("CustomCrop", "TextLabel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CustomCrop", "\345\275\242\347\212\266\350\256\276\347\275\256", nullptr));
        label_4->setText(QCoreApplication::translate("CustomCrop", "\350\276\223\345\207\272\345\275\242\347\212\266\357\274\232", nullptr));
        comboOutputShape->setItemText(0, QCoreApplication::translate("CustomCrop", "\347\237\251\345\275\242/\346\226\271\345\275\242", nullptr));
        comboOutputShape->setItemText(1, QCoreApplication::translate("CustomCrop", "\346\244\255\345\234\206/\345\234\206", nullptr));

        label_5->setText(QCoreApplication::translate("CustomCrop", "\350\243\201\345\211\252\345\275\242\347\212\266\357\274\232", nullptr));
        comboCropperShape->setItemText(0, QCoreApplication::translate("CustomCrop", "\347\237\251\345\275\242", nullptr));
        comboCropperShape->setItemText(1, QCoreApplication::translate("CustomCrop", "\346\226\271\345\275\242", nullptr));
        comboCropperShape->setItemText(2, QCoreApplication::translate("CustomCrop", "\345\233\272\345\256\232\347\237\251\345\275\242", nullptr));
        comboCropperShape->setItemText(3, QCoreApplication::translate("CustomCrop", "\345\234\206\345\275\242", nullptr));
        comboCropperShape->setItemText(4, QCoreApplication::translate("CustomCrop", "\346\244\255\345\234\206", nullptr));
        comboCropperShape->setItemText(5, QCoreApplication::translate("CustomCrop", "\345\233\272\345\256\232\346\244\255\345\234\206", nullptr));

        groupBox_4->setTitle(QCoreApplication::translate("CustomCrop", "\346\213\226\345\212\250\346\216\247\345\210\266\347\202\271\350\256\276\347\275\256", nullptr));
        btnChooseDragSquareColor->setText(QCoreApplication::translate("CustomCrop", "\351\200\211\346\213\251", nullptr));
        label_12->setText(QCoreApplication::translate("CustomCrop", "\346\230\276\347\244\272\346\213\226\345\212\250\346\226\271\345\235\227\357\274\232", nullptr));
        editDragSquareEdge->setPlaceholderText(QCoreApplication::translate("CustomCrop", "\350\276\223\345\205\245\350\276\271\351\225\277", nullptr));
        label_14->setText(QCoreApplication::translate("CustomCrop", "\346\213\226\345\212\250\346\226\271\345\235\227\347\232\204\351\242\234\350\211\262\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("CustomCrop", "\346\213\226\345\212\250\346\226\271\345\235\227\350\276\271\351\225\277\357\274\232", nullptr));
        labelDragSquareColor->setText(QCoreApplication::translate("CustomCrop", "TextLabel", nullptr));
        checkShowDragSquare->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("CustomCrop", "\345\260\272\345\257\270\350\256\276\347\275\256", nullptr));
        label_6->setText(QCoreApplication::translate("CustomCrop", "\345\233\272\345\256\232\345\244\247\345\260\217\357\274\232", nullptr));
        editCropperFixedHeight->setPlaceholderText(QCoreApplication::translate("CustomCrop", "\351\225\277\345\272\246", nullptr));
        label_7->setText(QCoreApplication::translate("CustomCrop", "\303\227", nullptr));
        editCropperFixedWidth->setPlaceholderText(QCoreApplication::translate("CustomCrop", "\345\256\275\345\272\246", nullptr));
        label_8->setText(QCoreApplication::translate("CustomCrop", "\346\234\200\345\260\217\345\275\242\347\212\266\357\274\232", nullptr));
        editCropperMinWidth->setItemText(0, QCoreApplication::translate("CustomCrop", "8", nullptr));
        editCropperMinWidth->setItemText(1, QCoreApplication::translate("CustomCrop", "16", nullptr));
        editCropperMinWidth->setItemText(2, QCoreApplication::translate("CustomCrop", "32", nullptr));
        editCropperMinWidth->setItemText(3, QCoreApplication::translate("CustomCrop", "64", nullptr));
        editCropperMinWidth->setItemText(4, QCoreApplication::translate("CustomCrop", "128", nullptr));
        editCropperMinWidth->setItemText(5, QCoreApplication::translate("CustomCrop", "256", nullptr));
        editCropperMinWidth->setItemText(6, QCoreApplication::translate("CustomCrop", "512", nullptr));
        editCropperMinWidth->setItemText(7, QCoreApplication::translate("CustomCrop", "1024", nullptr));

        label_9->setText(QCoreApplication::translate("CustomCrop", "\303\227", nullptr));
        editCropperMinHeight->setItemText(0, QCoreApplication::translate("CustomCrop", "8", nullptr));
        editCropperMinHeight->setItemText(1, QCoreApplication::translate("CustomCrop", "16", nullptr));
        editCropperMinHeight->setItemText(2, QCoreApplication::translate("CustomCrop", "32", nullptr));
        editCropperMinHeight->setItemText(3, QCoreApplication::translate("CustomCrop", "64", nullptr));
        editCropperMinHeight->setItemText(4, QCoreApplication::translate("CustomCrop", "128", nullptr));
        editCropperMinHeight->setItemText(5, QCoreApplication::translate("CustomCrop", "256", nullptr));
        editCropperMinHeight->setItemText(6, QCoreApplication::translate("CustomCrop", "512", nullptr));
        editCropperMinHeight->setItemText(7, QCoreApplication::translate("CustomCrop", "1024", nullptr));

        groupBox_5->setTitle(QCoreApplication::translate("CustomCrop", "\350\276\271\346\241\206\350\256\276\347\275\256", nullptr));
        label_18->setText(QCoreApplication::translate("CustomCrop", "\346\230\276\347\244\272\350\276\271\346\241\206\357\274\232", nullptr));
        checkShowRectBorder->setText(QString());
        label_16->setText(QCoreApplication::translate("CustomCrop", "\350\276\271\346\241\206\351\242\234\350\211\262\357\274\232", nullptr));
        labelRectBorderColor->setText(QCoreApplication::translate("CustomCrop", "TextLabel", nullptr));
        btnChooseRectBorderColor->setText(QCoreApplication::translate("CustomCrop", "\351\200\211\346\213\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomCrop: public Ui_CustomCrop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMCROP_H
