//
// Created by Howard Colin on 06/01/2023.
//

#include "../../md5_generator.h"
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int test_md5() {
    int err_code = 0;
    md5_generator md5_gen_ctx{};
    fs::path sample_file = "xxh_sample";

    unsigned char ref_digest[] = "\xd4\x1d\x8c\xd9\x8f\x00\xb2\x04\xe9\x80\x09\x98\xec\xf8\x42\x7e";

    if(md5_gen_ctx.md5_generate(sample_file) != 0) {
        return err_code + 1;
    }

    unsigned char *calculated_digest = md5_gen_ctx.get_digest();

    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(ref_digest[i]);
    }
    cout << endl;
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(calculated_digest[i]);
    }

    if(std::memcmp(calculated_digest, ref_digest , MD5_DIGEST_LENGTH) !=0){
        err_code = 1;
    };

    return err_code;
}

int main() {
    return test_md5();
}
