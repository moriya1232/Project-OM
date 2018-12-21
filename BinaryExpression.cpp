//
// Created by moriya on 08/12/18.
//

#include "BinaryExpression.h"
using namespace std;



BinaryExpression::BinaryExpression(Expression *left, Expression *right) :left(left), right(right) {}
//BinaryExpression::BinaryExpression(string line) {
void BinaryExpression:: setRight(Expression* r) {
    this->right = r;
}
void BinaryExpression:: setLeft(Expression* l) {
    this->left = l;
}

//}