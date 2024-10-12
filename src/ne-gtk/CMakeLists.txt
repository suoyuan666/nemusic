set (GTK_SRC
    tab_detail.c
)

set(
    GTK_INCLUDE
    ${PROJECT_SOURCE_DIR}/src/include/
    ${PROJECT_SOURCE_DIR}/third_party/
)

add_library(
    nemusic-gtk
    OBJECT
    ${GTK_SRC}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
add_definitions(${GTK4_CFLAGS_OTHER})

target_include_directories(nemusic-gtk PUBLIC ${GTK4_INCLUDE_DIRS})
target_include_directories(nemusic-gtk PUBLIC ${GTK_INCLUDE})
target_link_libraries(nemusic-gtk PUBLIC cjson)