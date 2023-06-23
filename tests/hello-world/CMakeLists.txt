cmake_minimum_required(VERSION 3.9)

project(hello-world VERSION 1.0.0 DESCRIPTION "Hello World libsdlpp")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${SDL2_NET_INCLUDE_DIR})
include_directories(${libsdlpp_SOURCE_DIR}/include)

add_executable(hello-world main.cpp)

target_link_libraries(hello-world PRIVATE ${SDL2_LIBRARY} 
										  ${SDL2_MAIN_LIBRARY} 
										  ${SDL2_IMAGE_LIBRARY}
										  ${SDL2_TTF_LIBRARY} 
										  ${SDL2_MIXER_LIBRARY}
									      ${SDL2_NET_LIBRARY})