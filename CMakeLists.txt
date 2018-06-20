cmake_minimum_required(VERSION 3.10)
project(tumbiChat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fpermissive")

add_executable(tumbiChat
        src/server.cpp src/server.h)
TARGET_LINK_LIBRARIES( tumbiChat
        pthread)

add_executable(tumbiClient
        src/client.cpp src/client.h)
TARGET_LINK_LIBRARIES( tumbiClient
        pthread)
