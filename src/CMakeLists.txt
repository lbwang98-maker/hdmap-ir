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

add_library(hdmap_ir_core
  core/ir/status.h
  core/ir/ids.h
  core/ir/lane.h
  core/ir/tile.h
  core/ir/catalog.h
  core/ir/catalog.cpp
  core/ir/builder.h
  core/ir/builder.cpp
)

target_link_libraries(hdmap_ir_core PUBLIC hdmap_geo)

target_include_directories(hdmap_ir_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include    # include/
    ${CMAKE_CURRENT_SOURCE_DIR}               # src/
)

target_compile_features(hdmap_ir_core PUBLIC cxx_std_17)