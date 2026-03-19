cmake_minimum_required(VERSION 3.31)
project(Labs)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE FILES "src/*.cpp")

foreach(file ${FILES})
    get_filename_component(target_name ${file} NAME_WE)

    add_executable(${target_name} ${file})
endforeach()
