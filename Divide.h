//
// Created by moriya on 08/12/18.
//

#ifndef UNTITLED5_DIVIDE_H
#define UNTITLED5_DIVIDE_H

#include "BinaryExpression.h"
#include "Expression.h"

using namespace std;

class Divide: public BinaryExpression {


public:

    Divide(Expression*, Expression*);
    double calculate();
    Divide();
    void setRight(Expression* r);
    void setLeft(Expression* l);
};
#endif //UNTITLED5_DIVIDE_H