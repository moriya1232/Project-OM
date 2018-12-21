//
// Created by moriya on 08/12/18.
//

#ifndef UNTITLED5_BINARYEXPRESSION_H
#define UNTITLED5_BINARYEXPRESSION_H

#include "Expression.h"
using namespace std;

class BinaryExpression : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    virtual double calculate()=0;
    BinaryExpression(Expression* left, Expression* right);
    void setRight(Expression*);
    void setLeft(Expression*);
};



#endif //UNTITLED5_BINARYEXPRESSION_H