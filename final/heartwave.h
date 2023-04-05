#ifndef HEARTWAVE_H
#define HEARTWAVE_H

#include <QMainWindow>
#include <iostream>

class Mediator;
using namespace std;

class HeartWave
{
public:
    HeartWave(Mediator*);

    void removeBattery();
    void resetBattery();
    int getBattery();
private:
    Mediator *mediator;
    float battery = 100;
    int breathPacer = 10;
    int challengeLevel;
    int achievementScore;
    string hrContact;
};

#endif // HEARTWAVE_H
