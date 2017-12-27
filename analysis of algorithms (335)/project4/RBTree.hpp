//
//  RBTree.hpp
//  aoa_hw4
//
//  Created by Muhammet Uçan on 9.12.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#ifndef RBTree_hpp
#define RBTree_hpp
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <math.h>
using namespace std;
struct node {
    string key;
    char gender;
    int age;
    char color;
    int num_woman;
    int num_man;
    int depth;
    node* parent;
    node* left;
    node* right;
};

class RBTree {
    node* root;
    node* q;
public:
    RBTree() {
        q = NULL;
        root = NULL;
    }
    void read_from_file(string);
    void insert(node*);
    void bst_insert(node*);
    void fix_insertion(node*);
    void left_rotate(node*);
    void right_rotate(node*);
    void get_level(node*);
    void print_r(node*);
    void print_root();
    void print_node(node*, int);
    void regulate_size(node*);
    node* get_root() {return root;}
    node* select_man(node*,int);
    node* select_woman(node*,int);
};

#endif /* RBTree_hpp */
