//
//  RBTree.cpp
//  aoa_hw4
//
//  Created by Muhammet Uçan on 9.12.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#include "RBTree.hpp"


void RBTree::read_from_file(string filename) {
    string line;
    string delimeter = "\t";
    string token;
    ifstream file (filename);
    
    if (file.is_open()) {
        while (getline(file,line)) {
            // create nodes here
            // line taken, split with tab delimeter
            node *temp = new node;
            token = line.substr(0,line.find("\t"));
            line.erase(0,line.find(delimeter)+1);
            temp->key = token;
            token = line.substr(0,line.find("\t"));
            line.erase(0,line.find(delimeter)+1);
            temp->gender = token[0];
            token = line.substr(0,line.find("\n"));
            line.erase(0,line.find(delimeter)+1);
            temp->age = stoi(token);
            temp->color = 'R';
            temp->parent = NULL;
            temp->left = NULL;
            temp->right = NULL;
            temp->depth = 0;
            temp->num_man = 0;
            temp->num_woman = 0;
            insert(temp);
        }
    }
    file.close();
}

void RBTree::bst_insert(node *new_node) {
    node *curr = root;
    node *parent = NULL;
    if (!root) {
        root = new_node;
        new_node->parent = NULL;
    } else {
        parent = root;
        while (curr) {
            parent = curr;
            
            if (new_node->key.compare(curr->key) > 0)
                curr = curr->right;
            else
                curr = curr->left;
        }
        
        new_node->parent = parent;
        
        if (new_node->key.compare(parent->key) > 0)
            parent->right = new_node;
        else
            parent->left = new_node;
    }
}

void RBTree::insert(node *n) {
    bst_insert(n);
    fix_insertion(n);
}

void RBTree::fix_insertion(node *n) {
    node *p = NULL; // parent
    node *g = NULL; // grand parent
    while (n != root && n->color != 'B' && n->parent->color == 'R') {
        p = n->parent;
        g = n->parent->parent;
        
        // parent of n is left child of grand parent of n
        if (p == g->left) {
            node *u = g->right; // uncle
            
            // uncle is red, do recoloring
            if (u && u->color == 'R') {
                g->color = 'R';
                p->color = 'B';
                u->color = 'B';
                n = g;
            }
            else {
                // n is right child, do left rotation
                if (n == p->right) {
                    left_rotate(p);
                    n = p;
                    p = n->parent;
                }
                
                // n is left child, do right rotation
                right_rotate(g);
                swap(p->color, g->color);
                n = p;
            }
        }
        // parent of n is right child of grand parent of n
        else {
            node *u= g->left; // uncle
            
            // uncle is red, do recoloring
            if (u && u->color == 'R') {
                g->color = 'R';
                p->color = 'B';
                u->color = 'B';
                n = g;
            }
            else {
                // n is left child, do right rotate
                if (n == p->left) {
                    right_rotate(p);
                    n = p;
                    p = n->parent;
                }
                
                // n is right child, do left rotate
                left_rotate(g);
                swap(p->color, g->color);
                n = p;
            }
        }
    }
    root->color = 'B';
}

void RBTree::left_rotate(node *n) {
    node *right_node = n->right;
    n->right = right_node->left;
    
    if (n->right)
        n->right->parent = n;
    
    right_node->parent = n->parent;
    
    if (!n->parent)
        root = right_node;
    else if (n == n->parent->left)
        n->parent->left = right_node;
    else
        n->parent->right = right_node;
    
    right_node->left = n;
    n->parent = right_node;
}

void RBTree::right_rotate(node *n) {
    node *left_node = n->left;
    n->left = left_node->right;
    
    if (n->left)
        n->left->parent = n;
    
    left_node->parent = n->parent;
    
    if (!n->parent)
        root = left_node;
    else if (n == n->parent->left)
        n->parent->left = left_node;
    else
        n->parent->right = left_node;
    
    left_node->right = n;
    n->parent = left_node;
}

void RBTree::regulate_size(node *n) {
    if (n) {
        if(n->left) regulate_size(n->left);
        if (n->right) regulate_size(n->right);
        // sum of ternary if conditions, if n left or right exists, take action otherwise 0
        n->num_woman = ((n->left) ? n->left->num_woman : 0) +  ((n->right) ? n->right->num_woman : 0);
        n->num_man = ((n->left) ? n->left->num_man : 0) +  ((n->right) ? n->right->num_man : 0);
        (n->gender == 'F') ? n->num_woman++ : n->num_man++;
    }
}

node* RBTree::select_man(node* n,int ith) {
    int r = ((n->left) ? n->left->num_man : 0) + ((n->gender == 'M') ? 1 : 0);
    if (ith == r) {
        if (n->gender == 'M') return n;
        else return select_man(n->left, ith);
    }
    else if (ith < r) return select_man(n->left, ith);
    else return select_man(n->right, ith-r);
}

node* RBTree::select_woman(node* n,int ith) {
    int r = ((n->left) ? n->left->num_woman : 0) + ((n->gender == 'F') ? 1 : 0);
    if (ith == r) {
        if (n->gender == 'F') return n;
        else return select_man(n->left, ith);
    }
    else if (ith < r) return select_woman(n->left, ith);
    else return select_woman(n->right, ith-r);
}

void RBTree::get_level(node *n) {
    node *t = n;
    while (t->parent && t->parent != root) {
        n->depth++;
        t = t->parent;
    }
}

void RBTree::print_r(node *n)
{
    if(root==NULL)
    {
        cout<<"\nEmpty";
        return ;
    }
    if(n!=NULL)
    {
        if(n->left)
            print_r(n->left);
        get_level(n);
        for (int i=0; i<n->depth*3; i++) {
            printf("\t");
        }
        if (n->parent && n == n->parent->left)
            printf("     ┌");
        if (n->parent && n == n->parent->right)
            printf("     └");
        if (n!=root) printf("--------");
        printf("(%c)%s-%d-%c | F:%d-M:%d\n",n->color,n->key.c_str(),n->age,n->gender,n->num_woman,n->num_man);
        if(n->right)
            print_r(n->right);
    }
}

void RBTree::print_node(node *n, int ith) {
    switch (ith) {
        case 1:
            cout << "1st" << ((n->gender == 'F') ? " woman: " : "man: ") << n->key << "\n";
            break;
        case 2:
            cout << "2nd" << ((n->gender == 'F') ? " woman: " : " man: ") << n->key << "\n";
            break;
        case 3:
            cout << "3rd" << ((n->gender == 'F') ? " woman: " : " man: ") << n->key << "\n";
            break;
        default:
            cout << ith << "th" << ((n->gender == 'F') ? " woman: " : " man: ") << n->key << "\n";
            break;
    }
}

void RBTree::print_root() {
    print_r(root);
}
