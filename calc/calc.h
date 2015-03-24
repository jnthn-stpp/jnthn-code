#ifndef CALC_H
#define CALC_H

#include "token.h"
#include <string>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace jnthn{
namespace calc{

void setAns(num ans);

std::vector<token*> parseLine(std::string line);

void setupDefFuns();

void printTStream(std::vector<token *> stream);

void simplify(int priority, std::vector<token *> & stack);

}
}

#endif
