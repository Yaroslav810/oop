cmake_minimum_required(VERSION 3.21)
project(oop)

set(CMAKE_CXX_STANDARD 20)

add_executable(copyfile labs/lab1/CopyFile/copyfile-my.cpp)
add_executable(replace labs/lab1/Replace/replace.cpp)
add_executable(radix labs/lab1/Radix/radix.cpp)
add_executable(crypt labs/lab1/Crypt/crypt.cpp)
add_executable(fill labs/lab1/Fill/fill.cpp)
add_executable(
        vector
        labs/lab2/Vector/main.cpp
        labs/lab2/Vector/vector.cpp
)
add_executable(
        vector_test
        labs/lab2/Vector/tests/vector_test.cpp
        labs/lab2/Vector/vector.cpp
)
