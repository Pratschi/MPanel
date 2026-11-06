cmake_minimum_required(VERSION 3.20)

project(MPanel
    VERSION 0.1.0
    DESCRIPTION "MPanel service for Linux Servers"
    LANGUAGES CXX
)

add_executable(MPanel
    src/main.cpp
)

target_compile_features(MPanel PRIVATE cxx_std_17)

set_target_properties(MPanel PROPERTIES
    CXX_EXTENSIONS OFF
)

find_package(yaml-cpp REQUIRED)

target_link_libraries(MPanel PRIVATE yaml-cpp::yaml-cpp)