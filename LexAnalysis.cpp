//
// Created by buaa-city on 2020/9/27.
//

#include "LexAnalysis.h"
#include "ioControl.h"

std::vector<Token *> tokens;

void LexAnalysis(const std::string &rawString) {

    std::string tmpToken;
    int lineNum = 1;
    int i = 0;
    TokenType type;
    while (i < rawString.length()) {
        tmpToken = "";
        type = static_cast<TokenType>(-1);
        while (isSpace(rawString[i])) {
            if (isNextLine(rawString[i])) {
                lineNum++;
            }
            i++;
        }
        if (isAlpha(rawString[i])) {
            std::string tmp;
            tmp = "";
            do {
                tmpToken += rawString[i];
                tmp += toLower(rawString[i]);
                i++;
            } while ((isAlpha(rawString[i]) || isDigit(rawString[i])) && i < rawString.length());
            if (tmp == "const") {
                type = TokenType::CONSTTK;
            } else if (tmp == "int") {
                type = TokenType::INTTK;
            } else if (tmp == "char") {
                type = TokenType::CHARTK;
            } else if (tmp == "void") {
                type = TokenType::VOIDTK;
            } else if (tmp == "main") {
                type = TokenType::MAINTK;
            } else if (tmp == "if") {
                type = TokenType::IFTK;
            } else if (tmp == "else") {
                type = TokenType::ELSETK;
            } else if (tmp == "switch") {
                type = TokenType::SWITCHTK;
            } else if (tmp == "case") {
                type = TokenType::CASETK;
            } else if (tmp == "default") {
                type = TokenType::DEFAULTTK;
            } else if (tmp == "while") {
                type = TokenType::WHILETK;
            } else if (tmp == "for") {
                type = TokenType::FORTK;
            } else if (tmp == "scanf") {
                type = TokenType::SCANFTK;
            } else if (tmp == "printf") {
                type = TokenType::PRINTFTK;
            } else if (tmp == "return") {
                type = TokenType::RETURNTK;
            } else {
                type = TokenType::IDENFR;
            }
        } else if (isDigit(rawString[i])) {
            do {
                tmpToken += rawString[i];
                i++;
            } while (isDigit(rawString[i]) && i < rawString.length());
            type = TokenType::INTCON;
        } else if (rawString[i] == '\'') {
            i++;
            if (i < rawString.length()) {
                if (isAlpha(rawString[i]) || isDigit(rawString[i])
                    || rawString[i] == '+' || rawString[i] == '-'
                    || rawString[i] == '*' || rawString[i] == '/') {
                    tmpToken += rawString[i];
                } else {
                    throw LexingException(lineNum);
                }
                i++;
                if (i < rawString.length() && rawString[i] == '\'') {
                    type = TokenType::CHARCON;
                    i++;
                } else {
                    throw LexingException(lineNum);
                }
            } else {
                throw LexingException(lineNum);
            }
        } else if (rawString[i] == '\"') {
            i++;
            while (isPrint(rawString[i]) && i < rawString.length()) {
                tmpToken += rawString[i];
                i++;
            }
            if (i < rawString.length() && rawString[i] == '\"') {
                type = TokenType::STRCON;
                i++;
            } else {
                throw LexingException(lineNum);
            }
        } else if (rawString[i] == '+') {
            tmpToken += rawString[i++];
            type = TokenType::PLUS;
        } else if (rawString[i] == '-') {
            tmpToken += rawString[i++];
            type = TokenType::MINU;
        } else if (rawString[i] == '*') {
            tmpToken += rawString[i++];
            type = TokenType::MULT;
        } else if (rawString[i] == '/') {
            tmpToken += rawString[i++];
            type = TokenType::DIV;
        } else if (rawString[i] == ':') {
            tmpToken += rawString[i++];
            type = TokenType::COLON;
        } else if (rawString[i] == ';') {
            tmpToken += rawString[i++];
            type = TokenType::SEMICN;
        } else if (rawString[i] == ',') {
            tmpToken += rawString[i++];
            type = TokenType::COMMA;
        } else if (rawString[i] == '(') {
            tmpToken += rawString[i++];
            type = TokenType::LPARENT;
        } else if (rawString[i] == ')') {
            tmpToken += rawString[i++];
            type = TokenType::RPARENT;
        } else if (rawString[i] == '[') {
            tmpToken += rawString[i++];
            type = TokenType::LBRACK;
        } else if (rawString[i] == ']') {
            tmpToken += rawString[i++];
            type = TokenType::RBRACK;
        } else if (rawString[i] == '{') {
            tmpToken += rawString[i++];
            type = TokenType::LBRACE;
        } else if (rawString[i] == '}') {
            tmpToken += rawString[i++];
            type = TokenType::RBRACE;
        } else if (rawString[i] == '!') {
            tmpToken += rawString[i++];
            if (i < rawString.length() && rawString[i] == '=') {
                tmpToken += rawString[i++];
                type = TokenType::NEQ;
            } else {
                throw LexingException(lineNum);
            }
        } else if (rawString[i] == '<') {
            tmpToken += rawString[i++];
            if (i < rawString.length() && rawString[i] == '=') {
                tmpToken += rawString[i++];
                type = TokenType::LEQ;
            } else {
                type = TokenType::LSS;
            }
        } else if (rawString[i] == '>') {
            tmpToken += rawString[i++];
            if (i < rawString.length() && rawString[i] == '=') {
                tmpToken += rawString[i++];
                type = TokenType::GEQ;
            } else {
                type = TokenType::GRE;
            }
        } else if (rawString[i] == '=') {
            tmpToken += rawString[i++];
            if (i < rawString.length() && rawString[i] == '=') {
                tmpToken += rawString[i++];
                type = TokenType::EQL;
            } else {
                type = TokenType::ASSIGN;
            }
        } else {
            throw LexingException(lineNum);
        }
        tokens.push_back(new Token(lineNum, tmpToken, type));
    }
}

void printLexingDebug() {
    for (Token *t:tokens) {
        fileout << *t << std::endl;
    }
}
