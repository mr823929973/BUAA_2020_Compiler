//
// Created by buaa-city on 2020/9/30.
//

#include "MyType.h"

std::string toLower(std::string str) {
    for (char & i : str) {
        i = toLower(i);
    }
    return str;
}