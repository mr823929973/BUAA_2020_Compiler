//
// Created by buaa-city on 2020/11/13.
//

#ifndef COMPILER_MIPS_OPERATOR_H
#define COMPILER_MIPS_OPERATOR_H


#include <ostream>
#include <cassert>

enum class Operator {
    ASSIGN,
    FUNC,
    CALL,
    CALL_END,
    LOD,
    ADD,
    MINU,
    MULT,
    DIV,
    RET,
    SCANF,
    PRINTF,
    FUNC_END,
    END,
    ARRAY,
    IF,
    WHILE,
    FOR,
    SWITCH
};

std::ostream &operator<<(std::ostream &out, Operator &tmp);


#endif //COMPILER_MIPS_OPERATOR_H
