//
// Created by buaa-city on 2020/9/30.
//

#ifndef COMPILER_MIPS_MYTYPE_H
#define COMPILER_MIPS_MYTYPE_H

#include <string>

inline bool isSpace(char tmp) {
    return tmp == ' ' || tmp == '\t' || tmp == '\n' || tmp == '\r';
}

inline bool isNextLine(char tmp) {
    return tmp == '\n';
}

inline bool isAlpha(char tmp) {
    return (tmp == '_') || (tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z');
}

inline bool isDigit(char tmp) {
    return (tmp >= '0' && tmp <= '9');
}

inline bool isPrint(char tmp) {
    return (tmp == 32) || (tmp == 33) || (tmp >= 35 && tmp <= 126);
}

inline char toLower(char tmp) {
    return (tmp >= 'A' && tmp <= 'Z') ? tmp + (char) 32 : tmp; /* NOLINT */
}

#endif //COMPILER_MIPS_MYTYPE_H
