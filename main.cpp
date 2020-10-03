#include "includes/ioControl.h"
#include "Lexing/LexAnalysis.h"

#define Lexing

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


    return 0;
}
