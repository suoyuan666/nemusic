set (NET_MSUSIC_SRC
    netmusic.c
)

set(
    NET_MSUSIC_INCLUDE
    ${PROJECT_SOURCE_DIR}/src/include/
    ${PROJECT_SOURCE_DIR}/third_party/
)

add_library(
    netmusic
    OBJECT
    ${NET_MSUSIC_SRC}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
add_definitions(${GTK4_CFLAGS_OTHER})

target_include_directories(netmusic PUBLIC ${GTK4_INCLUDE_DIRS})
target_include_directories(netmusic PUBLIC ${NET_MSUSIC_INCLUDE})
target_link_libraries(netmusic PUBLIC cjson)