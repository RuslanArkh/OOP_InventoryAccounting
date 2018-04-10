#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "mobile_phone.h"
#include "server_computer.h"
#include "computer.h"
#include "embedded_gsm.h"

#include <string>
#include <map>
#include <functional>
#include <fstream>
#include <regex>
#include <vector>
#include <memory>

//  Reads file and creates objects according to device types.
//  Key feature of this design is string-to-function map objects,
//  which helps to avoid big switch-case statement.
//  A little modification of Strategy design pattern.
// TODO: Ask a question:
//  Is above class and its responsibilities being as a Factory and a File Reader
//  at the same time is good design decision?
//  Does it look like something like Strategy pattern?
//  Are there some better design decisions for this case?
class DeviceFactory {

    static InventoryDevice * createComputer();
    static InventoryDevice * createEmbeddedGSM();
    static InventoryDevice * createMobilePhone();
    static InventoryDevice * createServerComputer();

    static const std::map<const std::string, std::function< InventoryDevice *() >> _strategyManager;

    static std::ifstream fs;

    static void NextLine();


    //  specify acceptable file formats
    const static std::regex filename_regex;

    static const char delim[];
    static const int MAXLINE = 256;
    static char oneline[MAXLINE];
    static char * token;
    static int lineNumber;

    static const std::string exception1;

public:

    static std::vector<std::unique_ptr<InventoryDevice>> Parse(const std::string & _filename);
};

#endif // FILEPARSER_H
