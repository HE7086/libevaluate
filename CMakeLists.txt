cmake_minimum_required(VERSION 3.17)
project(libevaluate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(EnableAddressSanitizer)
include(EnableUndefinedSanitizer)
include(clang-tidy)

add_custom_target(lint)

add_subdirectory(libevaluate)
add_subdirectory(main)
add_subdirectory(test)
