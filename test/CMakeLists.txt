add_executable(test test_grid.cpp)

target_include_directories(test PUBLIC ${CMAKE_SORCE_DIR}/external)

target_link_libraries(test PUBLIC grid)