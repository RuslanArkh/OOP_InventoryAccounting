
#include "computer.h"

const char * Computer::descriptor{"Computer"};

Computer::Computer(int _id,
                   const std::string & _model,
                   int _ram_Mb,
                   double _disk_memory_Gb,
                   const Date & _date)
        : InventoryDevice(_id, _date),
          processor_model{_model},
          RAM_MB{_ram_Mb},
          HDD_GB{_disk_memory_Gb}
{}

Computer::Computer(const Computer & _comp)
        : InventoryDevice(_comp._inventory_id, _comp._registered),
		  processor_model(_comp.processor_model),
          RAM_MB(_comp.RAM_MB),
          HDD_GB(_comp.HDD_GB)
{}
