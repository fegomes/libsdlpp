cmake_minimum_required(VERSION 3.9)

project(libsdlpp)

set(CMAKE_CXX_STANDARD 17)

file(GLOB src "include/libsdlpp/*.hpp")

if(MSVC)
    add_library(libsdlpp INTERFACE ${src})
else()
    add_library(libsdlpp INTERFACE)
    target_sources(libsdlpp INTERFACE ${src})
endif()


set_property(
    TARGET libsdlpp PROPERTY
    EXPORT_NAME libsdlpp
)

target_include_directories(
    libsdlpp ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(libsdlpp INTERFACE cxx_std_17)

add_subdirectory(tests)