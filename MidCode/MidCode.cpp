//
// Created by buaa-city on 2020/11/13.
//

#include "MidCode.h"


#include <utility>

MidCode::MidCode(Operator op, std::string srcA, std::string srcB, std::string srcC) {
    this->op = op;
    this->srcA = std::move(srcA);
    this->srcB = std::move(srcB);
    this->srcC = std::move(srcC);
}

std::ostream &operator<<(std::ostream &out, MidCode &tmp) {
    out << tmp.op << " " << tmp.srcA << " " << tmp.srcB << " " << tmp.srcC << std::endl;
    return out;
}

void MidCode::toAssCode() const {
    switch (op) {
        case Operator::ASSIGN: {
            std::pair<std::string, int> tmp = table::getOffset(srcA);
            if (srcB.empty()) {
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t0, 0($sp)" << std::endl;
            } else {
                AssCodeFile << "li $t0, " << srcB << std::endl;
            }
            if (tmp.first == "$gp") {
                AssCodeFile << "sw $t0, " << tmp.second << "($gp)" << std::endl;
            } else {
                AssCodeFile << "sw $t0, -" << tmp.second << "($fp)" << std::endl;
            }
            break;
        }
        case Operator::FUNC:
            AssCodeFile << "FUNC_" << srcA << ":" << std::endl;
            AssCodeFile << "move $fp, $sp" << std::endl;
            AssCodeFile << "addi $sp, $sp, -" << table::getFuncOffset(srcA) << std::endl;
            table::createTable(srcA, VarType::VOID);
            break;
        case Operator::CALL:
            //TODO

            AssCodeFile << "jal FUNC_" << srcA << std::endl;
            break;
        case Operator::LOD: {
            if (srcB.empty()) {
                Symbol *tmp = table::getSymbol(srcA);
                if (tmp != nullptr) {
                    if (tmp->symType == SymType::CONST) {
                        AssCodeFile << "li $t0, " << tmp->constValue << std::endl;
                    } else {
                        std::pair<std::string, int> temp = table::getOffset(srcA);
                        if (temp.first == "$gp") {
                            AssCodeFile << "lw $t0, " << temp.second << "($gp)" << std::endl;
                        } else {
                            AssCodeFile << "lw $t0, -" << temp.second << "($fp)" << std::endl;
                        }
                    }
                }

            } else {
                AssCodeFile << "li $t0, " << srcB << std::endl;
            }
            AssCodeFile << "sw $t0, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            break;
        }
        case Operator::ADD: {
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t1, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t0, 0($sp)" << std::endl;
            AssCodeFile << "add $t0, $t0, $t1" << std::endl;
            AssCodeFile << "sw $t0, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            break;
        }

        case Operator::MINU: {
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t1, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t0, 0($sp)" << std::endl;
            AssCodeFile << "sub $t0, $t0, $t1" << std::endl;
            AssCodeFile << "sw $t0, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            break;
        }
        case Operator::MULT: {
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t1, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t0, 0($sp)" << std::endl;
            AssCodeFile << "mult $t0, $t1" << std::endl;
            AssCodeFile << "mflo $t0" << std::endl;
            AssCodeFile << "sw $t0, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            break;
        }
        case Operator::DIV: {
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t1, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t0, 0($sp)" << std::endl;
            AssCodeFile << "div $t0, $t1" << std::endl;
            AssCodeFile << "mflo $t0" << std::endl;
            AssCodeFile << "sw $t0, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            break;
        }
        case Operator::RET:
            AssCodeFile << "jr $ra" << std::endl;
            break;
        case Operator::SCANF: {
            VarType type = table::getType(srcA);
            std::pair<std::string, int> tmp = table::getOffset(srcA);
            if (type == VarType::INT) {
                AssCodeFile << "li $v0, 5" << std::endl;
                AssCodeFile << "syscall" << std::endl;
            } else if (type == VarType::CHAR) {
                AssCodeFile << "li $v0, 12" << std::endl;
                AssCodeFile << "syscall" << std::endl;
            }
            if (tmp.first == "$gp") {
                AssCodeFile << "sw $v0, " << tmp.second << "($gp)" << std::endl;
            } else {
                AssCodeFile << "sw $v0, -" << tmp.second << "($fp)" << std::endl;
            }
            break;
        }
        case Operator::PRINTF: {
            if (srcB == "str") {
                AssCodeFile << "la $a0, " << srcA << std::endl;
                AssCodeFile << "li $v0, 4" << std::endl;
                AssCodeFile << "syscall" << std::endl;
            } else if (srcB == "int") {
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $a0, 0($sp)" << std::endl;
                AssCodeFile << "li $v0, 1" << std::endl;
                AssCodeFile << "syscall" << std::endl;
            } else if (srcB == "char") {
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $a0, 0($sp)" << std::endl;
                AssCodeFile << "li $v0, 11" << std::endl;
                AssCodeFile << "syscall" << std::endl;
            }
            break;
        }

        case Operator::FUNC_END:
            table::createTable(srcA, VarType::VOID);
            break;
        case Operator::END:
            AssCodeFile << "li $v0, 10" << srcA << std::endl;
            AssCodeFile << "syscall" << srcA << std::endl;
            break;
    }
}
