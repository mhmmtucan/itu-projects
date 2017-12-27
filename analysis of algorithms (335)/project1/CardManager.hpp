//
//  CardManager.hpp
//  aoa_hw1
//
//  Muhammet Uçan
//  150140707
//

#ifndef CardManager_hpp
#define CardManager_hpp


#include "Card.hpp"

class CardManager {
public:
    vector<Card> cards; // container for cards
    CardManager(string); // constructor for card manager
    
    // function prototypes
    void insertionSort(string);
    void mergeSort(int, int, string);
    void merge(int, int, int, string);
    vector<Card> readFromFile(string);
    
    // I/O functions
    void writeToFile(const vector<Card>&,string);
};

#endif /* CardManager_hpp */
