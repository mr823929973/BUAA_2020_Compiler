//
// Created by buaa-city on 2020/10/3.
//

#ifndef COMPILER_MIPS_PARSING_H
#define COMPILER_MIPS_PARSING_H

#include "../includes/Externs.h"
#include "../includes/SymType.h"
#include "../includes/MyType.h"
#include "../SymTable/TableOP.h"
#include "../SymTable/Symbol.h"
#include "../Error/error.h"
#include "ParsingException.h"
#include "../MidCode/MidCodeOP.h"
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

    VarType constant();

    VarType constant(int &value);

    void varDefUnInit();

    void returnFuncDesc();

    std::pair<VarType, std::string> defHead();

    std::vector<std::pair<VarType, std::string>> argList();

    void compState();

    void stateList();

    void statement();

    void loopState();

    void condition(int &ret);

    void relationOp(int &ret);

    VarType expression(int &tmpVa);

    VarType term(int &tmpVa);

    VarType factor(int &tmpVa);

    void stride(u_int &tmp);

    void condState();

    VarType returnFuncState();

    std::vector<VarType> vaArgList();

    void voidFuncState();

    void assiState();

    void readState();

    void writeState();

    int strcon();

    void switchState();

    void caseList(VarType type,int& caseNum,int label);

    void caseState(VarType type,int& caseNum,int label);

    void defaultState(int &caseNum,int label);

    void returnState();

    void voidFuncDesc();

    void mainFunc();

    void error();

    void error(int line, char type);
}


#endif //COMPILER_MIPS_PARSING_H
