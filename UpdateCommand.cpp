//
// Created by omer on 12/13/18.
//

#include "UsefulFunctions.h"
#include "UpdateCommand.h"


using namespace std;

    UpdateCommand:: UpdateCommand(string line, string name, Pro* p) : Command(line, name){ this->p = p;}

    int UpdateCommand:: doCommand() {
        this->p->setRun(true);
        string var = "", newValue = "";
        double val = 0;
        string lin = this->getLine();
        lin = removeSpaces(lin);
        var = extractVar(lin);
        // if var is a directory
        lin = lin.substr(var.length() + 1);
        lin = removeSpaces(lin);
        // get rid of the "="
        lin = removeEqual(lin);
        newValue = lin;
        // if lin is a var we also have in our symbolTable
        if (this->p->isExsistInSymbolTable(newValue)) {
            val = this->p->getSymbolTable()->at(newValue);
        } else {
            string directory = extractDirectory(this->getLine());
            directory = removeApostrophes(directory);
            if (directory != "" && this->p->isVarInSymbolTable(directory)) {
                val = this->p->getSymbolTable()->at(directory);
            } else {
                // if lin is an expression
                val = makeExpression(newValue, p)->calculate();
            }
        }
        if (var[0] == '/') {
            this->p->setValueInSimulator(var, val);
        } else {
            this->p->setVarInSymbolTable(var, val);
        }
        if (this->p->isVarBinded(var)) {
            list<string> bv = this->p->getBindMap().at(var);
            this->p->updateBindedVars(bv, val);
        }

        //p->setVar(var, val);
        this->p->setRun(false);
        return 0;
    }