#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    sessionUnderway = false;
    ui->setupUi(this);
    mediator = new Mediator(this); // TODO: might have parameters
    createGraph();

    mockGen = new MockHeartRate();

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

    connect(ui -> okButton, SIGNAL(clicked()), SLOT(session()));

    connect(ui -> highButton, SIGNAL(clicked()), SLOT(activateHighCoherence()));
    connect(ui -> lowButton, SIGNAL(clicked()), SLOT(activateLowCoherence()));
    connect(ui -> mediumButton, SIGNAL(clicked()), SLOT(activateMediumCoherence()));

    timer -> start(2000);
    timer_heart_coherence -> start(64000);
    timer_heart_rate -> start(1000);
//    timer_achievement -> start(5000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::activateHighCoherence() {
    ui->mediumButton->setEnabled(false);
    ui->lowButton->setEnabled(false);


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

void MainWindow::session() {
    if (sessionUnderway) {
        cout << "Ending Session.." << endl;
        mediator -> getHeartWave() -> endSession();
        sessionUnderway = false;
    } else {
        cout << "Starting Session.." << endl;
        mediator -> getHeartWave() -> startSession();
        sessionUnderway = true;
    }
}

void MainWindow::createGraph() {
    // Create the graph and add labels
    ui -> customPlot -> addGraph();
    ui -> customPlot -> xAxis -> setLabel("Time");
    ui -> customPlot -> yAxis -> setLabel("HeartBeat");
    ui -> customPlot -> xAxis -> setRange(0, 200);
    ui -> customPlot -> yAxis -> setRange(50, 110);
}

void MainWindow::addData(int heartbeat, int time) {
    // TODO: Add the data to the graph in real time
    // heartbeat = y, time = x
    ui -> customPlot -> graph(0) -> addData(time, heartbeat);
    ui -> customPlot -> replot();
    ui -> customPlot -> update();
}

void MainWindow::clearGraph() {
    ui -> customPlot -> graph(0) -> data() -> clear();
}
