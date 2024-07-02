#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <format>

using namespace spws::config;

body parser::parse(const std::string &path) {
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
            throw std::runtime_error(std::format("ERROR: Unknown operator (Var:{}): {}", i, oper));
        }
    }

    body body;


    return body;
}

std::vector<std::string> parser::getDumb(const std::string &path, char delim) {
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