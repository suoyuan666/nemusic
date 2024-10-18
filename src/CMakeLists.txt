set(
    MAIN_INCLUDE
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/third_party/
)

set(
    MAIN_LIB
    netmusic
    asio_utils
    nemusic-gtk
    nlohmann_json
    # cjson
    # music_core
)

add_subdirectory(services)
add_subdirectory(asio_utils)
add_subdirectory(ne-gtk)
# add_subdirectory(music_core)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtkmm-4.0)
add_definitions(${GTK4_CFLAGS_OTHER})

add_executable(new-gtk main.cpp)

target_include_directories(new-gtk PUBLIC ${GTK4_INCLUDE_DIRS})
target_include_directories(new-gtk PUBLIC ${GTK_INCLUDE})

target_link_libraries(new-gtk PRIVATE ${GTK4_LIBRARIES} ${MAIN_LIB})