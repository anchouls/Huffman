#include <CLI.h>

bool CLI::parseArguments(int argc, char **argv, mode &type_arch, std::string &file, std::string &output) {
    type_arch = UNDEFINED;
    if (argc != 6)
        return false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0)
            type_arch = COMPRESS;
        else if (strcmp(argv[i], "-u") == 0)
            type_arch = UNCOMPRESS;
        else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
            file = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
            output = argv[++i];
        else return false;
    }
    return !(type_arch == UNDEFINED || file.empty() || output.empty());
}