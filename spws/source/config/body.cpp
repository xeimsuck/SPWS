#include "body.hpp"
#include <iostream>
#include <fstream>
#include <format>

using namespace spws::config;

// BASE
void body::addServer(body::server server) {
    servers.push_back(server);
}
const std::vector<body::server> &body::getServers() const noexcept {
    return servers;
}

// SERVER
body::server::server(unsigned short _port, protocols _protocol) :
            port(_port), protocol(_protocol){
}
ushort body::server::getPort() const noexcept {
    return port;
}
void body::server::setPort(ushort p) noexcept {
    this->port = p;
}

protocols body::server::getProtocol() const noexcept {
    return protocol;
}
void body::server::setProtocol(spws::config::protocols _protocol) noexcept {
    protocol = _protocol;
}

