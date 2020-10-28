//
// Created by buaa-city on 2020/9/27.
//

#ifndef COMPILER_MIPS_LEXANALYSIS_H
#define COMPILER_MIPS_LEXANALYSIS_H

#include <string>
#include <vector>
#include "../includes/Token.h"
#include "../includes/MyType.h"
#include "../includes/Externs.h"
#include "../Error/error.h"


void LexAnalysis(const std::string &);

void printLexingDebug();

namespace Lexing{
    void error(int lineNum);
}

#endif //COMPILER_MIPS_LEXANALYSIS_H
