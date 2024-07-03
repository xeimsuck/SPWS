#include "session.hpp"
#include <iostream>

spws::network::session::session(boost::asio::ip::tcp::socket &&socket) :
                    socket(std::move(socket)) {
}

void spws::network::session::run() {
    std::cout << "run\n";
    listen();
}

void spws::network::session::listen() {
    auto self(shared_from_this());
    boost::asio::async_read_until(socket, buffer, "\0", [self, this](const boost::system::error_code ec, std::size_t size){
        if(error_handler(ec)) return;
        request(size);
        listen();
    });
}

void spws::network::session::request(const std::size_t size) {
    std::string str = "HTTP/1.1 200 OK\nContent-Type: text/html\r\nContent-Length: 52\r\n\r\n<html><head></head><body><h1>SPWS</h1></body></html>";
    boost::asio::write(socket, boost::asio::buffer(str));
    buffer.consume(buffer.size());
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
