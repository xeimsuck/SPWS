#ifndef SPWS_CONFIG_BODY_HPP
#define SPWS_CONFIG_BODY_HPP

#include <vector>

namespace spws {
    namespace config {
        struct body {
            struct server {
                unsigned short port = 80;
            };
            std::vector<server> servers;
        };
    }
}


#endif //SPWS_CONFIG_BODY_HPP
