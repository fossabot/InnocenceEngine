cmake_minimum_required(VERSION 2.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# compiler config file
configure_file ("${CMAKE_SOURCE_DIR}/engine/common/config.h.in" "${CMAKE_SOURCE_DIR}/engine/common/config.h")

# Use Clang?
option (INNO_COMPILER_CLANG "Use Clang as the default compiler" OFF)
if (INNO_COMPILER_CLANG)
set (CMAKE_C_COMPILER               "clang-cl")
set (CMAKE_C_FLAGS                  "-Wall")
set (CMAKE_C_FLAGS_DEBUG            "/Debug")
set (CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG")
set (CMAKE_C_FLAGS_RELEASE          "-O4 -DNDEBUG")
set (CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 /Debug")
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_COMPILER             "clang-cl")
set (CMAKE_CXX_FLAGS                "-Wall -Xclang -std=gnu++14")
set (CMAKE_CXX_FLAGS_DEBUG          "/Debug")
set (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 /Debug")
endif (INNO_COMPILER_CLANG)

option (USE_ROW_MAJOR_MEMORY_LAYOUT "use Row-Major memory layout" ON)
option (USE_COLUMN_MAJOR_MEMORY_LAYOUT "use Column-Major memory layout" OFF)

option (INNO_PLATFORM_WIN32 "Windows x86 32-bit" OFF)
option (INNO_PLATFORM_WIN64 "Windows x86-64 64-bit" ON)
option (INNO_PLATFORM_LINUX64 "Linux x86-64 64-bit" OFF)
option (INNO_PLATFORM_MACOS "MAC x86-64 64-bit" OFF)

option (INNO_RENDERER_OPENGL "OpenGL renderer for Multi-Platforms" ON)
option (INNO_RENDERER_DX "DirectX renderer for Windows OS only" OFF)
option (INNO_RENDERER_VULKAN "Vulkan renderer for Multi-Platforms" OFF)
option (INNO_RENDERER_METAL "Metal renderer for MacOS and iOS only" OFF)

option (BUILD_EDITOR "Build editor" OFF)
option (BUILD_GAME "Build game" OFF)
option (BUILD_TEST "Build test" ON)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib_archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (INNO_PLATFORM_WIN32)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external/lib/win32)
endif (INNO_PLATFORM_WIN32)

if (INNO_PLATFORM_WIN64)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external/lib/win64)
endif (INNO_PLATFORM_WIN64)

if (INNO_PLATFORM_LINUX64)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external/lib/unix)
endif (INNO_PLATFORM_LINUX64)

if (INNO_PLATFORM_MACOS)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external/lib/macos)
endif (INNO_PLATFORM_MACOS)

project (InnocenceEngine)

include_directories("engine")
include_directories("external/include")

add_subdirectory("engine")
add_subdirectory("game")
