#ifndef HEARTWAVE_H
#define HEARTWAVE_H

#include <QMainWindow>
#include "lights.h"
#include "coherence.h"
#include "log.h"

class HeartWave
{
public:
    HeartWave();
    Lights* getLight() {return light;};
    Coherence* getCoherence() {return coherence;};
    Log* getLog() {return log;};
private:
    Lights *light;
    Coherence *coherence;
    Log *log;
};

#endif // HEARTWAVE_H
