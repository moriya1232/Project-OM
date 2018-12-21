//
// Created by omer on 12/15/18.
//

#ifndef PROJECT_UNARYEXPRESSION_H
#define PROJECT_UNARYEXPRESSION_H

#include "Expression.h"
#include <string>

using namespace std;

class UnaryExpression : public Expression {

protected:
    double val;
public:
        UnaryExpression(string);
        UnaryExpression(double);
        double calculate();
};

#endif //PROJECT_UNARYEXPRESSION_H