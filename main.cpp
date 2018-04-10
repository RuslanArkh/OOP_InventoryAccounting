
#include <memory>
#include <string>
#include <cstring>
#include <fstream>
#include <regex>
#include <exception>
#include <iostream>

#include "computer.h"
#include "gsm_device.h"
#include "embedded_gsm.h"
#include "mobile_phone.h"
#include "server_computer.h"
#include "date.h"

#include "devicefactory.h"
#include "html_device_reporter.h"
#include "report_manager.h"

#include "my_utility.h"

int main(int argc, char *argv[]) {

    //  Device factory test
    try {

        std::vector<std::unique_ptr<InventoryDevice>> devices =
                DeviceFactory::Parse("hardware_inventory.txt");

        HTMLDeviceReporter * reporter2 = new HTMLDeviceReporter{"report_sorted_by_date.html"};

        ReportManager manager{devices};
        manager.ReportTo(reporter2,
                         ReportManager::SortField::DATE,
                         ReportManager::SortDirection::DESCENDING);
        delete reporter2;
    }
    catch (const std::logic_error & _e) {
        std::cout << "Caught an exception: " << _e.what() << std::endl;
    }

}
