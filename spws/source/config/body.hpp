#ifndef SPWS_CONFIG_BODY_HPP
#define SPWS_CONFIG_BODY_HPP

#include <vector>
#include <unordered_map>

namespace spws {
    namespace config {
        struct body {
            struct server {
                struct target {
                    std::string root = "/";
                };
                unsigned short port = 80;
                std::unordered_map<std::string, target> targets;
            };
            std::vector<server> servers;
        };
    }
}


#endif //SPWS_CONFIG_BODY_HPP
