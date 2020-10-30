//
// Created by buaa-city on 2020/9/27.
//

#ifndef COMPILER_MIPS_TOKEN_H
#define COMPILER_MIPS_TOKEN_H

#include <utility>
#include <string>
#include "TokenType.h"

class Token {
private:
    int lineNum;
    std::string rawString;
    TokenType tokenType;
public:
    Token();

    Token(int lineNum, std::string rawString, TokenType tokenType);

    TokenType getTokenType();

    int getLineNum() const;

    friend std::ostream &operator<<(std::ostream &out, Token &tmp);

    std::string getRawString();

};


#endif //COMPILER_MIPS_TOKEN_H
