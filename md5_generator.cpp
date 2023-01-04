//
// Created by Howard Colin on 04/01/2023.
//

#include "md5_generator.h"

int md5_generator::md5_generate(const fs::path& source) {
    FILE *src;
    ssize_t BUFFERSIZE = 512;
    char buf[BUFFERSIZE];
    ssize_t bytes = 0;

    src = fopen(source.string().c_str(), "rb");
    if(!src) return 1;

    MD5_CTX c;
    MD5_Init(&c);

    while((bytes = fread(buf, 1, BUFFERSIZE, src)) != 0) {
        if(bytes == 0) return 1;
        MD5_Update(&c, buf, bytes);
    }

    MD5_Final(this->digest, &c);
    fclose(src);
    return 0;
}