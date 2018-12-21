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
    string tempLine = this->getLine();
    tempLine = tempLine.substr(extractWordFromLine(tempLine).length() + 1);
    tempLine = removeSpaces(tempLine);
    string var = extractWordFromLine(tempLine);
    if (var[0]=='"' && var[var.length()-1=='"']) {
        cout << removeApostrophes(var) << endl;
    } else {
        double val = this->p->getSymbolTable().at(var);
        cout << var << " " << val << endl;
    }
    return 0;
}