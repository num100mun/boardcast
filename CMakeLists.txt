cmake_minimum_required(VERSION 3.24)
project(IPV4)

set(CMAKE_CXX_STANDARD 17)

add_executable(IPV4 main.cpp)
add_executable(server server.cpp)
add_executable(test test.cpp)
add_executable(test2 test2.cpp)
add_executable(client client.cpp)
