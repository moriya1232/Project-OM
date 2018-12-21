//
// Created by moriya on 13/12/18.
//

using namespace std;

#include "Condition.h"
#include "UsefulFunctions.h"

Condition:: Condition() {
    this->first = NULL;
    this->second = NULL;
    this->sign = "";
}

Condition:: Condition(string line, Pro* pro) {
    this->pro = pro;
    if(line!="true" && line!="false") {
        line = removeParenthesis(line);
        string fi = extractExpression(line);
        line = line.substr(fi.length() +1, line.length()-1);
        this->sign = extractSign(line);
        line = line.substr(this->sign.length()+1);
        string se = extractExpression(line);
        first = makeExpression(fi, pro);
        second = makeExpression(se, pro);

    } else {
        first = NULL;
        second = NULL;
        this->sign = line;
    }
}

bool Condition:: checkCondition() {
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
    }
}

string Condition:: extractWordFromLine(string line) {
    string result = "";
    int i = 0;
    while (line[i] != ' ' && line[i] != '\n' && i < line.length()) {
        result += line[i];
        i++;
    }
    return result;
}