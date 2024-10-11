cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF) # use c17 insead of gnuc17
set(CMAKE_C_STANDARD_REQUIRED ON)

project(nemusic
    VERSION 0.1
    LANGUAGES C
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # enable_testing()
    # add_subdirectory(test)
    set(CMAKE_C_FLAGS_DEBUG "-g3 -Wall -Wextra -Werror -Wextra -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring Release build")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -march=native -pipe -fPIE -Wall -Wextra -Wpedantic -Werror")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fcf-protection=full -fsanitize=integer -fsanitize-minimal-runtime")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -D_FORTIFY_SOURCE=3 -fstack-clash-protection -fstack-protector-all -fstack-protector-strong")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto=thin")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wl,-O2,-z,now,-z,noexecstack,--as-needed,--lto-O3,--icf=safe,--gc-sections,-z,relro")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wl,-O2,-z,now,-z,noexecstack,--as-needed,--gc-sections,-z,relro")
    endif()
endif()

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)
if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
    message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif()

add_subdirectory(third_party)
add_subdirectory(src)

message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
endif()
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")