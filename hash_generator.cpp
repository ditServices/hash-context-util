//
// Created by Howard Colin on 04/01/2023.
//

#include "xxhash.h"
#include "hash_generator.h"

uint64_t hash_generator::calc_xxh(fs::path source) {
    size_t const bufferSize = 512;
    void * const buffer = malloc(bufferSize);
    if(buffer == nullptr) {
        free(buffer);
        return 0;
    }

    XXH64_state_t* const state = XXH64_createState();
    XXH64_hash_t const seed = 0;
    if(XXH64_reset(state, seed)) {
        free(buffer);
        return 0;
    }

    FILE *src = fopen(source.string().c_str(), "rb");
    if(!src) {
        free(buffer);
        return 0;
    }

    ssize_t bytes;
    while((bytes = fread(buffer, 1, bufferSize, src)) != 0) {
        if(bytes == 0) {
            free(buffer);
            return 0;
        }
        if(XXH64_update(state, buffer, bytes) == XXH_ERROR) {
            free(buffer);
            return 0;
        }
    }

    uint64_t digest = XXH64_digest(state);
    fclose(src);
    free(buffer);
    return digest;
}