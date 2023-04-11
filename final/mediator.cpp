#include "mediator.h"
#include "mainwindow.h"

Mediator::Mediator(MainWindow* window)
{
    this -> window = window;
    hv = new HeartWave(this);  // TODO: might have parameters
}

void Mediator::updateSettings(int breathPacer, int challengeLevel) {
    cout << "Updating Breath Pacer to " << breathPacer << endl;
    cout << "Updating Challenge Level to " << challengeLevel << endl;
    this -> hv -> setBreathPacer(breathPacer);
}

void Mediator::updateUIElement(string element){
    if (element == "battery") {
        this -> window -> updateBattery(this -> hv -> getBattery());
    }
}

void Mediator::updateBattery() {
    this -> hv -> removeBattery();
}

void Mediator::addDataToGraph(int heartbeat, int time) {
    // Calls the addData method in MainWindow to add data to the graph
    this -> window -> addData(heartbeat, time);
}
