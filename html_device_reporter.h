#ifndef HTML_DEVICE_REPRESENTER_H
#define HTML_DEVICE_REPRESENTER_H

#include "inventory_device.h"
#include "gsm_device.h"
#include "device_reporter.h"
#include <fstream>
#include <string>
#include <vector>
#include <memory>

class HTMLDeviceReporter : public DeviceReporter {

    static const std::string _header;

    static const std::string _footer;

    std::ostringstream _content;

    std::string defaultDeviceData(const InventoryDevice * _d, int indent) const;
    std::string GSMData(const GSMDevice * _d, int indent) const ;

public:

    void add_device(const Computer * _d) override;
    void add_device(const EmbeddedGSM * _d) override;
    void add_device(const MobilePhone * _d) override;
    void add_device(const ServerComputer * _d) override;

    HTMLDeviceReporter(const std::string & _fileName);

    ~HTMLDeviceReporter();

    void MakeReport() override;
};

#endif // HTML_DEVICE_REPRESENTER_H
