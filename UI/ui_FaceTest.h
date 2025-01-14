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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceTest
{
public:
    QHBoxLayout *mainLayout;
    QLabel *lbCamera;
    QGraphicsView *graphicsView;
    QVBoxLayout *sidebarLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *btnCaptureImage;
    QPushButton *btnOPCamera;
    QGroupBox *detailGroupBox;
    QFormLayout *formLayout;
    QLabel *labelGender;
    QLabel *gender;
    QLabel *labelAge;
    QLabel *age;
    QLabel *labelFaceShape;
    QLabel *face_shape;
    QLabel *labelEmotion;
    QLabel *emotion;
    QLabel *labelBeauty;
    QLabel *beauty;
    QLabel *labelBeauty_2;
    QLabel *beauty_2;
    QLabel *labelBeauty_3;
    QLabel *beauty_3;
    QHBoxLayout *progressLayout;
    QLabel *labelProgress;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer;
    QLabel *infoLabel;

    void setupUi(QWidget *FaceTest)
    {
        if (FaceTest->objectName().isEmpty())
            FaceTest->setObjectName("FaceTest");
        FaceTest->resize(800, 600);
        FaceTest->setMinimumSize(QSize(800, 600));
        QFont font;
        font.setPointSize(11);
        FaceTest->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/faceTest.png"), QSize(), QIcon::Normal, QIcon::Off);
        FaceTest->setWindowIcon(icon);
        mainLayout = new QHBoxLayout(FaceTest);
        mainLayout->setObjectName("mainLayout");
        lbCamera = new QLabel(FaceTest);
        lbCamera->setObjectName("lbCamera");

        mainLayout->addWidget(lbCamera);

        graphicsView = new QGraphicsView(FaceTest);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(500, 0));

        mainLayout->addWidget(graphicsView);

        sidebarLayout = new QVBoxLayout();
        sidebarLayout->setObjectName("sidebarLayout");
        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        btnCaptureImage = new QPushButton(FaceTest);
        btnCaptureImage->setObjectName("btnCaptureImage");

        buttonLayout->addWidget(btnCaptureImage);

        btnOPCamera = new QPushButton(FaceTest);
        btnOPCamera->setObjectName("btnOPCamera");

        buttonLayout->addWidget(btnOPCamera);


        sidebarLayout->addLayout(buttonLayout);

        detailGroupBox = new QGroupBox(FaceTest);
        detailGroupBox->setObjectName("detailGroupBox");
        formLayout = new QFormLayout(detailGroupBox);
        formLayout->setObjectName("formLayout");
        labelGender = new QLabel(detailGroupBox);
        labelGender->setObjectName("labelGender");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelGender);

        gender = new QLabel(detailGroupBox);
        gender->setObjectName("gender");

        formLayout->setWidget(0, QFormLayout::FieldRole, gender);

        labelAge = new QLabel(detailGroupBox);
        labelAge->setObjectName("labelAge");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelAge);

        age = new QLabel(detailGroupBox);
        age->setObjectName("age");

        formLayout->setWidget(1, QFormLayout::FieldRole, age);

        labelFaceShape = new QLabel(detailGroupBox);
        labelFaceShape->setObjectName("labelFaceShape");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelFaceShape);

        face_shape = new QLabel(detailGroupBox);
        face_shape->setObjectName("face_shape");

        formLayout->setWidget(2, QFormLayout::FieldRole, face_shape);

        labelEmotion = new QLabel(detailGroupBox);
        labelEmotion->setObjectName("labelEmotion");

        formLayout->setWidget(3, QFormLayout::LabelRole, labelEmotion);

        emotion = new QLabel(detailGroupBox);
        emotion->setObjectName("emotion");

        formLayout->setWidget(3, QFormLayout::FieldRole, emotion);

        labelBeauty = new QLabel(detailGroupBox);
        labelBeauty->setObjectName("labelBeauty");

        formLayout->setWidget(4, QFormLayout::LabelRole, labelBeauty);

        beauty = new QLabel(detailGroupBox);
        beauty->setObjectName("beauty");

        formLayout->setWidget(4, QFormLayout::FieldRole, beauty);

        labelBeauty_2 = new QLabel(detailGroupBox);
        labelBeauty_2->setObjectName("labelBeauty_2");

        formLayout->setWidget(5, QFormLayout::LabelRole, labelBeauty_2);

        beauty_2 = new QLabel(detailGroupBox);
        beauty_2->setObjectName("beauty_2");

        formLayout->setWidget(5, QFormLayout::FieldRole, beauty_2);

        labelBeauty_3 = new QLabel(detailGroupBox);
        labelBeauty_3->setObjectName("labelBeauty_3");

        formLayout->setWidget(6, QFormLayout::LabelRole, labelBeauty_3);

        beauty_3 = new QLabel(detailGroupBox);
        beauty_3->setObjectName("beauty_3");

        formLayout->setWidget(6, QFormLayout::FieldRole, beauty_3);


        sidebarLayout->addWidget(detailGroupBox);

        progressLayout = new QHBoxLayout();
        progressLayout->setObjectName("progressLayout");
        labelProgress = new QLabel(FaceTest);
        labelProgress->setObjectName("labelProgress");

        progressLayout->addWidget(labelProgress);

        progressBar = new QProgressBar(FaceTest);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        progressLayout->addWidget(progressBar);


        sidebarLayout->addLayout(progressLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(verticalSpacer);

        infoLabel = new QLabel(FaceTest);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setWordWrap(true);

        sidebarLayout->addWidget(infoLabel);


        mainLayout->addLayout(sidebarLayout);


        retranslateUi(FaceTest);

        QMetaObject::connectSlotsByName(FaceTest);
    } // setupUi

    void retranslateUi(QWidget *FaceTest)
    {
        FaceTest->setWindowTitle(QCoreApplication::translate("FaceTest", "\344\272\272\350\204\270\344\277\241\346\201\257\346\243\200\346\265\213", nullptr));
        lbCamera->setText(QCoreApplication::translate("FaceTest", "TextLabel", nullptr));
        btnCaptureImage->setText(QCoreApplication::translate("FaceTest", "\346\213\215\347\205\247\346\243\200\346\265\213", nullptr));
        btnOPCamera->setText(QCoreApplication::translate("FaceTest", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", nullptr));
        detailGroupBox->setTitle(QCoreApplication::translate("FaceTest", "\346\202\250\347\232\204\344\277\241\346\201\257\357\274\232", nullptr));
        labelGender->setText(QCoreApplication::translate("FaceTest", "\346\200\247        \345\210\253\357\274\232", nullptr));
        labelAge->setText(QCoreApplication::translate("FaceTest", "\345\271\264        \351\276\204\357\274\232", nullptr));
        labelFaceShape->setText(QCoreApplication::translate("FaceTest", "\350\204\270        \345\236\213\357\274\232", nullptr));
        labelEmotion->setText(QCoreApplication::translate("FaceTest", "\346\203\205        \347\273\252\357\274\232", nullptr));
        labelBeauty->setText(QCoreApplication::translate("FaceTest", "\351\242\234        \345\200\274\357\274\232", nullptr));
        labelBeauty_2->setText(QCoreApplication::translate("FaceTest", "\344\275\251\346\210\264\347\234\274\351\225\234\357\274\237", nullptr));
        labelBeauty_3->setText(QCoreApplication::translate("FaceTest", "\344\275\251\346\210\264\345\217\243\347\275\251\357\274\237", nullptr));
        labelProgress->setText(QCoreApplication::translate("FaceTest", "\350\277\233\345\272\246:", nullptr));
        infoLabel->setText(QCoreApplication::translate("FaceTest", " AI\346\243\200\346\265\213\347\273\223\346\236\234\344\273\205\344\276\233\345\217\202\350\200\203\357\274\214\346\233\264\345\244\232\344\277\241\346\201\257\350\257\267\350\201\224\347\263\273\345\274\200\345\217\221\350\200\205\343\200\202\n"
"Email:uxinghaiwyi@163.com               ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FaceTest: public Ui_FaceTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACETEST_H
