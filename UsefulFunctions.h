//
// Created by moriya on 13/12/18.
//

#ifndef PROJECT_USEFULFUNCTION_H
#define PROJECT_USEFULFUNCTION_H

using namespace std;

#include "Expression.h"
#include "Number.h"
#include "Divide.h"
#include "Multiplication.h"
#include "Minus.h"
#include "Plus.h"
#include "Var.h"
#include <regex>


using namespace std;


/**
 *check if operator
 * @param c
 * @return true or false
 */
static bool checkIfOperator(char c) {
    if (c == '+' || c == '-' || c == '/' || c == '*' || c=='\342')
        return true;
    return false;
}


/**
 *check if < or > or = for to knoe if it condition
 * @param c
 * @return true or false
 */
static bool checkIfCondition(char c) {
    if (c == '=' || c == '<' || c == '>') {
        return true;
    }
    return false;
}

/**
 * check if it is a digit
 * @param c
 * @return true or false
 */
static bool checkIfDigit(char c) {
    if (c - '0' >= 0 && c - '0' < 10)
        return true;
    return false;
}


/**
 *check if letter
 * @param c
 * @return true or false
 */
static bool checkIfLetter(char c) {
    if ((c - '0' >= 'a' - '0' && c - '0' <= 'z' - '0') || (c - '0' >= 'A' - '0' && c - '0' <= 'Z' - '0'))
        return true;
    return false;
}


/**
 *check if small letter
 * @param c
 * @return true or false
 */
static bool checkIfSmallLetter(char c) {
    if ((c - '0' >= 'a' - '0' && c - '0' <= 'z' - '0'))
        return true;
    return false;
}


/**
 *check if }
 * @param c
 * @return true or false
 */
static bool ifStackHasGreaterOperator(char oper, string oper2) {
    string oper1 = to_string(oper);
    if (oper1 == "+" || oper1 == "-")
        if (oper2 == "*" || oper2 == "/")
            return true;
    return false;
}

/**
 *check if {
 * @param c
 * @return true or false
 */
static bool checkOpenClosure(char c) {
    if (c == '(')
        return true;
    return false;
}

/**
 *check id }
 * @param c
 * @return true or false
 */
static bool checkCloseClosure(char c) {
    if (c == ')')
        return true;
    return false;
}
/**
 * extract the number
 * @param line
 * @return the number
 */
static string extractNum (string line) {
    string result = "";
    for (int i=0;checkIfDigit(line[i]);i++) {
        result+=line[i];
    }
    return result;
}

/**
 * this function remove spaces from right
 * @param line
 * @return the string after the change
 */
static string removeSpacingFromBegin(string line) {
    for(int i=0; line[i] == ' ' || line[i] == '\t' || line[i] == '\b';) {
        line = line.substr(1, line.length()-1);
    }
    return line;
}

/**
 * this function remoce spaces from the end
 * @param line
 * @return the string after the change
 */
static string removeSpacingFromEnd(string line) {
    int i = line.length()-1;
    for(; line[i] == ' ' || line[i] == '\t' || line[i] == '\b';--i) {}
    line = line.substr(0, i+1);
    return line;
}

/**
 * remove the spcaes after tnf befor the word
 * @param line
 * @return the string after the change
 */
static string removeSpaces(string line) {
    line = removeSpacingFromBegin(line);
    line = removeSpacingFromEnd(line);
    return line;
}

/**
 * remove the apostrophes
 * @param line
 * @return the string after the change
 */
static string removeApostrophes(string line) {
    line = removeSpaces(line);
    if (line[0] == '"' && line[line.length() - 1] == '"') {
        line = line.substr(1);
        line = line.substr(0, line.length() - 1);
    }
    return line;
}

/**
 * remove the {
 * @param line
 * @return line after the change
 */
static string removeOpenSpiPar(string line) {
    line = removeSpaces(line);
    if(line[line.length()-1] == '{') {
        line = line.substr(0,line.length()-2);
    }
    return line;
}
/**
 * remove the equal in the string
 * @param line
 * @return the string after the change
 */
static string removeEqual(string line) {
    for(int i=0;line[i] == ' ' || line[i] == '=' ;) {
        line = line.substr(1, line.length()-1);
    }
    return line;
}
/**
 * removr the paranthesis from line
 * @param line
 * @return the string after the change
 */
static string removeParenthesis(string line) {
    line = removeSpaces(line);
    int counter = 0;
    if (line[0] == '(' && line[line.length()-1] == ')') {
        for (int i=1;i<line.length()-1;++i) {
            char c = line[i];
            if (c==')') {
                if (counter==0) {
                    counter--;
                    break;
                } else {
                    counter--;
                }
            } else if (c=='(') {
                counter++;
            }
        } if(counter==0) {
            line = line.substr(1, line.length() - 2);
        }
    }
    return line;
}
/**
 * extract a var
 * @param line
 * @return the var name
 */
static string extractVar (string line) {
    char ch = line[0];
    string forVar = "";
    if(checkIfLetter(ch) || ch == '_') {forVar+=ch;}
    else {
        return "";
    }
    if (line.length()>1) {
        ch = line[1];
        for (int i = 2; checkIfLetter(ch) || checkIfDigit(ch) || ch == '_'; i++) {
            forVar += ch;
            ch = line[i];
        }
    }
    return forVar;
}
static Expression* insertExpressionsToA (BinaryExpression* a, list<string> lis) {
    // a->setRight(getExpression(lis.pop_back()))

}

/**
 * check if the line exist number
 * @param ex
 * @return true or false
 */
static bool existNum(string ex){
    if (ex == "") {
        return false;
    }
    char c = ex[0];
    for(int i=0; i<ex.length(); i++) {
        if (checkIfDigit(ex[i])) {
            return true;
        }
        c=ex[i];
    }
    return false;
}

/**
 * this is a recursive function for take a list of string and connvert it to expression
 * @param pro
 * @return
 */
static Expression* getExpression(Pro* pro) {
    if(pro->getListForExp().size()==0) {
        return NULL;
    }
    BinaryExpression* a;
    string temp =pro->getListForExp().front();
    if (!existNum(temp) && checkIfOperator(temp[0])) {
        string oper = temp;
        if (oper == "+") {
            a = new(nothrow) Plus();
        } else if (oper == "-") {
            a = new(nothrow) Minus();
        } else if (oper == "*") {
            a = new( nothrow) Multiplication();
        } else if (oper == "/") {
            a = new(nothrow) Divide();
        }
        pro->getCollector()->addItem(a);
    } else {
        if (existNum(temp) && !checkIfLetter(temp[0])) {
            Number *num = new(nothrow) Number(temp);
            pro->getCollector()->addItem(num);
            pro->popFrontExp();
            return num;
        } else {
            Var *var = new (nothrow) Var(temp, pro->getSymbolTable()->at(temp));
            pro->getCollector()->addItem(var);
            pro->popFrontExp();
            return var;
        }
    }
    pro->popFrontExp();
    Expression* ex1 = getExpression(pro);
    a->setRight(ex1);
    Expression* ex2 = getExpression(pro);
    a->setLeft(ex2);
    return a;
}
/**
 * extract the firector from line
 * @param line
 * @return strin of directory
 */
static string extractDirectory (string line) {
    char c=line[0];
    int i=0;
    while (c != '"') {
        if (line=="") {
            break;
        }
        line=line.substr(1,line.length()-1);
        c = line[0];
    }
    c = line[line.length()-1];
    while (c != '"') {
        if (line=="") {
            break;
        }
        line=line.substr(line.length()-2);
        i = line.length()-1;
        c = line[i];
    }
    return line;
}
/**
 * this function take a string and convert it to expression
 * is is done by the algorithms that we shown in the video
 * @param line
 * @param pro
 * @return reult Expression
 */
static Expression* makeExpression(string line, Pro* pro) {
    line = removeSpaces(line);
    if(checkIfOperator(line[0])) {
        line = "0"+line;
    }
    string forVar = "";
    forVar = extractVar(line);
    Var* var1 = NULL;
    if(forVar != "" && forVar.length() == line.length()) {
        if (pro->isVarInSymbolTable(forVar)) {
            var1 = new(nothrow) Var(forVar, pro->getSymbolTable()->at(forVar));
            pro->getCollector()->addItem(var1);
        } else {
            string directory = pro->getNamesAndDirectories().at(forVar);
        }
        return var1;
    }
    queue<string> numbers;
    stack<string> operators;
    queue<string> tempQueue;
    int indx = 0;
    int length = line.length();
    int temp = 0;
    char c;
    string s = "";
    bool indicator = true;
    //those variebles hlp us to calculate expression like this:"5*(-1)
    bool forMinusAndPlus = false;
    bool changeToMinus = false;
    while (indx < length) {
        c = line[indx];
        s += c;
        indx++;
        // if c is a digit
        if (checkIfDigit(c)) {
            forMinusAndPlus = false;
            string takeNum = line.substr(indx-1, line.length());
            takeNum = extractNum(takeNum);
            indx+=takeNum.length()-1;
            if (takeNum !="") {
                if(changeToMinus) {
                    takeNum = "-" +takeNum;
                }
                numbers.push(takeNum);
                changeToMinus = false;
            }
            // is }
        } else if (checkOpenClosure(c))  {
            operators.push(s);
            //is {
        } else if (checkCloseClosure(c)) {
            if (forMinusAndPlus) {
                throw "illigal exception: +) or -)";
            }
            string tempString = operators.top();
            while (!checkOpenClosure(tempString[0])) {
                numbers.push(tempString);
                operators.pop();
                if (!operators.empty()) {
                    tempString = operators.top();
                }
            }
            operators.pop();
            // is operator
        } else if (checkIfOperator(c)) {
            if(forMinusAndPlus) {
                if (operators.top()=="-" && c=='-') {
                    operators.pop();
                    operators.push("+");
                    continue;
                } else if (operators.top()=="-" && c=='+' || operators.top()=="+" && c=='-' ) {
                    operators.pop();
                    operators.push("+");
                    continue;
                } else if (operators.top()=="+" && c=='+') {
                    continue;
                } else if (c=='-' || c== '+') {
                    if(c=='-') {
                        changeToMinus = true;
                    }
                    continue;
                } else {
                    throw "illigal expression ** */ -* -/ +* +/";
                }
            }
            forMinusAndPlus = true;
            if (!operators.empty() && ifStackHasGreaterOperator(c, operators.top())) {
                while (!operators.empty() && ifStackHasGreaterOperator(c, operators.top())) {
                    numbers.push(operators.top());
                    operators.pop();
                }
            }
            operators.push(s);
            //is var
        } else if (checkIfLetter(c)) {
            forMinusAndPlus = false;
            string takeVar = line.substr(indx-1, line.length());
            takeVar = extractVar(takeVar);
            if (changeToMinus) {
                takeVar = "-" + takeVar;
            }
            numbers.push(takeVar);
            indx+=takeVar.length()-1;
            changeToMinus = false;

        }
        s = "";
    }
    while (!operators.empty()) {
        string tempString = operators.top();
        numbers.push(tempString);
        operators.pop();
    }
    list<string> lis;
    while (!numbers.empty()) {
        string tempStr = numbers.front();
        if (tempStr != "(") {
            lis.push_back(tempStr);
        }
        numbers.pop();
    }
    lis.reverse();
    pro->clearListForExp();
    pro->setListForExp(lis);
    Expression* e = getExpression(pro);
    return e;
}

/**
 * extract the first word from line
 * @param line
 * @return word
 */
static string extractWordFromLine(string line) {
    line = removeSpaces(line);
    string result = "";
    int i = 0;
    while (line[i] != ' ' && line[i] != '\n' && i < line.length() && line[i] != '\t') {
        result += line[i];
        i++;
    }
    return result;
}

/**
 * ectract the expressin
 * @param line
 * @return the expressin
 */
static string extractExpression(string line) {
    line = removeSpaces(line);
    string ex = "";
    for (int i=0; checkIfDigit(line[i]) || checkIfSmallLetter(line[i]); i++ ){
        ex+=line[i];
    }
    return ex;
}
/**
 * ectract the sign
 * @param line
 * @return the sign
 */
static string extractSign(string line) {
    line = removeSpaces(line);
    string sign = "";
    for (int i=0; checkIfCondition(line[i]); i++ ){
        sign+=line[i];
    }
    return sign;
}

#endif //PROJECT_USEFULLFUNCTION_H