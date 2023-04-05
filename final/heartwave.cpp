#include "heartwave.h"
#include "mediator.h"

HeartWave::HeartWave(Mediator* mediator)
{
    this -> mediator = mediator;
}

void HeartWave::removeBattery() {
    this -> battery -= 1.5;
    this -> mediator -> updateUIElement("battery");
}

int HeartWave::getBattery() {
    return battery;
}
