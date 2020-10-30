//
// Created by buaa-city on 2020/10/30.
//

#ifndef COMPILER_MIPS_SYMTYPE_H
#define COMPILER_MIPS_SYMTYPE_H

enum class SymType{
    CONST,
    VAR,
    FUNC,
    ARRAY
};

enum class VarType {
    INT,
    CHAR,
    VOID
};


#endif //COMPILER_MIPS_SYMTYPE_H
