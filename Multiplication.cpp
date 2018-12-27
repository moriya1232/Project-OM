//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//

#include "Multiplication.h"

using namespace std;

/**
 * this function calculate nuliplication.
 * @return double with the result.
 */
double Multiplication::calculate() {
    return left->calculate()*right->calculate();

}

/**
 * this function is a constructor for multiplication. it insert the left and right expression
 * to multiplication that in binar expression.
 * @param left - the left expression
 * @param right - the right expression
 */
Multiplication::Multiplication(Expression* left, Expression* right) :BinaryExpression(left, right){}

/**
 * this is a default constractor, we insrt nothing to this constructor.
 */
Multiplication::Multiplication() :BinaryExpression(NULL, NULL){}