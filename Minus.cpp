//
// Created by moriya on 08/12/18.
//

#include "Minus.h"

using namespace std;
double Minus::calculate() {
    if (left == NULL) {
        return 0-right->calculate();
    }
    return left->calculate()-right->calculate();

}

Minus::Minus(Expression* left, Expression* right) :BinaryExpression(left, right){}

Minus::Minus() :BinaryExpression(NULL, NULL){}

void Minus:: setRight(Expression* r) {
    this->right = r;
}
void Minus:: setLeft(Expression* l) {
    this->left = l;
}