
#include "devicefactory.h"
#include "my_utility.h"

#include <exception>
#include <iostream>
#include <cstring>
#include <initializer_list>

const char DeviceFactory::delim[]{" =\","};

char DeviceFactory::oneline[DeviceFactory::MAXLINE] {};

int DeviceFactory::lineNumber{0};

const std::string DeviceFactory::exception1{"Wrong token or sequence"};

const std::map <const std::string, std::function< InventoryDevice *() >>
        DeviceFactory::_strategyManager
{
    {"COMPUTER", DeviceFactory::createComputer},
    {"EMBEDDED_GSM", DeviceFactory::createEmbeddedGSM},
    {"MOBILE_PHONE", DeviceFactory::createMobilePhone},
    {"SERVER_COMPUTER", DeviceFactory::createServerComputer},
};

const std::regex DeviceFactory::filename_regex { R"(^\w*[.](txt|ini|md)$)" };

std::ifstream DeviceFactory::fs {};

char * DeviceFactory::token {};


void DeviceFactory::NextLine() {
    fs.getline(oneline, MAXLINE);
    ++lineNumber;
    token = strtok(oneline, delim);
}

InventoryDevice * DeviceFactory::createComputer() {
    std::string temp_model;
    int temp_id, temp_ram;
    double temp_disk_memory;
    Date temp_date;

    NextLine();
    if (!strcmp(token, "inventory_id"))
        temp_id = atoi(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "registered"))
        temp_date = Date(strtok(NULL, delim), '/' );
    else
        throw std::logic_error{exception1};
    //std::cout << "Date: " << temp_date.ToString('/') << std::endl;

    NextLine();
    if (!strcmp(token, "cpu"))
        temp_model = strtok(NULL, delim);
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "ram"))
        temp_ram = atoi(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "hdd"))
        temp_disk_memory = atof(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    Computer * pComp = new Computer(temp_id, temp_model, temp_ram, temp_disk_memory, temp_date);

    return pComp;
}

InventoryDevice * DeviceFactory::createEmbeddedGSM() {
    int temp_id;
    Date temp_date;
    std::string temp_number;
    std::vector<int> temp_frequencies;
    double temp_clock;

    NextLine();
    if (!strcmp(token, "inventory_id"))
        temp_id = atoi(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "registered"))
        temp_date = Date(strtok(NULL, delim), '/' );
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "number"))
        temp_number = strtok(NULL, delim);
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "gsm_frequency"))
        while((token = strtok(NULL, delim)) != NULL)
            temp_frequencies.push_back(atoi(token));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "clock"))
        temp_clock = atof(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    EmbeddedGSM * pEmbGSM = new EmbeddedGSM(temp_id, temp_number, {}, temp_clock, temp_date);
    for (int x: temp_frequencies)
        pEmbGSM->SetFrequency(x);

    return pEmbGSM;
}

InventoryDevice * DeviceFactory::createMobilePhone() {
    int temp_id;
    Date temp_date;
    std::string temp_model, temp_number;
    int temp_ram;
    double temp_disk_memory;
    std::vector<int> temp_frequencies;

    NextLine();
    if (!strcmp(token, "inventory_id"))
        temp_id = atoi(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "registered"))
        temp_date = Date(strtok(NULL, delim), '/' );
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "cpu"))
        temp_model = strtok(NULL, delim);
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "ram"))
        temp_ram = atoi(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "hdd"))
        temp_disk_memory = atof(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "number"))
        temp_number = strtok(NULL, delim);
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "gsm_frequency"))
        while((token = strtok(NULL, delim)) != NULL)
            temp_frequencies.push_back(atoi(token));
    else
        throw std::logic_error{exception1};

    MobilePhone * pMobile = new MobilePhone(temp_id, temp_model, temp_ram,
                                            temp_disk_memory, "Unknown", "Unknown",
                                            temp_number, {}, temp_date);
    for (int x: temp_frequencies)
        pMobile->SetFrequency(x);
    return pMobile;
}

InventoryDevice * DeviceFactory::createServerComputer() {
    int temp_id;
    Date temp_date;
    int temp_ram, temp_hdd_replication;
    double temp_disk_memory;
    std::vector<std::string> temp_mac_vector;
    std::string temp_model;

    NextLine();
    if (!strcmp(token, "inventory_id"))
        temp_id = atoi(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "registered"))
        temp_date = Date(strtok(NULL, delim), '/' );
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "cpu"))
        temp_model = strtok(NULL, delim);
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "ram"))
        temp_ram = atoi(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "hdd"))
        temp_disk_memory = atof(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();
    if (!strcmp(token, "hpp_replication"))
        temp_hdd_replication = atoi(strtok(NULL, delim));
    else
        throw std::logic_error{exception1};

    NextLine();

    while (token != NULL) {
        if (!strcmp(token, "network_id"))
            temp_mac_vector.push_back(strtok(NULL, delim));
        NextLine();

    }


    ServerComputer *pServerComp = new ServerComputer(
                Computer(temp_id, temp_model, temp_ram,
                         temp_disk_memory, temp_date), temp_hdd_replication, {});
    for (std::string & x: temp_mac_vector)
        pServerComp->AddNetworkId(x);

    return pServerComp;
}


std::vector<std::unique_ptr<InventoryDevice>> DeviceFactory::Parse(const std::string & _filename) {

    if (std::regex_match(_filename, filename_regex))
        fs.open(_filename);
    else
        throw std::logic_error("Failed to open file: format is unacceptable!");

    //char oneline[MAXLINE];

    std::vector<std::unique_ptr<InventoryDevice>> temp_vec;
    std::string device_name_temp;
    try
    {
        while (!fs.eof()) {
            fs.getline(oneline, MAXLINE);
            ++lineNumber;
            std::string str{oneline};
            device_name_temp = MyUtility::Trim(str);
            //std::cout << device_name_temp << std::endl;

            auto func = _strategyManager.find(device_name_temp);
            if (func != _strategyManager.end())
                temp_vec.push_back(std::unique_ptr<InventoryDevice>(func->second()));
        }
    }
    catch (const std::logic_error & _e) {
        std::cout << "Caught an exception, while creating device: '"
                  << device_name_temp
                  << "'\nIn file: '" << _filename
                  << "' Line: " << lineNumber << "\nText: " << _e.what() << std::endl;
    }

    fs.close();
    return temp_vec;
}
