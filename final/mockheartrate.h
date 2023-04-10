#ifndef MOCKHEARTRATE_H
#define MOCKHEARTRATE_H

#include "QtGlobal"
#include "QVector"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "cmath"

using namespace std;
class MockHeartRate
{
public:
    MockHeartRate();

    void generate();

    // Setters
    void setMode(int);
    void setBreath(int);

    // Generate heart rate for high coherence
    void generateHigh();

    // Generate heart rate for medium coherence
    void generateMedium();

    // Generate heart rate for low coherence
    void generateLow();

    QVector<int> getList();

private:
    QVector<int> heartRateList;
    int breath;
    bool increasing;
    int previous;
    int mode;
};

#endif // MOCKHEARTRATE_H
