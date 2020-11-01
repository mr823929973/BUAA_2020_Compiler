//
// Created by buaa-city on 2020/10/29.
//

#include "SymTable.h"
#include "../includes/MyType.h"
#include <utility>


bool SymTable::addToTable(const std::string &Aname, Symbol *symbol) {
    if (this->symbols.insert({toLower(Aname), symbol}).second) return true;
    else return false;
}

Symbol *SymTable::getSym(const std::string &Sname) {
    auto tmp = this->symbols.find(toLower(Sname));
    if (tmp == symbols.end()) {
        return nullptr;
    } else {
        return tmp->second;
    }
}

SymTable::~SymTable() {
    std::map<std::string, Symbol *>::iterator iter;
    for (iter = symbols.begin(); iter != symbols.end(); iter++) {
        delete iter->second;
    }
}

SymTable::SymTable(std::string name, VarType type) {
    this->name = std::move(name);
    this->type = type;
}

