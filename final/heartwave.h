#ifndef HEARTWAVE_H
#define HEARTWAVE_H

#include <QMainWindow>
#include <iostream>
#include "lights.h"
#include "coherence.h"
#include "log.h"

class Mediator;
using namespace std;

class HeartWave
{
public:
    HeartWave(Mediator*);

    void removeBattery();
    void resetBattery();
    void startSession();
    void endSession();

    //Getters
    int getBattery();
    int GetAchievementScore() {return achievementScore;}
    Lights* getLight() {return light;};
    Coherence* getCoherence() {return coherence;};
    Log* getLog() {return log;};

    //Setters
    void AddToAchievement(int s) { achievementScore += s;}

private:
    Mediator *mediator;
    Lights *light;
    Coherence *coherence;
    Log *log;

    float battery = 100;
    int breathPacer = 10;
    int challengeLevel;
    int achievementScore;
    string hrContact;
};

#endif // HEARTWAVE_H
