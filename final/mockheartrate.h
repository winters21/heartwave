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
    MockHeartRate(int breath);

    void generate();

    void setMode(int);

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
