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
    ui -> breathPacer -> setValue(this -> mediator -> getHeartWave() -> getBreathPacer());
    ui -> Summary -> setVisible(false);

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
    connect(ui -> applyToSkin, SIGNAL(activated(int)), SLOT(setAppliedToSkin()));
    connect(ui -> SummaryButton, SIGNAL(clicked()), SLOT(removeSummary()));

    powerOn = false;
    createGraph();
    ui -> summaryGraph -> addGraph();
    turnOff();
    appliedToSkin = true;

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

    int randomScore;
    int type;

    if(mockGen->getMode() == 1){
        type = 1;
        randomScore = (rand() % 6);
    } else if (mockGen->getMode() == 2){
        type = 2;
        randomScore = (rand() % 5) + 6;
    }else{
        type = 3;
        randomScore = (rand() % 5) + 12;
    }

    mediator->getHeartWave()->AddCoherenceTimer(type);

    mediator->getHeartWave()->getLog()->addToCurrentLogs("Heartrate = "+to_string(mockGen->getList().last()));
    mediator->getHeartWave()->getCoherence()->SetScore(randomScore);

    //If this is the first score determined, change the light depending on the first score.
    if (!getFirstScore()){
        firstCoherence = randomScore;
        mediator->getHeartWave()->AddToAchievement(randomScore);
        mediator->getHeartWave()->getLog()->addToCurrentLogs("(INITIAL) Achievement Score = "+to_string(mediator->getHeartWave()->GetAchievementScore()));

        updateHeartCoherence();
        firstScoreSet(true);
    }

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

    int score = mediator->getHeartWave()->getCoherence()->GetScore();
    std::cout << "Score: " << score << std::endl;
    mediator->getHeartWave()->AddToAchievement(score);
    mediator->getHeartWave()->AddToCounter();

    mediator->getHeartWave()->getLog()->addToCurrentLogs("Achievement Score = "+to_string(mediator->getHeartWave()->GetAchievementScore()));

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

void MainWindow::resetModeButtons() {
    ui -> highButton -> setEnabled(true);
    ui -> mediumButton -> setEnabled(true);
    ui -> lowButton -> setEnabled(true);
}

void MainWindow::session() {
    if (sessionUnderway) {
        mediator->getHeartWave()->getLog()->addToCurrentLogs("Session Ended");
        cout << "Ending Session.." << endl;

        //!/ Stop all timers
        timer_heart_coherence -> stop();
        timer_heart_rate -> stop();
        timer_achievement -> stop();
        timer_session_time -> stop();
        timer_breath -> stop();
        ui -> breath -> setVisible(false);
        ui -> session -> setVisible(false);

        createSummary();
        ui -> Summary -> setVisible(true);
        sessionUnderway = false;

        // Clear the graph at the end of a session
        // along with the data
        clearGraph();
        mockGen -> clearList();
        resetModeButtons();
    } else {
        mediator->getHeartWave()->getLog()->addToCurrentLogs("Session Started");
        cout << "Starting Session.." << endl;

        //!/ Start all timers
        timer_heart_coherence -> start(64000);  //Get heart coherence every 64 seconds
        timer_heart_rate -> start(1000);        //Get heartrate every second.
        timer_achievement -> start(5000);       //Get the coherence score every 5 seconds.
        timer_session_time -> start(100);       //Update the time every .1 second/
        ui -> breath -> setVisible(true);
        ui -> breath -> setText("Breathing In");  // Set the label to 'Breathing In' to begin the session
        ui -> breath -> setStyleSheet("QLabel { color : white; }");
        ui -> session -> setVisible(true);     //Set the session label to true so it shows when a session is underway
        ui -> session -> setStyleSheet("QLabel { color : white; }");
        int pacer = this -> mediator -> getHeartWave() -> getBreathPacer();  // Get the breath pacer from heartwave
        timer_breath -> start((pacer / 2) * 1000);    // Start the breath pacer timer
        sessionUnderway = true;
    }
}

void MainWindow::createGraph() {
    // Create the graph and add labels
    ui -> customPlot -> addGraph();
    ui -> customPlot -> xAxis -> setLabel("Time");
    ui -> customPlot -> yAxis -> setLabel("HeartBeat");
    ui -> customPlot -> xAxis -> setRange(0, 10);
    ui -> customPlot -> yAxis -> setRange(40, 130);

    // Sets the line color
    QColor color(0, 0, 255);
    ui -> customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    ui -> customPlot->graph()->setPen(QPen(color));
}

void MainWindow::addData(int heartbeat, int time) {
    // heartbeat = y, time = x
    cout << "X: " << time << endl;
    ui -> customPlot -> graph() -> addData(time, heartbeat);
    ui -> customPlot -> rescaleAxes(true);
    ui -> customPlot -> replot();
    ui -> customPlot -> update();
}

void MainWindow::clearGraph() {
    ui -> customPlot -> graph() -> clearData();
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
    ui -> session -> setVisible(false);
    this -> mediator -> getHeartWave() -> resetBattery();
    timer_battery -> stop();

    mockGen->clearList();
    clearGraph();
    resetModeButtons();
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
        mockGen->clearList();
        clearGraph();
        resetModeButtons();
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

void MainWindow::setAppliedToSkin() {
    if (ui -> applyToSkin -> currentText() == "Yes") {
        appliedToSkin = true;
    } else {
        appliedToSkin = false;
    }
}

void MainWindow::removeSummary() {
    ui -> summaryGraph -> graph() -> clearData();
    ui -> summaryGraph -> replot();
    ui -> summaryGraph -> update();
    ui -> Summary -> setVisible(false);
}

void MainWindow::createSummary() {
    // Session Length
    string str = "Session Length: " + to_string(mediator -> getHeartWave() -> getSessionTime()) + "s";
    QString length(str.c_str());
    ui -> SessionLength -> setText(length);
    mediator->getHeartWave()->getLog()->addToCurrentLogs("[SUMMARY] Session Length (s) = " + to_string(mediator -> getHeartWave() -> getSessionTime()));

    // Average Coherence
    cout << mediator -> getHeartWave() -> GetAchievementScore() << endl;
    cout << mediator -> getHeartWave() -> GetCounter() + 1 << endl;
    str = "Average Coherence: " + to_string((mediator -> getHeartWave() -> GetAchievementScore()) / (mediator -> getHeartWave() -> GetCounter() + 1));
    QString avg(str.c_str());
    ui -> AverageCoherence -> setText(avg);
    mediator->getHeartWave()->getLog()->addToCurrentLogs("[SUMMARY] Average Coherence = " + to_string((mediator -> getHeartWave() -> GetAchievementScore()) / (mediator -> getHeartWave() -> GetCounter() + 1)));


    // Achievement Score
    str = "Achievement Score: " + to_string(mediator -> getHeartWave() -> GetAchievementScore());
    QString as(str.c_str());
    ui -> AchievementScore -> setText(as);

    mediator->getHeartWave()->getLog()->addToCurrentLogs("[SUMMARY] Achievement Score = " + to_string(mediator -> getHeartWave() -> GetAchievementScore()));

    // Percentage Times
    std::cout << "LC : " << mediator->getHeartWave()->GetLTime() << std::endl;
    std::cout << "MC : " << mediator->getHeartWave()->GetMTime() << std::endl;
    std::cout << "HC : " << mediator->getHeartWave()->GetHTime() << std::endl;

    std::string lstr = "LC (%): " + to_string((double) (mediator->getHeartWave()->GetLTime() / (mediator->getHeartWave()->getSessionTime())));
    std::string mstr = "MC (%): " + to_string((double) (mediator->getHeartWave()->GetMTime() / (mediator->getHeartWave()->getSessionTime())));
    std::string hstr = "HC (%): " + to_string((double) (mediator->getHeartWave()->GetHTime() / (mediator->getHeartWave()->getSessionTime())));

    QString lc(lstr.c_str());
    QString mc(mstr.c_str());
    QString hc(hstr.c_str());
    ui -> lowCoherence -> setText(lc);
    ui -> mediumCoherence -> setText(mc);
    ui -> highCoherence -> setText(hc);

    mediator->getHeartWave()->getLog()->addToCurrentLogs("[SUMMARY] Low Coherence Time Percentage = " + to_string((double) (mediator->getHeartWave()->GetLTime() / (mediator->getHeartWave()->getSessionTime()))));
    mediator->getHeartWave()->getLog()->addToCurrentLogs("[SUMMARY] Medium Coherence Time Percentage = " + to_string((double) (mediator->getHeartWave()->GetMTime() / (mediator->getHeartWave()->getSessionTime()))));
    mediator->getHeartWave()->getLog()->addToCurrentLogs("[SUMMARY] High Coherence Time Percentage = " + to_string((double) (mediator->getHeartWave()->GetHTime() / (mediator->getHeartWave()->getSessionTime()))));

    mediator->getHeartWave()->getLog()->addToSystemLog();


    //Reset some attributes

    //Timers
    mediator->getHeartWave()->ResetCounters();
    mediator->getHeartWave()->ResetSessionTime();

    //Lights
    ui->coherenceLightRed->setStyleSheet(QString::fromStdString("background-color: rgb(191, 64, 64)"));
    ui->coherenceLightBlue->setStyleSheet(QString::fromStdString("background-color: rgb(32, 74, 135)"));
    ui->coherenceLightGreen->setStyleSheet(QString::fromStdString("background-color: rgb(78, 154, 6)"));

    // Copy the graph to the summary
    copyGraph();
}

void MainWindow::copyGraph() {
    ui -> summaryGraph -> xAxis -> setLabel("Time");
    ui -> summaryGraph -> yAxis -> setLabel("HeartBeat");
    ui -> summaryGraph -> xAxis -> setRange(ui -> customPlot -> xAxis -> range());
    ui -> summaryGraph -> yAxis -> setRange(ui -> customPlot -> yAxis -> range());
    ui -> summaryGraph -> graph() -> addData(*(ui -> customPlot -> graph() -> data()));
    ui -> summaryGraph -> replot();
    ui -> summaryGraph -> update();
}
