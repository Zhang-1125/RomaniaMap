cmake_minimum_required(VERSION 3.26)
project(RomaniaMap)

set(CMAKE_CXX_STANDARD 17)

add_executable(RomaniaMap main.cpp
        headers/Node.h
        cpps/Node.cpp
        headers/Search.h
        cpps/Search.cpp
        headers/TreeNode.h
        cpps/TreeNode.cpp)
