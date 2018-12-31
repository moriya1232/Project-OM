//
// Created by moriya on 12/12/18.
//

//
// Created by omer on 12/8/18.
//
#include "Var.h"

/**
 * this is a constractor
 */
Var:: Var(): UnaryExpression(0){
    this->name="";
    this->value=0;
}

/**
 * this is a constractor
 * @param v - double
 * @param name
 */
Var::Var(string name, double v):UnaryExpression(v) {
    this->name = name;
    this->value = v;
}

/**
 * get the value
 * @return the value
 */
double Var::getValue() {
    return this->value;
}
/**
 * get the name
 * @return
 */
string Var::getName() {
    return this->name;
}


/**
 *  we need to get the currect value from the server somehow
 *  @param other
 *  @return double
 */

double Var::operator=(Var& other) {
    this->value = other.getValue();
}

/**
 * return caluculate
 * @return calculate
 */
double Var::calculate() {
    return this->getValue();
}

/**
 * reutrn 0
 * @return 0
 */
int doCommand() {
     return 0;
}