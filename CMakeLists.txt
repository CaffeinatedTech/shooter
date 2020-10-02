cmake_minimum_required(VERSION 3.17)
project(shooter)

set(CMAKE_CXX_STANDARD 20)

add_executable(shooter src/main.cpp src/engine.cpp headers/engine.hpp src/update.cpp src/draw.cpp src/input.cpp src/textureholder.cpp headers/textureholder.hpp src/player.cpp headers/player.hpp)

include_directories(headers /usr/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(shooter ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})