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

target_include_directories(netmusic PUBLIC ${NET_MSUSIC_INCLUDE})