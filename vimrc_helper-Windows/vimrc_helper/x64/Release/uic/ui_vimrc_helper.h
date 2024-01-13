/********************************************************************************
** Form generated from reading UI file 'vimrc_helper.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIMRC_HELPER_H
#define UI_VIMRC_HELPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vimrc_helperClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *vimrc_helperClass)
    {
        if (vimrc_helperClass->objectName().isEmpty())
            vimrc_helperClass->setObjectName("vimrc_helperClass");
        vimrc_helperClass->resize(600, 400);
        menuBar = new QMenuBar(vimrc_helperClass);
        menuBar->setObjectName("menuBar");
        vimrc_helperClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(vimrc_helperClass);
        mainToolBar->setObjectName("mainToolBar");
        vimrc_helperClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(vimrc_helperClass);
        centralWidget->setObjectName("centralWidget");
        vimrc_helperClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(vimrc_helperClass);
        statusBar->setObjectName("statusBar");
        vimrc_helperClass->setStatusBar(statusBar);

        retranslateUi(vimrc_helperClass);

        QMetaObject::connectSlotsByName(vimrc_helperClass);
    } // setupUi

    void retranslateUi(QMainWindow *vimrc_helperClass)
    {
        vimrc_helperClass->setWindowTitle(QCoreApplication::translate("vimrc_helperClass", "vimrc_helper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vimrc_helperClass: public Ui_vimrc_helperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIMRC_HELPER_H
