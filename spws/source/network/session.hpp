#ifndef SPWS_NET_SESSION_HPP
#define SPWS_NET_SESSION_HPP

#include <memory>
#include <boost/asio.hpp>

namespace spws {
    namespace network {
        class session : public std::enable_shared_from_this<session> {
        public:
            explicit session(boost::asio::ip::tcp::socket &&socket);

        public:
            void run();
        private:
            void listen();
            void request(std::size_t size);
            int error_handler(boost::system::error_code error);
        private:
            boost::asio::ip::tcp::socket socket;
            boost::asio::streambuf buffer;
        };
    }
}

#endif //SPWS_NET_SESSION_HPP
