#include "parser.hpp"
#include <fstream>
#include <unordered_set>
#include <format>

using namespace spws::config;

body parser::parse(const std::string &path) {
    auto globalBlock = getGlobalBlock(getConfig(path));
    for(decltype(auto) block : globalBlock.blocks){
        if(block.name=="body") return getBody(block);
    }
    throw std::runtime_error("CONFIG ERROR: block body missed");
}

std::vector<std::string> parser::getConfig(const std::string &path) {
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
types::block parser::getGlobalBlock(const std::vector<std::string> &config) {
    types::block globalBlock{.name="global", .parent=nullptr};
    types::block* currentBlock = &globalBlock;

    int i = 0;
    while (i<config.size()){
        decltype(auto) var1 = config[i++];
        if(var1=="}"){
            if(!currentBlock->parent) throw std::runtime_error("CONFIG ERROR: closing brace missed");
            currentBlock = currentBlock->parent;
            continue;
        }
        decltype(auto) oper = config[i++];
        if(oper=="="||oper==":"){
            currentBlock->variables.emplace_back(var1, config[i++]);
        } else if(oper=="{"){
            currentBlock->blocks.push_back(types::block{.name=var1, .parent=currentBlock});
            currentBlock = &currentBlock->blocks.back();
        } else {
            if(config[i++]!="{") throw std::runtime_error(std::format("CONFIG ERROR: unknown operator: {}", oper));
            currentBlock->blocks.push_back(types::block{.name=var1, .parent=currentBlock});
            currentBlock = &currentBlock->blocks.back();
            currentBlock->variables.emplace_back(var1, oper);
        }
    }
    return globalBlock;
}

body parser::getBody(const types::block &bodyBlock) {
    config::body body;
    for(decltype(auto) block : bodyBlock.blocks){
        if(block.name=="server")
            body.servers.push_back(getServer(block));
    }
    return body;
}

body::server parser::getServer(const types::block &serverBlock) {
    config::body::server server;
    for(decltype(auto) variable : serverBlock.variables){
        if(variable.name=="port") server.port = std::stoi(variable.value);
    }
    for(decltype(auto) block : serverBlock.blocks){
        if(block.name=="target") server.targets[block.variables.front().value] = getTarget(block);
    }
    return server;
}

body::server::target parser::getTarget(const types::block &targetBlock) {
    body::server::target target;
    for (decltype(auto) variable : targetBlock.variables) {
        if(variable.name=="root") target.root = variable.value;
    }
    return target;
}