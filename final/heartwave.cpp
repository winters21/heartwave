#include "heartwave.h"
#include "mediator.h"

HeartWave::HeartWave(Mediator* mediator)
{
    this -> mediator = mediator;
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
