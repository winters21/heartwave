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
    mediator = new Mediator(this);

    mockGen = new MockHeartRate();

    // Connect the set settings button for the settings tab
    connect(ui -> setSettings, SIGNAL(clicked()), this, SLOT(setSettings()));

    timer_battery = new QTimer();
    timer_achievement = new QTimer();
    timer_heart_coherence = new QTimer();
    timer_heart_rate = new QTimer();
    timer_session_time = new QTimer();

    connect(timer_battery, SIGNAL(timeout()), SLOT(update()));
    connect(timer_achievement, SIGNAL(timeout()), SLOT(updateAchievementScore()));
    connect(timer_heart_coherence, SIGNAL(timeout()), SLOT(updateHeartCoherence()));
    connect(timer_heart_rate, SIGNAL(timeout()), SLOT(generateHeartRate()));
    connect(timer_session_time, SIGNAL(timeout()), SLOT(updateSessionTime()));

    connect(ui -> okButton, SIGNAL(clicked()), SLOT(session()));

    connect(ui -> highButton, SIGNAL(clicked()), SLOT(activateHighCoherence(timer_heart_rate)));
    connect(ui -> lowButton, SIGNAL(clicked()), SLOT(activateLowCoherence(timer_heart_rate)));
    connect(ui -> mediumButton, SIGNAL(clicked()), SLOT(activateMediumCoherence(timer_heart_rate)));

    connect(ui -> powerButton, SIGNAL(clicked()), SLOT(power()));
    connect(ui -> chargeBattery, SIGNAL(clicked()), SLOT(chargeBattery()));

    powerOn = false;
    createGraph();
    turnOff();

    timer_heart_coherence -> start(64000);
//    timer_achievement -> start(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::activateHighCoherence(QTimer* timer) {
    ui->mediumButton->setEnabled(false);
    ui->lowButton->setEnabled(false);

    mockGen -> setMode(3);

    timer -> start(1000);
}

void MainWindow::activateMediumCoherence(QTimer* timer) {
    ui->highButton->setEnabled(false);
    ui->lowButton->setEnabled(false);

    mockGen -> setMode(2);

    timer -> start(1000);
}

void MainWindow::activateLowCoherence(QTimer* timer) {
    ui->mediumButton->setEnabled(false);
    ui->highButton->setEnabled(false);

    mockGen -> setMode(1);

    timer -> start(1000);
}

void MainWindow::generateHeartRate() {

    mockGen->generate();
    mediator->getHeartWave()->GetHeartbeats().push_back(mockGen->getList().last());

    //Current 64 seconds of heart beat rhythm.
    if (mediator->getHeartWave()->GetHeartbeats().size() > 64){
        mediator->getHeartWave()->GetHeartbeats().pop_front();
    }

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
    std::deque<int> heartbeats = mediator->getHeartWave()->GetHeartbeats();
    mediator->getHeartWave()->AddToCounter();

    //Get Coherence Score from a 0-16 scale.
    int min = 50;
    int max = 100;
    double avg = 0.0;

    for (int i = 0; i < heartbeats.size(); ++i){
        if (heartbeats[i] < min) {min = heartbeats[i];}
        if (heartbeats[i] > max) {max = heartbeats[i];}
        avg+=heartbeats[i];
    }

    avg = avg/heartbeats.size();
    double scaled_avg = ((avg - min) / (max - min)) * 16.0;

    mediator->getHeartWave()->getCoherence()->SetScore(scaled_avg);

    int score = mediator->getHeartWave()->getCoherence()->GetScore();
    std::cout << "Score: " << score << std::endl;
    mediator->getHeartWave()->AddToAchievement(score);
}

void MainWindow::updateHeartCoherence() {
    std::cout << "Updating Heart Coherence..." << std::endl;
    int score = mediator->getHeartWave()->getCoherence()->GetScore();
    int color;

    if (score >= 0 && score <= 5){
        //RED
        color = 0;

        //Light up Red Light
        ui->coherenceLightRed->setStyleSheet(QString::fromStdString("background-color: rgb(239, 41, 41)"));
        ui->coherenceLightBlue->setStyleSheet(QString::fromStdString("background-color: rgb(32, 74, 135)"));
        ui->coherenceLightGreen->setStyleSheet(QString::fromStdString("background-color: rgb(78, 154, 6)"));
    }
    if (score >= 6 && score <= 11){
        //BLUE
        color = 1;

        //Light up Blue Light
        ui->coherenceLightRed->setStyleSheet(QString::fromStdString("background-color: rgb(191, 64, 64)"));
        ui->coherenceLightBlue->setStyleSheet(QString::fromStdString("background-color: rgb(114, 159, 207)"));
        ui->coherenceLightGreen->setStyleSheet(QString::fromStdString("background-color: rgb(78, 154, 6)"));
    }
    if (score >= 12 && score <= 16){
        //GREEN
        color = 2;

        //Light up Green Light
        ui->coherenceLightRed->setStyleSheet(QString::fromStdString("background-color: rgb(191, 64, 64)"));
        ui->coherenceLightBlue->setStyleSheet(QString::fromStdString("background-color: rgb(32, 74, 135)"));
        ui->coherenceLightGreen->setStyleSheet(QString::fromStdString("background-color: rgb(138, 226, 52)"));
    }
    mediator->getHeartWave()->getLight()->setColor(color);

}

void MainWindow::updateSessionTime() {
    mediator->getHeartWave()->AddPointSecond();
    // TODO, update the session time with mediator->getHeartWave()->getSessionTime();
}

void MainWindow::session() {
    if (sessionUnderway) {
        cout << "Ending Session.." << endl;

        //!/ Stop all timers
        timer_heart_coherence -> stop();
        timer_heart_rate -> stop();
        timer_achievement -> stop();
        timer_session_time -> stop();

        mediator -> getHeartWave() -> endSession();
        sessionUnderway = false;
    } else {
        cout << "Starting Session.." << endl;

        //!/ Start all timers
        timer_heart_coherence -> start(64000);  //Get heart coherence every 64 seconds
        timer_heart_rate -> start(1000);        //Get heartrate every second.
        timer_achievement -> start(5000);       //Get the coherence score every 5 seconds.
        timer_session_time -> start(100);       //Update the time every .1 second/

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

void MainWindow::power() {
    if (powerOn) {
        turnOff();
        powerOn = false;
    } else {
        turnOn();
        powerOn = true;
    }
}

void MainWindow::turnOn() {
    ui -> customPlot -> setVisible(true);
    ui -> upButton -> setEnabled(true);
    ui -> downButton -> setEnabled(true);
    ui -> leftButton -> setEnabled(true);
    ui -> rightButton -> setEnabled(true);
    ui -> okButton -> setEnabled(true);
    ui -> batteryLevel -> setVisible(true);

    // Start the battery QTimer
    timer_battery -> start(2000);
}

void MainWindow::turnOff() {
    // Hide all of the UI stuff (graph, buttons, etc) until the user turns the device on
    ui -> customPlot -> setVisible(false);
    ui -> upButton -> setEnabled(false);
    ui -> downButton -> setEnabled(false);
    ui -> leftButton -> setEnabled(false);
    ui -> rightButton -> setEnabled(false);
    ui -> okButton -> setEnabled(false);
    ui -> batteryLevel -> setVisible(false);
    this -> mediator -> getHeartWave() -> resetBattery();
    timer_battery -> stop();
}

void MainWindow::chargeBattery() {
    this -> mediator -> getHeartWave() -> resetBattery();
}
