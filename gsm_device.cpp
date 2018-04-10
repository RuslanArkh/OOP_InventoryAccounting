//
// Created by ruslan on 3/23/17.
//

#include "gsm_device.h"

const std::regex GSMDevice::phone_number_regex {R"(^([+]38)?0(\d{9})$)" };

#include <sstream>
#include <algorithm>
#include <iostream>

const std::vector<int> GSMDevice::Frequency_array  = { 450, 900, 1800, 1900 };

GSMDevice::GSMDevice(const std::string &_number, std::initializer_list<int> _lst)
        : account_number(_number), m_Frequency(0) {
    try {
        if (_lst.size() > 0)
            for (int f: _lst)
                SetFrequency(f);
	} catch (const std::runtime_error & _e) {
		throw _e;
    }
    if (!std::regex_match(_number, phone_number_regex)) {
        throw std::logic_error("Failed to create GSMDevice: Wrong phone format.");
    }
}

GSMDevice::GSMDevice(const GSMDevice &_gsm)
    : account_number{_gsm.account_number}
    , m_Frequency{_gsm.m_Frequency}
{}

void GSMDevice::PassThroughFrequencyArray(int _frec, std::function<void(int)> func) {
	for (int i = 0; i < 4; ++i) {
		if (_frec == Frequency_array[i]) {
            func(i);
			m_vectorUpToDate = false;
			return;
		}
	}
	std::ostringstream stream;
	stream << "Frequency " << _frec << " is not allowed by standard.";
    //  C++11 :
	throw std::runtime_error(stream.str());
}

void GSMDevice::SetFrequency(int _frec) {
	try {
		PassThroughFrequencyArray(_frec, [this](int i) noexcept {
			m_Frequency |= 1 << i;
		});
	} catch (const std::runtime_error & _e) {
		throw _e;
	}
}

void GSMDevice::DeleteFrequency(int _frec)  {
	PassThroughFrequencyArray(_frec, [this](int i) noexcept {
		m_Frequency &= ~(1 << i);
	});
}

const std::vector<int> & GSMDevice::GetFrequencies() const  {
	if (! m_vectorUpToDate) {
		m_vec.clear();
		for (int i = 0; i < 4; ++i)
			if (m_Frequency & (1 << i))
				m_vec.push_back(Frequency_array[i]);
		m_vectorUpToDate = true;
	}
	return m_vec;
}

