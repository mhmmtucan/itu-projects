//
//  strategies1.hpp
//  homework2
//
//  150140707
//  Muhammet UÇAN
//

#ifndef strategies1_hpp
#define strategies1_hpp

#include <iostream>
#include "AdderRemover.hpp"
#include "strategies2.hpp"
using namespace std;

class FAFR: public AdderRemover {
public:
    void add(int);
    void remove();
    void setTraverser();
    void display() const;
    void traverse() const;
};

class FALR: public AdderRemover {
public:
    void add(int);
    void remove();
    void setTraverser();
    void display() const;
    void traverse() const;
};

class LAFR: public AdderRemover {
public:
    void add(int);
    void remove();
    void setTraverser();
    void display() const;
    void traverse() const;
};

class LALR: public AdderRemover {
public:
    void add(int);
    void remove();
    void setTraverser();
    void display() const;
    void traverse() const;
};

#endif /* strategies1_hpp */
