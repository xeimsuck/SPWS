#include "cache.hpp"
#include <fstream>
#include <iostream>

using namespace spws::network;

std::string cache::getFile(const std::string &path) {
    if(files.find(path)==files.end()) addFile(path);
    return files[path];
}

void cache::addFile(const std::string &path) {
    std::fstream stream(path, std::ios::in);
    if(!stream.is_open()) return;
    std::string file, line;
    while (std::getline(stream, line)) file+=line+"\n";
    files[path] = file;
}