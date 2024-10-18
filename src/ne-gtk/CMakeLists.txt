set (GTK_SRC
    tab_detail.cpp
    main_window.cpp
)

set(
    GTK_INCLUDE
    ${PROJECT_SOURCE_DIR}/src/include/
    ${PROJECT_SOURCE_DIR}/third_party/json/include
)

add_library(
    nemusic-gtk
    OBJECT
    ${GTK_SRC}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtkmm-4.0)
add_definitions(${GTK4_CFLAGS_OTHER})

target_include_directories(nemusic-gtk PUBLIC ${GTK4_INCLUDE_DIRS})
target_include_directories(nemusic-gtk PUBLIC ${GTK_INCLUDE})