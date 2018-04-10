
#ifndef LB_3_INVENTORYACCOUNTING_MOBILEPHONE_H
#define LB_3_INVENTORYACCOUNTING_MOBILEPHONE_H

#include "gsm_device.h"
#include "computer.h"


class MobilePhone
		: public Computer, public GSMDevice {

    static const char * descriptor;

	const std::string manufacturer, model_title;

public:

    MobilePhone(int _id
            , const std::string & _model
	        , int _ram
            //  Free HDD memory
			, double _disk_memory
			, const std::string & _manuf
			, const std::string & _model_title
            // GSM: number of account
            , const std::string & _number
            //  GSM: list of supported frequencies
            , std::initializer_list<int> _lst
			, const Date & _date = Date()
            );
    MobilePhone(const MobilePhone & _mobile);

	const std::string & GetManufacturerTitle() const;
	const std::string & GetModelTitle() const;

    void DumpToReporter(DeviceReporter & _r) const override;

    const char * type() const override;

    std::unique_ptr<InventoryDevice> clone() const override;
};

inline const std::string & MobilePhone::GetManufacturerTitle() const { return manufacturer; }

inline const std::string & MobilePhone::GetModelTitle() const { return model_title; }

inline void MobilePhone::DumpToReporter(DeviceReporter & _r) const {
    _r.add_device(this);
}

inline const char * MobilePhone::type() const { return MobilePhone::descriptor; }

inline std::unique_ptr<InventoryDevice> MobilePhone::clone() const {
    return std::unique_ptr<InventoryDevice>(new MobilePhone(*this));
}

#endif //LB_3_INVENTORYACCOUNTING_MOBILEPHONE_H
