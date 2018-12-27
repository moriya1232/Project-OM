//
// Created by omer on 12/13/18.
//

#include "PrintCommand.h"

using namespace std;


PrintCommand:: PrintCommand(string line, string name, Pro* p) : Command(line, name) {
    this->p = p;
}

string PrintCommand:: extractWordFromLine(string line) {
    string result = "";
    int i = 0;
    while (line[i] != ' ' && line[i] != '\n' && i < line.length()) {
        result += line[i];
        i++;
    }
    return result;
}

int PrintCommand:: doCommand() {
    bool isParam = false;
    string tempLine = this->getLine();
    //remove "print"
    tempLine = tempLine.substr(extractWordFromLine(tempLine).length() + 1);
    tempLine = removeSpaces(tempLine);
    string var = extractDirectory(tempLine);
    if (var =="") {
        isParam = true;
        var = extractWordFromLine(tempLine);
    }
    if (isParam) {
        //string directory = this->p->getNamesAndDirectories().at(var);
        // double val = this->p->getValueFromSimulator(directory);
        double val2 = this->p->getSymbolTable()->at(var);
        // cout << "simulator:" << var << " " << val << endl;
        cout << var << " " << val2 << endl;
    } else {
        var = removeApostrophes(var);
        cout << var << endl;
    }
    return 0;
}