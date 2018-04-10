#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include <vector>
#include <initializer_list>
#include <memory>

class DeviceReporter;
class InventoryDevice;

class ReportManager {

    typedef std::vector<std::unique_ptr<InventoryDevice>> DEVICES_CONTAINER;

    DEVICES_CONTAINER * m_devices;

    // TODO: Maybe.
    std::vector<const DeviceReporter *> m_reporters;

public:
    ReportManager(DEVICES_CONTAINER & _devices);

    ReportManager(DEVICES_CONTAINER & _devices,
                  const std::vector<const DeviceReporter *> & _reporters);

    ReportManager(DEVICES_CONTAINER & _devices,
                  const std::initializer_list<const DeviceReporter *> & _reporters_list);

    void AddReporter(const DeviceReporter * _rep);

    enum class SortField {
        ID,
        DATE
    };
    enum class SortDirection {
        UNSORTED,
        ASCENDING,
        DESCENDING
    };

    void ReportTo(DeviceReporter * _reporter,
                  SortField _f = SortField::ID,
                  SortDirection _d = SortDirection::UNSORTED);

    // Invoke multiple reporters at a time
    //void MakeAllReports(SortField _f, SortDirection _d = SortDirection::ASCENDING);
};

#endif // REPORT_MANAGER_H
