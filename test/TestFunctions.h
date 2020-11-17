#ifndef HW_03_TESTFUNCTIONS_H
#define HW_03_TESTFUNCTIONS_H

#include "Archiver.h"
#include "Huffman.h"
#include <sstream>
#include "Functions.h"
#include <cstring>


TEST_CASE ("random testing") {
    for (int i = 0; i < 100; i++) {
        std::string input = gen(i * 123);
                CHECK(f(input) == input);
    }
}

TEST_CASE ("compression resting") {
    for (int i = 10; i < 100; i++) {
        std::pair<int, int> size = Compression(gen(i * 123));
                CHECK(size.second < size.first);
    }
}

TEST_CASE ("testing the same symbols") {
    std::string input = "aaaaaaaaaaaaaaaaaaaaaa";
            CHECK(f(input) == input);
    std::pair<int, int> size = Compression(input);
            CHECK(size.second < size.first);
}

TEST_CASE ("testing one symbol") {
    std::string input = "a";
            CHECK(f(input) == input);
    Archiver::Archiver arh;
    stringstream input1, buf;
    input1 << input;
    arh.createArchive(input1, buf);
            CHECK(arh.getBeforSize() == 1);
            CHECK(arh.getAfterSize() == 1);
}

TEST_CASE ("testing zero symbol") {
    std::string input = "";
            CHECK(f(input) == input);
    Archiver::Archiver arh;
    stringstream input1, buf;
    input1 << input;
    arh.createArchive(input1, buf);
            CHECK(arh.getBeforSize() == 0);
            CHECK(arh.getAfterSize() == 0);
}

TEST_CASE ("testing the alphabet") {
    std::string input = "abcdefghijklmnopqrstuvwxyz";
            CHECK(f(input) == input);
}

TEST_CASE ("testing strange symbols") {
    std::string input = "D○◘╚N╤A☼D○TN.ч☼╗ПР▐B8wzO§♫↨→↓♀♂◙";
            CHECK(f(input) == input);
}

TEST_CASE ("testing null") {
    std::string input = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
            CHECK(f(input) == input);
    Archiver::Archiver arh;
    stringstream input1, buf;
    input1 << input;
    arh.createArchive(input1, buf);
            CHECK(arh.getBeforSize() == 0);
            CHECK(arh.getAfterSize() == 0);
}

TEST_CASE ("BIG BIG BIG PIG test") {
    stringstream s;
    for (int i = 0; i < 1000000; i++) {
        s << "BIG BIG BIG PIG ";
    }
            CHECK(f(s.str()) == s.str());
    std::pair<int, int> size = Compression(s.str());
            CHECK(size.second < size.first);
}


TEST_CASE ("testing abacaba sequence") {
    std::string input = "abacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacab"
                        "ahabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabaca"
                        "baiabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabaca"
                        "bahabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacab"
                        "ajabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacaba"
                        "habacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabaia"
                        "bacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabahabac"
                        "abadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabakabacabad"
                        "abacabaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabahabacabadabac"
                        "abaeabacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabaiabacabadabacabae"
                        "abacabadabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabahabacabadabacabaeabaca"
                        "badabacabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabajabacabadabacabaeabacabadaba"
                        "cabafabacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabahabacabadabacabaeabacabadabacabafa"
                        "bacabadabacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabaiabacabadabacabaeabacabadabacabafabacabad"
                        "abacabaeabacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacabahabacabadabacabaeabacabadabacabafabacabadabacabae"
                        "abacabadabacabagabacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacaba";
            CHECK(f(input) == input);
    std::pair<int, int> size = Compression(input);
            CHECK(size.second < size.first);
}


#endif //HW_03_TESTFUNCTIONS_H
