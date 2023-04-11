#include "heartwave.h"
#include "mediator.h"

HeartWave::HeartWave(Mediator* mediator)
{
    this -> mediator = mediator;
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

void HeartWave::startSession() {

}

void HeartWave::endSession() {

}

void HeartWave::readHR(int hr, int time) {
    this -> mediator ->addDataToGraph(hr, time);
}
