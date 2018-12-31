//
// Created by omer on 12/13/18.
//

#include "PrintCommand.h"
#include "UsefulFunctions.h"

using namespace std;



/**
 * this is a constractor
 * @param line
 * @param name
 * @param p - pro
 */
PrintCommand:: PrintCommand(string line, string name, Pro* p) : Command(line, name) {
    this->p = p;
}

/**
 * so the commnd of printing
 * @return 0;
 */
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
        double val2 = this->p->getSymbolTable()->at(var);
        // cout << "simulator:" << var << " " << val << endl;
        cout << var << " " << val2 << endl;
    } else {
        var = removeApostrophes(var);
        cout << var << endl;
    }
    return 0;
}