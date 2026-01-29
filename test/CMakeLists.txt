if(BUILD_TESTING)
  add_executable(test_geo
    unit/geo/test_vec2.cpp
    unit/geo/test_segment.cpp
  )
  target_link_libraries(test_geo
    PRIVATE
      gtest_main
      hdmap_geo
  )
  target_compile_features(test_geo PRIVATE cxx_std_17)
  
  include(GoogleTest)
  gtest_discover_tests(test_geo
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DISCOVERY_TIMEOUT 30
  )
endif()