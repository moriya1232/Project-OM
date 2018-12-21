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

static bool checkIfOperator(char c) {
    if (c == '+' || c == '-' || c == '/' || c == '*' || c=='\342')
        return true;
    return false;
}
static bool checkIfCondition(char c) {
    if (c == '=' || c == '<' || c == '>') {
        return true;
    }
    return false;
}

static bool checkIfDigit(char c) {
    if (c - '0' >= 0 && c - '0' < 10)
        return true;
    return false;
}

static bool checkIfLetter(char c) {
    if ((c - '0' >= 'a' - '0' && c - '0' <= 'z' - '0') || (c - '0' >= 'A' - '0' && c - '0' <= 'Z' - '0'))
        return true;
    return false;
}
static bool checkIfSmallLetter(char c) {
    if ((c - '0' >= 'a' - '0' && c - '0' <= 'z' - '0'))
        return true;
    return false;
}

static bool ifStackHasGreaterOperator(char oper, string oper2) {
    string oper1 = to_string(oper);
    if (oper1 == "+" || oper1 == "-")
        if (oper2 == "*" || oper2 == "/")
            return true;
    return false;
}

static bool checkOpenClosure(char c) {
    if (c == '(')
        return true;
    return false;
}

static bool checkCloseClosure(char c) {
    if (c == ')')
        return true;
    return false;
}

static string removeApostrophes(string line) {
    if ((line[0] != '\"' || line[line.length() - 1] != '\"') &&
        (line[0] != '\'' || line[line.length() - 1] != '\'')) {
        throw ("doesn't have any apostrophes!");
    }
    line = line.substr(1, line.length() - 2);
    return line;
}

static string removeSpacingFromBegin(string line) {
    for(int i=0; line[i] == ' ' || line[i] == '\t' || line[i] == '\b';) {
        line = line.substr(1, line.length()-1);
    }
    return line;
}

static string removeSpacingFromEnd(string line) {
    int i = line.length()-1;
    for(; line[i] == ' ' || line[i] == '\t' || line[i] == '\b';--i) {}
    line = line.substr(0, i+1);
    return line;
}

static string removeSpaces(string line) {
    line = removeSpacingFromBegin(line);
    line = removeSpacingFromEnd(line);
    return line;
}

static string removeOpenSpiPar(string line) {
    line = removeSpaces(line);
    if(line[line.length()-1] == '{') {
        line = line.substr(0,line.length()-2);
    }
    return line;
}

static string removeEqual(string line) {
    for(int i=0;line[i] == ' ' || line[i] == '=' ;) {
        line = line.substr(1, line.length()-1);
    }
    return line;
}


static string removeParenthesis(string line) {
    line = removeSpaces(line);
    if (line[0] == '(' && line[line.length()-1] == ')') {
        line = line.substr(1,line.length()-2);
    }
    return line;
}


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
        } else {
            if (existNum(temp) && !checkIfLetter(temp[0])) {
                Number *num = new(nothrow) Number(temp);
                pro->popFrontExp();
                return num;
            } else {
                Var *var = new (nothrow) Var(temp, pro->getSymbolTable().at(temp));
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
static string removeBind (string line) {
    char c = line[0];
    string result="";
    string temp1;
    string temp2;
for (int i=0; i<line.length()-4;i++){
    if (c=='b' && line[i+1] == 'i' && line[i+2] == 'n' && line[i+3] == 'd') {
        temp1 = line.substr(0,i);
        temp2 = line.substr(i+4,line.length()-1);
        result = temp1+temp2;
    }
    c = line[i];
}
return result;
}

static string extractSecondVar (string line) {
    int i=0;
    char c = line[i];
    while (c != '=') {
        c = line[++i];
    }
    if (i>=line.length()) {
        return "";
    }
    line = line.substr(i+1, line.length()-1);
    line = removeSpaces(line);
    line = removeBind(line);
    line = removeSpaces(line);
    return line;
}



static string extractNum (string line) {
    string result = "";
    for (int i=0;checkIfDigit(line[i]);i++) {
        result+=line[i];
    }
    return result;
}
static Expression* makeExpression(string line, Pro* pro) {
    line = removeSpaces(line);
    if(checkIfOperator(line[0])) {
        line = "0"+line;
    }
    string forVar = "";
    forVar = extractVar(line);
    Var* var1 = NULL;
    if(forVar != "") {
        var1 =  new (nothrow) Var(forVar,pro->getSymbolTable().at(forVar));
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
            /*while (checkIfDigit(line[indx])) {
                c = line[indx];
                temp = stoi(s) * 10;
                temp += (c - '0');
                s = to_string(temp);
                indx++;
            }*/
            indx+=takeNum.length()-1;
            if (takeNum !="") {
                if(changeToMinus) {
                    takeNum = "-" +takeNum;
                }
                numbers.push(takeNum);
                changeToMinus = false;
            }
        } else if (checkOpenClosure(c))  {
            operators.push(s);
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
        } else if (checkIfLetter(c)) {
            forMinusAndPlus = false;
            string takeVar = line.substr(indx-1, line.length()-1);
            takeVar = extractVar(takeVar);
            if (changeToMinus) {
                takeVar = "-" + takeVar;
            }
            //var1 =  new (nothrow) Var(forVar,pro->getSymbolTable().at(takeVar));
            numbers.push(takeVar);
            indx+=takeVar.length()-1;
            changeToMinus = false;

        }
        s = "";
        indicator = true;
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

/*static findMinusAndPlus(string line) {
    char c = line[0];
    for(int i=0;c[i] != '-' && i<;i++)
}*/

static string extractWordFromLine(string line) {
    string result = "";
    int i = 0;
    while (line[i] != ' ' && line[i] != '\n' && i < line.length() && line[i] != '\t') {
        result += line[i];
        i++;
    }
    while(result[0] == ' ')
        result = result.substr(1);
    return result;
}

static string extractExpression(string line) {
    line = removeSpaces(line);
    string ex = "";
    for (int i=0; checkIfDigit(line[i]) || checkIfSmallLetter(line[i]); i++ ){
        ex+=line[i];
    }
    return ex;
}

static string extractSign(string line) {
    line = removeSpaces(line);
    string sign = "";
    for (int i=0; checkIfCondition(line[i]); i++ ){
        sign+=line[i];
    }
    return sign;
}




#endif //PROJECT_USEFULLFUNCTION_H