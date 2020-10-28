//
// Created by buaa-city on 2020/10/3.
//

#ifndef COMPILER_MIPS_EXTERNS_H
#define COMPILER_MIPS_EXTERNS_H

#include <fstream>
#include <vector>
#include <set>
#include "Token.h"

extern std::ofstream fileout;
extern std::ofstream fileerr;
extern std::vector<Token *> tokens;
extern std::set<int> errorLine;

#endif //COMPILER_MIPS_EXTERNS_H
