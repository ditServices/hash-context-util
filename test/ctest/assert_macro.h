//
// Created by Howard Colin on 04/01/2023.
//

#ifndef CONTEXT_HASH_ASSERT_MACRO_H
#define CONTEXT_HASH_ASSERT_MACRO_H

#include <iostream>
#include <sstream>

#define assertEqual( ... )               \
do {                                            \
    if( !( __VA_ARGS__ ) ) {                     \
        std::cerr << "Unit test assert [ " \
        << ( #__VA_ARGS__ )             \
        << " ] failed in line [ "       \
        << __LINE__                     \
        << " ] file [ "                 \
        << __FILE__ << " ]"             \
        << std::endl;                     \
        err_code = 1;                           \
    }                                            \
} while( false )

#endif //CONTEXT_HASH_ASSERT_MACRO_H
