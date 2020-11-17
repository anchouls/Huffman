#ifndef HW_03_ARCHIVER_H
#define HW_03_ARCHIVER_H

#include <fstream>
#include <exception>
#include <string>
#include <map>
#include "Huffman.h"

namespace Archiver {

    class DecodingException : public std::exception {
    public:
        const char *what() const noexcept;
    };

    class Archiver {
    public:
        Archiver();

        void createArchive(std::istream &fin, std::ostream &fout);

        void unpackArchive(std::istream &fin, std::ostream &fout);

        int getBeforSize();

        int getAfterSize();

        int getAdditSize();

    private:

        void writeHeadBit(std::ostream &fout);

        void writeTailbit(std::ostream &fout, int bit);

        void genCode(std::ostream &fout, HuffmanTree::HuffmanTree::HuffmanNode *node);

        void writeAdditional(std::ostream &fout, const std::map<char, int> &freq);

        void readAdditional(std::istream &fin, std::map<char, int> &freq);

        int _before_size;
        int _after_size;
        int _additional_size;

        char buff = 0;
        int cur_pos = 0;
    };

}

#endif //HW_03_ARCHIVER_H
