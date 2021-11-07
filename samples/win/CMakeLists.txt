add_executable(
    imwin WIN32
    src/story.cpp
    src/main.cpp
)

target_include_directories(
    imwin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(imwin PRIVATE imgui paints)
