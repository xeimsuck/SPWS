#ifndef SPWS_CONFIG_TYPES_HPP
#define SPWS_CONFIG_TYPES_HPP

#include <string>
#include <utility>
#include <vector>

namespace spws {
    namespace config {
        namespace types {
            using entry = std::pair<std::string, std::string>;
            using entries = std::vector<entry>;
            using section = std::pair<std::string, entries>;
            using config = std::vector<section>;
        }
    }
}

#endif //SPWS_CONFIG_TYPES_HPP
