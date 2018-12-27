//
// Created by moriya on 25/12/18.
//

#ifndef PROJECT_ANOTHER_COPY_COLLECTOR_H
#define PROJECT_ANOTHER_COPY_COLLECTOR_H

#include <string>
#include <list>

using namespace std;

class Collector {
    list<void*> items;
    list<string> strings;
public:
    Collector();
    void addItem(void*);
    void addString(string);
    ~Collector();
};

#endif //PROJECT_ANOTHER_COPY_COLLECTOR_H
