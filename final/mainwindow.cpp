#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mediator = new Mediator(this); // TODO: might have parameters

    mockGen = new MockHeartRate(1);

    // Connect the set settings button for the settings tab
    connect(ui -> setSettings, SIGNAL(clicked()), this, SLOT(setSettings()));

    QTimer* timer = new QTimer();
    QTimer* timer_achievement = new QTimer();
    QTimer* timer_heart_coherence = new QTimer();
    QTimer* timer_heart_rate = new QTimer();

    connect(timer, SIGNAL(timeout()), SLOT(update()));
    connect(timer_achievement, SIGNAL(timeout()), SLOT(updateAchievementScore()));
    connect(timer_heart_coherence, SIGNAL(timeout()), SLOT(updateHeartCoherence()));
    connect(timer_heart_rate, SIGNAL(timeout()), SLOT(generateHeartRate()));

    timer -> start(2000);
    timer_heart_coherence -> start(64000);
    timer_heart_rate -> start(1000);
//    timer_achievement -> start(5000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateHeartRate() {
    mockGen->generate();
    std::cout << mockGen->getList().last() << endl;
}

void MainWindow::update() {
    this -> mediator-> updateBattery();
}

void MainWindow::setSettings() {
    std::cout << "Updating settings..." << std::endl;
    mediator -> updateSettings(ui -> breathPacer -> value(), ui -> challengeLevel -> value());
}

void MainWindow::updateBattery(float batt) {
    ui -> batteryLevel -> setNum(batt);
    ui -> batteryLevel -> setStyleSheet("QLabel { color : white; }");
}

void MainWindow::updateAchievementScore() {
    std::cout << "Updating Achievement Score..." << std::endl;

    // TODO Need to actually have a Coherence class in HeartWave.
    int score = mediator->getHeartWave()->getCoherence()->GetScore();
    mediator->getHeartWave()->AddToAchievement(score);

}

void MainWindow::updateHeartCoherence() {
    std::cout << "Updating Heart Coherence..." << std::endl;
    int score = mediator->getHeartWave()->getCoherence()->GetScore();
    int color;
    if (score >= 0 && score <= 5){
        //RED
        color = 0;
    }
    if (score >= 6 && score <= 11){
        //BLUE
        color = 1;
    }
    if (score >= 12 && score <= 16){
        //GREEN
        color = 2;
    }

    mediator->getHeartWave()->getLight()->setColor(color);
}
