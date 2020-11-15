//
// Created by buaa-city on 2020/11/14.
//

#ifndef COMPILER_MIPS_MIDCODEOP_H
#define COMPILER_MIPS_MIDCODEOP_H

#include <vector>
#include "MidCode.h"
#include "../includes/MyType.h"
#include "../includes/Externs.h"
#include "../SymTable/TableOP.h"


namespace MidCodeOP {
    void addMidCode(MidCode *midCode);

    int addStrcon(const std::string&);

    void printMidCode();

    void printAssCode();
}


#endif //COMPILER_MIPS_MIDCODEOP_H
