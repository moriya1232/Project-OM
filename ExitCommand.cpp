//
// Created by omer on 12/26/18.
//

#include "ExitCommand.h"

ExitCommand::ExitCommand(string line, string name, Pro* p) : Command(line, name) {
    this->p = p;
}

int ExitCommand::doCommand() {
    delete(p);
    exit(0);
}

ExitCommand::~ExitCommand() {}