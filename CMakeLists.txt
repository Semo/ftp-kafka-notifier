cmake_minimum_required(VERSION 3.10)
project(kafkawrap)

set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -pedantic -Wextra")


link_directories(/usr/local/lib)


add_executable(kafkawrap
        main
        main.cpp
        Makefile)

target_link_libraries(kafkawrap rdkafka)
