cmake_minimum_required(VERSION 3.0)
project(compiler_mips)

set(CMAKE_CXX_STANDARD 11)

add_executable(compiler_mips main.cpp
        includes/Externs.h includes/Token.cpp includes/Token.h includes/ioControl.cpp includes/ioControl.h includes/TokenType.cpp includes/TokenType.h includes/MyType.cpp includes/MyType.h includes/SymType.cpp includes/SymType.h
        Lexing/LexAnalysis.cpp Lexing/LexAnalysis.h
        Parsing/Parsing.cpp Parsing/Parsing.h Parsing/ParsingException.cpp Parsing/ParsingException.h
        Error/error.cpp Error/error.h Error/error.cpp Error/error.h
        SymTable/SymTable.cpp SymTable/SymTable.h SymTable/Symbol.cpp SymTable/Symbol.h SymTable/TableOP.cpp SymTable/TableOP.h
        MidCode/MidCode.cpp MidCode/MidCode.h MidCode/Operator.cpp MidCode/Operator.h MidCode/MidCodeOP.cpp MidCode/MidCodeOP.h
        )