//
// Created by ruslan on 3/23/17.
//

#include "mobile_phone.h"
#include <iostream>

const char * MobilePhone::descriptor{"MobilePhone"};

MobilePhone::MobilePhone(
        int _id
    ,	const std::string & _model
	,   int _ram
	,   double _disk_memory
	,   const std::string & _manuf
	,   const std::string & _model_title
	,   const std::string & _number
	,   std::initializer_list<int> _lst
	,   const Date & _date
)
        :   Computer(_id, _model, _ram, _disk_memory, _date)
		,   GSMDevice(_number, _lst)
		,   manufacturer(_manuf)
		,   model_title(_model_title)
{}

MobilePhone::MobilePhone(const MobilePhone & _mobile)
    : Computer{_mobile}
    , GSMDevice{_mobile}
    , manufacturer{_mobile.manufacturer}
    , model_title{_mobile.model_title}
{}
