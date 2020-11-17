#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <Archiver.h>
#include <CLI.h>
#include "iostream"


void invalidArguments() {
    std::cerr << "Invalid arguments" << std::endl;
    exit(1);
}

void checkFiles(std::ifstream &fin, std::ofstream &fout) {
    if (fin.good() && fout.good()) return;
    if (!fin.good()) std::cerr << "Error when opening input file occurred" << std::endl;
    else fin.close();
    if (!fout.good()) std::cerr << "Error when opening output file occurred" << std::endl;
    else fout.close();
    exit(2);
}

int main(int argc, char **argv) {
    std::ios::sync_with_stdio(false);
    mode type_arch;
    std::string file, output;
    if (!CLI::parseArguments(argc, argv, type_arch, file, output)) {
        invalidArguments();
    }
    std::ifstream fin;
    std::ofstream fout;

    Archiver::Archiver archive;
    try {
        if (type_arch == COMPRESS) {
            fin = std::ifstream(file, std::ifstream::in);
            fout = std::ofstream(output, std::ofstream::binary);
            checkFiles(fin, fout);
            archive.createArchive(fin, fout);
        } else {
            fin = std::ifstream(file, std::ifstream::binary);
            fout = std::ofstream(output, std::ofstream::out);
            checkFiles(fin, fout);
            archive.unpackArchive(fin, fout);
        }
        std::cout << archive.getBeforSize() << '\n' << archive.getAfterSize() << '\n' << archive.getAdditSize()
                  << std::endl;
        fin.close();
        fout.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        fin.close();
        fout.close();
        return 1;
    }

    return 0;
}