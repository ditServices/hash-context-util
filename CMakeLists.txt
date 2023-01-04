cmake_minimum_required(VERSION 3.24)
project(context_hash)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
add_subdirectory(lib/cargs)
add_subdirectory(test/ctest)

option(BUILD_SHARED_LIBS "Build shared libs" OFF) #optional
add_subdirectory(lib/xxHash/cmake_unofficial lib/xxHash/build EXCLUDE_FROM_ALL)

set(OPENSSL_ROOT_DIR "lib/openssl")
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

add_executable(context_hash main.cpp xxhash_generator.cpp xxhash_generator.h md5_generator.cpp md5_generator.h)
target_link_libraries(context_hash LINK_PUBLIC xxHash::xxhash cargs OpenSSL::Crypto OpenSSL::SSL)
