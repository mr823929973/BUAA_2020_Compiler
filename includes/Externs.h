//
// Created by buaa-city on 2020/10/3.
//

#ifndef COMPILER_MIPS_EXTERNS_H
#define COMPILER_MIPS_EXTERNS_H

#include <fstream>
#include <vector>
#include <set>
#include "Token.h"
#include "../SymTable/SymTable.h"

extern std::ofstream fileout;
extern std::ofstream fileerr;
extern std::ofstream MidCodeFile;
extern std::ofstream AssCodeFile;
extern std::vector<Token *> tokens;
extern int lineNum;

#endif //COMPILER_MIPS_EXTERNS_H
