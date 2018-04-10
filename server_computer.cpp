//
// Created by ruslan on 3/23/17.
//

#include "server_computer.h"

const char * ServerComputer::descriptor{"ServerComputer"};

const std::regex ServerComputer::mac_address_regex {R"(^(\w{2}[:]){5}(\w{2})$)" };

ServerComputer::ServerComputer(const Computer & _comp, int _hdds, std::initializer_list<std::string> _macs)
		: Computer(_comp), hdd_replication(_hdds) {

    for (std::string macs_str: _macs) {
        if (std::regex_match(macs_str, mac_address_regex)) {
            mac_vector.push_back(macs_str);
        }
    }
}

ServerComputer::ServerComputer(const ServerComputer & _server)
    : Computer{_server}
    , hdd_replication{_server.hdd_replication}
    , mac_vector{_server.mac_vector}
{}

void ServerComputer::AddNetworkId(const std::string & macs_str) {
    if (std::regex_match(macs_str, mac_address_regex)) {
        mac_vector.push_back(macs_str);
    }
    else {
        std::string str = "Mac address '" + macs_str + "' format mismatch.";
        throw std::logic_error(str);
    }
}
