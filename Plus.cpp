//
// Created by moriya on 08/12/18.
//

#include "Plus.h"

using namespace std;
double Plus::calculate() {
    return left->calculate()+right->calculate();

}

Plus::Plus(Expression* left, Expression* right) :BinaryExpression(left, right){}

Plus::Plus() :BinaryExpression(NULL, NULL){}

void Plus:: setRight(Expression* r) {
    this->right = r;
}
void Plus:: setLeft(Expression* l) {
    this->left = l;
}
