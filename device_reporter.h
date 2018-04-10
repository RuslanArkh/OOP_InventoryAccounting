#ifndef DEVICE_REPRESENTER_H
#define DEVICE_REPRESENTER_H

#include <fstream>
#include <string>
class Computer;
class EmbeddedGSM;
class MobilePhone;
class ServerComputer;

class DeviceReporter {

public:

    virtual void add_device(const Computer * _d) = 0;
    virtual void add_device(const EmbeddedGSM * _d) = 0;
    virtual void add_device(const MobilePhone * _d) = 0;
    virtual void add_device(const ServerComputer * _d) = 0;

    virtual void MakeReport() = 0;

    DeviceReporter(const std::string & _fileName);

protected:

    std::ofstream * outputFile;

    const std::string FileName;

    virtual ~DeviceReporter();
};

#endif // DEVICE_REPRESENTER_H
