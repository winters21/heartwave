#include "heartwave.h"
#include "mediator.h"

HeartWave::HeartWave(Mediator* mediator)
{
    this -> mediator = mediator;
    this -> coherenceCount = 0;
    this -> battery = 100;

    this -> coherence = new Coherence();
    this -> log = new Log();
    this -> light = new Lights();

    this -> achievementScore = 0.0;
}

void HeartWave::removeBattery() {
    this -> battery -= 0.7;
    this -> mediator -> updateUIElement("battery");
}

int HeartWave::getBattery() {
    return battery;
}

void HeartWave::resetBattery() {
    this -> battery = 100;
    this -> mediator -> updateUIElement("battery");
}

void HeartWave::AddCoherenceTimer(int type){
    if (type == 1){
        low_time += 1.0;
    } else if (type == 2) {
        med_time += 1.0;
    } else {
        high_time += 1.0;
    }
}

void HeartWave::readHR(int hr, int time) {
    this -> mediator ->addDataToGraph(hr, time);
}
