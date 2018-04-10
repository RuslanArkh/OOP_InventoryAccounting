
#ifndef LB_3_INVENTORYACCOUNTING_SERVER_COMPUTER_H
#define LB_3_INVENTORYACCOUNTING_SERVER_COMPUTER_H

#include <vector>
#include <regex>
#include <initializer_list>
#include <string>
#include "computer.h"


class ServerComputer
		: public Computer {

    static const char * descriptor;

	const int hdd_replication;

    const static std::regex mac_address_regex;
	const static int mac_address_length;

    std::vector<std::string> mac_vector;

public:

    ServerComputer(const Computer & _comp, int _hdds, std::initializer_list<std::string> _macs);

    ServerComputer(const ServerComputer & _server);

    int GetHDDReplication() const;

    int GetMacAddressLength() const;

    void AddNetworkId(const std::string & _id);

    void DumpToReporter(DeviceReporter & _r) const override;

    const std::vector<std::string> & GetIds() const;

    const char * type() const override;

    std::unique_ptr<InventoryDevice> clone() const override;

};

inline int ServerComputer::GetHDDReplication() const { return hdd_replication; }

inline int ServerComputer::GetMacAddressLength() const { return mac_address_length; }

inline void ServerComputer::DumpToReporter(DeviceReporter & _r) const { _r.add_device(this); }

inline const std::vector<std::string> & ServerComputer::GetIds() const { return mac_vector; }

inline const char * ServerComputer::type() const { return ServerComputer::descriptor; }

inline std::unique_ptr<InventoryDevice> ServerComputer::clone() const {
    return std::unique_ptr<InventoryDevice>(new ServerComputer(*this));
}

#endif //LB_3_INVENTORYACCOUNTING_SERVER_COMPUTER_H
