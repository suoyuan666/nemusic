set (ASIO_UTILS_SRC
    asio_utils.cpp
)

set(
    ASIO_UTILS_INCLUDE
    ${PROJECT_SOURCE_DIR}/src/include/
)

find_package(CURL REQUIRED)

add_library(
    asio_utils
    OBJECT
    ${ASIO_UTILS_SRC}
)

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(GTK4 REQUIRED gtkmm-4.0)
# add_definitions(${GTK4_CFLAGS_OTHER})

# target_include_directories(curl_utils PUBLIC ${GTK4_INCLUDE_DIRS})
target_include_directories(asio_utils PUBLIC ${ASIO_UTILS_INCLUDE})
target_link_libraries(asio_utils PUBLIC CURL::libcurl)