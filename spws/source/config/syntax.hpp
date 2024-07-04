#ifndef SPWS_CONFIG_SYNTAX_HPP
#define SPWS_CONFIG_SYNTAX_HPP

#include <string>
#include <vector>

namespace spws {
    namespace config {
        namespace types {
            struct variable {
                std::string name;
                std::string value;
            };
            struct block {
                std::string name;
                std::vector<variable> variables;
                std::vector<block> blocks;
                block* parent;
            };
        }
    }
}

#endif //SPWS_CONFIG_SYNTAX_HPP
