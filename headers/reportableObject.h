#pragma once
#include<string>
#include<iostream>
#include <fstream>

class reportableObject {
    static reportableObject* logObj;
    static std::ofstream logFile;
    static std::string logName;
protected:
    std::string objectName;
public:
    enum logType { INFO, WARNING, ERROR, UNKNOWN };
    void log(logType ltype, std::string ltext);
    ~reportableObject();
};