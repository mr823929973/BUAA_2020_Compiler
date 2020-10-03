//
// Created by buaa-city on 2020/9/27.
//

#ifndef COMPILER_MIPS_LEXANALYSIS_H
#define COMPILER_MIPS_LEXANALYSIS_H

#include <string>
#include <vector>
#include "../includes/Token.h"
#include "../includes/MyType.h"
#include "LexingException.h"

extern std::vector<Token *> tokens;

void LexAnalysis(const std::string &);

void printLexingDebug();

#endif //COMPILER_MIPS_LEXANALYSIS_H
