cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 14)

set(ANDROID_PLATFORM 21)
#armeabi-v7a arm64-v8a
set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)
set(ANDROID_ABI arm64-v8a)
set(CMAKE_BUILD_TYPE O3)
set(DCMAKE_EXPORT_COMPILE_COMMANDS on)
set(ANDROID_STL c++_static)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static") # 静态链接库
set(CMAKE_SYSTEM_VERSION 21)

# 替换成自己电脑上的 NDK 路径
set(NDK /home/ethan/Android/Sdk/ndk/21.4.7075529)
set(CMAKE_TOOLCHAIN_FILE ${NDK}/build/cmake/android.toolchain.cmake)

project(lesson1)

#include_directories(src)
#include_directories(src/aarch64)
aux_source_directory(src lesson1_source_files)
#aux_source_directory(src/aarch64 vixl_src_files_arm64)

# find_library( # Sets the name of the path variable.
#         log-lib

#         # Specifies the name of the NDK library that
#         # you want CMake to locate.
#         log)

# message(${log-lib})
link_directories(src/lib)
# add_library(lesson1 SHARED ${lesson1_source_files})





add_executable(lesson1 ${lesson1_source_files})

target_link_libraries(lesson1 -static -lc)

add_custom_command(
    TARGET lesson1 POST_BUILD
    COMMAND ${ANDROID_TOOLCHAIN_PREFIX}strip${ANDROID_TOOLCHAIN_SUFFIX} "${CMAKE_BINARY_DIR}/lesson1"
    VERBATIM
)
# message(STATUS "path: ${CMAKE_BINARY_DIR}")
# message(STATUS ${ANDROID_HOST_TAG})
# message(STATUS ${ANDROID_ABI})
# message(STATUS ${ANDROID_NDK_REVISION})
# message(STATUS ${ANDROID_SYSROOT_ABI})
# message(STATUS ${ANDROID_TOOLCHAIN_SUFFIX})
message(STATUS ${ANDROID_TOOLCHAIN_PREFIX}strip${ANDROID_TOOLCHAIN_SUFFIX} "${CMAKE_BINARY_DIR}/lesson1")