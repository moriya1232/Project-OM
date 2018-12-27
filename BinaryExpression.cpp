//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//

#include "BinaryExpression.h"
using namespace std;


/**
 * this function is a constructor of Binary Expression, this is does super.
 * @param left - expression of the left size
 * @param right - expression of the right size
 */
BinaryExpression::BinaryExpression(Expression *left, Expression *right) :left(left), right(right) {}

/**
 * this function set the right expression of the binary expression.
 * @param r - right expression
 */
void BinaryExpression:: setRight(Expression* r) {
    this->right = r;
}
/**
 * this function set the left expression of the binary expression.
 * @param l- left expression
 */
void BinaryExpression:: setLeft(Expression* l) {
    this->left = l;
}

//}