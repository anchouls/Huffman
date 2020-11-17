#include <set>

#include "Huffman.h"

namespace HuffmanTree {

    HuffmanTree::HuffmanTree() {
        _root = new HuffmanNode();
    }

    HuffmanTree::HuffmanTree(const std::map<char, int> &freq) {
        auto compare = [](const std::pair<int, HuffmanNode *> &a, const std::pair<int, HuffmanNode *> &b) -> bool {
            if (a.first != b.first) return a.first < b.first;
            return a.second->_id < b.second->_id;
        };

        std::set<std::pair<int, HuffmanNode *>, decltype(compare)> rep(compare);
        for (auto &symbol : freq) {
            auto *node = new HuffmanNode(symbol.first, nullptr, nullptr, nullptr);
            _pos[symbol.first] = node;
            rep.insert({symbol.second, node});
        }
        switch (rep.size()) {
            case 0:
                _root = new HuffmanNode();
                break;
            case 1: {
                _root = new HuffmanNode();
                _root->_left = rep.begin()->second;
                _root->_left->_p = _root;
                break;
            }
            default:
                while (rep.size() > 1) {
                    auto l = *rep.begin();
                    rep.erase(rep.begin());
                    auto r = *rep.begin();
                    rep.erase(rep.begin());
                    auto *node = new HuffmanNode(0, l.second, r.second, nullptr);
                    rep.insert({l.first + r.first, node});
                }
                _root = rep.begin()->second;
                break;
        }
    }

    HuffmanTree::~HuffmanTree() {
        HuffmanNode *node = _root;
        while (true) {
            if (node->haveLeaf(false)) {
                node = node->down(false);
                continue;
            }
            if (node->haveLeaf(true)) {
                node = node->down(true);
                continue;
            }
            if (!node->haveParent()) break;
            HuffmanNode *par = node->up();
            node == par->down(false) ? par->_left = nullptr : par->_right = nullptr;
            delete node;
            node = par;
        }
        delete _root;
    }


    HuffmanTree::HuffmanNode *HuffmanTree::getNode(char symbol) {
        return _pos[symbol];
    }

    HuffmanTree::HuffmanNode *HuffmanTree::getRoot() {
        return _root;
    }

    HuffmanTree::HuffmanNode::HuffmanNode() : _value(0), _left(nullptr), _right(nullptr), _p(nullptr) {
        _id = nextId();
    }

    HuffmanTree::HuffmanNode::HuffmanNode(char value, HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent)
            : _value(
            value), _left(left), _right(right), _p(parent) {
        if (_left) _left->_p = this;
        if (_right) _right->_p = this;
        _id = nextId();
    }

    int HuffmanTree::HuffmanNode::nextId() const {
        static int GLOBAL_ID = 0;
        return GLOBAL_ID++;
    }

    HuffmanTree::HuffmanNode *HuffmanTree::HuffmanNode::down(bool edge) const {
        return edge ? _right : _left;
    }

    bool HuffmanTree::HuffmanNode::haveLeaf(bool edge) const {
        return edge ? _right : _left;
    }

    HuffmanTree::HuffmanNode *HuffmanTree::HuffmanNode::up() const {
        return _p;
    }

    bool HuffmanTree::HuffmanNode::haveParent() const {
        return _p;
    }

    bool HuffmanTree::HuffmanNode::isLeaf() const {
        return !_left && !_right;
    }


    char HuffmanTree::HuffmanNode::getValue() const {
        return _value;
    }


}