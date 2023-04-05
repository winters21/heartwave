#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mediator = new Mediator(); // TODO: might have parameters

    // Connect the set settings button for the settings tab
    connect(ui -> setSettings, SIGNAL(clicked()), this, SLOT(setSettings()));

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(update()));
    timer -> start(2000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update() {
    std::cout << "Updating..." << std::endl;
    // this -> device -> batterylvl -= 1;
}

void MainWindow::setSettings() {
    std::cout << "Updating settings..." << std::endl;
    mediator -> updateSettings(ui -> breathPacer -> value(), ui -> challengeLevel -> value());
}

