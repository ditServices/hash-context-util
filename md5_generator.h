//
// Created by Howard Colin on 04/01/2023.
//

#ifndef CONTEXT_HASH_MD5_GENERATOR_H
#define CONTEXT_HASH_MD5_GENERATOR_H

#include <filesystem>
#include <openssl/md5.h>

namespace fs = std::filesystem;

class md5_generator {
private:
    unsigned char digest[MD5_DIGEST_LENGTH];
public:
    int md5_generate(const fs::path& source);
};


#endif //CONTEXT_HASH_MD5_GENERATOR_H
