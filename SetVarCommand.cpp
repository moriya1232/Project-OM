//
// Created by omer on 12/8/18.
//

#include "SetVarCommand.h"

/**
 * constractor
 * @param line
 * @param name
 * @param p
 */
SetVarCommand:: SetVarCommand(string line, string name, Pro* p) :Command(line, name) {
    this->p = p;
}

/**
 * get the var after thr"="
 * @param line
 * @return string
 */
string SetVarCommand::getOtherVar(string line) {
    int i = 0;
    string s = "";
    char c = line[i];
    while (c != '=' && i < line.length()) {
        c = line[++i];
    }
    i++;
    c = line[i];
    while (i < line.length()) {
        s += c;
        c = line[++i];
    }
    s = removeSpaces(s);
    if (shouldBind()) {
        if (s.substr(0, 4) == "bind") {
            s = s.substr(4);
        }
    }
    return s;
}

/**
 * get the name from line
 * @param line
 * @return the ncme
 */
string extractName(string line) {
    int i = 0, count = 0;
    char c = line[i];
    while (i < line.length()) {
        if (c == ' ') {
            count++;
        }
        c = line[++i];
    }
    if (count < 2) {
        return "";
    }
    line = line.substr(extractWordFromLine(line).length() + 1);
    return extractWordFromLine(line);
}
/**
 * extract the name
 * @return 0 it cussess
 */
int SetVarCommand::  doCommand() {
    double value = 0;
    string varName = extractName(this->getLine());
    // get the directory
    string directory = extractDirectory(this->getLine());
    string otherVar = getOtherVar(this->getLine());
    otherVar = removeSpaces(otherVar);
    directory = removeApostrophes(directory);
    // had directory
    if (directory != "") {
        if(this->p->isVarInSymbolTable(directory)) {
            value = this->p->getSymbolTable()->at(directory);
        } else {
            value =0;
        }
    } else {
        if (this->p->isVarInSymbolTable(otherVar)) {
            value = this->p->getSymbolTable()->at(otherVar);
        } else {
            value = makeExpression(otherVar, p)->calculate();
        }
    }
    //update
    if (!this->p->isVarInSymbolTable(varName)) {
        this->p->addSymbolTable(varName, value);
    } else {
        this->p->setVarInSymbolTable(varName, value);
    }
    if (shouldBind()) {
        if (varName == "rpm") {
            int x  =5;
        }
        if (directory != "") {
            p->addNamesAndDirectory(varName, directory);
            p->setVarBind(varName, directory);
        } else {
            p->setVarBind(varName, otherVar);
        }
    }
}

/**
 * if should bind
 * @return true or false
 */
bool SetVarCommand::shouldBind() {
    string line = this->getLine();
    bool found1 = false, found2 = false;
    int i = 0;
    char c = line[i];
    string s = "";
    while (i < line.length()) {
        while (c != ' ' && c != '/' && c != '"' && c != '=' && c != '\0' && '\\') {
            s += c;
            c = line[++i];
        }
        //check if bind or var
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