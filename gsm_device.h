
#ifndef LB_3_INVENTORYACCOUNTING_GSM_DEVICE_H
#define LB_3_INVENTORYACCOUNTING_GSM_DEVICE_H

#include <string>
#include <vector>
#include <stdexcept>
#include <functional>
#include <initializer_list>
#include <regex>

#define DEFAULT_FREQ 0b0001

class GSMDevice {



    const static std::regex phone_number_regex;

    mutable std::string account_number;
    char m_Frequency;
	mutable bool m_vectorUpToDate;
	mutable std::vector<int> m_vec;

	const static std::vector<int> Frequency_array;

	void PassThroughFrequencyArray(int _frec, std::function<void(int)> cmp);

public:

	void SetFrequency(int _frec);
	void DeleteFrequency(int _frec);

	const std::vector<int> & GetFrequencies() const;

	const std::string & GetAccountNumber() const;

    virtual ~GSMDevice() = 0;

protected:

    GSMDevice(const std::string & _number,
              std::initializer_list<int> _lst);

    GSMDevice(const GSMDevice & _gsm);

    std::string & NumberString();

};

inline const std::string & GSMDevice::GetAccountNumber() const { return account_number; }

inline GSMDevice::~GSMDevice() {}

inline std::string & GSMDevice::NumberString() { return account_number; }

#endif //LB_3_INVENTORYACCOUNTING_GSM_DEVICE_H
