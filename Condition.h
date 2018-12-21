//
// Created by moriya on 15/12/18.
//

#ifndef PROJECT_CONDITION_H
#define PROJECT_CONDITION_H

//
// Created by moriya on 13/12/18.
//

using namespace std;

#include <string>
#include "Pro.h"
#include "Expression.h"
#include <queue>
#include <stack>
#include <list>
#include "Number.h"
#include "Plus.h"
#include "Minus.h"
#include "Multiplication.h"
#include "Divide.h"
#include "Var.h"
#include "iostream"


class Condition {
    Expression* first;
    Expression* second;
    string sign;
    Pro* pro;
public:
    Condition();
    Condition(string line, Pro* pro);
    bool checkCondition();
    string extractWordFromLine(string);
};

#endif //PROJECT_CONDITION_H