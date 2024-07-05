#ifndef SPWS_NET_SESSION_HPP
#define SPWS_NET_SESSION_HPP

#include <memory>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include "network/cache.hpp"

namespace spws {
    namespace network {
        class session : public std::enable_shared_from_this<session> {
        public:
            explicit session(boost::asio::ip::tcp::socket &&socket,
                             network::cache& serverCache,
                             const std::unordered_map<std::string, std::string>& targets);

        public:
            void run();
        private:
            void listen();
            void handleRequest(std::size_t size);
            boost::beast::http::request<boost::beast::http::string_body>
                    parseRequest();
            std::string getPath(const std::string& target);
            std::string getBody(const std::string& target, const std::string& shortTarget);
            int error_handler(boost::system::error_code error);
        private:
            boost::asio::ip::tcp::socket socket;
            boost::asio::streambuf buffer;
            network::cache& serverCache;
            const std::unordered_map<std::string, std::string>& targets;
        };
    }
}

#endif //SPWS_NET_SESSION_HPP
