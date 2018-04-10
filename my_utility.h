#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <string>

class MyUtility {
public:
    static const char * toLower(const char * str);
    static const std::string & Trim(std::string & s);
    static void ReadFileToConsole(const char * _fileName);
};

#endif // MY_UTILITY_H
