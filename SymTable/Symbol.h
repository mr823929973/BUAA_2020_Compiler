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
    /* TO DO
     * int value;
     * int length;
     * int wide;
     * std::map<int,int> *
     * std::map<std::pair<int,int>,int> *
     * ......
     */
    std::string name;
    VarType varType;
    SymType symType;
    int dimension;
    std::vector<SymType> *paraList;

    Symbol(std::string name, VarType symType);

    Symbol(std::string name, VarType symType, SymType varType);

    Symbol(std::string name, VarType symType, int dimension);

    Symbol(std::string name, VarType symType, std::vector<SymType> *paraList);

    ~Symbol();


};


#endif //COMPILER_MIPS_SYMBOL_H
