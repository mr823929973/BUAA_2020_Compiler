#include "includes/ioControl.h"
#include "Lexing/LexAnalysis.h"
#include "Parsing/Parsing.h"

#define Parsing

int main() {
    std::string rawString = read();
    try {
        LexAnalysis(rawString);
    } catch (LexingException &e) {
        std::cerr << "Lexing Error in Line " << e.getLineNum() << std::endl;
    }

#ifdef Lexing
    printLexingDebug();
#endif
#ifdef Parsing
    try {
        ParsingAnalysis();
    } catch (ParsingException &e) {
        std::cerr << e;
    }

#endif

    return 0;
}
