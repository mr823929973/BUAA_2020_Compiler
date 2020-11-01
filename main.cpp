#include "includes/ioControl.h"
#include "Lexing/LexAnalysis.h"
#include "Parsing/Parsing.h"

#define Parsing
#define ERRORS
#define DEBUG

int main() {
    std::string rawString = read();
#ifdef DEBUG
    std::cout << "=========================Lexing================================" << std::endl;
#endif
    LexAnalysis(rawString);
#ifdef DEBUG
    std::cout << "=======================Lexing Complete=========================" << std::endl;
#endif

#ifdef Lexing
    printLexingDebug();
#endif

#ifdef DEBUG
    std::cout << "=========================Parsing===============================" << std::endl;
#endif

#ifdef Parsing
    try {
        ParsingAnalysis();
    } catch (ParsingException &e) {
        std::cerr << e;
    }
#endif

#ifdef DEBUG
    std::cout << "=======================Parsing Complete========================" << std::endl;
#endif

#ifdef ERRORS
    err::printErr();
#endif

    return 0;
}
