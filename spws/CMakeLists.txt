# spws
## sources
file(GLOB_RECURSE spws_SOURCE
        "source/*.hpp"
        "source/*.cpp"
)
## build
add_executable(spws ${spws_SOURCE})
target_include_directories(spws PRIVATE source)

# boost
## set
set(Boost_USE_STATIC_LIBS ON)

## link
find_package(Boost REQUIRED)
target_include_directories(spws PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(spws ${Boost_LIBRARIES})
