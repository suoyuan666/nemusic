set (MUSIC_CORE_SRC
    music_core.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBVLC REQUIRED IMPORTED_TARGET
    libvlc
)

add_library(
    music_core
    OBJECT
    ${MUSIC_CORE_SRC}
)

target_include_directories(music_core PRIVATE ${LIBVLCINCLUDE_DIRS})
target_link_libraries(music_core PRIVATE PkgConfig::LIBVLC)