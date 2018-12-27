//
// Created by moriya on 25/12/18.
//

#include "Collector.h"

Collector::Collector() {
    list<void*> l1;
    list<string> l2;
    this->items = l1;
    this->strings = l2;
}

void Collector::addItem(void* v) {
    this->items.push_back(v);
}

void Collector::addString(string s) {
    this->strings.push_back(s);
}

Collector::~Collector() {
    for (list<void*>::iterator it = items.begin(); it != items.end(); it++) {
        delete(*it);
    }
}