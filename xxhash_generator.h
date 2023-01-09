//
// Created by Howard Colin on 04/01/2023.
//

#ifndef CONTEXT_HASH_XXHASH_GENERATOR_H
#define CONTEXT_HASH_XXHASH_GENERATOR_H

#include <filesystem>

namespace fs = std::filesystem;

class xxhash_generator {
    uint64_t digest = 0;
public:
    int calc_xxh(const fs::path& source);
    uint64_t get_hash();
};


#endif //CONTEXT_HASH_XXHASH_GENERATOR_H
