//
// Created by moriya on 25/12/18.
//

#include "Collector.h"

/**
 * this is a constractor
 */
Collector::Collector() {
    list<void*> l1;
    list<string> l2;
    this->items = l1;
    this->strings = l2;
}

/**
 * add an opject to collector
 * @param v  - the object
 */
void Collector::addItem(void* v) {
    this->items.push_back(v);
}

/**
 * thiis is a distractor
 */
Collector::~Collector() {
    for (list<void*>::iterator it = items.begin(); it != items.end(); it++) {
        delete(*it);
    }
}