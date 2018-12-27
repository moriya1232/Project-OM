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
    Pro* p;
    bool shouldBind();
    string getOtherVar(string);
    string extratName(string);
public:
    SetVarCommand(string, string, Pro*);
    int doCommand();
};

#endif //PROJECT_SETVARCOMMAND_H
