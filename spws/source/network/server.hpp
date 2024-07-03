#ifndef SPWS_NET_SERVER_HPP
#define SPWS_NET_SERVER_HPP

#include <boost/asio.hpp>

namespace spws {
    namespace network {
        class server {
        public:
            server(boost::asio::io_service& service, ushort port);

        public:
            void accept();
        private:
            int error_handler(boost::system::error_code error);
            void accept_handler(const boost::system::error_code& error, boost::asio::ip::tcp::socket& socket);

        private:
            boost::asio::io_service& service;
            boost::asio::ip::tcp::acceptor acceptor;
        };
    }
}

#endif //SPWS_NET_SERVER_HPP
