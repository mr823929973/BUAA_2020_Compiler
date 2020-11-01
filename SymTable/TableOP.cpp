//
// Created by buaa-city on 2020/10/30.
//


#include "TableOP.h"

#include <utility>
#include "../Error/error.h"

static std::vector<SymTable *> SymTableStack;

void table::createTable(std::string name, VarType type) {
    SymTableStack.push_back(new SymTable(std::move(name),type));
}

void table::deleteTable() {
    delete SymTableStack.back();
    SymTableStack.pop_back();
}

void table::addToTable(Symbol *symbol) {
    if (!SymTableStack.back()->addToTable(symbol->name, symbol)) {
        err::error(lineNum, 'b');
    }

}

VarType table::getType(const std::string &name) {
    Symbol *symbol = nullptr;
    int i = (int) SymTableStack.size() - 1;
    while (i >= 0 && symbol == nullptr) {
        symbol = SymTableStack[i]->getSym(name);
        i--;
    }
    if (symbol == nullptr) {
        err::error(lineNum, 'c');
        return VarType::VOID;
    }
    return symbol->varType;
}

void table::setType(const std::string &name) {
    Symbol *symbol = nullptr;
    int i = (int) SymTableStack.size() - 1;
    while (i >= 0 && symbol == nullptr) {
        symbol = SymTableStack[i]->getSym(name);
        i--;
    }
    if (symbol == nullptr) {
        err::error(lineNum, 'c');
    } else if (symbol->symType == SymType::CONST) {
        err::error(lineNum, 'j');
    }
}

VarType table::getFunc(const std::string &name, const std::vector<VarType> &paraList) {
    Symbol *symbol = nullptr;
    int i = (int) SymTableStack.size() - 1;
    while (i >= 0 && symbol == nullptr) {
        symbol = SymTableStack[i]->getSym(name);
        i--;
    }
    if (symbol == nullptr) {
        err::error(lineNum, 'c');
        return VarType::VOID;
    } else if (symbol->symType == SymType::FUNC) {
        if (paraList.size() != symbol->paraList->size()) err::error(lineNum, 'd');
        else
            for (i = 0; i < paraList.size(); i++) {
                if (paraList[i] != (symbol->paraList)->at(i)) err::error(lineNum, 'e');
            }
    }
    return symbol->varType;
}

VarType table::getReturn() {
    return SymTableStack.back()->type;
}




