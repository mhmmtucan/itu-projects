//
//  strategies2.cpp
//  homework2
//
//  150140707
//  Muhammet UÇAN
//

#include "strategies2.hpp"


bool ARTF::hasNode() const {
    return current;
}

Node* ARTF::next() {
    Node *temp = current;
    current = current->next;
    return temp;
}


bool ARTL::hasNode() const {
    return current;
}

Node* ARTL::next() {
    Node *temp = current;
    current = current->prev;
    return temp;
}
