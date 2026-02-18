cmake_minimum_required(VERSION 3.15)

project(ninjadbg VERSION 0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2 -g")

set(SOURCES
    src/main.cpp
    src/debugger.cpp
    src/process.cpp
)


add_executable(ninjadbg ${SOURCES})

target_include_directories(ninjadbg PRIVATE include)


target_link_libraries(ninjadbg PRIVATE pthread)



