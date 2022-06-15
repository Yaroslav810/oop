add_executable(
        http_url
        main.cpp
        CHttpUrl.h
        CHttpUrl.cpp
        CUrlParsingError.h
        CUrlParsingError.cpp
)

add_executable(
        http_url_test
        tests/http_url_test.cpp
        CHttpUrl.h
        CHttpUrl.cpp
        CUrlParsingError.h
        CUrlParsingError.cpp
)
