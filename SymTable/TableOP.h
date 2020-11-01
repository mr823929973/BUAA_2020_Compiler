//
// Created by buaa-city on 2020/10/30.
//

#ifndef COMPILER_MIPS_TABLEOP_H
#define COMPILER_MIPS_TABLEOP_H

#endif //COMPILER_MIPS_TABLEOP_H

#include <vector>
#include "SymTable.h"


namespace table {

    void createTable(std::string name,VarType type);

    void deleteTable();

    void addToTable(Symbol *symbol);

    VarType getType(const std::string& name);

    void setType(const std::string& name);

    VarType getFunc(const std::string& name, const std::vector<VarType> &paraList);

    VarType getReturn();

}
