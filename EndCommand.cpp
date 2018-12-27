//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//

#include "EndCommand.h"

/**
 * this function is a constructor of end command, this command is tells us that we end the
 * if or loop command, we insert to this command if we get "}"
 * @param line - the line of the end command
 * @param name - the name of the command.
 */
EndCommand:: EndCommand(string line, string name):Command(line,name){}

/**
 * this function does the end shows us that the function is done. but it does nothing so
 * is returns 0.
 * @return 0
 */
int EndCommand:: doCommand(){
    return 0;
}