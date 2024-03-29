#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mediator.h"
#include "mockheartrate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateBattery(float);
    void createGraph();
    void addData(int, int);
    void clearGraph();
    void powerOffBattery();
    void resetModeButtons();
    void createSummary();
    void copyGraph();
    void reloadMenu();

    bool getFirstScore(){return firstScore;}
    bool firstScoreSet(bool s){firstScore = s;}

private slots:
    void update();
    void setSettings();
    void updateAchievementScore();
    void updateHeartCoherence();
    void updateSessionTime();
    void generateHeartRate();
    void session();
    void activateHighCoherence();
    void activateMediumCoherence();
    void activateLowCoherence();
    void power();
    void chargeBattery();
    void updateBreathLabel();
    void setAppliedToSkin();
    void removeSummary();

    void goDownMenu();
    void goUpMenu();
    
private:
    Ui::MainWindow *ui;
    Mediator *mediator;
    MockHeartRate *mockGen;

    QTimer* timer_battery;
    QTimer* timer_achievement;
    QTimer* timer_heart_coherence;
    QTimer* timer_session_time;
    QTimer* timer_heart_rate;
    QTimer* timer_coherence_calculate;
    QTimer* timer_breath;

    bool sessionUnderway;
    bool powerOn;
    bool firstScore = false;
    bool appliedToSkin;
    int firstCoherence;

    // Methods
    void turnOn();
    void turnOff();
};
#endif // MAINWINDOW_H
