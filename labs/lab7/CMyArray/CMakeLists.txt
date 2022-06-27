add_executable(
        my_array
        main.cpp
        CMyArray.h
        CMyArrayIterator.h
)

add_executable(
        my_array_test
        tests/my_array_test.cpp
        CMyArray.h
        CMyArrayIterator.h
)
