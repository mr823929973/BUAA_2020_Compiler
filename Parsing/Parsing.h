//
// Created by buaa-city on 2020/10/3.
//

#ifndef COMPILER_MIPS_PARSING_H
#define COMPILER_MIPS_PARSING_H

#include "../includes/Externs.h"
#include "ParsingException.h"

void ParsingAnalysis();

namespace Parsing {
    void getNextToken();
    void program();
}


#endif //COMPILER_MIPS_PARSING_H
