#include "device_reporter.h"

DeviceReporter::DeviceReporter(const std::string & _fileName)
    : FileName{_fileName}{
    outputFile = new std::ofstream();
}

DeviceReporter::~DeviceReporter() {
    delete outputFile;
}
