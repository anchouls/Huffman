cmake_minimum_required(VERSION 3.10)
project(hw_03)

set(CMAKE_CXX_STANDARD 14)

include_directories(include/)


add_executable(hw_03 src/main.cpp src/Archiver.cpp include/Archiver.h src/Huffman.cpp include/Huffman.h src/CLI.cpp include/CLI.h)


add_executable(test_hw_03 test/TestMain.cpp test/doctest.h src/Archiver.cpp include/Archiver.h src/Huffman.cpp include/Huffman.h test/TestFunctions.h test/Functions.h)

