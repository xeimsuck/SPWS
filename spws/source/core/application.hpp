#ifndef SPWS_CORE_APPLICATION_HPP
#define SPWS_CORE_APPLICATION_HPP

#include <boost/asio.hpp>
#include "network/server.hpp"

namespace spws {
    class application {
    public:
        application(const application &copy) = delete;
        application &operator=(const application &copy) = delete;

        static application *init();
    private:
        application();
        ~application() = default;

    public:
        void runServers();
        int update(const std::string& path, std::string& errorBuffer);
        int exec();
    private:
        void updateConfig(const std::string& path);

    private:
        boost::asio::io_service service;
        std::vector<network::server> servers;
    };
}

#endif //SPWS_CORE_APPLICATION_HPP
