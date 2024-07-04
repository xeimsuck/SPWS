#ifndef SPWS_NET_SERVER_HPP
#define SPWS_NET_SERVER_HPP

#include <boost/asio.hpp>
#include <vector>
#include <utility>

namespace spws {
    namespace network {
        class server {
        public:
            server(boost::asio::io_service& service,
                   ushort port,
                   const std::unordered_map<std::string, std::string>& targets);

        public:
            void accept();
        private:
            int error_handler(boost::system::error_code error);
            void accept_handler(const boost::system::error_code& error, boost::asio::ip::tcp::socket& socket);

        private:
            boost::asio::io_service& service;
            boost::asio::ip::tcp::acceptor acceptor;

            std::unordered_map<std::string, std::string> targets;
        };
    }
}

#endif //SPWS_NET_SERVER_HPP
