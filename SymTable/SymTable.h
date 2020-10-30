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

    explicit SymTable(std::string name);

    ~SymTable();

    bool addToTable(const std::string &name, Symbol *symbol);

    Symbol *getSym(const std::string &name);

};


#endif //COMPILER_MIPS_SYMTABLE_H
