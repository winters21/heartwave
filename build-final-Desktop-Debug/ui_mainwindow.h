/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *powerButton;
    QPushButton *okButton;
    QLabel *breathPacerLabel;
    QSpinBox *breathPacer;
    QLabel *settingsLabel;
    QPushButton *setSettings;
    QSpinBox *challengeLevel;
    QLabel *challengeLevelLabel;
    QLabel *batteryLevel;
    QOpenGLWidget *deviceBackground;
    QGraphicsView *graphView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setGeometry(QRect(550, 290, 40, 40));
        upButton->setAutoFillBackground(false);
        upButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/upButton.svg);\n"
"background-color: #ffffff;\n"
"border-radius: 20px;\n"
"}"));
        downButton = new QPushButton(centralwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setGeometry(QRect(550, 390, 40, 40));
        downButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/downButton.svg);\n"
"background-color: #ffffff;\n"
"border-radius: 20px;\n"
"}"));
        leftButton = new QPushButton(centralwidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        leftButton->setGeometry(QRect(500, 340, 40, 40));
        leftButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/leftButton.svg);\n"
"background-color: #ffffff;\n"
"border-radius: 20px;\n"
"}"));
        rightButton = new QPushButton(centralwidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        rightButton->setGeometry(QRect(600, 340, 40, 40));
        rightButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/rightButton.svg);\n"
"background-color: #ffffff;\n"
"border-radius: 20px;\n"
"}"));
        powerButton = new QPushButton(centralwidget);
        powerButton->setObjectName(QString::fromUtf8("powerButton"));
        powerButton->setGeometry(QRect(550, 440, 40, 40));
        powerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/powerButton.svg);\n"
"background-color: #ffffff;\n"
"border-radius: 20px;\n"
"}"));
        okButton = new QPushButton(centralwidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(550, 340, 40, 40));
        okButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/okButton.svg);\n"
"background-color: #ffffff;\n"
"border-radius: 20px;\n"
"}"));
        breathPacerLabel = new QLabel(centralwidget);
        breathPacerLabel->setObjectName(QString::fromUtf8("breathPacerLabel"));
        breathPacerLabel->setGeometry(QRect(60, 70, 181, 31));
        breathPacer = new QSpinBox(centralwidget);
        breathPacer->setObjectName(QString::fromUtf8("breathPacer"));
        breathPacer->setGeometry(QRect(190, 70, 45, 26));
        breathPacer->setMinimum(1);
        breathPacer->setMaximum(30);
        settingsLabel = new QLabel(centralwidget);
        settingsLabel->setObjectName(QString::fromUtf8("settingsLabel"));
        settingsLabel->setGeometry(QRect(120, 30, 54, 17));
        setSettings = new QPushButton(centralwidget);
        setSettings->setObjectName(QString::fromUtf8("setSettings"));
        setSettings->setGeometry(QRect(100, 150, 80, 25));
        challengeLevel = new QSpinBox(centralwidget);
        challengeLevel->setObjectName(QString::fromUtf8("challengeLevel"));
        challengeLevel->setGeometry(QRect(190, 110, 45, 26));
        challengeLevel->setMinimum(1);
        challengeLevel->setMaximum(4);
        challengeLevelLabel = new QLabel(centralwidget);
        challengeLevelLabel->setObjectName(QString::fromUtf8("challengeLevelLabel"));
        challengeLevelLabel->setGeometry(QRect(60, 110, 181, 31));
        batteryLevel = new QLabel(centralwidget);
        batteryLevel->setObjectName(QString::fromUtf8("batteryLevel"));
        batteryLevel->setGeometry(QRect(680, 40, 54, 17));
        deviceBackground = new QOpenGLWidget(centralwidget);
        deviceBackground->setObjectName(QString::fromUtf8("deviceBackground"));
        deviceBackground->setGeometry(QRect(420, 29, 300, 471));
        graphView = new QGraphicsView(centralwidget);
        graphView->setObjectName(QString::fromUtf8("graphView"));
        graphView->setGeometry(QRect(440, 80, 261, 181));
        MainWindow->setCentralWidget(centralwidget);
        deviceBackground->raise();
        breathPacerLabel->raise();
        breathPacer->raise();
        settingsLabel->raise();
        setSettings->raise();
        challengeLevelLabel->raise();
        challengeLevel->raise();
        leftButton->raise();
        rightButton->raise();
        okButton->raise();
        upButton->raise();
        powerButton->raise();
        downButton->raise();
        batteryLevel->raise();
        graphView->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        upButton->setText(QString());
        downButton->setText(QString());
        leftButton->setText(QString());
        rightButton->setText(QString());
        powerButton->setText(QString());
        okButton->setText(QString());
        breathPacerLabel->setText(QApplication::translate("MainWindow", "Breath Pacer", nullptr));
        settingsLabel->setText(QApplication::translate("MainWindow", "Settings", nullptr));
        setSettings->setText(QApplication::translate("MainWindow", "Set Settings", nullptr));
        challengeLevelLabel->setText(QApplication::translate("MainWindow", "Challenge Level", nullptr));
        batteryLevel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">100%</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
