#include "report_manager.h"

#include "computer.h"
#include "embedded_gsm.h"
#include "mobile_phone.h"
#include "server_computer.h"
#include "date.h"

#include <memory>
#include <algorithm>

ReportManager::ReportManager(DEVICES_CONTAINER &_devices)
    : m_devices{&_devices} {}

ReportManager::ReportManager(DEVICES_CONTAINER &_devices,
                             const std::initializer_list<const DeviceReporter *> &_reporters_list)
    : m_devices{&_devices} {
    for (const DeviceReporter * rep: _reporters_list)
        m_reporters.push_back(rep);
}


ReportManager::ReportManager(DEVICES_CONTAINER &_devices,
                             const std::vector<const DeviceReporter *> &_reporters)
    : m_devices{&_devices}, m_reporters{_reporters} {}

void ReportManager::AddReporter(const DeviceReporter * _rep) {
    m_reporters.push_back(_rep);
}


void ReportManager::ReportTo(DeviceReporter * _reporter,
              SortField _f,
              SortDirection _d) {
    if (_d == SortDirection::UNSORTED) {
        for (std::unique_ptr<InventoryDevice> & d: *m_devices)
            d->DumpToReporter(*_reporter);
    } else {
        std::vector<std::unique_ptr<InventoryDevice>> devices_copy;
        for (std::unique_ptr<InventoryDevice> & device: *m_devices)
            devices_copy.push_back(std::unique_ptr<InventoryDevice>{device->clone()});
        if (_f == SortField::ID) {
            std::sort(devices_copy.begin(), devices_copy.end(),
                      [_d]
                      (std::unique_ptr<InventoryDevice> & _dev1,
                       std::unique_ptr<InventoryDevice> & _dev2){
                return (_d == SortDirection::ASCENDING ?
                            (_dev1->GetId() < _dev2->GetId())
                          : (_dev1->GetId() > _dev2->GetId()));
            });
        } else {
            std::sort(devices_copy.begin(), devices_copy.end(),
                      [_d]
                      (std::unique_ptr<InventoryDevice> & _dev1,
                       std::unique_ptr<InventoryDevice> & _dev2){
                return (_d == SortDirection::ASCENDING ?
                            (_dev1->GetDate() < _dev2->GetDate())
                          : (_dev1->GetDate() > _dev2->GetDate()));
            });
        }
        for (std::unique_ptr<InventoryDevice> & d: devices_copy)
            d->DumpToReporter(*_reporter);
    }
    _reporter->MakeReport();
}
