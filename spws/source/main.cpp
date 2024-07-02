#include "core/application.hpp"

using namespace spws;

int main(int argc, char** argv){
    auto app = application::init();
    return app ? app->exec() : -1;
}