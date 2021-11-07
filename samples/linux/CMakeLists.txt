set(baseon X)

if(${baseon} STREQUAL X)
    set(build_src src/main_x.cpp)
    set(build_inc /usr/include/X11)
    set(build_lib X11)
elseif(${baseon} STREQUAL DRM)
    set(build_src src/main_drm.cpp)
    set(build_inc /usr/include/libdrm)
    set(build_lib drm)
else(${baseon} STREQUAL FB)
    set(build_src src/fb.cpp src/main_fb.cpp)
    set(build_inc )
    set(build_lib )
endif()

add_executable(
    imlin
    ${build_src}
)

target_include_directories(
    imlin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${build_inc}
)

target_link_libraries(imlin PRIVATE imgui paints ${build_lib})
