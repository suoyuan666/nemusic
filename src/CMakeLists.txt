set(
    MAIN_INCLUDE
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/third_party/
)

set(
    MAIN_LIB
    netmusic
    curl_utils
    nemusic-gtk
    cjson
)

add_subdirectory(services)
add_subdirectory(curl_utils)
add_subdirectory(ne-gtk)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
add_definitions(${GTK4_CFLAGS_OTHER})

add_executable(new-gtk main.c)

target_include_directories(new-gtk PUBLIC ${GTK4_INCLUDE_DIRS})
target_include_directories(new-gtk PUBLIC ${MAIN_INCLUDE})

target_link_libraries(new-gtk PRIVATE ${GTK4_LIBRARIES} ${MAIN_LIB})