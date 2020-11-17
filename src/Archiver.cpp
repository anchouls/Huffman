#include <iostream>
#include <fstream>
#include <cstddef>
#include <set>
#include <Archiver.h>

namespace Archiver {


    const char *DecodingException::what() const noexcept {
        return "Error when unpacking archive occurred";
    }

    Archiver::Archiver() : _before_size(0), _after_size(0), _additional_size(0) {}

    void Archiver::createArchive(std::istream &fin, std::ostream &fout) {
        fin.seekg(0, fin.end);
        int len = _before_size = fin.tellg();
        fin.seekg(0, fin.beg);
        std::map<char, int> freq;
        char symbol;
        for (int i = 0; i < len; i++) {
            fin.get(symbol);
            freq[symbol]++;
        }
        HuffmanTree::HuffmanTree tree(freq);
        writeAdditional(fout, freq);
        fout.write((char *) &len, sizeof(int));
        _additional_size += sizeof(int);
        fin.seekg(0, fin.beg);
        for (int i = 0; i < len; i++) {
            fin.get(symbol);
            genCode(fout, tree.getNode(symbol));
        }
        writeHeadBit(fout);
    }

    void Archiver::unpackArchive(std::istream &fin, std::ostream &fout) {
        std::map<char, int> freq;
        readAdditional(fin, freq);
        HuffmanTree::HuffmanTree tree(freq);
        HuffmanTree::HuffmanTree::HuffmanNode *node = tree.getRoot();
        int len;
        fin.read((char *) &len, sizeof(int));
        _additional_size += sizeof(int);
        char byte;
        while (len) {
            if (!fin.good()) throw DecodingException();
            _before_size++;
            fin.read(&byte, 1);
            for (int i = 0; i < 8 && len; i++) {
                int bit = (byte & (1 << i)) > 0;
                if (!node->haveLeaf(bit) && !node->isLeaf()) throw DecodingException();
                if (!node->haveLeaf(bit)) node = tree.getRoot();
                node = node->down(bit);
                if (node->isLeaf()) {
                    fout.put(node->getValue());
                    _after_size++;
                    len--;
                }
            }
        }
    }

    void Archiver::writeAdditional(std::ostream &fout, const std::map<char, int> &freq) {
        int size = freq.size();
        fout.write((char *) &size, sizeof(int));
        for (auto &symbol : freq) {
            fout.write(&symbol.first, 1);
            fout.write((char *) &symbol.second, sizeof(int));
        }
        _additional_size += size * 5 + 4;
    }


    void Archiver::genCode(std::ostream &fout, HuffmanTree::HuffmanTree::HuffmanNode *node) {
        if (!node->haveParent()) return;
        genCode(fout, node->up());
        writeTailbit(fout, node->up()->down(0) == node ? 0 : 1);
    }

    void Archiver::readAdditional(std::istream &fin, std::map<char, int> &freq) {
        int size, count;
        char symbol;
        fin.read((char *) &size, sizeof(int));
        for (int i = 0; i < size; i++) {
            fin.read(&symbol, 1);
            fin.read((char *) &count, sizeof(int));
            freq[symbol] = count;
        }
        _additional_size = size * 5 + 4;
    }

    void Archiver::writeHeadBit(std::ostream &fout) {
        if (cur_pos) {
            fout.write(&buff, 1);
            _after_size++;
        }
    }

    void Archiver::writeTailbit(std::ostream &fout, int bit) {
        buff |= bit << cur_pos;
        cur_pos = (cur_pos + 1) & 7;
        if (!cur_pos) {
            fout.write(&buff, 1);
            _after_size++;
            buff = 0;
        }
    }

    int Archiver::getBeforSize() {
        return _before_size;
    }

    int Archiver::getAfterSize() {
        return _after_size;
    }

    int Archiver::getAdditSize() {
        return _additional_size;
    }
}