
#include "embedded_gsm.h"

const char * EmbeddedGSM::descriptor{"EmbeddedGSM"};

EmbeddedGSM::EmbeddedGSM(int _id,
                         const std::string &_number,
                         std::initializer_list<int> _lst,
                         double _clock_freq,
                         const Date & _date)
        : InventoryDevice(_id, _date),
          GSMDevice(_number, _lst),
		  clock_frequency(_clock_freq)
{
}

EmbeddedGSM::EmbeddedGSM(const EmbeddedGSM & _comp)
    : InventoryDevice(_comp._inventory_id, _comp._registered),
      GSMDevice{_comp},
      clock_frequency(_comp.clock_frequency)
{}
