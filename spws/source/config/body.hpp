#ifndef SPWS_CONFIG_BASE_HPP
#define SPWS_CONFIG_BASE_HPP

#include <vector>
#include <string>

namespace spws {
    namespace config {
        class body {
        public:
            class server{
            public:
                server(unsigned short port = 80);
            public:
                [[nodiscard]]short getPort() const noexcept;
                void setPort(short port) noexcept;
            private:
                unsigned short port = 80;
            };

            body() = default;
            ~body() = default;
        public:
            std::string printInfo();
            void addServer(server server);
            [[nodiscard]]const std::vector<server>& getServers() const noexcept;

        private:
            std::vector<server> servers;
        };
    }
}

#endif //SPWS_CONFIG_BASE_HPP
