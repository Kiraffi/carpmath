cmake_minimum_required(VERSION 3.27)
project(carpmath)

set(CMAKE_CXX_STANDARD 17)

add_library(carpmath OBJECT
        mat4.h
        mat4.cpp
        quat.h
        quat.cpp
        vec2.h
        vec2.cpp
        vec3.h
        vec3.cpp
        vec4.h
        vec4.cpp
)

add_executable(carpmathexec main.cpp)
target_link_libraries(carpmathexec PRIVATE carpmath)
