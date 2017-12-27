//
//  strategies1.cpp
//  homework2
//
//  150140707
//  Muhammet UÇAN
//

#include "strategies1.hpp"


// First add First Remove
void FAFR::add(int num) {
    temp = new Node;
    temp->data = num;
    temp->next = NULL;
    temp->prev = NULL;
    nodeCount++;
    if (!head) {
        head = temp;
        tail = temp;
    } else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

void FAFR::remove() {
    temp = head;
    head = head->next;
    head->prev = NULL;
    nodeCount--;
    delete temp;
}

void FAFR::setTraverser() {
    traverser = new ARTF(head);
}

void FAFR::display() const {
    cout << "FAFR | NodeCount: " << nodeCount << endl;
    cout << "-----------------" << endl;
    AdderRemover::display();
}

void FAFR::traverse() const {
    cout << "FAFR | NodeCount: " << nodeCount << endl;
    cout << "-----------------" << endl;
    AdderRemover::traverse();
}

// First Add Last Remove
void FALR::add(int num) {
    temp = new Node;
    temp->data = num;
    temp->next = NULL;
    temp->prev = NULL;
    nodeCount++;
    if (!head) {
        head = temp;
        tail = temp;
    } else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

void FALR::remove() {
    temp = tail;
    tail = tail->prev;
    tail->next = NULL;
    nodeCount--;
    delete temp;
}

void FALR::setTraverser() {
    traverser = new ARTF(head);
}

void FALR::display() const {
    cout << "FALR | NodeCount: " << nodeCount << endl;
    cout << "-----------------" << endl;
    AdderRemover::display();
}

void FALR::traverse() const {
    cout << "FALR | NodeCount: " << nodeCount << endl;
    cout << "-----------------" << endl;
    AdderRemover::traverse();
}

// Last Add First Remove
void LAFR::add(int num) {
    temp = new Node;
    temp->data = num;
    temp->next = NULL;
    temp->prev = NULL;
    nodeCount++;
    if (!head) {
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void LAFR::remove() {
    temp = head;
    head = head->next;
    head->prev = NULL;
    nodeCount--;
    delete temp;
}

void LAFR::setTraverser() {
    traverser = new ARTL(tail);
}

void LAFR::display() const {
    cout << "LAFR | NodeCount: " << nodeCount << endl;
    cout << "-----------------" << endl;
    AdderRemover::display();
}

void LAFR::traverse() const {
    cout << "LAFR | NodeCount: " << nodeCount << endl;
    cout << "-----------------" << endl;
    AdderRemover::traverse();
}

// Last Add Last Remove
void LALR::add(int num) {
    temp = new Node;
    temp->data = num;
    temp->next = NULL;
    temp->prev = NULL;
    nodeCount++;
    if (!head) {
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void LALR::remove() {
    temp = tail;
    tail = tail->prev;
    tail->next = NULL;
    nodeCount--;
    delete temp;
}

void LALR::setTraverser() {
    traverser = new ARTL(tail);
}

void LALR::display() const {
    cout << "LALR | NodeCount: " << nodeCount << endl;
    cout << "-----------------" << endl;
    AdderRemover::display();
}

void LALR::traverse() const {
    cout << "LALR | NodeCount: " << nodeCount << endl;
    cout << "-----------------" << endl;
    AdderRemover::traverse();
}
