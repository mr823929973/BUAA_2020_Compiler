//
// Created by buaa-city on 2020/10/30.
//

#ifndef COMPILER_MIPS_SYMBOL_H
#define COMPILER_MIPS_SYMBOL_H


#include <string>
#include <vector>
#include <utility>
#include "../includes/SymType.h"

class Symbol {
public:
    /*
     * TODO
     * int value;
     * int length;
     * int wide
     * ......
     */
    std::string name;
    VarType varType;
    SymType symType;
    int dimension;
    std::vector<VarType> *paraList;
    unsigned offset;
    int constValue;

    Symbol(int offset,std::string name, VarType symType);

    Symbol(std::string name, VarType symType, SymType varType,int constValue);

    Symbol(std::string name, VarType symType, int dimension);

    Symbol(std::string name, VarType symType, std::vector<VarType> *paraList);

    ~Symbol();


};


#endif //COMPILER_MIPS_SYMBOL_H
