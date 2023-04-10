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

private slots:
    void update();
    void setSettings();
    void updateAchievementScore();
    void updateHeartCoherence();
    void updateSessionTime();
    void generateHeartRate();
    void session();
    void activateHighCoherence(QTimer*);
    void activateMediumCoherence(QTimer*);
    void activateLowCoherence(QTimer*);
    
private:
    Ui::MainWindow *ui;
    Mediator *mediator;
    MockHeartRate *mockGen;

    QTimer* timer;
    QTimer* timer_achievement;
    QTimer* timer_heart_coherence;
    QTimer* timer_session_time;
    QTimer* timer_heart_rate;
    QTimer* timer_coherence_calculate;

    bool sessionUnderway;
};
#endif // MAINWINDOW_H
