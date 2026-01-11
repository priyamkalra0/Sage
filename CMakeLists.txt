cmake_minimum_required(VERSION 3.14)
project(Sage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
        sage
        src/Application.cpp
)

target_include_directories(sage PUBLIC include)
