
#ifndef INVENTORY_DEVICE_H
#define INVENTORY_DEVICE_H
#include <memory>
#include "date.h"
#include "device_reporter.h"

class InventoryDevice {


protected:

	int _inventory_id;

	Date _registered;

    InventoryDevice(int _id, const Date & _date = Date()) : _inventory_id(_id), _registered(_date) {}

public:

    virtual ~InventoryDevice() = 0;

	int GetId() const;

    const char * GetDateStr() const;

    const Date & GetDate() const;

    virtual void DumpToReporter(DeviceReporter & _r) const = 0;

    virtual const char * type() const = 0;

    virtual std::unique_ptr<InventoryDevice> clone() const = 0;
};

inline int InventoryDevice::GetId() const { return _inventory_id; }

inline const char * InventoryDevice::GetDateStr() const {
	return _registered.ToString('/');
}

inline const Date & InventoryDevice::GetDate() const {
    return _registered;
}

inline InventoryDevice::~InventoryDevice() {}

#endif
