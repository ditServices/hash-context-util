#include <iostream>
#include <filesystem>
#include "cargs.h"

#include "xxhash_generator.h"
#include "md5_generator.h"

namespace fs = std::filesystem;
using namespace std;

// option identifiers for cargs - command line argument parser.
static struct cag_option options[]{
        {.identifier = 's',
                .access_letters = "s",
                .access_name = "src",
                .value_name = "VALUE",
                .description = "Path to source file that will be processed"
        },

        {.identifier = 'x',
               // .access_letters = "x",
                .access_name = "xxh",
                .description = "Set the hash type to xxHash"
        },

        {.identifier = 'm',
                //.access_letters = "m",
                .access_name = "md5",
                .description = "Set the hash type to MD5"},

        {.identifier = 'h',
                .access_name = "help",
                .description = "Shows the commands help information."}
};

// configuration variables for cargs, data is stored here when parsed.
struct configuration {
    fs::path source_file;
    bool is_md5 = false;
    bool is_xxHash = true; //default if no choice is made
};

int main(int argc, char *argv[]) {
    //cargs argument parser pre-amble declarations
    char identifier;
    cag_option_context context;
    struct configuration config;
    cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);

    //cargs arg parser switch statement.
    while (cag_option_fetch(&context)) {
        identifier = cag_option_get(&context);
        switch (identifier) {
            case 's':
                config.source_file = cag_option_get_value(&context);
                break;
            case 'x':
                config.is_xxHash = true;
                break;
            case 'm':
                config.is_md5 = true;
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

    //declare our checksum generator objects
    xxhash_generator hash_gen_ctx;
    md5_generator md5_gen_ctx;

    if (is_regular_file(config.source_file)) {
        int hash_status;

        if(config.is_md5)
            hash_status = md5_gen_ctx.md5_generate(config.source_file);
        else {
            hash_status = hash_gen_ctx.calc_xxh(config.source_file);
        }

        // results all ok
        if (hash_status == 0) {
            cout << config.source_file.filename() << ": ";

            //display md5 output
            if(config.is_md5) {
                unsigned char *calculated_digest = md5_gen_ctx.get_digest();
                for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
                    std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(calculated_digest[i]);
                }
                cout << endl;
            }
            else {
                cout << setfill('0') << setw(16) << std::hex << hash_gen_ctx.get_hash() << std::endl;
            }
        }
        else {  // results not ok
            cout << "Hash Calculation Error" << endl;
        }

    } else {
        cout << "Unable to read file or incorrect file / directory supplied" << endl;
    }

    return 0;
}
