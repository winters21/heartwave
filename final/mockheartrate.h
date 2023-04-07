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

    QVector<int> getList();

private:
    QVector<int> heartRateList;
    int breath;
    bool increasing;
    int previous;
};

#endif // MOCKHEARTRATE_H
