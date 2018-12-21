//
// Created by moriya on 15/12/18.
//

#ifndef PROJECT_SETVARCOMMAND_H
#define PROJECT_SETVARCOMMAND_H

//
// Created by omer on 12/8/18.
//

#include "Command.h"
#include "Var.h"
#include "Pro.h"

class SetVarCommand : public Command {
    Var *var;
    double newDouble;
    Pro* pro;
    bool shouldBind();
public:
    SetVarCommand(Var* var1, string name, double d, string line, Pro* pro1);
    SetVarCommand(string v, string name, double d, string line, Pro* pro1);
    int doCommand();
};

#endif //PROJECT_SETVARCOMMAND_H
