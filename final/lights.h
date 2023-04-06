#ifndef LIGHTS_H
#define LIGHTS_H


class Lights
{
public:
    Lights();
    Lights(bool, bool, int);

    bool getLightOn();
    bool getPowerOn();
    int getCoherenceLight();

    void setLightOn(bool);
    void setPowerOn(bool);
    void setCoherenceLight(int);

    void turnOnPacer();
    void setColor(int);

private:
    bool lightOn;
    bool powerOn;
    int coherenceLight;
};

#endif // LIGHTS_H
