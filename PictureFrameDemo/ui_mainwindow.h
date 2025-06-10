/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *cb_item;
    QRadioButton *btn_Rect;
    QRadioButton *btn_Line;
    QRadioButton *btn_Point;
    QCheckBox *btn_scale;
    QPushButton *btn_SelectImg;
    QPushButton *btn_Clear;
    QPushButton *btn_Save;
    QVBoxLayout *verticalLayout_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1098, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cb_item = new QComboBox(widget);
        cb_item->addItem(QString());
        cb_item->addItem(QString());
        cb_item->addItem(QString());
        cb_item->setObjectName(QString::fromUtf8("cb_item"));

        horizontalLayout->addWidget(cb_item);

        btn_Rect = new QRadioButton(widget);
        btn_Rect->setObjectName(QString::fromUtf8("btn_Rect"));

        horizontalLayout->addWidget(btn_Rect);

        btn_Line = new QRadioButton(widget);
        btn_Line->setObjectName(QString::fromUtf8("btn_Line"));

        horizontalLayout->addWidget(btn_Line);

        btn_Point = new QRadioButton(widget);
        btn_Point->setObjectName(QString::fromUtf8("btn_Point"));

        horizontalLayout->addWidget(btn_Point);

        btn_scale = new QCheckBox(widget);
        btn_scale->setObjectName(QString::fromUtf8("btn_scale"));

        horizontalLayout->addWidget(btn_scale);

        btn_SelectImg = new QPushButton(widget);
        btn_SelectImg->setObjectName(QString::fromUtf8("btn_SelectImg"));

        horizontalLayout->addWidget(btn_SelectImg);

        btn_Clear = new QPushButton(widget);
        btn_Clear->setObjectName(QString::fromUtf8("btn_Clear"));

        horizontalLayout->addWidget(btn_Clear);

        btn_Save = new QPushButton(widget);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));

        horizontalLayout->addWidget(btn_Save);


        verticalLayout->addWidget(widget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1098, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        cb_item->setItemText(0, QCoreApplication::translate("MainWindow", "Rect", nullptr));
        cb_item->setItemText(1, QCoreApplication::translate("MainWindow", "Point", nullptr));
        cb_item->setItemText(2, QCoreApplication::translate("MainWindow", "Line", nullptr));

        btn_Rect->setText(QCoreApplication::translate("MainWindow", "Rect", nullptr));
        btn_Line->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        btn_Point->setText(QCoreApplication::translate("MainWindow", "Point", nullptr));
        btn_scale->setText(QCoreApplication::translate("MainWindow", "Image Scale", nullptr));
        btn_SelectImg->setText(QCoreApplication::translate("MainWindow", "select image", nullptr));
        btn_Clear->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        btn_Save->setText(QCoreApplication::translate("MainWindow", "savePic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
