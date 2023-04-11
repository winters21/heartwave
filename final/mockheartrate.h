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

    // Generates a heart rate based on the mode given
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

    // Clears the list - this will be used in the event of a new session,
    // and when the user decides to try a different coherence mode
    void clearList();

    QVector<int> getList();

private:
    QVector<int> heartRateList;
    bool increasing;
    int previous;
    int mode;
};

#endif // MOCKHEARTRATE_H
