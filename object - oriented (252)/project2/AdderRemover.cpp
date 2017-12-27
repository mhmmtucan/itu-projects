//
//  AdderRemover.cpp
//  homework2
//
//  150140707
//  Muhammet UÇAN
//

#include <iostream>
#include "AdderRemover.hpp"
using namespace std;

AdderRemover::AdderRemover() {
    head = NULL;
    tail = NULL;
    temp = NULL;
    nodeCount = 0;
    traverser = NULL;
}

void AdderRemover::display() const {
    if (nodeCount!=0) {
        Node *temp = head;
        while (temp) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    } else {
        cout << "There is no element to print" << endl;
    }
}

void AdderRemover::removeAll() {
    Node *temp = head;
    while (head) {
        temp = head->next;
        delete head;
        head = temp;
        nodeCount--;
    }
    tail = NULL;
}

void AdderRemover::traverse() const {
    if (nodeCount!=0) {
        Node *temp;
        while (traverser->hasNode()) {
            temp = traverser->next();
            cout << temp->data << endl;
        }
    } else {
        cout << "There is no element to print" << endl;
    }
}
