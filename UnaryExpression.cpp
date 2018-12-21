//
// Created by omer on 12/15/18.
//

#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(double d) {
    this->val = d;
}

UnaryExpression::UnaryExpression(string s) {
    this->val = stod(s);
    /*double res = 0;
    long decades =1;
    int i = 0;
    int length = s.length();
    double curr = 0;
    char c;
    bool hasFloatingPoint = false;
    while (i < length) {
        c = s[i];
        if (c == '.') {
            hasFloatingPoint = true;
        }
        i++;
    }
    i = length - 1;
    if (!hasFloatingPoint) {
        while (i >= 0) {
            curr = s[i] - '0';
            res += (curr* decades);
            decades*=10;
            i--;
        }
        this->val = res;
    } else {
        this->val = 999;
    }*/
}

double UnaryExpression:: calculate() {
    return this->val;
}