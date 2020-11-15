//
// Created by buaa-city on 2020/11/13.
//

#include "Operator.h"

std::ostream &operator<<(std::ostream &out, Operator &tmp) {
    switch (tmp) {
        case Operator::ASSIGN:
            out << "ASSIGN";
            break;
        case Operator::FUNC:
            out << "FUNC";
            break;
        case Operator::CALL:
            out << "CALL";
            break;
        case Operator::LOD:
            out << "LOAD";
            break;
        case Operator::ADD:
            out << "ADD";
            break;
        case Operator::MINU:
            out << "MINU";
            break;
        case Operator::MULT:
            out << "MULT";
            break;
        case Operator::DIV:
            out << "DIV";
            break;
        case Operator::RET:
            out << "RET";
            break;
        case Operator::SCANF:
            out << "SCANF";
            break;
        case Operator::PRINTF:
            out << "PRINTF";
            break;
        case Operator::END:
            out << "END";
            break;
        case Operator::FUNC_END:
            out << "FUNC_END";
            break;
    }
    return out;
}
