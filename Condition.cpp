//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//
using namespace std;

#include "Condition.h"
#include "UsefulFunctions.h"

/**
 * this function is a constructor of the condition.
 */
Condition:: Condition() {
    this->first = NULL;
    this->second = NULL;
    this->sign = "";
}

/**
 * this function is a constructor of the condition.
 * @param line  - this line pf the condition from the text
 * @param pro - the pro
 */
Condition:: Condition(string line, Pro* pro) {
    this->pro = pro;
    //this is an expression
    if(line!="true" && line!="false") {
        //remove parenthesis
        line = removeParenthesis(line);
        //fi will be the first expression (in the left side of the sign)
        string fi = extractExpression(line);
        line = line.substr(fi.length(), line.length());
        // extract the sign
        this->sign = extractSign(line);
        line = removeSpaces(line);
        line = line.substr(this->sign.length());
        // se will be the second expression (in the right side of the sign)
        string se = extractExpression(line);
        // switch fi and se to expression
        first = makeExpression(fi, pro);
        second = makeExpression(se, pro);
    } else {
        first = NULL;
        second = NULL;
        this->sign = line;
    }
}

/**
 * this function check if the condition is still right
 * @return true if the condition right, false otherwise
 */
bool Condition:: checkCondition() {
    //check all the options.
    if(sign == "<") {
        return first->calculate() < second->calculate();
    } else if (sign == ">") {
        return first->calculate() > second->calculate();
    } else if (sign == "<=") {
        return first->calculate() <= second->calculate();
    } else if (sign == ">=") {
        return first->calculate() >= second->calculate();
    } else if (sign == "true") {
        return true;
    } else if (sign == "false") {
        return false;
    } else if (sign == "==") {
        return (first->calculate() == second->calculate());
    } else if (sign == "true") {
        return true;
    } else if (sign == "false") {
        return false;
    }
}