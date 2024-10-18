cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF) # use c++17 insead of gnu++c17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE) # for generate full compile_commands.json

project(nemusic
    VERSION 0.1
    LANGUAGES CXX
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # enable_testing()
    # add_subdirectory(test)
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Wall -Wextra -Werror -Wextra")
    # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring Release build")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -march=native -pipe -fPIE -Wall -Wextra -Wpedantic -Werror")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fcf-protection=full -fsanitize=integer -fsanitize-minimal-runtime")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_FORTIFY_SOURCE=3 -fstack-clash-protection -fstack-protector-all -fstack-protector-strong")
    if (CMAKE_CXXXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto=thin")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wl,-O2,-z,now,-z,noexecstack,--as-needed,--lto-O3,--icf=safe,--gc-sections,-z,relro")
    elseif(CMAKE_CXXXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wl,-O2,-z,now,-z,noexecstack,--as-needed,--gc-sections,-z,relro")
    endif()
endif()

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)
if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
    message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif()

add_subdirectory(third_party)
add_subdirectory(src)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
endif()
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")