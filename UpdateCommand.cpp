//
// Created by omer on 12/13/18.
//

#include "UsefulFunctions.h"
#include "UpdateCommand.h"
#include "BindVarCommand.h"


using namespace std;

    UpdateCommand:: UpdateCommand(string line, string name, Pro* p) : Command(line, name){ this->p = p;}


    int UpdateCommand:: doCommand() {
        string var = "", newValue = "";
        string lin = this->getLine();
        lin = removeSpaces(lin);
        var = extractVar(lin);
        lin = lin.substr(var.length() + 1);
        lin = removeSpaces(lin);
        // get rid of the "="
        lin = removeEqual(lin);
        newValue = lin;
        double val = makeExpression(newValue,p)->calculate();
        p->setVar(var, val);
        cout << this->getName() << " " << val << endl;
        // breaks = 0
        return 0;
    }