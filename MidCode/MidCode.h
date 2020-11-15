//
// Created by buaa-city on 2020/11/13.
//

#ifndef COMPILER_MIPS_MIDCODE_H
#define COMPILER_MIPS_MIDCODE_H

#include <string>
#include "Operator.h"
#include "../SymTable/TableOP.h"
#include "../includes/Externs.h"

class MidCode {
public:
    Operator op;
    std::string srcA;
    std::string srcB;
    std::string srcC;

    MidCode(Operator op, std::string srcA, std::string srcB, std::string srcC);

    void toAssCode() const;

    friend std::ostream &operator<<(std::ostream &out, MidCode &tmp);
};


#endif //COMPILER_MIPS_MIDCODE_H
