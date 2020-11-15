//
// Created by buaa-city on 2020/9/30.
//

#include "MyType.h"

std::string toLower(std::string str) {
    for (char &i : str) {
        i = toLower(i);
    }
    return str;
}

std::string toEscape(const std::string& src) {
    std::string result;
    result.reserve(src.size());
    for (char i : src) {
        if (i == '\\') {
            result += "\\";
        }
        result += i;
    }
    return result;
}
