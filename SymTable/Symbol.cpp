//
// Created by buaa-city on 2020/10/30.
//

#include "Symbol.h"


Symbol::Symbol(int offset, std::string name, VarType varType) {
    this->name = std::move(name);
    this->varType = varType;
    this->symType = SymType::VAR;
    this->dimension = 0;
    this->paraList = nullptr;
    this->offset = offset;
}

Symbol::Symbol(std::string name, VarType varType, SymType symType, int constValue) {
    this->name = std::move(name);
    this->varType = varType;
    this->symType = symType;
    this->dimension = 0;
    this->paraList = nullptr;
    this->constValue = constValue;
}

Symbol::Symbol(int offset, std::string name, VarType varType, int dimension) {
    this->name = std::move(name);
    this->varType = varType;
    this->symType = SymType::ARRAY;
    this->dimension = dimension;
    this->paraList = nullptr;
    this->offset = offset;
}

Symbol::Symbol(std::string name, VarType varType, std::vector<VarType> *paraList) {
    this->name = std::move(name);
    this->varType = varType;
    this->symType = SymType::FUNC;
    this->dimension = 0;
    this->paraList = paraList;
}

Symbol::~Symbol() {
    delete this->paraList;
}


