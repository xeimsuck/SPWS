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
            static body parse(const std::string& path);
        private:
            static types::config getConfig(const std::string& path);
            static body getBody(const types::config& config);
            static std::vector<std::string>getDumb(const std::string& path);
        };
    }
}

#endif //SPWS_CONFIG_PARSER_HPP
