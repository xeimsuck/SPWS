#ifndef SPWS_CONFIG_PARSER_HPP
#define SPWS_CONFIG_PARSER_HPP

#include <string>
#include <vector>
#include "syntax.hpp"
#include "body.hpp"

namespace spws {
    namespace config {
        class parser {
        public:
            body parse(const std::string& path);
        private:
            types::config getConfig(const std::string& path);
            std::vector<std::string>getDumb(const std::string& path);
            types::section addSection(const std::string& name, std::fstream& in);
        };
    }
}

#endif //SPWS_CONFIG_PARSER_HPP
