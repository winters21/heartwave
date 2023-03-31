#include "log.h"

Log::Log(){}

/**
 * @brief Log::addToSystemLog
 * This method adds the logs to a txt file at the end of a session, it then resets the sessions logs
 */
void Log::addToSystemLog() {
    ofstream file("../Session.txt");  // TODO: add unique id depending if the files get overridden

    // Loop through the vector and add the logs to the output file
    for (string log: currentSession) {
        file << log;
    }

    file.close();
    resetCurrentSession();
}

/**
 * @brief Log::addToCurrentLogs
 * @param log
 * Adds a timestamp to the log and adds it to the current sessions logs
 */
void Log::addToCurrentLogs(string log) {
    time_t t = time(0);
    string currTime = ctime(&t);

    // Remove the \n character from the current time so the log does not appear on a new line
    if (!currTime.empty()) {
        if (currTime[currTime.length() - 1] == '\n')
            currTime.erase(currTime.length() - 1);
    }

    string fullLog = currTime + " -- " + log;
    cout << fullLog << endl;
    currentSession.push_back(fullLog);
}

/**
 * @brief Log::resetCurrentSession
 * Resets the current sessiin logs to make room for a new sessions logs
 */
void Log::resetCurrentSession() {
    currentSession.clear();
}
