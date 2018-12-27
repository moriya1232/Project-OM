//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
#include "Minus.h"

using namespace std;
double Minus::calculate() {
    if (left == NULL) {
        return 0-right->calculate();
    }
    return left->calculate()-right->calculate();

}

/**
 * this function is a constructor for minus, we get left and right expressions
 * for to insert them to minus in binary expression
 * @param left - the left expression
 * @param right - the right expression
 */
Minus::Minus(Expression* left, Expression* right) :BinaryExpression(left, right){}

/**
 * this is a default constractor to minus. we insert nothing to this.
 */
Minus::Minus() :BinaryExpression(NULL, NULL){}