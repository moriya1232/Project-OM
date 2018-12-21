//
// Created by moriya on 08/12/18.
//

#include "Multiplication.h"

using namespace std;
double Multiplication::calculate() {
   /* if (right == NULL) {
        return left->calculate();
    } else if (left == NULL) {
        return right->calculate();
    }*/
    return left->calculate()*right->calculate();

}

Multiplication::Multiplication(Expression* left, Expression* right) :BinaryExpression(left, right){}

Multiplication::Multiplication() :BinaryExpression(NULL, NULL){}

void Multiplication:: setRight(Expression* r) {
    this->right = r;
}
void Multiplication:: setLeft(Expression* l) {
    this->left = l;
}