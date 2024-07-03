#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <format>
#include <climits>

using namespace spws::config;

body parser::parse(const std::string &path) {
    return getBody(getConfig(path));
}

std::vector<std::string> parser::getDumb(const std::string &path) {
    std::fstream in(path, std::ios::in);
    if(!in.is_open()) throw std::runtime_error(std::string("ERROR: Could not open configuration file (") + path + ")");

    std::unordered_set<char> sug {'\t', '\n', ' ', '=', ':'};
    std::vector<std::string> dumb(1);

    char ch;
    while (in.get(ch)){
        auto it = sug.find(ch);
        if(it!=sug.end()){
            if(*it == '=' || *it == ':'){
                if(dumb.back().empty()) dumb.back()+=*it;
                else dumb.push_back(std::string{*it});
                dumb.emplace_back();
            } else {
                if(!dumb.back().empty()) dumb.emplace_back();
            }
            continue;
        }
        dumb.back()+=ch;
    }

    in.close();
    dumb.pop_back();
    return dumb;
}
types::config parser::getConfig(const std::string &path) {
    auto dumb = getDumb(path);
    types::config config;
    config.emplace_back("global", types::entries{});
    std::stack<types::config::iterator> blocks;
    blocks.push(config.begin());

    size_t i = 0;
    while (i < dumb.size()){
        const std::string word = dumb[i++];
        if(word.empty()) continue;
        if(word=="}") {
            if(blocks.empty()) throw std::runtime_error("ERROR: Unnecessary braces \'}\'");
            blocks.pop();
            continue;
        }
        const std::string oper = dumb[i++];
        if(oper=="="||oper==":"){
            std::string operand = dumb[i++];
            blocks.top()->second.emplace_back(word, operand);
        } else if (oper=="{") {
            config.emplace_back(word, types::entries());
            blocks.push(config.end()-1);
        } else {
            throw std::runtime_error(std::format("ERROR: Unknown operator: {}",  oper));
        }
    }
    if(blocks.size()!=1) throw std::runtime_error("ERROR: Unnecessary braces \'{\'");
    return config;
}
body parser::getBody(const types::config &config) {
    body body;

    auto itBody = config.end();
    for(auto it = config.begin(); it!=config.end(); ++it){
        if(it->first=="body") {
            itBody = it;
            continue;
        }
        if(it->first=="server"){
            body::server server;
            for(decltype(auto) itServ : it->second){
                if(itServ.first == "port") {
                    auto port = std::stoi(itServ.second);
                    if(port<0 || port>USHRT_MAX) throw std::runtime_error( std::format("ERROR: Type port in range of 0 to {}", USHRT_MAX));
                    server.setPort(static_cast<ushort>(port));
                } else if(itServ.first == "protocol"){
                    std::string protocol = itServ.second;
                    std::transform(protocol.begin(), protocol.end(), protocol.begin(), [](char c){return std::tolower(c);});
                    if(protocol=="tcp"){
                        server.setProtocol(protocols::tcp);
                    } else if(protocol=="udp"){
                        server.setProtocol(protocols::udp);
                    } else {
                        throw std::runtime_error(std::format("ERROR: Unknown protocol: {}", itServ.second));
                    }
                }
            }
            body.addServer(server);
        }
    }
    if(itBody==config.end()) throw std::runtime_error("ERROR: No \"body\" section");


    return body;
}
