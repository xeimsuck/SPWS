#include "application.hpp"
#include <iostream>
#include "config/parser.hpp"

using namespace spws;
using namespace spws::config;

application *application::init() {
    static application app;
    return &app;
}

application::application() {
    std::string buffer;
    if(update("/usr/local/etc/spws/spws.conf", buffer)){
        throw std::runtime_error(buffer);
    }
    runServers();
}

void application::runServers() {
    for(decltype(auto) server : servers) server.accept();
}

int application::update(const std::string &path, std::string& errorBuffer) {
    try {
        updateConfig(path);
    } catch (std::exception& error){
        errorBuffer = error.what();
        return 1;
    }
    return 0;
}

void application::updateConfig(const std::string &path) {
    auto body = parser::parse(path);

    typeof(servers) tempServers;
    for(decltype(auto) serverConfig : body.servers){
        tempServers.emplace_back(service, serverConfig.port);
    }
    servers = std::move(tempServers);
}


int application::exec() {
    std::cout << "EXEC\n";
    service.run();
    return 0;
}