cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)
set(LINKER_FLAGS "-ffixed-x18 -Wl,--hash-style=both")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=format -fdata-sections -ffunction-sections -fvisibility=hidden -Wl,--exclude-libs,ALL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -fvisibility=hidden -Wl,--exclude-libs,ALL")

project("wind")
include_directories(.)

find_library(EGL_LIB egl)
find_library(GLESV2_LIB GLESv2)
find_library(ANDROID_LIB android)
find_library(LOG_LIB log)

add_library(local_dobby STATIC IMPORTED)
set_target_properties(local_dobby PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI}/libdobby.a)

include_directories(imgui)
add_library(imgui STATIC
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_impl_android.cpp
        imgui/imgui_impl_opengl3.cpp)

add_library(wind SHARED wind.cpp)

set_target_properties(wind PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI})
target_link_libraries(wind android local_dobby EGL GLESv2 imgui log)