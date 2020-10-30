//
// Created by buaa-city on 2020/10/29.
//

#include "SymTable.h"

#include <utility>


bool SymTable::addToTable(const std::string &name, Symbol *symbol) {
    if (this->symbols.insert({name, symbol}).second) return true;
    else return false;
}

Symbol *SymTable::getSym(const std::string &name) {
    auto tmp = this->symbols.find(name);
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

SymTable::SymTable(std::string name) {
    this->name = std::move(name);
}
