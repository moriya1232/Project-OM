//
// Created by moriya on 08/12/18.
//

#ifndef UNTITLED5_Multiplication_H
#define UNTITLED5_Multiplication_H

#include "BinaryExpression.h"
#include "Expression.h"

using namespace std;

class Multiplication: public BinaryExpression {


public:

    Multiplication(Expression* left, Expression* right);
    double calculate();
    Multiplication();
    void setRight(Expression* r);
    void setLeft(Expression* l);
};
#endif //UNTITLED5_Multiplication_H