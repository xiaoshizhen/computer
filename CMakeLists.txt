cmake_minimum_required(VERSION 3.16)
project(calculator VERSION 3.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(calculator
    main.cpp
    calculator.cpp
)

target_include_directories(calculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
