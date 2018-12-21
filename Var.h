//
// Created by omer on 12/8/18.
//


#ifndef PROJECT_VAR_H
#define PROJECT_VAR_H
#include <string>
#include "UnaryExpression.h"

using namespace std;

class Var : public UnaryExpression {
    string name;
    double value;
public:
    Var();
    Var(string, double);
    string extractWordFromLine(string);
    double getValue();
    double operator=(Var&);
    string getName();
    void setName(string name);
    void setValue(double d);
    double calculate();
};

#endif //PROJECT_VAR_H