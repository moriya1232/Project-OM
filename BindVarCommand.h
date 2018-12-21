//
// Created by omer on 12/16/18.
//

#ifndef PROJECT_BINDVARCOMMAND_H
#define PROJECT_BINDVARCOMMAND_H

#include "iostream"
#include "Command.h"
#include "Pro.h"

using namespace std;

class BindVarCommand : public Command {
    Pro* p;
    string name;
    string line;
    string getLine(string);
public:
    BindVarCommand(Pro*, string, string);
    BindVarCommand(Pro*);
    int doCommand();
    double getValue(string);
    double getValueFromSimulator(string);
    void setValue(string, double);
    void setValueInSimulator(string, double);
    //string alreadyBinded(string);
};

#endif //PROJECT_BINDVARCOMMAND_H