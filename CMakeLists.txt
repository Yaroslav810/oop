cmake_minimum_required(VERSION 3.21)
project(oop)

set(CMAKE_CXX_STANDARD 17)

add_executable(copyfile labs/lab1/CopyFile/copyfile-my.cpp)
add_executable(replace labs/lab1/Replace/replace.cpp)
add_executable(radix labs/lab1/Radix/radix.cpp)
add_executable(crypt labs/lab1/Crypt/crypt.cpp)
add_executable(fill labs/lab1/Fill/fill.cpp)
add_executable(
        vector
        labs/lab2/vector/main.cpp
        labs/lab2/vector/vector.cpp
)

