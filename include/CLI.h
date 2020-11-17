#ifndef HW_03_CLI_H
#define HW_03_CLI_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

enum mode {
    COMPRESS,
    UNCOMPRESS,
    UNDEFINED
};

class CLI {

public:
    static bool parseArguments(int argc, char **argv,
                               mode &type_arch, std::string &file, std::string &output);

};

#endif //HW_03_CLI_H
