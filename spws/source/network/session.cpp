#include "session.hpp"
#include <iostream>
#include <string>

using namespace boost::beast;
using namespace spws::network;

spws::network::session::session(boost::asio::ip::tcp::socket &&_socket,
                                network::cache& _serverCache,
                                const std::unordered_map<std::string, std::string>& _targets) :
                    socket(std::move(_socket)), serverCache(_serverCache),
                    targets(_targets){
}

void spws::network::session::run() {
    std::cout << "run\n";
    listen();
}

void spws::network::session::listen() {
    auto self(shared_from_this());
    boost::asio::async_read_until(socket, buffer, "\0", [self, this](const boost::system::error_code ec, std::size_t size){
        if(error_handler(ec)) return;
        handleRequest(size);
        buffer.consume(buffer.size());
        listen();
    });
}

void spws::network::session::handleRequest(std::size_t size) {
    auto request = parseRequest();
    std::string body;
    if(request.target().size()<=1) {
        body = serverCache.getFile(getPath("/")+"/index.html");
    } else {
        body = serverCache.getFile(getPath(request.target()));
    }
    http::response<http::string_body> response;
    response.body() = body;
    response.result(200);
    response.content_length(body.size());
    std::stringstream stream;
    stream << response;
    boost::asio::write(socket, boost::asio::buffer(stream.str()));
}

boost::beast::http::request<boost::beast::http::string_body> spws::network::session::parseRequest() {
    boost::beast::http::request_parser<boost::beast::http::string_body> parser;
    boost::beast::error_code code;
    parser.put(buffer.data(), code);
    return parser.get();
}

std::string session::getPath(const std::string &target) {
    auto it = targets.find(target);
    if(it==targets.end()){
        return getPath(target.substr(0, target.find_last_of('/', target.size() - 2) + 1)) + target;
    }
    return it->second;
}

int spws::network::session::error_handler(boost::system::error_code error) {
    if(!error) return 0;
    switch (error.value()) {
        case boost::asio::error::eof:
            return 1;
        case boost::asio::error::connection_aborted:
            return 1;
        case boost::asio::error::connection_reset:
            return 1;
        case boost::asio::error::connection_refused:
            return 1;
    }
    std::cerr << "SESSION ERROR: " << error.what() << "\n";
    return 1;
}
