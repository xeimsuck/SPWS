#include "body.hpp"
#include <iostream>
#include <fstream>
#include <format>

using namespace spws::config;

// BASE
std::string body::printInfo() {
    std::string info = std::format(
            "SERVERS COUNT: {}", servers.size());
    return info;
}

void body::addServer(body::server server) {
    servers.push_back(server);
}
const std::vector<body::server> &body::getServers() const noexcept {
    return servers;
}

// SERVER
body::server::server(unsigned short port) : port(port){
}
short body::server::getPort() const noexcept {
    return port;
}
void body::server::setPort(short p) noexcept {
    this->port = p;
}

