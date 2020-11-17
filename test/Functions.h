#ifndef HW_03_FUNCTIONS_H
#define HW_03_FUNCTIONS_H

#include "Archiver.h"
#include "Huffman.h"
#include <sstream>
#include <cstring>

using std::stringstream;

std::string f(std::string inputStr) {
    Archiver::Archiver arh;
    stringstream input, buf, output;
    input << inputStr;
    arh.createArchive(input, buf);
    arh.unpackArchive(buf, output);
    return output.str();
}

std::string gen(int n) {
    stringstream s;
    for (int i = 0; i < n; i++) {
        s << (char) ((rand() % 57) + 65);
    }
    return s.str();

}

std::pair<int, int> Compression(std::string inputStr) {
    Archiver::Archiver arh;
    stringstream input, buf;
    input << inputStr;
    arh.createArchive(input, buf);
    return {arh.getBeforSize(), arh.getAfterSize() + arh.getAdditSize()};
}

#endif //HW_03_FUNCTIONS_H
