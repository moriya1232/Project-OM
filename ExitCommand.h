//
// Created by omer on 12/26/18.
//

#include "Command.h"
using namespace std;
#ifndef PROJECT_ANOTHER_COPY_EXITCOMMAND_H
#define PROJECT_ANOTHER_COPY_EXITCOMMAND_H

class ExitCommand : public Command {
    Pro* p;
public:
    ExitCommand(string, string, Pro*);
    int doCommand();
    ~ExitCommand();
};

#endif //PROJECT_ANOTHER_COPY_EXITCOMMAND_H
