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
    if (nextToken != tokens.end()) {
        nextToken++;
        if ((*nextToken)->getTokenType() != (TokenType) -1) {
            fileout << *(*nextToken) << std::endl;
        }
    }
}

void Parsing::program() {

}
