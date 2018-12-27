//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//

#include "Command.h"

using namespace std;

/**
 * this function is the constructor of Command.
 * @param line - the line of the command.
 * @param name - the name of the command
 */
Command::Command(string line, string name) {
    this->line = line;
    this->name = name;
}

/**
 * this function get the line of the command.
 * @return string of the line.
 */
string Command::getLine() {
    return this->line;
}

/**
 * this function get the name of the command.
 * @return stirng of the name.
 */
string Command::getName() {return this->name;}