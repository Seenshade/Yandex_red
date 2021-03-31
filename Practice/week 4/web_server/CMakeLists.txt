cmake_minimum_required(VERSION 3.17)
project(web_server)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:\\Coursera\\Red\\Practice\\Include)

add_executable(web_server main.cpp stats.cpp)