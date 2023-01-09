//
// Created by Howard Colin on 04/01/2023.
//

#include "xxhash.h"
#include "xxhash_generator.h"

int xxhash_generator::calc_xxh(const fs::path& source) {
    size_t const bufferSize = 512;
    void * const buffer = malloc(bufferSize);
    if(buffer == nullptr) {
        free(buffer);
        return 1;
    }

    XXH64_state_t* const state = XXH64_createState();
    XXH64_hash_t const seed = 0;
    if(XXH64_reset(state, seed)) {
        free(buffer);
        return 1;
    }

    FILE *src = fopen(source.string().c_str(), "rb");
    if(!src) {
        free(buffer);
        return 1;
    }

    ssize_t bytes;
    while((bytes = fread(buffer, 1, bufferSize, src)) != 0) {
        if(bytes == 0) {
            free(buffer);
            return 1;
        }
        if(XXH64_update(state, buffer, bytes) == XXH_ERROR) {
            free(buffer);
            return 1;
        }
    }

    this->digest = XXH64_digest(state);
    fclose(src);
    free(buffer);
    return 0;
}

uint64_t xxhash_generator::get_hash() {
    return this->digest;
}
