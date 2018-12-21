//
// Created by moriya on 08/12/18.
//

#ifndef UNTITLED5_Minus_H
#define UNTITLED5_Minus_H

#include "BinaryExpression.h"
#include "Expression.h"

using namespace std;

class Minus: public BinaryExpression {


public:

    Minus(Expression* left, Expression* right);
    double calculate();
    Minus();
    void setRight(Expression* r);
    void setLeft(Expression* l);
};
#endif //UNTITLED5_Minus_H