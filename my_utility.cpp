#include "my_utility.h"

#include <cstring>
#include <iostream>
#include <fstream>

const char * MyUtility::toLower(const char * str) {
    char * temp_str = strdup(str);
    char * p;
    for (p = temp_str; *p != '\0'; ++p)
        *p = (char)tolower(*p);
    return temp_str;
}

const std::string & MyUtility::Trim(std::string & s) {
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);
    p = s.find_last_not_of(": \t");
    if (std::string::npos != p)
        s.erase(p+1);
    return s;
}

void MyUtility::ReadFileToConsole(const char * _fileName) {
    const int MAXLINE = 256;
    char oneline[MAXLINE];
    std::ifstream fs(_fileName, std::ios::in);
    std::cout << "\nContents of file '" << _fileName << "':\n";
    while(!fs.eof()) {
        fs.getline(oneline, MAXLINE);
        std::cout << oneline << std::endl;
    }
}
