#ifndef SPWS_NETWORK_CACHE_HPP
#define SPWS_NETWORK_CACHE_HPP

#include <unordered_map>
#include <string>

namespace spws {
    namespace network {
        class cache {
        public:
            std::string getFile(const std::string& path);
        private:
            void addFile(const std::string& file);
            std::unordered_map<std::string, std::string> files;
        };
    }
}


#endif //SPWS_NETWORK_CACHE_HPP