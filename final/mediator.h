#ifndef MEDIATOR_H
#define MEDIATOR_H

#include<iostream>
#include "heartwave.h"

using namespace std;

class Mediator
{
public:
    Mediator();
    void updateSettings(int, int);
private:
    HeartWave *hv;
};

#endif // MEDIATOR_H
