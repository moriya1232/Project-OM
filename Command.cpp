//
// Created by omer on 12/7/18.
//

#include "Command.h"

using namespace std;

Command::Command(string line, string name) {
    this->line = line;
    this->name = name;
}

string Command::getLine() {
    return this->line;
}

string Command::getName() {return this->name;}