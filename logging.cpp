#include <iostream>
#include <fstream>

#include <stdio.h>

#include "logging.h"

using namespace std;

DataFlowException::DataFlowException(const char *type, const char *error) {
    sprintf(msg, "Throwing Exception: (%s): %s", type, error);
    Logger::LogEvent(msg);
}

void Logger::LogEvent(const char *event) {
    fstream logger;
    if(logger.is_open()) {
        logger << event << endl;
        logger.close();
    }
    else {
        logger.open("logfile.txt", fstream::app);
        logger << event << endl;
        logger.close();
    }
}

void Logger::Finalize() {
    //logger.close();
}