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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *m_pactShowLog;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *m_pcbxSelectItem;
    QRadioButton *m_prbtnRect;
    QRadioButton *m_prbtnLine;
    QRadioButton *m_prbtnPoint;
    QPushButton *m_ppbtnSelectImage;
    QPushButton *m_ppbtnClear;
    QPushButton *m_ppbtnSaveImage;
    QVBoxLayout *m_pImageVerticalLayout;
    QTextEdit *m_pteShowLog;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1098, 720);
        m_pactShowLog = new QAction(MainWindow);
        m_pactShowLog->setObjectName(QString::fromUtf8("m_pactShowLog"));
        m_pactShowLog->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pcbxSelectItem = new QComboBox(widget);
        m_pcbxSelectItem->addItem(QString());
        m_pcbxSelectItem->addItem(QString());
        m_pcbxSelectItem->addItem(QString());
        m_pcbxSelectItem->setObjectName(QString::fromUtf8("m_pcbxSelectItem"));

        horizontalLayout->addWidget(m_pcbxSelectItem);

        m_prbtnRect = new QRadioButton(widget);
        m_prbtnRect->setObjectName(QString::fromUtf8("m_prbtnRect"));

        horizontalLayout->addWidget(m_prbtnRect);

        m_prbtnLine = new QRadioButton(widget);
        m_prbtnLine->setObjectName(QString::fromUtf8("m_prbtnLine"));

        horizontalLayout->addWidget(m_prbtnLine);

        m_prbtnPoint = new QRadioButton(widget);
        m_prbtnPoint->setObjectName(QString::fromUtf8("m_prbtnPoint"));

        horizontalLayout->addWidget(m_prbtnPoint);

        m_ppbtnSelectImage = new QPushButton(widget);
        m_ppbtnSelectImage->setObjectName(QString::fromUtf8("m_ppbtnSelectImage"));

        horizontalLayout->addWidget(m_ppbtnSelectImage);

        m_ppbtnClear = new QPushButton(widget);
        m_ppbtnClear->setObjectName(QString::fromUtf8("m_ppbtnClear"));

        horizontalLayout->addWidget(m_ppbtnClear);

        m_ppbtnSaveImage = new QPushButton(widget);
        m_ppbtnSaveImage->setObjectName(QString::fromUtf8("m_ppbtnSaveImage"));

        horizontalLayout->addWidget(m_ppbtnSaveImage);


        verticalLayout->addWidget(widget);

        m_pImageVerticalLayout = new QVBoxLayout();
        m_pImageVerticalLayout->setObjectName(QString::fromUtf8("m_pImageVerticalLayout"));

        verticalLayout->addLayout(m_pImageVerticalLayout);

        m_pteShowLog = new QTextEdit(centralwidget);
        m_pteShowLog->setObjectName(QString::fromUtf8("m_pteShowLog"));
        m_pteShowLog->setMinimumSize(QSize(0, 100));
        m_pteShowLog->setMaximumSize(QSize(16777215, 100));

        verticalLayout->addWidget(m_pteShowLog);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1098, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(m_pactShowLog);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        m_pactShowLog->setText(QCoreApplication::translate("MainWindow", "showlog", nullptr));
        m_pcbxSelectItem->setItemText(0, QCoreApplication::translate("MainWindow", "Rect", nullptr));
        m_pcbxSelectItem->setItemText(1, QCoreApplication::translate("MainWindow", "Point", nullptr));
        m_pcbxSelectItem->setItemText(2, QCoreApplication::translate("MainWindow", "Line", nullptr));

        m_prbtnRect->setText(QCoreApplication::translate("MainWindow", "Rect", nullptr));
        m_prbtnLine->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        m_prbtnPoint->setText(QCoreApplication::translate("MainWindow", "Point", nullptr));
        m_ppbtnSelectImage->setText(QCoreApplication::translate("MainWindow", "select image", nullptr));
        m_ppbtnClear->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        m_ppbtnSaveImage->setText(QCoreApplication::translate("MainWindow", "savePic", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "view", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
