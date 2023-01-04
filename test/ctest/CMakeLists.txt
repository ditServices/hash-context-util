cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

add_executable(ctest_calc_xxhash ctest_calc_xxhash.cpp ../../hash_generator.cpp ../../hash_generator.h)
target_link_libraries(ctest_calc_xxhash LINK_PUBLIC xxHash::xxhash)

add_test(ctest_calc_xxhash_result ctest_calc_xxhash)

add_custom_command(
        TARGET ctest_calc_xxhash POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/xxh_sample
        ${CMAKE_CURRENT_BINARY_DIR}/xxh_sample)