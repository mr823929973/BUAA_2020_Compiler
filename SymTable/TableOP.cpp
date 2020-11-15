//
// Created by buaa-city on 2020/10/30.
//


#include "TableOP.h"

#include <utility>
#include "../Error/error.h"

static std::vector<SymTable *> SymTableStack;
std::map<std::string, SymTable *> SymTables;

void table::createTable(const std::string &name, VarType type) {
    if (!SymTables.count(name)) {
        auto *tmp = new SymTable(name, type);
        SymTables.insert(std::map<std::string, SymTable *>::value_type(name, tmp));
        SymTableStack.push_back(tmp);
    } else {
        SymTableStack.push_back(SymTables[name]);
    }
}

void table::deleteTable() {
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

void table::setOffset(const std::string &name, int offset) {
    SymTables[name]->offset = offset;
}

std::pair<std::string, int> table::getOffset(const std::string &name) {
    Symbol *symbol = nullptr;
    std::pair<std::string, unsigned> tmp;
    int i = (int) SymTableStack.size() - 1;
    while (i >= 0 && symbol == nullptr) {
        symbol = SymTableStack[i]->getSym(name);
        if (symbol != nullptr) {
            tmp.second = symbol->offset;
            if (SymTableStack[i]->name == ".global") {
                tmp.first = "$gp";
            } else {
                tmp.first = "$fp";
            }

        }
        i--;
    }
    return tmp;
}

std::string table::getFuncName() {
    return SymTableStack.back()->name;
}

int table::getFuncOffset(const std::string &name) {
    return SymTables[name]->offset;
}

Symbol *table::getSymbol(const std::string &name) {
    Symbol *symbol = nullptr;
    int i = (int) SymTableStack.size() - 1;
    while (i >= 0 && symbol == nullptr) {
        symbol = SymTableStack[i]->getSym(name);
        i--;
    }
    return symbol;
}






