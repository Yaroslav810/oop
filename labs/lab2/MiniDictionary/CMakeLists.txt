add_executable(
        dictionary
        main.cpp
        dictionary.h
        dictionary.cpp
        dictionaryController.h
        dictionaryController.cpp
)

add_executable(
        dictionary_test
        tests/dictionary_test.cpp
        dictionary.h
        dictionary.cpp
)
