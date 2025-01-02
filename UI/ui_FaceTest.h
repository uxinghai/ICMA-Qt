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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout_2;
    QGraphicsView *graphicsView;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnCaptureImage;
    QPushButton *btnOPCamera;
    QGroupBox *detailGroupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *gender;
    QLabel *age;
    QLabel *face_shape;
    QLabel *emotion;
    QLabel *beauty;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer;
    QLabel *label;

    void setupUi(QWidget *FaceTest)
    {
        if (FaceTest->objectName().isEmpty())
            FaceTest->setObjectName("FaceTest");
        FaceTest->resize(773, 567);
        FaceTest->setMinimumSize(QSize(773, 567));
        FaceTest->setMaximumSize(QSize(773, 567));
        QFont font;
        font.setPointSize(11);
        FaceTest->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/faceTest.png"), QSize(), QIcon::Normal, QIcon::Off);
        FaceTest->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(FaceTest);
        gridLayout_2->setObjectName("gridLayout_2");
        graphicsView = new QGraphicsView(FaceTest);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMaximumSize(QSize(16777215, 16777215));
        graphicsView->setRenderHints(QPainter::RenderHint::Antialiasing|QPainter::RenderHint::SmoothPixmapTransform|QPainter::RenderHint::TextAntialiasing);
        graphicsView->setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorUnderMouse);

        gridLayout_2->addWidget(graphicsView, 0, 0, 1, 1);

        widget = new QWidget(FaceTest);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(200, 16777215));
        widget->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 5, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btnCaptureImage = new QPushButton(widget);
        btnCaptureImage->setObjectName("btnCaptureImage");

        horizontalLayout_2->addWidget(btnCaptureImage);

        btnOPCamera = new QPushButton(widget);
        btnOPCamera->setObjectName("btnOPCamera");

        horizontalLayout_2->addWidget(btnOPCamera);


        verticalLayout->addLayout(horizontalLayout_2);

        detailGroupBox = new QGroupBox(widget);
        detailGroupBox->setObjectName("detailGroupBox");
        verticalLayout_2 = new QVBoxLayout(detailGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gender = new QLabel(detailGroupBox);
        gender->setObjectName("gender");

        verticalLayout_2->addWidget(gender);

        age = new QLabel(detailGroupBox);
        age->setObjectName("age");

        verticalLayout_2->addWidget(age);

        face_shape = new QLabel(detailGroupBox);
        face_shape->setObjectName("face_shape");

        verticalLayout_2->addWidget(face_shape);

        emotion = new QLabel(detailGroupBox);
        emotion->setObjectName("emotion");

        verticalLayout_2->addWidget(emotion);

        beauty = new QLabel(detailGroupBox);
        beauty->setObjectName("beauty");

        verticalLayout_2->addWidget(beauty);


        verticalLayout->addWidget(detailGroupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName("progressBar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMaximumSize(QSize(16777215, 25));
        progressBar->setValue(0);

        horizontalLayout->addWidget(progressBar);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(widget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(250, 16777215));
        label->setScaledContents(true);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);


        gridLayout_2->addWidget(widget, 0, 1, 1, 1);


        retranslateUi(FaceTest);

        QMetaObject::connectSlotsByName(FaceTest);
    } // setupUi

    void retranslateUi(QWidget *FaceTest)
    {
        FaceTest->setWindowTitle(QCoreApplication::translate("FaceTest", "\344\272\272\350\204\270\344\277\241\346\201\257\346\243\200\346\265\213", nullptr));
        btnCaptureImage->setText(QCoreApplication::translate("FaceTest", "\346\213\215\347\205\247\346\243\200\346\265\213", nullptr));
        btnOPCamera->setText(QCoreApplication::translate("FaceTest", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", nullptr));
        detailGroupBox->setTitle(QCoreApplication::translate("FaceTest", "\346\202\250\347\232\204\344\277\241\346\201\257\357\274\232", nullptr));
        gender->setText(QString());
        age->setText(QString());
        face_shape->setText(QString());
        emotion->setText(QString());
        beauty->setText(QString());
        label_2->setText(QCoreApplication::translate("FaceTest", "\350\277\233\345\272\246:", nullptr));
        progressBar->setFormat(QString());
        label->setText(QCoreApplication::translate("FaceTest", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">AI\346\243\200\346\265\213(\346\235\245\350\207\252\347\231\276\345\272\246\344\272\221AI)\357\274\214\346\225\260\346\215\256\344\273\205\344\276\233\345\217\202\350\200\203\343\200\202\346\234\211\345\205\263\351\242\234\345\200\274\351\241\271\357\274\214\345\246\202\346\236\234\345\200\274\350\276\203\344\275\216\343\200\202\351\202\243\344\270\200\345\256\232\346\230\257\346\210\221\347"
                        "\232\204\347\250\213\345\272\217\345\207\272\351\224\231\344\272\206~</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\344\270\252\344\272\272\344\277\241\346\201\257\351\241\271\350\277\230\345\217\257\344\273\245\346\267\273\345\212\240\346\233\264\345\244\232\350\257\246\347\273\206\357\274\214\346\234\211\351\234\200\346\261\202\350\257\267\350\201\224\347\263\273\345\274\200\345\217\221\350\200\205\357\274\232uxinghaiwyi@163.com</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FaceTest: public Ui_FaceTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACETEST_H
