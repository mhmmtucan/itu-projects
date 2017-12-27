//
//  p3dict.cpp
//  aoa_hw3
//
//  Created by Muhammet Uçan on 19.11.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#include "p3dict.hpp"
#include <cmath>

HashMap::HashMap() {
    table = new HashNode * [TABLE_SIZE];
    totalCollision = 0;
    avColFor1k = 0; avColFor10k = 0; avColFor100k=0; avColForAll = 0;
}

HashMap::~HashMap() {
    for (int i=0; i<TABLE_SIZE; i++) {
        table[i] = NULL;
    }
    delete [] table;
}

unsigned long HashMap::hashFunc(unsigned long key) {
    double a = 0.61803398875;
    return floor(TABLE_SIZE * fmod(key * a, 1));
}

unsigned long HashMap::quadraticProbe(unsigned long hashValue, int& collisions) {
    collisions++;
    unsigned long newHashValue = hashValue + (7 * collisions) + (3 * collisions * collisions);
    if (newHashValue > TABLE_SIZE) newHashValue = newHashValue % TABLE_SIZE;
    return newHashValue;
}

int HashMap::put(unsigned long key, const BookChar &value) {
    unsigned long hashValue = hashFunc(key);
    HashNode *entry = table[hashValue];
    int collisions = 0;
    while (entry != NULL && entry->getKey() != key) {
        // collision
        // when collisions occur send collision number to probe function by reference
        // get new hashvalue, end point with entry
        hashValue = quadraticProbe(hashValue, collisions);
        entry = table[hashValue];
    }
    if (entry == NULL) {
        table[hashValue] = new HashNode(key,value);
        // after inserting return collision number to calculate avarage
        return collisions;
    } else {
        printf("table cannot found suitable hashvalue\n");
        return 0;
    }
}

BookChar HashMap::get(unsigned long key) {
    unsigned long hashValue = hashFunc(key);
    HashNode *entry = table[hashValue];
    int collisionNum = 0;
    while (entry != NULL) {
        // travese table until finding key
        if (entry->getKey() == key) {
            return entry->getValue();
        } else {
            hashValue = quadraticProbe(hashValue, collisionNum);
            entry = table[hashValue];
        }
    }
    // not found
    return BookChar();
}

bool HashMap::readFromFile(string filename,bool isInsertion) {
    ifstream file;
    file.open(filename);
    if (!file.is_open()) return false;
    int lineCount = 0;
    BookChar temp = BookChar(isInsertion);
    while (!file.eof()) {
        file >> temp;
        lineCount++;
        
        totalCollision += put(temp.getKey(), temp);
        switch (lineCount) {
            case 1000:
                avColFor1k = (double)totalCollision / lineCount;
                break;
            case 10000:
                avColFor10k = (double)totalCollision / lineCount;
                break;
            case 100000:
                avColFor100k = (double)totalCollision /lineCount;
                break;
            case TABLE_SIZE-1:
                avColForAll = (double)totalCollision / lineCount;
                break;
            default:
                break;
        }
    }
    file.close();
    return true;
}
// read and put to the table
bool HashMap::insertion() {
    return readFromFile("ds-set-input.txt",true);
}
// lookup and write to file
bool HashMap::lookup() {
    ifstream inFile;
    inFile.open("ds-set-lookup.txt");
    ofstream outFile;
    outFile.open("ds-set-output-dict.txt");
    if (!inFile.is_open()) return false;
    
    BookChar temp = BookChar(false);
    while (!inFile.eof()) {
        inFile >> temp;
        temp.setC(get(temp.getKey()).getC());
        outFile << temp;
    }
    inFile.close();
    outFile.close();
    return true;
}

double HashMap::getAverages(int numberofAv) {
    switch (numberofAv) {
        case 1000:
            return avColFor1k;
            break;
        case 10000:
            return avColFor10k;
            break;
        case 100000:
            return avColFor100k;
            break;
        default:
            return avColForAll;
            break;
    }
}

