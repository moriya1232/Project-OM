//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//

using namespace std;

#include "Number.h"

/**
 * this is a constractor to unary expression. we insert a double to a number.
 * @param d - the double.
 */
Number:: Number(double d) : UnaryExpression(d) {}

/**
 * this is a constractor tor number by insert a string to this number.
 * @param s -this string that will become to double.
 */
Number:: Number(string s) : UnaryExpression(s) {}
