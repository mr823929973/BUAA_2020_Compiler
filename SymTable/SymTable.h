//
// Created by buaa-city on 2020/10/29.
//

#ifndef COMPILER_MIPS_SYMTABLE_H
#define COMPILER_MIPS_SYMTABLE_H

#include <map>
#include <string>
#include <utility>
#include "Symbol.h"

class SymTable {
private:
    std::map<std::string, Symbol *> symbols;
public:
    std::string name;

    VarType type;

    int offset;

    SymTable(std::string name,VarType type);

    ~SymTable();

    bool addToTable(const std::string &name, Symbol *symbol);

    Symbol *getSym(const std::string &Sname);

};


#endif //COMPILER_MIPS_SYMTABLE_H
