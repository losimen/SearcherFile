cmake_minimum_required(VERSION 3.21.1)
project(SearchFile)

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY( MyLib STATIC Searcher.cpp )

ADD_EXECUTABLE( SearchFile main.cpp)
TARGET_LINK_LIBRARIES(SearchFile MyLib)
