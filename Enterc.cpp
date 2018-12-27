//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//

#include "Enterc.h"
#include "iostream"
#include "unistd.h"
using namespace std;

/**
 * this function is a constractor of enterc, it just insert the values to command.
 * @param line - the line of the command
 * @param name - the name of the command
 */
Enterc:: Enterc(string line, string name) : Command(line,name) {}

/**
 * this command do the command, in this command we just get 1 char.
 * @return 0
 */
int Enterc::doCommand() {
    char c;
    cin >> c;
    return 0;
}

