//
// Created by buaa-city on 2020/10/28.
//

#include "error.h"

std::set<int> errorLine;

void err::error(int lineNumber, char type) {
    if(!errorLine.count(lineNumber)){
        fileerr << lineNumber << " " << type << std::endl;
        errorLine.insert(lineNumber);
    }
    std::cout << "[error]:type[" << type << "]in line[" << lineNumber << "]!" << std::endl;
}