cmake_minimum_required(VERSION 3.1)

project(log-parser VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(log-parser
    src/log_entry.c
    src/log_loader.c
    src/main.c
)

add_executable(test_runner
    tests/test_runner.c
    tests/test_log_entry.c
    tests/unity/unity.c
)

target_include_directories(log-parser PRIVATE
    include
)

target_include_directories(test_runner PRIVATE
    include
    tests/unity
)