//
// Created by buaa-city on 2020/11/13.
//

#ifndef COMPILER_MIPS_OPERATOR_H
#define COMPILER_MIPS_OPERATOR_H


#include <ostream>

enum class Operator {
    ASSIGN,
    FUNC,
    CALL,
    LOD,
    ADD,
    MINU,
    MULT,
    DIV,
    RET,
    SCANF,
    PRINTF,
    FUNC_END,
    END
};

std::ostream &operator<<(std::ostream &out, Operator &tmp);


#endif //COMPILER_MIPS_OPERATOR_H
