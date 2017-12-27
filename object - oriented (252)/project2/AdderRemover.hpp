//
//  AdderRemover.hpp
//  homework2
//
//  Created by Muhammet Uçan on 20.04.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#ifndef AdderRemover_hpp
#define AdderRemover_hpp

#include <string>
#include "node.h"
#include "ARTraverser.hpp"
using namespace std;

class AdderRemover {
protected:
    Node *head;
    Node *tail;
    Node *temp; // if AdderRemover class was written by someone, temp can be included in derived classes, for the sake of clarity it added here
    string name;
    int nodeCount;
    ARTraverser *traverser;
    
public:
    AdderRemover();
    ~AdderRemover() {
        Node *p;
        while (temp) {
            p = temp->next;
            delete temp;
            temp = p;
        }
    }
    virtual void add(int) = 0; // pure virtual
    virtual void remove() = 0; // pure virtual
    virtual void setTraverser() = 0; // pure virtual
    virtual void display() const;
    void removeAll();
    virtual void traverse() const;
};

#endif /* AdderRemover_hpp */
