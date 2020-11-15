//
// Created by buaa-city on 2020/11/14.
//

#include "MidCodeOP.h"


std::vector<MidCode *> MidCodes;
std::vector<std::string> Strcons;

void MidCodeOP::addMidCode(MidCode *midCode) {
    MidCodes.push_back(midCode);
}

int MidCodeOP::addStrcon(const std::string &str) {
    Strcons.push_back(toEscape(str));
    return (int) Strcons.size() - 1;
}

void MidCodeOP::printMidCode() {
    MidCodeFile << ".data" << std::endl;
    for (int i = 0; i < Strcons.size(); i++) {
        MidCodeFile << "STR_" << i << ":" << Strcons[i] << std::endl;
    }
    MidCodeFile << "STR_ENTER:" << "\\n" << std::endl;
    MidCodeFile << ".text" << std::endl;
    for (MidCode *i: MidCodes) {
        MidCodeFile << *i;
    }
}

void MidCodeOP::printAssCode() {
    AssCodeFile << ".data" << std::endl;
    for (int i = 0; i < Strcons.size(); i++) {
        AssCodeFile << "STR_" << i << ": .asciiz \"" << Strcons[i] << "\"" << std::endl;
    }
    AssCodeFile << R"(STR_ENTER: .asciiz "\n")" << std::endl;
    AssCodeFile << ".text" << std::endl;

    table::createTable(".global", VarType::VOID);
    for (MidCode *i: MidCodes) {
        i->toAssCode();
    }
    table::deleteTable();
}



