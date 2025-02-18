/********************************************************************************
** Form generated from reading UI file 'SimpleCrop.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLECROP_H
#define UI_SIMPLECROP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "../src/Widgets/photoShop/ImgCropper/Tool/ImageCropperLabel.h"

QT_BEGIN_NAMESPACE

class Ui_SimpleCrop
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSavePreview;
    QPushButton *btnQuit;
    ImageCropperLabel *imgCropperLabel;

    void setupUi(QWidget *SimpleCrop)
    {
        if (SimpleCrop->objectName().isEmpty())
            SimpleCrop->setObjectName("SimpleCrop");
        SimpleCrop->resize(600, 500);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SimpleCrop->sizePolicy().hasHeightForWidth());
        SimpleCrop->setSizePolicy(sizePolicy);
        SimpleCrop->setMinimumSize(QSize(600, 500));
        SimpleCrop->setMaximumSize(QSize(600, 500));
        gridLayout = new QGridLayout(SimpleCrop);
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer = new QSpacerItem(417, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        btnSavePreview = new QPushButton(SimpleCrop);
        btnSavePreview->setObjectName("btnSavePreview");

        gridLayout->addWidget(btnSavePreview, 1, 1, 1, 1);

        btnQuit = new QPushButton(SimpleCrop);
        btnQuit->setObjectName("btnQuit");

        gridLayout->addWidget(btnQuit, 1, 2, 1, 1);

        imgCropperLabel = new ImageCropperLabel(SimpleCrop);
        imgCropperLabel->setObjectName("imgCropperLabel");
        imgCropperLabel->setMinimumSize(QSize(0, 0));
        imgCropperLabel->setFrameShape(QFrame::NoFrame);
        imgCropperLabel->setFrameShadow(QFrame::Plain);
        imgCropperLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(imgCropperLabel, 0, 0, 1, 3);


        retranslateUi(SimpleCrop);

        QMetaObject::connectSlotsByName(SimpleCrop);
    } // setupUi

    void retranslateUi(QWidget *SimpleCrop)
    {
        SimpleCrop->setWindowTitle(QCoreApplication::translate("SimpleCrop", "\350\207\252\347\224\261\350\243\201\345\211\252\342\200\224\342\200\224\351\253\230\347\272\247\350\243\201\345\211\252", nullptr));
        btnSavePreview->setText(QCoreApplication::translate("SimpleCrop", "\347\241\256\345\256\232", nullptr));
        btnQuit->setText(QCoreApplication::translate("SimpleCrop", "\345\217\226\346\266\210", nullptr));
        imgCropperLabel->setText(QCoreApplication::translate("SimpleCrop", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimpleCrop: public Ui_SimpleCrop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLECROP_H
