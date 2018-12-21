//
// Created by moriya on 08/12/18.
//

#ifndef UNTITLED5_Plus_H
#define UNTITLED5_Plus_H

#include "BinaryExpression.h"
#include "Expression.h"

using namespace std;

class Plus: public BinaryExpression {

public:

    Plus(Expression* left, Expression* right);
    double calculate();
    Plus();
    void setRight(Expression* r);
    void  setLeft(Expression* l);
};
#endif //UNTITLED5_Plus_H