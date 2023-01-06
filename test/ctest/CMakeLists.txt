cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

add_executable(ctest_calc_xxhash ctest_calc_xxhash.cpp ../../xxhash_generator.cpp ../../xxhash_generator.h)
target_link_libraries(ctest_calc_xxhash LINK_PUBLIC xxHash::xxhash)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
add_executable(ctest_calc_md5 ctest_calc_md5.cpp ../../md5_generator.cpp ../../md5_generator.h)
target_link_libraries(ctest_calc_md5 OpenSSL::Crypto)

add_test(ctest_calc_xxhash_result ctest_calc_xxhash)
add_test(ctest_calc_md5_result ctest_calc_md5)

add_custom_command(
        TARGET ctest_calc_xxhash POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/xxh_sample
        ${CMAKE_CURRENT_BINARY_DIR}/xxh_sample)