#if (APPLE)
#    set(CMAKE_OSX_SYSROOT XCODE_VERSION)
#endif (APPLE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(imgui)

add_subdirectory(imgui)
add_subdirectory(samples/paints)

if (MSVC OR WIN32)
    add_subdirectory(samples/win)
elseif (APPLE)
    add_subdirectory(samples/mac)
else (UNIX)
    add_subdirectory(samples/linux)
endif ()
