#include "./../headers/reportableObject.h"

void reportableObject::log(logType ltype, std::string ltext) {
    if (logObj == NULL) {
        logObj = this;
        logFile.open(logName);
    }

    switch (ltype)
    {
    case reportableObject::INFO:
        logFile << "INFO ";
        break;
    case reportableObject::WARNING:
        logFile << "WARNING ";
        break;
    case reportableObject::ERROR:
        logFile << "ERROR ";
        break;
    default:
        logFile << "UNKNOWN ";
        break;
    }

    logFile << objectName <<": "<< ltext << std::endl;
}

 reportableObject* reportableObject::logObj=NULL;
 std::string reportableObject::logName = "log.txt";
 std::ofstream reportableObject::logFile;
 
 reportableObject::~reportableObject() {
     if (logObj == this) {
         logFile.close();
     }
 }
