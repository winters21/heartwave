#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <iostream>
#include "heartwave.h"
#include "QString"

class MainWindow;
using namespace std;

class Mediator
{
public:
    Mediator(MainWindow*);

    void updateSettings(int);
    void updateUIElement(string);
    void updateBattery();

    void addDataToGraph(int, int);

    //Getter
    HeartWave* getHeartWave() {return hv;}

private:
    HeartWave *hv;
    MainWindow *window;
};

#endif // MEDIATOR_H
