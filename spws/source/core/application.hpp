#ifndef SPWS_CORE_APPLICATION_HPP
#define SPWS_CORE_APPLICATION_HPP

#include "config/parser.hpp"

namespace spws {
    class application {
    public:
        application(const application &copy) = delete;
        application &operator=(const application &copy) = delete;

        static application *init();
    private:
        application();
        ~application() = default;

    public:
        int exec();

    private:
        config::parser parser;
        config::body base;
    };
}

#endif //SPWS_CORE_APPLICATION_HPP
