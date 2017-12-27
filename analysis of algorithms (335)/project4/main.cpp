//
//  main.cpp
//  aoa_hw4
//
//  Created by Muhammet Uçan on 9.12.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#include <iostream>
#include "RBTree.hpp"

int main(int argc, const char * argv[]) {
    RBTree my_tree = *new RBTree();
    
    my_tree.read_from_file(argv[1]);
    my_tree.regulate_size(my_tree.get_root());
    my_tree.print_root();
    my_tree.print_node(my_tree.select_man(my_tree.get_root(), 3), 3);
    my_tree.print_node(my_tree.select_woman(my_tree.get_root(), 4), 4);
    
    
    return 0;
}
