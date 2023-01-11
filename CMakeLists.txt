cmake_minimum_required(VERSION 3.24)
project(cpp_search_server)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(cpp_search_server
        document.cpp
        main.cpp
        read_input_functions.cpp
        request_queue.cpp
        search_server.cpp
        string_processing.cpp
        )
