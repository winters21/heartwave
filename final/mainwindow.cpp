#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

