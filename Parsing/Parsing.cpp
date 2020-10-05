//
// Created by buaa-city on 2020/10/3.
//

#include "Parsing.h"

using namespace Parsing;
static std::vector<Token *>::iterator nextToken;

void ParsingAnalysis() {
    nextToken = tokens.begin() - 1;
    getNextToken();
    program();
}

void Parsing::getNextToken() {
    if (nextToken >= tokens.begin() && (*nextToken)->getTokenType() != (TokenType) -1) {
        fileout << *(*nextToken) << std::endl;
    }

    if (nextToken != tokens.end()) {
        nextToken++;
    }
}

void Parsing::program() {
    if ((*nextToken)->getTokenType() == TokenType::CONSTTK) {
        constDesc();
    }
    if ((*nextToken)->getTokenType() == TokenType::CHARTK
        || (*nextToken)->getTokenType() == TokenType::INTTK) {
        if ((nextToken + 2) < tokens.end() &&
            (*(nextToken + 2))->getTokenType() != TokenType::LPARENT) {
            varDesc();
        }
    }
    while ((*nextToken)->getTokenType() == TokenType::CHARTK
           || (*nextToken)->getTokenType() == TokenType::INTTK
           || (*nextToken)->getTokenType() == TokenType::VOIDTK) {
        if ((*nextToken)->getTokenType() == TokenType::CHARTK
            || (*nextToken)->getTokenType() == TokenType::INTTK) {
            returnFuncDesc();
        } else {
            if ((nextToken + 1) < tokens.end() &&
                (*(nextToken + 1))->getTokenType() == TokenType::MAINTK) {
                break;
            } else {
                voidFuncDesc();
            }
        }
    }
    mainFunc();
    getNextToken();
    fileout << "＜程序＞" << std::endl;
}

void Parsing::constDesc() {
    do {
        if ((*nextToken)->getTokenType() != TokenType::CONSTTK) {
            error();
        } else {
            getNextToken();
            constDef();
            if ((*nextToken)->getTokenType() != TokenType::SEMICN) {
                error();
            } else {
                getNextToken();
            }
        }
    } while ((*nextToken)->getTokenType() == TokenType::CONSTTK);
    fileout << "＜常量说明＞" << std::endl;
}

void Parsing::constDef() {
    if ((*nextToken)->getTokenType() == TokenType::INTTK) {
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
        getNextToken();
        integer();
        while ((*nextToken)->getTokenType() == TokenType::COMMA) {
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
            getNextToken();
            integer();
        }
    } else if ((*nextToken)->getTokenType() == TokenType::CHARTK) {
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::CHARCON) error();
        getNextToken();
        while ((*nextToken)->getTokenType() == TokenType::COMMA) {
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::CHARCON) error();
            getNextToken();
        }
    } else {
        error();
    }
    fileout << "＜常量定义＞" << std::endl;
}

int Parsing::integer() {
    int tmp = 1;
    if ((*nextToken)->getTokenType() == TokenType::PLUS) {
        getNextToken();
    } else if ((*nextToken)->getTokenType() == TokenType::MINU) {
        tmp = -1;
        getNextToken();
    }
    tmp = tmp * (int) unsignedInt();
    fileout << "＜整数＞" << std::endl;
    return tmp;
}

unsigned Parsing::unsignedInt() {
    if ((*nextToken)->getTokenType() != TokenType::INTCON) error();
    unsigned tmp = std::stoi((*nextToken)->getRawString());
    getNextToken();
    fileout << "＜无符号整数＞" << std::endl;
    return tmp;
}

void Parsing::varDesc() {
    do {
        if ((nextToken + 2) < tokens.end() &&
            (*(nextToken + 2))->getTokenType() == TokenType::LPARENT) {
            break;
        }
        varDef();
        if ((*nextToken)->getTokenType() != TokenType::SEMICN) error();
        getNextToken();
    } while ((*nextToken)->getTokenType() != TokenType::INTTK
             || ((*nextToken)->getTokenType() != TokenType::CHARTK));
    fileout << "＜变量说明＞" << std::endl;
}

void Parsing::varDef() {
    if (((nextToken + 2) < tokens.end() && (*(nextToken + 2))->getTokenType() == TokenType::ASSIGN)
        || ((nextToken + 5) < tokens.end() && (*(nextToken + 5))->getTokenType() == TokenType::ASSIGN)
        || ((nextToken + 8) < tokens.end() && (*(nextToken + 8))->getTokenType() == TokenType::ASSIGN)) {
        varDefInit();
    } else {
        varDefUnInit();
    }
    fileout << "＜变量定义＞" << std::endl;
}

void Parsing::varDefInit() {
    bool type;
    if ((*nextToken)->getTokenType() == TokenType::CHARTK) type = true;
    else if ((*nextToken)->getTokenType() == TokenType::INTTK) type = false;
    else error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
    getNextToken();
    if ((*nextToken)->getTokenType() == TokenType::ASSIGN) {
        getNextToken();
        bool tmp = constant();
        if (tmp != type) error();
    } else if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
        getNextToken();
        unsigned line = unsignedInt();
        if (line <= 0) error();
        if ((*nextToken)->getTokenType() != TokenType::RBRACK) error();
        getNextToken();
        if ((*nextToken)->getTokenType() == TokenType::ASSIGN) {
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
            getNextToken();
            bool tmp = constant();
            if (tmp != type) error();
            for (int i = 1; i < line; i++) {
                if ((*nextToken)->getTokenType() != TokenType::COMMA) error();
                getNextToken();
                tmp = constant();
                if (tmp != type) error();
            }
            if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
            getNextToken();
        } else if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
            getNextToken();
            unsigned column = unsignedInt();
            if (column <= 0) error();
            if ((*nextToken)->getTokenType() != TokenType::RBRACK) error();
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
            getNextToken();
            bool tmp = constant();
            if (tmp != type) error();
            for (int i = 1; i < column; i++) {
                if ((*nextToken)->getTokenType() != TokenType::COMMA) error();
                getNextToken();
                tmp = constant();
                if (tmp != type) error();
            }
            if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
            getNextToken();
            for (int j = 1; j < line; j++) {
                if ((*nextToken)->getTokenType() != TokenType::COMMA) error();
                getNextToken();
                if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
                getNextToken();
                tmp = constant();
                if (tmp != type) error();
                for (int i = 1; i < column; i++) {
                    if ((*nextToken)->getTokenType() != TokenType::COMMA) error();
                    getNextToken();
                    tmp = constant();
                    if (tmp != type) error();
                }
                if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
                getNextToken();
            }
            if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
            getNextToken();
        } else {
            error();
        }
    } else {
        error();
    }
    fileout << "＜变量定义及初始化＞" << std::endl;
}

bool Parsing::constant() {
    bool tmp;
    if ((*nextToken)->getTokenType() == TokenType::CHARCON) {
        tmp = true;
        getNextToken();
    } else {
        integer();
        tmp = false;
    }
    fileout << "＜常量＞" << std::endl;
    return tmp;
}

void Parsing::varDefUnInit() {
    if ((*nextToken)->getTokenType() != TokenType::CHARTK
        && (*nextToken)->getTokenType() != TokenType::INTTK) {
        error();
    }
    do {
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        getNextToken();
        if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
            getNextToken();
            unsigned tmp = unsignedInt();
            if (tmp <= 0) error();
            if ((*nextToken)->getTokenType() != TokenType::RBRACK) error();
            getNextToken();
            if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
                getNextToken();
                tmp = unsignedInt();
                if (tmp <= 0) error();
                if ((*nextToken)->getTokenType() != TokenType::RBRACK) error();
                getNextToken();
            }
        }
    } while ((*nextToken)->getTokenType() == TokenType::COMMA);
    fileout << "＜变量定义无初始化＞" << std::endl;
}

void Parsing::returnFuncDesc() {

}

void Parsing::voidFuncDesc() {

}

void Parsing::mainFunc() {

}

void Parsing::error() {

}





