//
// Created by moriya on 15/12/18.
//

#ifndef PROJECT_UPDATECOMMAND_H
#define PROJECT_UPDATECOMMAND_H


//
// Created by omer on 12/13/18.
//

#include "Command.h"
#include "Pro.h"

using namespace std;

class UpdateCommand : public Command {
    Pro* p;

public:
    UpdateCommand(string line, string name, Pro* p);

    int doCommand();
};
#endif //PROJECT_UPDATECOMMAND_H
