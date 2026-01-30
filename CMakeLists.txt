cmake_minimum_required(VERSION 3.21)
project(hdmap_ir LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_TESTING "Enable tests" ON)
include(CTest)

# include(FetchContent)
# set(FETCHCONTENT_QUIET OFF) # 方便首次拉取时看到日志
# FetchContent_Declare(
#     googletest
#     URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
# )
# # 为了与某些系统覆盖的 gtest 不冲突
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)

# Use local googletest snapshot (downloaded到 third_party/googletest-1.14.0)
set(GTEST_LOCAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest-1.14.0")
if(EXISTS "${GTEST_LOCAL_PATH}/CMakeLists.txt")
  add_subdirectory("${GTEST_LOCAL_PATH}" third_party/googletest)
else()
  message(FATAL_ERROR "googletest source not found at ${GTEST_LOCAL_PATH}. 请确认已解压或调整路径。")
endif()
