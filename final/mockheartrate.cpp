#include "mockheartrate.h"

MockHeartRate::MockHeartRate(HeartWave* hw)
{
    this->hw = hw;
    this->increasing = true;
    srand(time(NULL));
    this->previous = (rand() % 50) + 50;
}

void MockHeartRate::setMode(int mode) {
    this->mode = mode;
}

void MockHeartRate::generate() {
    switch(mode) {
        case 1:
            generateLow();
        break;

        case 2:
            generateMedium();
        break;

        default:
            generateHigh();
        break;
    }
    this->hw->readHR(this->heartRateList.last(), this->heartRateList.size());
}

void MockHeartRate::clearList() {
    this -> heartRateList.clear();
}

void MockHeartRate::generateLow() {
    int hr = 0;
    srand(time(NULL));
    int chance = (rand() % 4) + 1;

    if (increasing == true) {
        hr = previous + (rand() % 20);

        // Stop increasing when HR is greater than or equal to 100 BPM or chance is equal to 3
        // Gives this a one in 4 chance to stop
        if (hr >= 100 || (chance == 3)) {
            increasing = false;
        }
    } else {
        hr = previous - (rand() % 20);

        // Stop decreasing when HR is less than or equal to 50 BPM or chance is equal to 1
        // Gives this a one in 4 chance to stop
        if (hr <= 50 || (chance == 1)) {
            increasing = true;
        }
    }
    previous = hr;
    heartRateList.append(hr);
}

void MockHeartRate::generateMedium() {
    int hr = 0;
    srand(time(NULL));
    int chance = (rand() % 10) + 1;

    if (increasing == true) {
        hr = previous + (rand() % 7);

        // Stop increasing when HR is greater than or equal to 100 BPM or chance is equal to 7
        // Gives this a one in 10 chance to stop
        if (hr >= 100 || (chance == 7)) {
            increasing = false;
        }
    } else {
        hr = previous - (rand() % 7);

        // Stop decreasing when HR is less than or equal to 50 BPM or chance is equal to 3
        // Gives this a one in 10 chance to stop
        if (hr <= 50 || (chance == 3)) {
            increasing = true;
        }
    }
    previous = hr;
    heartRateList.append(hr);
}

void MockHeartRate::generateHigh() {
    int hr = 0;
    srand(time(NULL));
    int chance = (rand() % 20) + 1;

    if (increasing == true) {
        hr = previous + (rand() % 2);

        // Stop increasing when HR is greater than or equal to 100 BPM or chance is equal to 7
        // Gives this a one in 20 chance to stop
        if (hr >= 100 || (chance == 7)) {
            increasing = false;
        }
    } else {
        hr = previous - (rand() % 2);

        // Stop decreasing when HR is less than or equal to 50 BPM or chance is equal to 13
        // Gives this a one in 20 chance to stop
        if (hr <= 50 || (chance == 13)) {
            increasing = true;
        }
    }
    previous = hr;
    heartRateList.append(hr);
}

QVector<int> MockHeartRate::getList() { return this->heartRateList; }
