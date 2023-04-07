#include "mockheartrate.h"

MockHeartRate::MockHeartRate(int breath)
{
    this->breath = breath;
    this->increasing = true;
    srand(time(NULL));
    this->previous = (rand() % 50) + 50;
}

void MockHeartRate::generate() {
    int hr = 0;
    srand(time(NULL));
    int chance = (rand() % 10) + 1;

    if (increasing == true) {
        hr = previous + 1;

        // Stop increasing when HR is greater than or equal to 100 BPM or chance is equal to 4
        // Gives this a one in 5 chance to stop
        if (hr >= 100 || (chance == 7)) {
            increasing = false;
        }
    } else {
        hr = previous - 1;

        // Stop decreasing when HR is less than or equal to 50 BPM or chance is equal to 4
        // Gives this a one in 5 chance to stop
        if (hr <= 50 || (chance == 3)) {
            increasing = true;
        }
    }
    previous = hr;
    heartRateList.append(hr);
}

QVector<int> MockHeartRate::getList() { return this->heartRateList; }
