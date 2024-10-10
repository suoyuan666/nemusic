set (CURL_UTILS_SRC
    curl_utils.c
)

set(
    CURL_UTILS_INCLUDE
    ${PROJECT_SOURCE_DIR}/src/include/
)

find_package(CURL REQUIRED)

add_library(
    curl_utils
    OBJECT
    ${CURL_UTILS_SRC}
)

target_include_directories(curl_utils PUBLIC ${CURL_UTILS_INCLUDE})
target_link_libraries(curl_utils PUBLIC CURL::libcurl)