#include <Arduino.h>
#ifndef DebugLogger_h
#define DebugLogger_h

class DebugLogger
{
    public:
        DebugLogger(char*);
        char* getType();
        bool getIsAllowedToLog();
        void startLogging();
        void stopLogging();
        void logText(char*);
        void logTextWithNewLine(char*);
    
    private:
        char* _type = nullptr;
        bool _isAllowedToLog;
};

#endif

