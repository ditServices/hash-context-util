//
// Created by Howard Colin on 04/01/2023.
//

#ifndef CONTEXT_HASH_HASH_GENERATOR_H
#define CONTEXT_HASH_HASH_GENERATOR_H

#include <filesystem>

namespace fs = std::filesystem;

class hash_generator {
public:
    uint64_t calc_xxh(fs::path source);
};


#endif //CONTEXT_HASH_HASH_GENERATOR_H
