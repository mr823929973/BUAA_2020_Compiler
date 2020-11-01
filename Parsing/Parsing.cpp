//
// Created by buaa-city on 2020/10/3.
//

#include "Parsing.h"

using namespace Parsing;
static std::vector<Token *>::iterator nextToken;
int lineNum = 0;
int returnCount = 0;

void ParsingAnalysis() {
    nextToken = tokens.begin();
    getNextToken();
    program();
}

void Parsing::getNextToken() {
    if (nextToken > tokens.begin() && (*nextToken)->getTokenType() != (TokenType) -1) {
        fileout << *(*nextToken) << std::endl;
        lineNum = (*nextToken)->getLineNum();
    }

    if (nextToken != tokens.end()) {
        nextToken++;
    }
}

void Parsing::program() {
    table::createTable("", VarType::VOID);
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
    fileout << "<程序>" << std::endl;
    table::deleteTable();
}

void Parsing::constDesc() {
    do {
        if ((*nextToken)->getTokenType() != TokenType::CONSTTK) {
            error();
        } else {
            getNextToken();
            constDef();
            if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
            else getNextToken();
        }
    } while ((*nextToken)->getTokenType() == TokenType::CONSTTK);
    fileout << "<常量说明>" << std::endl;
}

void Parsing::constDef() {
    std::string name;
    if ((*nextToken)->getTokenType() == TokenType::INTTK) {
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        name = toLower((*nextToken)->getRawString());
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
        getNextToken();
        integer();
        table::addToTable(new Symbol(name, VarType::INT, SymType::CONST));
        while ((*nextToken)->getTokenType() == TokenType::COMMA) {
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
            name = toLower((*nextToken)->getRawString());
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
            getNextToken();
            integer();
            table::addToTable(new Symbol(name, VarType::INT, SymType::CONST));
        }
    } else if ((*nextToken)->getTokenType() == TokenType::CHARTK) {
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        name = toLower((*nextToken)->getRawString());
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::CHARCON) error();
        getNextToken();
        table::addToTable(new Symbol(name, VarType::CHAR, SymType::CONST));
        while ((*nextToken)->getTokenType() == TokenType::COMMA) {
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
            name = toLower((*nextToken)->getRawString());
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::CHARCON) error();
            getNextToken();
            table::addToTable(new Symbol(name, VarType::CHAR, SymType::CONST));
        }
    } else {
        error();
    }
    fileout << "<常量定义>" << std::endl;
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
    fileout << "<整数>" << std::endl;
    return tmp;
}

unsigned Parsing::unsignedInt() {
    if ((*nextToken)->getTokenType() != TokenType::INTCON) error();
    unsigned tmp = std::stoi((*nextToken)->getRawString());
    getNextToken();
    fileout << "<无符号整数>" << std::endl;
    return tmp;
}

void Parsing::varDesc() {
    do {
        if ((nextToken + 2) < tokens.end() &&
            (*(nextToken + 2))->getTokenType() == TokenType::LPARENT) {
            break;
        }
        varDef();
        if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
        else getNextToken();
    } while ((*nextToken)->getTokenType() == TokenType::INTTK
             || ((*nextToken)->getTokenType() == TokenType::CHARTK));
    fileout << "<变量说明>" << std::endl;
}

void Parsing::varDef() {
    if ((nextToken + 2) < tokens.end() && (*(nextToken + 2))->getTokenType() != TokenType::LBRACK) {
        if ((nextToken + 2) < tokens.end() && (*(nextToken + 2))->getTokenType() == TokenType::ASSIGN) {
            varDefInit();
        } else {
            varDefUnInit();
        }
    } else {
        if ((nextToken + 5) < tokens.end() && (((*(nextToken + 5))->getTokenType() != TokenType::LBRACK)
                                               && (*(nextToken + 4))->getTokenType() != TokenType::LBRACK))
            if ((nextToken + 5) < tokens.end() && ((*(nextToken + 5))->getTokenType() == TokenType::ASSIGN
                                                   || (*(nextToken + 4))->getTokenType() == TokenType::ASSIGN)) {
                varDefInit();
            } else {
                varDefUnInit();
            }
        else {
            if ((nextToken + 8) < tokens.end() && ((*(nextToken + 8))->getTokenType() == TokenType::ASSIGN
                                                   || ((*(nextToken + 7))->getTokenType() == TokenType::ASSIGN))) {
                varDefInit();
            } else {
                varDefUnInit();
            }
        }
    }
    fileout << "<变量定义>" << std::endl;
}

void Parsing::varDefInit() {
    VarType type;
    std::string name;
    if ((*nextToken)->getTokenType() == TokenType::CHARTK) type = VarType::CHAR;
    else if ((*nextToken)->getTokenType() == TokenType::INTTK) type = VarType::INT;
    else error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
    name = toLower((*nextToken)->getRawString());
    getNextToken();
    if ((*nextToken)->getTokenType() == TokenType::ASSIGN) {
        getNextToken();
        VarType tmp = constant();
        if (tmp != type) error(lineNum, 'o');
        table::addToTable(new Symbol(name, type));
    } else if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
        getNextToken();
        unsigned line = unsignedInt();
        if (line <= 0) error();
        if ((*nextToken)->getTokenType() != TokenType::RBRACK) error(lineNum, 'm');
        else getNextToken();
        if ((*nextToken)->getTokenType() == TokenType::ASSIGN) {
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
            int i = 0;
            do {
                getNextToken();
                if (constant() != type) error(lineNum, 'o');
                i++;
            } while ((*nextToken)->getTokenType() == TokenType::COMMA);
            if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
            if (i != line) error(lineNum, 'n');
            getNextToken();
            table::addToTable(new Symbol(name, type, 1));
        } else if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
            getNextToken();
            unsigned column = unsignedInt();
            if (column <= 0) error();
            if ((*nextToken)->getTokenType() != TokenType::RBRACK) error(lineNum, 'm');
            else getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
            int i = 0;
            do {
                int j = 0;
                getNextToken();
                if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
                do {
                    getNextToken();
                    if (constant() != type) error(lineNum, 'o');
                    j++;
                } while ((*nextToken)->getTokenType() == TokenType::COMMA);
                if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
                if (j != column) error(lineNum, 'n');
                getNextToken();
                i++;
            } while ((*nextToken)->getTokenType() == TokenType::COMMA);
            if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
            if (i != line) error(lineNum, 'n');
            getNextToken();
            table::addToTable(new Symbol(name, type, 2));
        } else {
            error();
        }
    } else {
        error();
    }
    fileout << "<变量定义及初始化>" << std::endl;
}

VarType Parsing::constant() {
    VarType tmp;
    if ((*nextToken)->getTokenType() == TokenType::CHARCON) {
        tmp = VarType::CHAR;
        getNextToken();
    } else {
        integer();
        tmp = VarType::INT;
    }
    fileout << "<常量>" << std::endl;
    return tmp;
}

void Parsing::varDefUnInit() {
    std::string name;
    VarType type;
    if ((*nextToken)->getTokenType() == TokenType::CHARTK) {
        type = VarType::CHAR;
    } else if ((*nextToken)->getTokenType() == TokenType::INTTK) {
        type = VarType::INT;
    } else {
        error();
    }
    do {
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        name = toLower((*nextToken)->getRawString());
        getNextToken();
        if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
            getNextToken();
            unsigned tmp = unsignedInt();
            if (tmp <= 0) error();
            if ((*nextToken)->getTokenType() != TokenType::RBRACK) error(lineNum, 'm');
            else getNextToken();
            if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
                getNextToken();
                tmp = unsignedInt();
                if (tmp <= 0) error();
                if ((*nextToken)->getTokenType() != TokenType::RBRACK) error(lineNum, 'm');
                else getNextToken();
                table::addToTable(new Symbol(name, type, 2));
            } else {
                table::addToTable(new Symbol(name, type, 1));
            }
        } else {
            table::addToTable(new Symbol(name, type));
        }
    } while ((*nextToken)->getTokenType() == TokenType::COMMA);
    fileout << "<变量定义无初始化>" << std::endl;
}

void Parsing::returnFuncDesc() {
    returnCount = 0;
    std::pair<VarType, std::string> tmp = defHead();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    std::vector<std::pair<VarType, std::string>> vec = argList();
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    auto *paraList = new std::vector<VarType>();
    for (const std::pair<VarType, std::string> &a :vec) {
        paraList->push_back(a.first);
    }
    table::addToTable(new Symbol(tmp.second, tmp.first, paraList));
    table::createTable(tmp.second, tmp.first);
    for (const std::pair<VarType, std::string> &a :vec) {
        table::addToTable(new Symbol(a.second, a.first));
    }
    if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
    getNextToken();
    compState();
    if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
    getNextToken();
    if (returnCount <= 0) error(lineNum, 'h');
    returnCount = 0;
    table::deleteTable();
    fileout << "<有返回值函数定义>" << std::endl;
}

std::pair<VarType, std::string> Parsing::defHead() {
    std::pair<VarType, std::string> tmp;
    if ((*nextToken)->getTokenType() == TokenType::INTTK) {
        tmp.first = VarType::INT;
    } else if ((*nextToken)->getTokenType() == TokenType::CHARTK) {
        tmp.first = VarType::CHAR;
    } else {
        error();
    }
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
    tmp.second = toLower((*nextToken)->getRawString());
    //   returnFunc.insert((*nextToken)->getRawString());
    getNextToken();
    fileout << "<声明头部>" << std::endl;
    return tmp;
}

std::vector<std::pair<VarType, std::string>> Parsing::argList() {
    std::vector<std::pair<VarType, std::string>> vector;
    std::pair<VarType, std::string> tmp;
    if ((*nextToken)->getTokenType() == TokenType::CHARTK
        || (*nextToken)->getTokenType() == TokenType::INTTK) {
        if ((*nextToken)->getTokenType() == TokenType::CHARTK) {
            tmp.first = VarType::CHAR;
        } else {
            tmp.first = VarType::INT;
        }
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        tmp.second = toLower((*nextToken)->getRawString());
        getNextToken();
        vector.push_back(tmp);
        while ((*nextToken)->getTokenType() == TokenType::COMMA) {
            getNextToken();
            if ((*nextToken)->getTokenType() == TokenType::CHARTK) {
                tmp.first = VarType::CHAR;
            } else if ((*nextToken)->getTokenType() == TokenType::INTTK) {
                tmp.first = VarType::INT;
            } else {
                error();
            }
            getNextToken();
            if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
            tmp.second = toLower((*nextToken)->getRawString());
            getNextToken();
            vector.push_back(tmp);
        }
    }
    fileout << "<参数表>" << std::endl;
    return vector;
}

void Parsing::compState() {
    if ((*nextToken)->getTokenType() == TokenType::CONSTTK) {
        constDesc();
    }
    if ((*nextToken)->getTokenType() == TokenType::CHARTK
        || (*nextToken)->getTokenType() == TokenType::INTTK) {
        varDesc();
    }
    stateList();
    fileout << "<复合语句>" << std::endl;
}

void Parsing::stateList() {
    while ((*nextToken)->getTokenType() == TokenType::WHILETK
           || (*nextToken)->getTokenType() == TokenType::FORTK
           || (*nextToken)->getTokenType() == TokenType::IFTK
           || (*nextToken)->getTokenType() == TokenType::SCANFTK
           || (*nextToken)->getTokenType() == TokenType::PRINTFTK
           || (*nextToken)->getTokenType() == TokenType::SWITCHTK
           || (*nextToken)->getTokenType() == TokenType::LBRACE
           || (*nextToken)->getTokenType() == TokenType::RETURNTK
           || (*nextToken)->getTokenType() == TokenType::IDENFR
           || (*nextToken)->getTokenType() == TokenType::SEMICN) {
        statement();
    }
    fileout << "<语句列>" << std::endl;
}

void Parsing::statement() {
    if ((*nextToken)->getTokenType() == TokenType::WHILETK
        || (*nextToken)->getTokenType() == TokenType::FORTK) {
        loopState();
    } else if ((*nextToken)->getTokenType() == TokenType::IFTK) {
        condState();
    } else if ((*nextToken)->getTokenType() == TokenType::SCANFTK) {
        readState();
        if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
        else getNextToken();
    } else if ((*nextToken)->getTokenType() == TokenType::PRINTFTK) {
        writeState();
        if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
        else getNextToken();
    } else if ((*nextToken)->getTokenType() == TokenType::SWITCHTK) {
        switchState();
    } else if ((*nextToken)->getTokenType() == TokenType::LBRACE) {
        getNextToken();
        stateList();
        if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
        getNextToken();
    } else if ((*nextToken)->getTokenType() == TokenType::RETURNTK) {
        returnState();
        if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
        else getNextToken();
    } else if ((*nextToken)->getTokenType() == TokenType::IDENFR) {
        if ((nextToken + 1) < tokens.end() &&
            (*(nextToken + 1))->getTokenType() == TokenType::LPARENT) {
            if (table::getType((*nextToken)->getRawString()) != VarType::VOID) {
                returnFuncState();
                if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
                else getNextToken();
            } else {
                voidFuncState();
                if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
                else getNextToken();
            }
        } else {
            assiState();
            if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
            else getNextToken();
        }
    } else if ((*nextToken)->getTokenType() == TokenType::SEMICN) {
        getNextToken();
    } else {
        error();
    }
    fileout << "<语句>" << std::endl;
}

void Parsing::loopState() {
    if ((*nextToken)->getTokenType() == TokenType::WHILETK) {
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
        getNextToken();
        condition();
        if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
        else getNextToken();
        statement();
    } else if ((*nextToken)->getTokenType() == TokenType::FORTK) {
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        table::setType((*nextToken)->getRawString());
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
        getNextToken();
        expression();
        if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
        else getNextToken();
        condition();
        if ((*nextToken)->getTokenType() != TokenType::SEMICN) error(lineNum, 'k');
        else getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        table::setType((*nextToken)->getRawString());
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
        getNextToken();
        if ((*nextToken)->getTokenType() != TokenType::PLUS
            && (*nextToken)->getTokenType() != TokenType::MINU)
            error();
        getNextToken();
        stride();
        if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
        else getNextToken();
        statement();
    } else {
        error();
    }
    fileout << "<循环语句>" << std::endl;
}

void Parsing::condition() {
    if (expression() != VarType::INT) error(lineNum, 'f');
    relationOp();
    if (expression() != VarType::INT) error(lineNum, 'f');
    fileout << "<条件>" << std::endl;
}

void Parsing::relationOp() {
    switch ((*nextToken)->getTokenType()) {
        case TokenType::LSS:
        case TokenType::LEQ:
        case TokenType::GRE:
        case TokenType::GEQ:
        case TokenType::EQL:
        case TokenType::NEQ:
            getNextToken();
            break;
        default:
            error();
    }
}

VarType Parsing::expression() {
    VarType tmp = VarType::VOID;
    if ((*nextToken)->getTokenType() == TokenType::PLUS
        || (*nextToken)->getTokenType() == TokenType::MINU) {
        getNextToken();
        tmp = VarType::INT;
    }
    if (tmp == VarType::VOID) tmp = term();
    else term();
    while ((*nextToken)->getTokenType() == TokenType::PLUS
           || (*nextToken)->getTokenType() == TokenType::MINU) {
        getNextToken();
        term();
        tmp = VarType::INT;
    }
    fileout << "<表达式>" << std::endl;
    return tmp;
}

VarType Parsing::term() {
    VarType tmp = factor();
    while ((*nextToken)->getTokenType() == TokenType::MULT
           || (*nextToken)->getTokenType() == TokenType::DIV) {
        tmp = VarType::INT;
        getNextToken();
        factor();
    }
    fileout << "<项>" << std::endl;
    return tmp;
}

VarType Parsing::factor() {
    VarType tmp;
    if ((*nextToken)->getTokenType() == TokenType::IDENFR) {
        if ((nextToken + 1) < tokens.end() &&
            (*(nextToken + 1))->getTokenType() == TokenType::LPARENT) {
            tmp = returnFuncState();
        } else {
            tmp = table::getType((*nextToken)->getRawString());
            getNextToken();
            if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
                getNextToken();
                if (expression() != VarType::INT) error(lineNum, 'i');
                if ((*nextToken)->getTokenType() != TokenType::RBRACK) error(lineNum, 'm');
                else getNextToken();
                if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
                    getNextToken();
                    if (expression() != VarType::INT) error(lineNum, 'i');
                    if ((*nextToken)->getTokenType() != TokenType::RBRACK)error(lineNum, 'm');
                    else getNextToken();
                }
            }
        }
    } else if ((*nextToken)->getTokenType() == TokenType::CHARCON) {
        tmp = VarType::CHAR;
        getNextToken();
    } else if ((*nextToken)->getTokenType() == TokenType::LPARENT) {
        tmp = VarType::INT;
        getNextToken();
        expression();
        if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
        else getNextToken();
    } else {
        tmp = VarType::INT;
        integer();
    }
    fileout << "<因子>" << std::endl;
    return tmp;
}

void Parsing::stride() {
    unsignedInt();
    fileout << "<步长>" << std::endl;
}

void Parsing::condState() {
    if ((*nextToken)->getTokenType() != TokenType::IFTK) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    condition();
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    statement();
    if ((*nextToken)->getTokenType() == TokenType::ELSETK) {
        getNextToken();
        statement();
    }
    fileout << "<条件语句>" << std::endl;
}

VarType Parsing::returnFuncState() {
    std::string name;
    if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
    name = (*nextToken)->getRawString();
    if (table::getType(name) == VarType::VOID) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    std::vector<VarType> vaList = vaArgList();
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    fileout << "<有返回值函数调用语句>" << std::endl;
    return table::getFunc(name, vaList);
}

std::vector<VarType> Parsing::vaArgList() {
    std::vector<VarType> vaList;
    if ((*nextToken)->getTokenType() != TokenType::RPARENT && (*nextToken)->getTokenType() != TokenType::SEMICN) {
        vaList.push_back(expression());
        while ((*nextToken)->getTokenType() == TokenType::COMMA) {
            getNextToken();
            vaList.push_back(expression());
        }
    }
    fileout << "<值参数表>" << std::endl;
    return vaList;
}

void Parsing::voidFuncState() {
    if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
    std::string name = (*nextToken)->getRawString();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    std::vector<VarType> vaList = vaArgList();
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    table::getFunc(name, vaList);
    fileout << "<无返回值函数调用语句>" << std::endl;
}

void Parsing::assiState() {
    std::string name;
    if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
    name = ((*nextToken)->getRawString());
    getNextToken();
    table::setType(name);
    if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
        getNextToken();
        expression();
        if ((*nextToken)->getTokenType() != TokenType::RBRACK) error(lineNum, 'm');
        else getNextToken();
        if ((*nextToken)->getTokenType() == TokenType::LBRACK) {
            getNextToken();
            expression();
            if ((*nextToken)->getTokenType() != TokenType::RBRACK) error(lineNum, 'm');
            else getNextToken();
        }
    }
    if ((*nextToken)->getTokenType() != TokenType::ASSIGN) error();
    getNextToken();
    expression();
    fileout << "<赋值语句>" << std::endl;
}

void Parsing::readState() {
    if ((*nextToken)->getTokenType() != TokenType::SCANFTK) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
    table::setType((*nextToken)->getRawString());
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    fileout << "<读语句>" << std::endl;
}

void Parsing::writeState() {
    if ((*nextToken)->getTokenType() != TokenType::PRINTFTK) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    if ((*nextToken)->getTokenType() == TokenType::STRCON) {
        strcon();
        if ((*nextToken)->getTokenType() == TokenType::COMMA) {
            getNextToken();
            expression();
        }
    } else {
        expression();
    }
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    fileout << "<写语句>" << std::endl;
}

void Parsing::strcon() {
    if ((*nextToken)->getTokenType() != TokenType::STRCON) error();
    getNextToken();
    fileout << "<字符串>" << std::endl;
}

void Parsing::switchState() {
    VarType tmp;
    bool err = false;
    if ((*nextToken)->getTokenType() != TokenType::SWITCHTK) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    tmp = expression();
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
    getNextToken();
    caseList(tmp);
    if ((*nextToken)->getTokenType() != TokenType::DEFAULTTK) err = true;
    else defaultState();
    if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
    if(err) error(lineNum,'p');
    getNextToken();
    fileout << "<情况语句>" << std::endl;
}

void Parsing::caseList(VarType type) {
    caseState(type);
    while ((*nextToken)->getTokenType() == TokenType::CASETK) {
        caseState(type);
    }
    fileout << "<情况表>" << std::endl;
}

void Parsing::caseState(VarType type) {
    if ((*nextToken)->getTokenType() != TokenType::CASETK) error();
    getNextToken();
    if (constant() != type) error(lineNum, 'o');
    if ((*nextToken)->getTokenType() != TokenType::COLON) error();
    getNextToken();
    statement();
    fileout << "<情况子语句>" << std::endl;
}

void Parsing::defaultState() {
    if ((*nextToken)->getTokenType() != TokenType::DEFAULTTK) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::COLON) error();
    getNextToken();
    statement();
    fileout << "<缺省>" << std::endl;
}

void Parsing::returnState() {
    if ((*nextToken)->getTokenType() != TokenType::RETURNTK) error();
    getNextToken();
    returnCount++;
    if ((*nextToken)->getTokenType() == TokenType::LPARENT) {
        if (table::getReturn() == VarType::VOID) {
            error(lineNum, 'g');
            getNextToken();
            expression();
        } else {
            getNextToken();
            if (table::getReturn() != expression()) error(lineNum, 'h');
        }
        if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
        else getNextToken();
    } else {
        if (table::getReturn() != VarType::VOID) error(lineNum, 'h');
    }
    fileout << "<返回语句>" << std::endl;
}

void Parsing::voidFuncDesc() {
    std::string name;
    if ((*nextToken)->getTokenType() != TokenType::VOIDTK) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::IDENFR) error();
    name = toLower((*nextToken)->getRawString());
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    std::vector<std::pair<VarType, std::string>> vec = argList();
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    auto *paraList = new std::vector<VarType>();
    for (const std::pair<VarType, std::string> &a :vec) {
        paraList->push_back(a.first);
    }
    table::addToTable(new Symbol(name, VarType::VOID, paraList));
    table::createTable(name, VarType::VOID);
    for (const std::pair<VarType, std::string> &a :vec) {
        table::addToTable(new Symbol(a.second, a.first));
    }
    if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
    getNextToken();
    compState();
    if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
    getNextToken();
    table::deleteTable();
    fileout << "<无返回值函数定义>" << std::endl;
}

void Parsing::mainFunc() {
    if ((*nextToken)->getTokenType() != TokenType::VOIDTK) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::MAINTK) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::LPARENT) error();
    getNextToken();
    if ((*nextToken)->getTokenType() != TokenType::RPARENT) error(lineNum, 'l');
    else getNextToken();
    table::addToTable(new Symbol("main", VarType::VOID, new std::vector<VarType>));
    table::createTable("main", VarType::VOID);
    if ((*nextToken)->getTokenType() != TokenType::LBRACE) error();
    getNextToken();
    compState();
    if ((*nextToken)->getTokenType() != TokenType::RBRACE) error();
    getNextToken();
    table::deleteTable();
    fileout << "<主函数>" << std::endl;
}

void Parsing::error() {
    std::cerr << *(*nextToken) << " " << (*nextToken)->getLineNum() << std::endl;
    throw ParsingException();
}

void Parsing::error(int line, char type) {
    err::error(line, type);
}
