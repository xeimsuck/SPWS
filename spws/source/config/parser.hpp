#ifndef SPWS_CONFIG_PARSER_HPP
#define SPWS_CONFIG_PARSER_HPP

#include <vector>
#include <string>
#include "config/body.hpp"
#include "syntax.hpp"

namespace spws {
    namespace config {
        class parser {
        public:
            static body parse(const std::string& path);
        private:
            static std::vector<std::string> getConfig(const std::string& path);
            static types::block getGlobalBlock(const std::vector<std::string>& config);

            static body getBody(const types::block& bodyBlock);
            static body::server getServer(const types::block& serverBlock);
        };
    }
}

#endif //SPWS_CONFIG_PARSER_HPP
