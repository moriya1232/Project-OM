//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//

#include "Plus.h"

using namespace std;

/**
 * this function is calaulate the expression Plus
 * @return double with the result
 */
double Plus::calculate() {
    return left->calculate()+right->calculate();
}

/**
 * this function is a constractor to plus, we insert left and right expressions to this plus
 * expression, by insert it to binary expression.
 * @param left - the left expression
 * @param right - the right expression
 */
Plus::Plus(Expression* left, Expression* right) :BinaryExpression(left, right){}

/**
 * this is a default constractor. we insert nothing to this.
 */
Plus::Plus() :BinaryExpression(NULL, NULL){}
