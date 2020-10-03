//
// Created by buaa-city on 2020/9/30.
//

#ifndef COMPILER_MIPS_LEXINGEXCEPTION_H
#define COMPILER_MIPS_LEXINGEXCEPTION_H

#include <exception>

class LexingException : public std::exception {
private:
    int lineNum;

public:
    LexingException();

    explicit LexingException(int lineNum);

    int getLineNum();
};


#endif //COMPILER_MIPS_LEXINGEXCEPTION_H
