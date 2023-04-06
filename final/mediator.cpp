#include "mediator.h"

Mediator::Mediator()
{
    hv = new HeartWave();  // TODO: might have parameters
}

void Mediator::updateSettings(int breathPacer, int challengeLevel) {
    cout << "Updating Breath Pacer to " << breathPacer << endl;
    cout << "Updating Challenge Level to " << challengeLevel << endl;
    // TODO: Once the HW is setup, change it's above values
}
