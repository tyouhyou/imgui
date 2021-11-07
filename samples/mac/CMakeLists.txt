link_directories(/usr/X11/lib)

add_executable(
    immac
    src/main.cpp
)

target_include_directories(
    immac PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/X11/include
)

target_link_libraries(immac PRIVATE imgui paints X11)