cmake_minimum_required(VERSION 3.0)
project(compiler_mips)

set(CMAKE_CXX_STANDARD 11)

add_executable(compiler_mips main.cpp includes/Token.cpp includes/Token.h Lexing/LexAnalysis.cpp Lexing/LexAnalysis.h includes/ioControl.cpp includes/ioControl.h includes/TokenType.cpp includes/TokenType.h includes/MyType.cpp includes/MyType.h Lexing/LexingException.cpp Lexing/LexingException.h Parsing/Parsing.cpp Parsing/Parsing.h includes/Externs.h Parsing/ParsingException.cpp Parsing/ParsingException.h)