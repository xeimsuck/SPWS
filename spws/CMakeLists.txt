file(GLOB_RECURSE spws_SOURCE
        "source/*.hpp"
        "source/*.cpp"
)
add_executable(spws ${spws_SOURCE})
target_include_directories(spws PRIVATE source)