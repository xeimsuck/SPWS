#include "server.hpp"

#include <iostream>
#include <memory>
#include "session.hpp"

using namespace boost::asio;
using ip::tcp;

spws::network::server::server(boost::asio::io_service &_service, ushort _port) :
                service(_service), acceptor(_service, tcp::endpoint(tcp::v4(), _port)){
}

void spws::network::server::accept() {
    acceptor.async_accept([this](const boost::system::error_code& error, tcp::socket socket){
        if(error_handler(error)) return;
        accept_handler(error, socket);
        accept();
    });
}

int spws::network::server::error_handler(boost::system::error_code error) {
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
    std::cerr << "SERVER ERROR: " << error.what() << "\n";
    return 1;
}

void spws::network::server::accept_handler(const boost::system::error_code &error, boost::asio::ip::tcp::socket &socket) {
    if(error) throw std::runtime_error(error.what());
    std::make_shared<session>(std::move(socket))->run();
}