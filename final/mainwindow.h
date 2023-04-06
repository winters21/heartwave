#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mediator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void update();
    void updateAchievementScore();
    void updateHeartCoherence();
    void setSettings();
private:
    Ui::MainWindow *ui;
    Mediator *mediator;
};
#endif // MAINWINDOW_H
