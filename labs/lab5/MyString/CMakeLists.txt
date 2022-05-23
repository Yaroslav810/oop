add_executable(
        my_string
        main.cpp
        CMyString.h
        CMyString.cpp
)

add_executable(
        my_string_test
        tests/my_string_test.cpp
        CMyString.h
        CMyString.cpp
)
