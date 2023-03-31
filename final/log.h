#ifndef LOG_H
#define LOG_H

#include<vector>
#include<iostream>
#include<string>
#include<ctime>
#include<fstream>

using namespace std;

class Log
{
public:
    Log();
    void addToCurrentLogs(string);
    void addToSystemLog();
    void resetCurrentSession();
private:
    vector<string> currentSession;
};

#endif // LOG_H
