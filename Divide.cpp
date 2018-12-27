//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//

#include "Divide.h"

using namespace std;

/**
 * this function is a constructor of divide.
 * @param left - the left expression
 * @param right  - the right expression
 */
Divide::Divide(Expression* left, Expression* right) :BinaryExpression(left, right){}

/**
 * this is a default constractor, in this constractor we inserted nulls.
 */
Divide::Divide() :BinaryExpression(NULL, NULL){}

/**
 * this function calculate the expression.
 * @return the result/
 */
double Divide::calculate() {
    return left->calculate()/right->calculate();

}

