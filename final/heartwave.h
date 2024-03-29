#ifndef HEARTWAVE_H
#define HEARTWAVE_H

#include <QMainWindow>
#include <iostream>
#include <deque>
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

    //Getters
    int getBattery();
    int GetAchievementScore() {return achievementScore;}
    int GetCounter() {return coherenceCount;}
    double GetLTime() {return low_time;}
    double GetMTime() {return med_time;}
    double GetHTime() {return high_time;}

    std::deque<int> GetHeartbeats() {return heartbeats;}

    double getSessionTime(){return session_time;}

    Lights* getLight() {return light;};
    Coherence* getCoherence() {return coherence;};
    Log* getLog() {return log;};
    int getBreathPacer(){return breathPacer;};

    //Setters
    void setBreathPacer(int pacer) { breathPacer = pacer; };
    void AddToAchievement(double s) { achievementScore += s;}
    void AddPointSecond(){session_time += 0.1;}
    void AddToCounter(){coherenceCount += 1;}
    void AddCoherenceTimer(int);

    void fixTimer(int);

    void ResetSessionTime(){session_time = 0.0;}
    void ResetCounters(){low_time = 0.0; med_time = 0.0; high_time = 0.0;}

    void readHR(int, int);

private:
    Mediator *mediator;
    Lights *light;
    Coherence *coherence;
    Log *log;

    float battery;
    double session_time = 0.0;

    double low_time = 0.0;
    double med_time = 0.0;
    double high_time = 0.0;

    std::deque<int> heartbeats;
    int breathPacer = 10;
    int challengeLevel;
    double achievementScore;
    int coherenceCount;

    string hrContact;
};

#endif // HEARTWAVE_H
