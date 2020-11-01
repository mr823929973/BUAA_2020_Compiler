//
// Created by buaa-city on 2020/10/28.
//

#include "error.h"

static std::map<int, char> errors;

void err::error(int lineNumber, char type) {
    errors.insert({lineNumber,type});
    std::cout << "[error]:type[" << type << "]in line[" << lineNumber << "]!" << std::endl;
}

void err::printErr() {
    for (auto & error : errors) {
        fileerr << error.first << " " << error.second << std::endl;
    }

}