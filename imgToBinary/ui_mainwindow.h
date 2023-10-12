/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *loadImageBtn;
    QPushButton *toBinaryBtn;
    QPushButton *toImageBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 300);
        MainWindow->setMinimumSize(QSize(600, 300));
        MainWindow->setMaximumSize(QSize(600, 300));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(20, 20, 421, 261));
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::LosslessImageRendering|QPainter::NonCosmeticBrushPatterns|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing|QPainter::VerticalSubpixelPositioning);
        graphicsView->setOptimizationFlags(QGraphicsView::IndirectPainting);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(450, 20, 143, 88));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        loadImageBtn = new QPushButton(widget);
        loadImageBtn->setObjectName("loadImageBtn");

        verticalLayout->addWidget(loadImageBtn);

        toBinaryBtn = new QPushButton(widget);
        toBinaryBtn->setObjectName("toBinaryBtn");

        verticalLayout->addWidget(toBinaryBtn);


        verticalLayout_2->addLayout(verticalLayout);

        toImageBtn = new QPushButton(widget);
        toImageBtn->setObjectName("toImageBtn");

        verticalLayout_2->addWidget(toImageBtn);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ImageConverter", nullptr));
        loadImageBtn->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        toBinaryBtn->setText(QCoreApplication::translate("MainWindow", "\320\222 \320\264\320\262\320\276\320\270\321\207\320\275\321\213\320\271 \320\272\320\276\320\264", nullptr));
        toImageBtn->setText(QCoreApplication::translate("MainWindow", "\320\222 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
