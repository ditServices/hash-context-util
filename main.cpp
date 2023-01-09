#include <iostream>
#include <xxhash.h>
#include <filesystem>
#include "cargs.h"

#include "xxhash_generator.h"
#include "md5_generator.h"

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

        { .identifier = 't',
          .access_letters = "t",
          .access_name = "hash-type",
          .value_name = "VALUE",
          .description = "set the hash type xxh or md5"
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

    xxhash_generator hash_gen_ctx;

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

    if(is_regular_file(config.source_file)) {
        int hash_status = hash_gen_ctx.calc_xxh(config.source_file);

        if (hash_status == 0) {
            cout << config.source_file.filename() << ": ";
            cout << setfill('0') << setw(16) << std::hex << hash_gen_ctx.get_hash() << std::endl;
        } else {
            cout << "Hash Calculation Error" << endl;
        }
    } else {
        cout << "Unable to read file or incorrect file / directory supplied" << endl;
    }

    return 0;
}
