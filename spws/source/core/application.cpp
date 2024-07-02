#include "application.hpp"
#include <iostream>

using namespace spws;

application *application::init() {
    static application app;
    return &app;
}

application::application() {
    base = parser.parse("/usr/local/etc/spws/spws.conf");
    std::cout << base.printInfo() << std::endl;
}

int application::exec() {
    return 0;
}