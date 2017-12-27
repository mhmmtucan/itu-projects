//
//  strategies2.hpp
//  homework2
//
//  150140707
//  Muhammet UÇAN
//

#ifndef strategies2_hpp
#define strategies2_hpp

#include <iostream>
#include "ARTraverser.hpp"

class ARTF: public ARTraverser {
public:
    ARTF(Node *first) {
        current = first;
    }
    bool hasNode()const;
    Node* next();
};

class ARTL: public ARTraverser {
public:
    ARTL(Node *last) {
        current = last;
    }
    bool hasNode() const;
    Node* next();
};

#endif /* strategies2_hpp */
