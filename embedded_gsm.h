
#ifndef LB_3_INVENTORYACCOUNTING_EMBEDDED_GSM_H
#define LB_3_INVENTORYACCOUNTING_EMBEDDED_GSM_H

#include "gsm_device.h"
#include "inventory_device.h"

class EmbeddedGSM : public InventoryDevice, public GSMDevice {

    static const char * descriptor;

	const double clock_frequency;

public:

    //EmbeddedGSM(const GSMDevice & _gsm, double _clock_freq);
    EmbeddedGSM(
                int _id,
                //  GSM: number of account
                const std::string & _number,
                //  GSM: list of supported frequencies
                std::initializer_list<int> _lst,
                double _clock_freq,
                const Date & _date = Date());

    EmbeddedGSM(const EmbeddedGSM & _comp);

	double GetClockFrequency() const;

    void DumpToReporter(DeviceReporter & _r) const override;

    const char * type() const override;

    std::unique_ptr<InventoryDevice> clone() const override;

};

inline double EmbeddedGSM::GetClockFrequency() const { return clock_frequency; }

inline void EmbeddedGSM::DumpToReporter(DeviceReporter & _r) const { _r.add_device(this); }

inline const char * EmbeddedGSM::type() const { return EmbeddedGSM::descriptor; }

inline std::unique_ptr<InventoryDevice> EmbeddedGSM::clone() const {
    return std::unique_ptr<InventoryDevice>(new EmbeddedGSM(*this));
}

#endif //LB_3_INVENTORYACCOUNTING_EMBEDDED_GSM_H
