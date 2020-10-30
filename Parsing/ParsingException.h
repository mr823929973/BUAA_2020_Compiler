//
// Created by buaa-city on 2020/10/4.
//

#ifndef COMPILER_MIPS_PARSINGEXCEPTION_H
#define COMPILER_MIPS_PARSINGEXCEPTION_H

#include <exception>
#include <string>

class ParsingException : public std::exception {
private:
    std::string message;
public:
    ParsingException();

    ParsingException(std::string message);

    friend std::ostream &operator<<(std::ostream &out, ParsingException &tmp);
};


#endif //COMPILER_MIPS_PARSINGEXCEPTION_H
