cmake_minimum_required(VERSION 3.21)
project(hdmap_ir LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_TESTING "Enable tests" ON)
include(CTest)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF) # 方便首次拉取时看到日志
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# 为了与某些系统覆盖的 gtest 不冲突
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)