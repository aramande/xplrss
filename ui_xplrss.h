/********************************************************************************
** Form generated from reading UI file 'xplrss.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPLRSS_H
#define UI_XPLRSS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XplRSS
{
public:
    QAction *actionOptions;
    QAction *actionAdd_Feed;
    QAction *actionAbout;
    QAction *actionDate_Ascending;
    QAction *actionDate_Descending;
    QAction *actionRead_Ascending;
    QAction *actionRead_Descending;
    QAction *actionQuit;
    QAction *actionAdd_Branch;
    QAction *actionReload;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QMenuBar *menuBar;
    QMenu *menuTools;
    QMenu *menuSort_Date;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *XplRSS)
    {
        if (XplRSS->objectName().isEmpty())
            XplRSS->setObjectName(QStringLiteral("XplRSS"));
        XplRSS->resize(600, 400);
        actionOptions = new QAction(XplRSS);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/32/settings"), QSize(), QIcon::Normal, QIcon::Off);
        actionOptions->setIcon(icon);
        actionAdd_Feed = new QAction(XplRSS);
        actionAdd_Feed->setObjectName(QStringLiteral("actionAdd_Feed"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/32/add"), QSize(), QIcon::Normal, QIcon::On);
        actionAdd_Feed->setIcon(icon1);
        actionAbout = new QAction(XplRSS);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionDate_Ascending = new QAction(XplRSS);
        actionDate_Ascending->setObjectName(QStringLiteral("actionDate_Ascending"));
        actionDate_Descending = new QAction(XplRSS);
        actionDate_Descending->setObjectName(QStringLiteral("actionDate_Descending"));
        actionRead_Ascending = new QAction(XplRSS);
        actionRead_Ascending->setObjectName(QStringLiteral("actionRead_Ascending"));
        actionRead_Descending = new QAction(XplRSS);
        actionRead_Descending->setObjectName(QStringLiteral("actionRead_Descending"));
        actionQuit = new QAction(XplRSS);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionAdd_Branch = new QAction(XplRSS);
        actionAdd_Branch->setObjectName(QStringLiteral("actionAdd_Branch"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/32/branch"), QSize(), QIcon::Normal, QIcon::On);
        actionAdd_Branch->setIcon(icon2);
        actionReload = new QAction(XplRSS);
        actionReload->setObjectName(QStringLiteral("actionReload"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/32/refresh"), QSize(), QIcon::Normal, QIcon::On);
        actionReload->setIcon(icon3);
        centralWidget = new QWidget(XplRSS);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(splitter);

        XplRSS->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(XplRSS);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuSort_Date = new QMenu(menuTools);
        menuSort_Date->setObjectName(QStringLiteral("menuSort_Date"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        XplRSS->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XplRSS);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        XplRSS->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(XplRSS);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        XplRSS->setStatusBar(statusBar);

        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuTools->addAction(actionAdd_Feed);
        menuTools->addAction(actionAdd_Branch);
        menuTools->addAction(actionReload);
        menuTools->addAction(actionOptions);
        menuTools->addAction(menuSort_Date->menuAction());
        menuTools->addAction(actionQuit);
        menuSort_Date->addAction(actionDate_Descending);
        menuSort_Date->addAction(actionDate_Ascending);
        menuSort_Date->addAction(actionRead_Descending);
        menuSort_Date->addAction(actionRead_Ascending);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionAdd_Feed);
        mainToolBar->addAction(actionAdd_Branch);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionReload);
        mainToolBar->addAction(actionOptions);

        retranslateUi(XplRSS);

        QMetaObject::connectSlotsByName(XplRSS);
    } // setupUi

    void retranslateUi(QMainWindow *XplRSS)
    {
        XplRSS->setWindowTitle(QApplication::translate("XplRSS", "XplRSS", 0));
        actionOptions->setText(QApplication::translate("XplRSS", "Options", 0));
        actionAdd_Feed->setText(QApplication::translate("XplRSS", "Add Feed", 0));
        actionAbout->setText(QApplication::translate("XplRSS", "About", 0));
        actionDate_Ascending->setText(QApplication::translate("XplRSS", "Date Ascending", 0));
#ifndef QT_NO_TOOLTIP
        actionDate_Ascending->setToolTip(QApplication::translate("XplRSS", "Sort by Date Ascending", 0));
#endif // QT_NO_TOOLTIP
        actionDate_Descending->setText(QApplication::translate("XplRSS", "Date Descending", 0));
#ifndef QT_NO_TOOLTIP
        actionDate_Descending->setToolTip(QApplication::translate("XplRSS", "Sort by Date Descending", 0));
#endif // QT_NO_TOOLTIP
        actionRead_Ascending->setText(QApplication::translate("XplRSS", "Read Ascending", 0));
#ifndef QT_NO_TOOLTIP
        actionRead_Ascending->setToolTip(QApplication::translate("XplRSS", "Sort by Read Ascending", 0));
#endif // QT_NO_TOOLTIP
        actionRead_Descending->setText(QApplication::translate("XplRSS", "Read Descending", 0));
#ifndef QT_NO_TOOLTIP
        actionRead_Descending->setToolTip(QApplication::translate("XplRSS", "Sort by Read Descending", 0));
#endif // QT_NO_TOOLTIP
        actionQuit->setText(QApplication::translate("XplRSS", "Quit", 0));
        actionAdd_Branch->setText(QApplication::translate("XplRSS", "Add Branch", 0));
        actionReload->setText(QApplication::translate("XplRSS", "Reload", 0));
        menuTools->setTitle(QApplication::translate("XplRSS", "Tools", 0));
        menuSort_Date->setTitle(QApplication::translate("XplRSS", "Sort", 0));
        menuHelp->setTitle(QApplication::translate("XplRSS", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class XplRSS: public Ui_XplRSS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPLRSS_H
