//
// Created by omer on 12/15/18.
//

#include "UnaryExpression.h"

/**
 * this is a constracor
 * @param d
 */
UnaryExpression::UnaryExpression(double d) {
    this->val = d;
}


/**
 * this is a constracor
 * @param s - string
 */
UnaryExpression::UnaryExpression(string s) {
    this->val = stod(s);
    }



/**
 * this is a calculate the expression
 * @param d
 */
double UnaryExpression:: calculate() {
    return this->val;
}