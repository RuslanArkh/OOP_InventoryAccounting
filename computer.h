
#ifndef LB_3_INVENTORYACCOUNTING_COMPUTER_H
#define LB_3_INVENTORYACCOUNTING_COMPUTER_H

#include <string>

#include "inventory_device.h"

class Computer : public InventoryDevice {

	const std::string processor_model;
    const int RAM_MB;
    const double HDD_GB;

    static const char * descriptor;

public:

	Computer() = delete;

    Computer(int _id, const std::string & _model, int _ram, double _disk_memory, const Date & _date = Date());

	Computer(const Computer & _comp);

	const std::string & GetProcessorModel() const;

	int GetRAM() const;

	double GetDiskMemory() const;

    void DumpToReporter(DeviceReporter & _r) const override;

    const char * type() const override;

    std::unique_ptr<InventoryDevice> clone() const override;
};

inline const std::string & Computer::GetProcessorModel() const { return processor_model; }

inline int Computer::GetRAM() const { return RAM_MB; }

inline double Computer::GetDiskMemory() const { return HDD_GB; }

inline void Computer::DumpToReporter(DeviceReporter & _r) const { _r.add_device(this); }

inline const char * Computer::type() const { return Computer::descriptor; }

inline std::unique_ptr<InventoryDevice> Computer::clone() const {
    return std::unique_ptr<InventoryDevice>(new Computer(*this));
}

#endif //LB_3_INVENTORYACCOUNTING_COMPUTER_H
