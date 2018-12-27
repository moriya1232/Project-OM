//
// Created by moriya on 22/12/18.
//

#ifndef PROJECT_ANOTHER_COPY_ENTERC_H
#define PROJECT_ANOTHER_COPY_ENTERC_H

#include "Command.h"


class Enterc: public Command{

public:
    Enterc(string line, string name);
    int doCommand();


};


#endif //PROJECT_ANOTHER_COPY_ENTERC_H
