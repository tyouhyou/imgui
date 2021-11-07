if (MSVC OR WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(
    paints SHARED
    src/gfxpainter.cpp
)

target_include_directories(
    paints PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(paints PRIVATE imgui)