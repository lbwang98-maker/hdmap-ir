# src/CMakeLists.txt

add_library(hdmap_geo
    geo/geometry/aabb.cpp
    geo/geometry/vec2.cpp
    geo/geometry/segment.cpp
)

target_include_directories(hdmap_geo
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(hdmap_geo PUBLIC cxx_std_17)