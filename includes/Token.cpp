//
// Created by buaa-city on 2020/9/27.
//

#include "Token.h"


Token::Token() {
    this->lineNum = -1;
    this->tokenType = static_cast<TokenType>(-1);
}

Token::Token(int lineNum, std::string rawString, TokenType tokenType) {
    this->lineNum = lineNum;
    this->rawString = std::move(rawString);
    this->tokenType = tokenType;
}

std::ostream &operator<<(std::ostream &out, Token &tmp) {
    out << tmp.tokenType << ' ' << tmp.rawString;
    return out;
}

int Token::getLineNum() const {
    return this->lineNum;
}

TokenType Token::getTokenType() {
    return this->tokenType;
}

std::string Token::getRawString() {
    return this->rawString;
}
