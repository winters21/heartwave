#include "lights.h"

Lights::Lights()
{
    lightOn = false;
    powerOn = false;
    coherenceLight = 0;
}

Lights::Lights(bool light, bool power, int coh) {
    lightOn = light;
    powerOn = power;
    coherenceLight = coh;
}

bool Lights::getLightOn() {
    return lightOn;
}

bool Lights::getPowerOn() {
    return powerOn;
}

int Lights::getCoherenceLight() {
    return coherenceLight;
}

void Lights::setLightOn(bool light) {
    lightOn = light;
}

void Lights::setPowerOn(bool power) {
    powerOn = power;
}

void Lights::setCoherenceLight(int c) {
    coherenceLight = c;
}

void Lights::turnOnPacer() {
    powerOn = true;
}

// TODO
void Lights::setColor(int color) {

}
