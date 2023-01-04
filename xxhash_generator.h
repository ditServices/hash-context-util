//
// Created by Howard Colin on 04/01/2023.
//

#ifndef CONTEXT_HASH_XXHASH_GENERATOR_H
#define CONTEXT_HASH_XXHASH_GENERATOR_H

#include <filesystem>

namespace fs = std::filesystem;

class xxhash_generator {
public:
    static uint64_t calc_xxh(const fs::path& source);
};


#endif //CONTEXT_HASH_XXHASH_GENERATOR_H
