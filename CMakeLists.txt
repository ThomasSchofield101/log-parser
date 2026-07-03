cmake_minimum_required(VERSION 3.1)

project(log-parser VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(log-parser
    src/log_entry.c
    src/log_loader.c
    src/main.c
)

target_include_directories(log-parser PRIVATE
    include
    tests/unity
)