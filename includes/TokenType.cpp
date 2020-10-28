//
// Created by buaa-city on 2020/9/30.
//

#include "TokenType.h"

std::ostream &operator<<(std::ostream &out, TokenType tp) {
    switch (tp) {
        case TokenType::IDENFR:
            out << "IDENFR";
            break;
        case TokenType::INTCON:
            out << "INTCON";
            break;
        case TokenType::CHARCON:
            out << "CHARCON";
            break;
        case TokenType::STRCON:
            out << "STRCON";
            break;
        case TokenType::CONSTTK:
            out << "CONSTTK";
            break;
        case TokenType::INTTK:
            out << "INTTK";
            break;
        case TokenType::CHARTK:
            out << "CHARTK";
            break;
        case TokenType::VOIDTK:
            out << "VOIDTK";
            break;
        case TokenType::MAINTK:
            out << "MAINTK";
            break;
        case TokenType::IFTK:
            out << "IFTK";
            break;
        case TokenType::ELSETK:
            out << "ELSETK";
            break;
        case TokenType::SWITCHTK:
            out << "SWITCHTK";
            break;
        case TokenType::CASETK:
            out << "CASETK";
            break;
        case TokenType::DEFAULTTK:
            out << "DEFAULTTK";
            break;
        case TokenType::WHILETK:
            out << "WHILETK";
            break;
        case TokenType::FORTK:
            out << "FORTK";
            break;
        case TokenType::SCANFTK:
            out << "SCANFTK";
            break;
        case TokenType::PRINTFTK:
            out << "PRINTFTK";
            break;
        case TokenType::RETURNTK:
            out << "RETURNTK";
            break;
        case TokenType::PLUS:
            out << "PLUS";
            break;
        case TokenType::MINU:
            out << "MINU";
            break;
        case TokenType::MULT:
            out << "MULT";
            break;
        case TokenType::DIV:
            out << "DIV";
            break;
        case TokenType::LSS:
            out << "LSS";
            break;
        case TokenType::LEQ:
            out << "LEQ";
            break;
        case TokenType::GRE:
            out << "GRE";
            break;
        case TokenType::GEQ:
            out << "GEQ";
            break;
        case TokenType::EQL:
            out << "EQL";
            break;
        case TokenType::NEQ:
            out << "NEQ";
            break;
        case TokenType::COLON:
            out << "COLON";
            break;
        case TokenType::ASSIGN:
            out << "ASSIGN";
            break;
        case TokenType::SEMICN:
            out << "SEMICN";
            break;
        case TokenType::COMMA:
            out << "COMMA";
            break;
        case TokenType::LPARENT:
            out << "LPARENT";
            break;
        case TokenType::RPARENT:
            out << "RPARENT";
            break;
        case TokenType::LBRACK:
            out << "LBRACK";
            break;
        case TokenType::RBRACK:
            out << "RBRACK";
            break;
        case TokenType::LBRACE:
            out << "LBRACE";
            break;
        case TokenType::RBRACE:
            out << "RBRACE";
            break;
        default:
           // std::cerr << "[error]:Undefined token type!" << std::endl;
            break;
    }
    return out;
}
