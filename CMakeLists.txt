cmake_minimum_required(VERSION 3.22)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
option(BUILD_SKYRIMAE "Build for Skyrim AE" OFF)
option(BUILD_SKYRIMVR "Build for Skyrim VR" OFF)

# ---- Project ----
project(
    ScrabsPapyrusExtender
    VERSION 1.0.0.0
    LANGUAGES CXX
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Plugin.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/Plugin.h
    @ONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake/version.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.rc
    @ONLY
)

# ---- Globals ----
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Include guards ----
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# ---- Cache build vars ----
macro(set_from_environment VARIABLE)
    if(NOT DEFINED ${VARIABLE} AND DEFINED ENV{${VARIABLE}})
        set(${VARIABLE} $ENV{${VARIABLE}})
    endif()
endmacro()

set_from_environment(VCPKG_ROOT)
if(DEFINED VCPKG_ROOT)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
else()
    message(WARNING "Variable VCPKG_ROOT is not set. Continuing without vcpkg.")
endif()

# ---- Dependencies ----
if(BUILD_SKYRIMVR)
    add_compile_definitions(SKYRIMVR)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_subdirectory("./lib/CommonLibVR" CommonLibSSE)
    set(CommonLibName "CommonLibVR")
    message("Building Skyrim VR")
else()
    if(BUILD_SKYRIMAE)
        add_compile_definitions(SKYRIM_AE)
        add_compile_definitions(SKYRIM_SUPPORT_AE)
        message("Building Skyrim 1.6")
    else()
        message("Building Skyrim 1.5")
    endif()
    set(CommonLibName "CommonLibSSE")
    add_subdirectory("./lib/CommonLibSSE" CommonLibSSE)
endif()

find_package(sol2 REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)
find_package(Lua REQUIRED)

# ---- Add source files ----
include(CMake/source-list.cmake)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES ${CXX_FILES}
)

source_group(
    TREE "${CMAKE_CURRENT_BINARY_DIR}"
    FILES "${CMAKE_CURRENT_BINARY_DIR}/include/Plugin.h"
)

# ---- Create DLL ----
add_library(
    "${PROJECT_NAME}"
    SHARED
    ${CXX_FILES}
    "${CMAKE_CURRENT_BINARY_DIR}/include/Plugin.h"
    "${CMAKE_CURRENT_BINARY_DIR}/version.rc"
    ".clang-format"
    ".editorconfig"
)

target_compile_features(
    "${PROJECT_NAME}"
    PRIVATE
    cxx_std_23
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(
        "${PROJECT_NAME}"
        PRIVATE
        "/sdl" # Enable Additional Security Checks
        "/utf-8" # Set Source and Executable character sets to UTF-8
        "/Zi" # Debug Information Format

        "/permissive-" # Standards conformance
        "/Zc:preprocessor" # Enable preprocessor conformance mode

        "/wd4201" # nonstandard extension used : nameless struct/union

        "$<$<CONFIG:DEBUG>:>"
        "$<$<CONFIG:RELEASE>:/Zc:inline;/JMC-;/Ob3>"
    )

    target_link_options(
        "${PROJECT_NAME}"
        PRIVATE
        "$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
        "$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
    )
endif()

target_include_directories(
    "${PROJECT_NAME}"
    PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${LUA_INCLUDE_DIR}"
)

target_link_libraries(
    "${PROJECT_NAME}"
    PRIVATE
    ${CommonLibName}::${CommonLibName}
    spdlog::spdlog
    "${LUA_LIBRARIES}"
    sol2
)

target_precompile_headers(
    "${PROJECT_NAME}"
    PRIVATE
    "src/PCH.h"
)
