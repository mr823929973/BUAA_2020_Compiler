//
// Created by buaa-city on 2020/10/30.
//

#include "Symbol.h"


Symbol::Symbol(std::string name, VarType symType) {
    this->name = std::move(name);
    this->varType = symType;
    this->symType = SymType::VAR;
    this->dimension = 0;
    this->paraList = nullptr;
}

Symbol::Symbol(std::string name, VarType symType, SymType varType) {
    this->name = std::move(name);
    this->varType = symType;
    this->symType = varType;
    this->dimension = 0;
    this->paraList = nullptr;
}

Symbol::Symbol(std::string name, VarType symType, int dimension) {
    this->name = std::move(name);
    this->varType = symType;
    this->symType = SymType::ARRAY;
    this->dimension = dimension;
    this->paraList = nullptr;
}

Symbol::Symbol(std::string name, VarType symType, std::vector<SymType> *paraList) {
    this->name = std::move(name);
    this->varType = symType;
    this->symType = SymType::FUNC;
    this->dimension = 0;
    this->paraList = paraList;
}

Symbol::~Symbol() {
    delete this->paraList;
}


