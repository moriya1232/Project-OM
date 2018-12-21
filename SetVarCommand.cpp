//
// Created by omer on 12/8/18.
//

#include "SetVarCommand.h"


SetVarCommand:: SetVarCommand(Var* var1, string name, double d, string line, Pro* pro1) :Command(line, name) {
    this->var = var1;
    this->newDouble = d;
    this->pro = pro1;

}
SetVarCommand:: SetVarCommand(string v, string name, double d, string line, Pro* pro1) :Command(line, name) {
    Var* temp = new (nothrow) Var(v,d);
    this->var = temp;
    this->newDouble = d;
    this->pro = pro1;

}
int SetVarCommand::  doCommand() {
    string directory = extractDirectory(this->getLine());
    string secondVar ="";
    bool isDire;
    if (directory =="") {
        isDire = false;
        secondVar = extractSecondVar(this->getLine());
    } else {
        isDire = true;
    }
    if (shouldBind()) {
        string name = this->var->getName();
        if (isDire) {
            pro->addNamesAndDirectory(name, directory);
            pro->setVarBind(this->var->getName(), directory);
        } else {
            pro->setVarBind(this->var->getName(), secondVar);
        }
        // extract the other name
        /*string otherName = "";
        int i = 0;
        char c = this->getLine()[i];
        while (c != '=') {
            c = this->getLine()[++i];
        }
        i += 1;
        while (i < this->getLine().length()) {
            c = this->getLine()[i];
            otherName += c;
            i++;
        }*/
        //otherName = removeSpaces(otherName);

    }
    var->setValue(this->pro->getValueFromSimulator(var->getName(), directory));
    if (isDire) {
        if (!pro->isVarInSymbolTable(directory)) {
            pro->addSymbolTable(directory, this->newDouble);
        } else {
            if (newDouble != pro->getSymbolTable().at(directory)) {
                pro->setVar(directory, this->newDouble);
            }
        }
    }/* else {
        pro->setVar(var->getName(), this->newDouble);
    }*/

}
bool SetVarCommand::shouldBind() {
    string line = this->getLine();
    bool found1 = false, found2 = false;
    int i = 0;
    char c = line[i];
    string s = "";
    while (i < line.length()) {
        while (c != ' ' && c != '/' && c != '"' && c != '=') {
            s += c;
            c = line[++i];
        }
        if (s == "var") {
            found1 = true;
        }
        if (s == "bind") {
            found2 = true;
        }
        s = "";
        c = line[++i];
    }
    if (found1 && found2) {
        return true;
    }
    return false;
}