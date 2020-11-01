//
// Created by buaa-city on 2020/10/28.
//

#ifndef COMPILER_MIPS_ERROR_H
#define COMPILER_MIPS_ERROR_H

#include "../includes/Externs.h"

namespace err {
    void error(int lineNumber, char type);

    void printErr();
};


#endif //COMPILER_MIPS_ERROR_H
