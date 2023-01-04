#include <iostream>
#include <xxhash.h>
#include <filesystem>
#include "cargs.h"

#include "hash_generator.h"

namespace fs = std::filesystem;
using namespace std;

// option identifiers for cargs - command line argument parser.
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

// configuration variables for cargs, data is stored here when parsed.
struct configuration {
    fs::path source_file;
};

int main(int argc, char* argv[]) {
    char identifier;
    cag_option_context context;
    struct configuration config;

    hash_generator hash_gen_ctx;

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
        ::uint64_t result = hash_gen_ctx.calc_xxh(config.source_file);
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
