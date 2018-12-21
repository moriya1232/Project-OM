//
// Created by moriya on 08/12/18.
//

#include "Divide.h"

using namespace std;
double Divide::calculate() {
    return left->calculate()/right->calculate();

}

Divide::Divide(Expression* left, Expression* right) :BinaryExpression(left, right){}

Divide::Divide() :BinaryExpression(NULL, NULL){}