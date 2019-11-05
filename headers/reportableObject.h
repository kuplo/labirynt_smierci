#pragma once
#include<string>
#include<iostream>
class reportableObject {
protected:
    enum logType { INFO, WARNING, ERROR, UNKNOWN };
    void log(logType ltype, std::string ltext);
};