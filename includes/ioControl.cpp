//
// Created by buaa-city on 2020/9/27.
//

#include "ioControl.h"

const std::string inputFile = "testfile.txt";/* NOLINT */
const std::string outputFile = "output.txt";/* NOLINT */
const std::string midCodeFile = "mid.txt";/* NOLINT */
const std::string assCodeFile = "mips.txt";/* NOLINT */
const std::string errFile = "error.txt";/* NOLINT */

std::string read() {
    std::ifstream t(inputFile);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    return str;
}

std::ofstream fileout = std::ofstream(outputFile, std::ios::out | std::ios::trunc);/* NOLINT */
std::ofstream fileerr = std::ofstream(errFile, std::ios::out | std::ios::trunc);/* NOLINT */
std::ofstream MidCodeFile = std::ofstream(midCodeFile, std::ios::out | std::ios::trunc);/* NOLINT */
std::ofstream AssCodeFile = std::ofstream(assCodeFile, std::ios::out | std::ios::trunc);/* NOLINT */