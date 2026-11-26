cmake_minimum_required(VERSION 3.20)

project(MPanel
    VERSION 0.1.0
    DESCRIPTION "MPanel service for Linux Servers"
    LANGUAGES CXX
)

add_executable(MPanel
    src/main.cpp
)

# Including the web/ folder as 'embedded_web.hpp'
file(GLOB_RECURSE WEB_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/web/*"
)

set(EMBEDDED_HEADER "${CMAKE_CURRENT_BINARY_DIR}/embedded_web.hpp")

file(WRITE "${EMBEDDED_HEADER}"
    "#pragma once\n#include <string_view>\n"
    "namespace embedded_web {\n"
    "struct Asset { std::string_view path; std::string_view content; };\n"
    "inline constexpr Asset assets[] = {\n"
)

foreach(WEB_FILE IN LISTS WEB_FILES)
    if(IS_DIRECTORY "${WEB_FILE}")
        continue()
    endif()

    file(READ "${WEB_FILE}" CONTENT)
    file(RELATIVE_PATH REL_PATH
        "${CMAKE_CURRENT_SOURCE_DIR}/web"
        "${WEB_FILE}"
    )

    string(SHA256 HASH "${CONTENT}")
    string(SUBSTRING "${HASH}" 0 8 SHORT_HASH)
    set(DELIM "MP${SHORT_HASH}")

    string(FIND "${CONTENT}" ")${DELIM}\"" COLLISION)
    if(NOT COLLISION EQUAL -1)
        message(FATAL_ERROR "Raw-string delimiter collision in ${WEB_FILE}")
    endif()

    file(APPEND "${EMBEDDED_HEADER}"
        "    {R\"${DELIM}(${REL_PATH})${DELIM}\", "
        "R\"${DELIM}(${CONTENT})${DELIM}\"},\n"
    )
endforeach()

file(APPEND "${EMBEDDED_HEADER}" "};\n}\n")

target_include_directories(MPanel PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")



target_compile_features(MPanel PRIVATE cxx_std_17)

set_target_properties(MPanel PROPERTIES
    CXX_EXTENSIONS OFF
)