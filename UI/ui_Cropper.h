/********************************************************************************
** Form generated from reading UI file 'Cropper.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CROPPER_H
#define UI_CROPPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cropper
{
public:
    QFormLayout *formLayout;
    QToolButton *customCrop;
    QToolButton *simpleCrop;

    void setupUi(QWidget *Cropper)
    {
        if (Cropper->objectName().isEmpty())
            Cropper->setObjectName("Cropper");
        Cropper->resize(288, 114);
        Cropper->setMinimumSize(QSize(0, 0));
        Cropper->setMaximumSize(QSize(16777215, 16777215));
        formLayout = new QFormLayout(Cropper);
        formLayout->setObjectName("formLayout");
        customCrop = new QToolButton(Cropper);
        customCrop->setObjectName("customCrop");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customCrop->sizePolicy().hasHeightForWidth());
        customCrop->setSizePolicy(sizePolicy);
        customCrop->setMinimumSize(QSize(270, 33));
        customCrop->setMaximumSize(QSize(270, 30));
        customCrop->setLayoutDirection(Qt::LeftToRight);

        formLayout->setWidget(0, QFormLayout::LabelRole, customCrop);

        simpleCrop = new QToolButton(Cropper);
        simpleCrop->setObjectName("simpleCrop");
        sizePolicy.setHeightForWidth(simpleCrop->sizePolicy().hasHeightForWidth());
        simpleCrop->setSizePolicy(sizePolicy);
        simpleCrop->setMinimumSize(QSize(270, 33));
        simpleCrop->setMaximumSize(QSize(270, 30));

        formLayout->setWidget(1, QFormLayout::LabelRole, simpleCrop);


        retranslateUi(Cropper);

        QMetaObject::connectSlotsByName(Cropper);
    } // setupUi

    void retranslateUi(QWidget *Cropper)
    {
        Cropper->setWindowTitle(QCoreApplication::translate("Cropper", "\350\243\201\345\211\252\345\267\245\345\205\267", nullptr));
        customCrop->setText(QCoreApplication::translate("Cropper", "\344\275\277\347\224\250\351\253\230\347\272\247\350\243\201\345\211\252", nullptr));
        simpleCrop->setText(QCoreApplication::translate("Cropper", "\344\275\277\347\224\250\347\256\200\345\215\225\350\243\201\345\211\252", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Cropper: public Ui_Cropper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CROPPER_H
