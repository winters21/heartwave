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

    mockGen = new MockHeartRate(this->mediator->getHeartWave());

    // Connect the set settings button for the settings tab
    connect(ui -> setSettings, SIGNAL(clicked()), this, SLOT(setSettings()));

    timer_battery = new QTimer();
    timer_achievement = new QTimer();
    timer_heart_coherence = new QTimer();
    timer_heart_rate = new QTimer();
    timer_session_time = new QTimer();
    timer_breath = new QTimer();

    connect(timer_battery, SIGNAL(timeout()), SLOT(update()));
    connect(timer_achievement, SIGNAL(timeout()), SLOT(updateAchievementScore()));
    connect(timer_heart_coherence, SIGNAL(timeout()), SLOT(updateHeartCoherence()));
    connect(timer_heart_rate, SIGNAL(timeout()), SLOT(generateHeartRate()));
    connect(timer_session_time, SIGNAL(timeout()), SLOT(updateSessionTime()));
    connect(timer_breath, SIGNAL(timeout()), SLOT(updateBreathLabel()));

    connect(ui -> okButton, SIGNAL(clicked()), SLOT(session()));

    connect(ui -> highButton, SIGNAL(clicked()), SLOT(activateHighCoherence()));
    connect(ui -> lowButton, SIGNAL(clicked()), SLOT(activateLowCoherence()));
    connect(ui -> mediumButton, SIGNAL(clicked()), SLOT(activateMediumCoherence()));

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

void MainWindow::activateHighCoherence() {
    ui->mediumButton->setEnabled(false);
    ui->lowButton->setEnabled(false);

    mockGen -> setMode(3);
}

void MainWindow::activateMediumCoherence() {
    ui->highButton->setEnabled(false);
    ui->lowButton->setEnabled(false);

    mockGen -> setMode(2);
}

void MainWindow::activateLowCoherence() {
    ui->mediumButton->setEnabled(false);
    ui->highButton->setEnabled(false);

    mockGen -> setMode(1);
}

void MainWindow::generateHeartRate() {

    mockGen->generate();

    double randomScore;
    if(mockGen->getMode() == 1){
        randomScore = ((double) rand() / RAND_MAX) * 0.5;
    } else if (mockGen->getMode() == 2){
        randomScore = (((double) rand() / RAND_MAX) * 0.5) + 0.5;
    }else{
        randomScore = (((double) rand() / RAND_MAX) * 4.1) + 1.0;
    }

    mediator->getHeartWave()->getCoherence()->SetScore(randomScore);
}

void MainWindow::update() {
    this -> mediator-> updateBattery();
}

void MainWindow::setSettings() {
    std::cout << "Updating settings..." << std::endl;
    mediator -> updateSettings(ui -> breathPacer -> value());
}

void MainWindow::updateBattery(float batt) {
    if (batt <= 0) {
        powerOffBattery();
    }
    ui -> batteryLevel -> setNum(batt);
    ui -> batteryLevel -> setStyleSheet("QLabel { color : white; }");
}

void MainWindow::updateAchievementScore() {
    std::cout << "Updating Achievement Score..." << std::endl;

    double score = mediator->getHeartWave()->getCoherence()->GetScore();
    std::cout << "Score: " << score << std::endl;
    mediator->getHeartWave()->AddToAchievement(score);
}

void MainWindow::updateHeartCoherence() {
    std::cout << "Updating Heart Coherence..." << std::endl;
    double score = mediator->getHeartWave()->getCoherence()->GetScore();
    int color;

    if (score >= 0.0 && score <= 0.5){
        //RED
        color = 0;

        //Light up Red Light
        ui->coherenceLightRed->setStyleSheet(QString::fromStdString("background-color: rgb(239, 41, 41)"));
        ui->coherenceLightBlue->setStyleSheet(QString::fromStdString("background-color: rgb(32, 74, 135)"));
        ui->coherenceLightGreen->setStyleSheet(QString::fromStdString("background-color: rgb(78, 154, 6)"));
    }
    if (score >= 0.6 && score <= 1.0){
        //BLUE
        color = 1;

        //Light up Blue Light
        ui->coherenceLightRed->setStyleSheet(QString::fromStdString("background-color: rgb(191, 64, 64)"));
        ui->coherenceLightBlue->setStyleSheet(QString::fromStdString("background-color: rgb(114, 159, 207)"));
        ui->coherenceLightGreen->setStyleSheet(QString::fromStdString("background-color: rgb(78, 154, 6)"));
    }
    if (score >= 1.1 && score <= 5.1){
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
        timer_breath -> stop();
        ui -> breath -> setVisible(false);

        mediator -> getHeartWave() -> endSession();
        sessionUnderway = false;
    } else {
        cout << "Starting Session.." << endl;

        //!/ Start all timers
        timer_heart_coherence -> start(64000);  //Get heart coherence every 64 seconds
        timer_heart_rate -> start(1000);        //Get heartrate every second.
        timer_achievement -> start(5000);       //Get the coherence score every 5 seconds.
        timer_session_time -> start(100);       //Update the time every .1 second/
        ui -> breath -> setVisible(true);
        ui -> breath -> setText("Breathing In");  // Set the label to 'Breathing In' to begin the session
        ui -> breath -> setStyleSheet("QLabel { color : white; }");
        int pacer = this -> mediator -> getHeartWave() -> getBreathPacer();  // Get the breath pacer from heartwave
        timer_breath -> start((pacer / 2) * 1000);    // Start the breath pacer timer

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
    ui -> customPlot -> replot();
    ui -> customPlot -> update();
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
    ui -> breath -> setVisible(false);
    this -> mediator -> getHeartWave() -> resetBattery();
    timer_battery -> stop();
}

void MainWindow::chargeBattery() {
    this -> mediator -> getHeartWave() -> resetBattery();

    // If we charge the battery from being dead we want to restore the power button
    if (!timer_battery -> isActive()) {
        ui -> powerButton -> setEnabled(true);
        connect(ui -> powerButton, SIGNAL(clicked()), SLOT(power()));
    }
}

void MainWindow::updateBreathLabel() {
    if (ui -> breath -> text() == "Breathing In") {
        ui -> breath -> setText("Breathing Out");
    } else {
        ui -> breath -> setText("Breathing In");
    }
    ui -> breath -> setStyleSheet("QLabel { color : white; }");
}

void MainWindow::powerOffBattery() {
    // This method gets called when the battery reaches 0
    if (sessionUnderway) {
        cout << "Session is underway while battery died stopping and reseting.." << endl;
        //!/ Stop all timers and reset the graph
        timer_heart_coherence -> stop();
        timer_heart_rate -> stop();
        timer_achievement -> stop();
        timer_session_time -> stop();
        timer_breath -> stop();
        sessionUnderway = false;
        clearGraph();
    }
    // Disable all the UI features until battery is recharged
    ui -> customPlot -> setVisible(false);
    ui -> upButton -> setEnabled(false);
    ui -> downButton -> setEnabled(false);
    ui -> leftButton -> setEnabled(false);
    ui -> rightButton -> setEnabled(false);
    ui -> okButton -> setEnabled(false);
    ui -> powerButton -> setEnabled(false);
    ui -> batteryLevel -> setVisible(false);
    ui -> breath -> setVisible(false);
    timer_battery -> stop();
}
