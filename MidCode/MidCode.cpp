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
            if (srcA == ".array") {
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t0, 0($sp)" << std::endl;
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t1, 0($sp)" << std::endl;
                AssCodeFile << "sw $t0, 0($t1)" << std::endl;
            } else {
                std::pair<std::string, int> tmp = table::getOffset(srcA);
                int offset = tmp.second;
                if (srcB.empty()) {
                    AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                    AssCodeFile << "lw $t0, 0($sp)" << std::endl;
                } else {
                    AssCodeFile << "li $t0, " << srcB << std::endl;
                    if (!srcC.empty()) {
                        offset += std::stoi(srcC);
                    }
                }
                if (tmp.first == "$gp") {
                    AssCodeFile << "sw $t0, " << offset << "($gp)" << std::endl;
                } else {
                    AssCodeFile << "sw $t0, -" << offset << "($fp)" << std::endl;
                }
            }
            break;
        }
        case Operator::FUNC:
            AssCodeFile << "FUNC_" << srcA << ":" << std::endl;
            AssCodeFile << "move $fp, $s1" << std::endl;
            AssCodeFile << "addi $sp, $fp, -" << table::getFuncOffset(srcA) << std::endl;
            table::createTable(srcA, VarType::VOID);
            break;
        case Operator::CALL:
            AssCodeFile << "sw $ra, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp ,-4" << std::endl;
            AssCodeFile << "sw $fp, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp ,-4" << std::endl;
            AssCodeFile << "move $s1, $sp" << std::endl;
            break;
        case Operator::CALL_END:
            AssCodeFile << "jal FUNC_" << srcA << std::endl;
            AssCodeFile << "move $sp, $fp" << std::endl;
            AssCodeFile << "addi $sp, $sp ,4" << std::endl;
            AssCodeFile << "lw $fp, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp ,4" << std::endl;
            AssCodeFile << "lw $ra, 0($sp)" << std::endl;
            break;
        case Operator::LOD: {
            if (srcA == ".array") {
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t0, 0($sp)" << std::endl;
                AssCodeFile << "lw $t0, 0($t0)" << std::endl;
                AssCodeFile << "sw $t0, 0($sp)" << std::endl;
                AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            } else if (srcA == ".returnFunc") {
                AssCodeFile << "sw $s0, 0($sp)" << std::endl;
                AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            } else {
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
            }
            break;
        }
        case Operator::ADD: {
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t1, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t0, 0($sp)" << std::endl;
            AssCodeFile << "addu $t0, $t0, $t1" << std::endl;
            AssCodeFile << "sw $t0, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            break;
        }
        case Operator::MINU: {
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t1, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, 4" << std::endl;
            AssCodeFile << "lw $t0, 0($sp)" << std::endl;
            AssCodeFile << "subu $t0, $t0, $t1" << std::endl;
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
        case Operator::RET: {
            if (!srcB.empty()) {
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $s0, 0($sp)" << std::endl;
            }
            AssCodeFile << "jr $ra" << std::endl;
            break;
        }
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
        case Operator::ARRAY: {
            std::pair<std::string, int> tmp = table::getOffset(srcA);
            int dim = table::getDim(srcA);
            if (srcB.empty()) {
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t0, 0($sp)" << std::endl;
            } else {
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t0, 0($sp)" << std::endl;
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t1, 0($sp)" << std::endl;
                AssCodeFile << "li $t2, " << dim << std::endl;
                AssCodeFile << "mult $t1, $t2 " << std::endl;
                AssCodeFile << "mflo $t1" << std::endl;
                AssCodeFile << "addu $t0, $t0, $t1" << std::endl;
            }
            AssCodeFile << "sll $t0, $t0 ,2" << std::endl;
            AssCodeFile << "addi $t0, $t0, " << tmp.second << std::endl;
            if (tmp.first == "$gp") {
                AssCodeFile << "addu $t0, $gp, $t0" << std::endl;
            } else {
                AssCodeFile << "subu $t0, $fp, $t0" << std::endl;
            }
            AssCodeFile << "sw $t0, 0($sp)" << std::endl;
            AssCodeFile << "addi $sp, $sp, -4" << std::endl;
            break;
        }
        case Operator::IF: {
            if (!srcC.empty()) {
                int tmp = std::stoi(srcB);
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t1, 0($sp)" << std::endl;
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t0, 0($sp)" << std::endl;
                switch (tmp) {
                    case 1: //<
                        AssCodeFile << "bge $t0, $t1, " << "IF_" << srcA << "_ELSE" << std::endl;
                        break;
                    case 2: //<=
                        AssCodeFile << "bgt $t0, $t1, " << "IF_" << srcA << "_ELSE" << std::endl;
                        break;
                    case 3: //>
                        AssCodeFile << "ble $t0, $t1, " << "IF_" << srcA << "_ELSE" << std::endl;
                        break;
                    case 4: //>=
                        AssCodeFile << "blt $t0, $t1, " << "IF_" << srcA << "_ELSE" << std::endl;
                        break;
                    case 5: //==
                        AssCodeFile << "bne $t0, $t1, " << "IF_" << srcA << "_ELSE" << std::endl;
                        break;
                    case 6: //!=
                        AssCodeFile << "beq $t0, $t1, " << "IF_" << srcA << "_ELSE" << std::endl;
                        break;
                    default:
                        break;
                }
            } else {
                if (srcB == "ELSE") {
                    AssCodeFile << "j IF_" << srcA << "_END" << std::endl;
                }
                AssCodeFile << "IF_" << srcA << "_" << srcB << ":" << std::endl;
            }
            break;
        }
        case Operator::WHILE: {
            if (!srcC.empty()) {
                int tmp = std::stoi(srcB);
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t1, 0($sp)" << std::endl;
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t0, 0($sp)" << std::endl;
                switch (tmp) {
                    case 1: //<
                        AssCodeFile << "bge $t0, $t1, " << "WHILE_" << srcA << "_END" << std::endl;
                        break;
                    case 2: //<=
                        AssCodeFile << "bgt $t0, $t1, " << "WHILE_" << srcA << "_END" << std::endl;
                        break;
                    case 3: //>
                        AssCodeFile << "ble $t0, $t1, " << "WHILE_" << srcA << "_END" << std::endl;
                        break;
                    case 4: //>=
                        AssCodeFile << "blt $t0, $t1, " << "WHILE_" << srcA << "_END" << std::endl;
                        break;
                    case 5: //==
                        AssCodeFile << "bne $t0, $t1, " << "WHILE_" << srcA << "_END" << std::endl;
                        break;
                    case 6: //!=
                        AssCodeFile << "beq $t0, $t1, " << "WHILE_" << srcA << "_END" << std::endl;
                        break;
                    default:
                        break;
                }
            } else {
                if (srcB == "END") {
                    AssCodeFile << "j WHILE_" << srcA << "_START" << std::endl;
                }
                AssCodeFile << "WHILE_" << srcA << "_" << srcB << ":" << std::endl;
            }
            break;
        }
        case Operator::FOR: {
            if (!srcC.empty()) {
                int tmp = std::stoi(srcB);
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t1, 0($sp)" << std::endl;
                AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                AssCodeFile << "lw $t0, 0($sp)" << std::endl;
                switch (tmp) {
                    case 1: //<
                        AssCodeFile << "bge $t0, $t1, " << "FOR_" << srcA << "_END" << std::endl;
                        break;
                    case 2: //<=
                        AssCodeFile << "bgt $t0, $t1, " << "FOR_" << srcA << "_END" << std::endl;
                        break;
                    case 3: //>
                        AssCodeFile << "ble $t0, $t1, " << "FOR_" << srcA << "_END" << std::endl;
                        break;
                    case 4: //>=
                        AssCodeFile << "blt $t0, $t1, " << "FOR_" << srcA << "_END" << std::endl;
                        break;
                    case 5: //==
                        AssCodeFile << "bne $t0, $t1, " << "FOR_" << srcA << "_END" << std::endl;
                        break;
                    case 6: //!=
                        AssCodeFile << "beq $t0, $t1, " << "FOR_" << srcA << "_END" << std::endl;
                        break;
                    default:
                        break;
                }
            } else {
                if (srcB == "END") {
                    AssCodeFile << "j FOR_" << srcA << "_START" << std::endl;
                }
                AssCodeFile << "FOR_" << srcA << "_" << srcB << ":" << std::endl;
            }
            break;
        }
        case Operator::SWITCH: {
            if (!srcB.empty()) {
                if (std::stoi(srcB) > 0) {
                    AssCodeFile << "j SWITCH_" << srcA << "_END" << std::endl;
                }
                AssCodeFile << "SWITCH_" << srcA << "_CASE" << srcB << ":" << std::endl;
                if (srcC != "DEFAULT") {
                    AssCodeFile << "li $t1, " << srcC << std::endl;
                    AssCodeFile << "bne $t0, $t1, " << "SWITCH_" << srcA << "_CASE" << std::stoi(srcB) + 1 << std::endl;
                }
            } else {
                if (srcC == "START") {
                    AssCodeFile << "addi $sp, $sp, 4" << std::endl;
                    AssCodeFile << "lw $t0, 0($sp)" << std::endl;
                } else {
                    AssCodeFile << "SWITCH_" << srcA << "_END" << ":" << std::endl;
                }

            }
            break;
        }
    }

}
