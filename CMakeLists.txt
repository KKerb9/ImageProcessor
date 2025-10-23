cmake_minimum_required(VERSION 3.16)
project(image_processor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(image_processor ${SOURCES})

target_compile_options(image_processor PRIVATE
    -fsanitize=address,undefined
    -g
)

target_link_options(image_processor PRIVATE
    -fsanitize=address,undefined
)
