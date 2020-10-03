//
// Created by buaa-city on 2020/9/30.
//

#include "LexingException.h"

LexingException::LexingException() {
    this->lineNum = -1;
}

LexingException::LexingException(int lineNum) {
    this->lineNum = lineNum;
}

int LexingException::getLineNum() {
    return lineNum;
}
