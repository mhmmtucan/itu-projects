//
//  ARTraverser.hpp
//  homework2
//
//  150140707
//  Muhammet UÇAN
//

#ifndef ARTraverser_hpp
#define ARTraverser_hpp

#include "node.h"

class ARTraverser {
protected:
    Node *current;
public:
    ARTraverser(){current = NULL;}
    virtual bool hasNode()const = 0;
    virtual Node* next() = 0;
};

#endif /* ARTraverser_hpp */
