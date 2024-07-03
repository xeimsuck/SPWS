#ifndef SPWS_CONFIG_BASE_HPP
#define SPWS_CONFIG_BASE_HPP

#include <vector>
#include <string>
#include "syntax.hpp"

namespace spws {
    namespace config {
        class body {
        public:
            class server{
            public:
                server(ushort port = 80, protocols protocol = protocols::tcp);

            public:
                [[nodiscard]]ushort getPort() const noexcept;
                void setPort(ushort port) noexcept;

                [[nodiscard]]protocols getProtocol() const noexcept;
                void setProtocol(protocols protocol) noexcept;

            private:
                ushort port = 80;
                protocols protocol;
            };

            body() = default;
            ~body() = default;
        public:
            void addServer(server server);
            [[nodiscard]]const std::vector<server>& getServers() const noexcept;

        private:
            std::vector<server> servers;
        };
    }
}

#endif //SPWS_CONFIG_BASE_HPP
