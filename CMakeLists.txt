cmake_minimum_required(VERSION 3.13)
project(OSProject1)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall" )

add_executable(os main.cpp
        Argument.cpp Argument.h
        Processes.cpp Processes.h
        Process.cpp Process.h
        ReadyQueue.cpp ReadyQueue.h
        Output.cpp Output.h)
