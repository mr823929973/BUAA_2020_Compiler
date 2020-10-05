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

    void constDesc();

    void constDef();

    int integer();

    unsigned unsignedInt();

    void varDesc();

    void varDef();

    void varDefInit();

    bool constant();

    void varDefUnInit();

    void returnFuncDesc();

    void voidFuncDesc();

    void mainFunc();

    void error();


}


#endif //COMPILER_MIPS_PARSING_H
