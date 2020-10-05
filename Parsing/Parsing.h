//
// Created by buaa-city on 2020/10/3.
//

#ifndef COMPILER_MIPS_PARSING_H
#define COMPILER_MIPS_PARSING_H

#include "../includes/Externs.h"
#include "ParsingException.h"
#include <set>

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

    void defHead();

    void argList();

    void compState();

    void stateList();

    void statement();

    void loopState();

    void condition();

    void relationOp();

    void expression();

    void term();

    void stride();

    void condState();

    void returnFuncState();

    void voidFuncState();

    void assiState();

    void readState();

    void writeState();

    void switchState();

    void returnState();

    void voidFuncDesc();

    void mainFunc();

    void error();


}


#endif //COMPILER_MIPS_PARSING_H
