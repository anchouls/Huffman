#ifndef HW_03_HUFFMAN_H
#define HW_03_HUFFMAN_H

#include <fstream>
#include <exception>
#include <string>
#include <map>

namespace HuffmanTree {

    class HuffmanTree {
    public:
        HuffmanTree();

        HuffmanTree(const std::map<char, int> &freq);

        ~HuffmanTree();


        class HuffmanNode {
            friend class HuffmanTree;

        public:
            HuffmanNode();

            HuffmanNode *down(bool edge) const;

            bool haveLeaf(bool edge) const;

            HuffmanNode *up() const;

            bool haveParent() const;

            bool isLeaf() const;

            char getValue() const;

        private:
            HuffmanNode(char value, HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent);

            int nextId() const;

            char _value;
            HuffmanNode *_left;
            HuffmanNode *_right;
            HuffmanNode *_p;
            int _id;
        };

        HuffmanNode *getNode(char symbol);

        HuffmanNode *getRoot();

    private:
        HuffmanNode *_root;
        std::map<char, HuffmanNode *> _pos;
    };

}

#endif //HW_03_HUFFMAN_H
