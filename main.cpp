#include <iostream>
#include <xxhash.h>
#include <filesystem>
#include "cargs.h"

namespace fs = std::filesystem;
using namespace std;

uint64_t calc_xxh(fs::path source);

static struct cag_option options[] {
        {   .identifier = 's',
                 .access_letters = "s",
                 .access_name = "src",
                 .value_name = "VALUE",
                 .description = "Path to source file that will be processed"
        },

        {.identifier = 'h',
         .access_name = "help",
         .description = "Shows the commands help information."}
};

struct configuration {
    fs::path source_file;
};

int main(int argc, char* argv[]) {
    char identifier;
    cag_option_context context;
    struct configuration config;

    cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);

    while (cag_option_fetch(&context)) {
        identifier = cag_option_get(&context);
        switch (identifier) {
            case 's':
                config.source_file = cag_option_get_value(&context);
                break;
            case 'h':
                cout << "Usage: gen_hash [OPTION]..." << endl;
                cout << "Generates the xxHash checksum of a single file" << endl;
                cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
                return EXIT_SUCCESS;
            default:
                cout << "ERROR: Invalid option flag(s) entered" << endl;
                return EXIT_FAILURE;
        }
    }

    if(is_regular_file(config.source_file)){
        ::uint64_t result = calc_xxh(config.source_file);
        if(result != 0) {
            cout << config.source_file.filename() << ": ";
            cout << setfill('0') << setw(16) << std::hex << result << std::endl;
        } else {
            cout << "Hash / File Error" << endl;
        }
    } else {
        cout << "ERROR: Invalid or unable to read source file" << endl;
    }

    return 0;
}

uint64_t calc_xxh(fs::path source) {
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