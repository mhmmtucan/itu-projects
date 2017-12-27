//
//  p3list.cpp
//  aoa_hw3
//
//  Created by Muhammet Uçan on 19.11.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#include "p3list.hpp"

// if readFromFile is for insertion bool has to set true
bool List::readFromFile(string filename,bool isInsertion) {
    ifstream file;
    file.open(filename);
    if (!file.is_open()) return false;
    
    BookChar temp = BookChar(isInsertion);
    while (!file.eof()) {
        file >> temp;
        container.push_back(temp);
    }
    file.close();
    return true;
}

bool List::insertion() {
    return readFromFile("ds-set-input.txt",true);
}

bool List::readForlookup() {
    return readFromFile("ds-set-lookup.txt",false);
}


void List::lookup(List& listToLookUp) {
    ofstream file;
    file.open("ds-set-output-list.txt");
    vector<BookChar> lookUpContainer = listToLookUp.getContainer();
    
    
    for (int i=0; i<lookUpContainer.size(); i++) {
        const unsigned long key = lookUpContainer[i].getKey();
        
        auto it = find_if(container.begin(), container.end(), [&key](const BookChar& obj) {
            return obj.getKey() == key;
        });
        
        if (it != container.end())
        {
            // found element. it is an iterator to the first matching element.
            auto index = std::distance(container.begin(), it);
            lookUpContainer[i].setC(container[index].getC());
            file << lookUpContainer[i];
        }
    }
    
    /*
     // another way off traversing container, can be used
    for (int i=0; i<lookUpContainer.size(); i++) {
        printf("%d-",i);
        for (int j=0; j<container.size(); j++) {
            if (lookUpContainer[i].getKey() == container[j].getKey()) {
                lookUpContainer[i].setC(container[j].getC());
                file << lookUpContainer[i];
            }
        }
    }
     */
    file.close();
}
