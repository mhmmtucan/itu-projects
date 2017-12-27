//
//  Card.hpp
//  aoa_hw1
//
//  Muhammet Uçan
//  150140707
//
using namespace std;
#ifndef Card_hpp
#define Card_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <stdio.h>
#include <cstring>

class Card {
private:
    string cardName;
    string cardClass;
    string cardRarity;
    string cardSet;
    string cardType;
    int cardCost;
public:
    Card(); // constructor
    Card(const Card&); // copy constructor
    void operator=(const Card&); // operator overloading for =
    
    // get & set methods in case of requirement
    string getCardName() const {return cardName;}
    string getCardClass() const {return cardClass;}
    string getCardRarity() const {return cardRarity;}
    string getCardSet() const {return cardSet;}
    string getCardType() const {return cardType;}
    int getCardCost() const {return cardCost;}
    void setCardName(string x) {cardName=x;}
    void setCardClass(string x) {cardClass=x;}
    void setCardRarity(string x) {cardRarity=x;}
    void setCardSet(string x) {cardSet=x;}
    void setCardType(string x) {cardType=x;}
    void setCardCost(int x) {cardCost=x;}
    
    // writing friend functions for input/output stream
    friend ostream &operator<<( ostream &output, const Card &tempCard ) {
        output << tempCard.cardName << "\t" << tempCard.cardClass << "\t" << tempCard.cardRarity << "\t" << tempCard.cardSet << "\t" << tempCard.cardType << "\t" << tempCard.cardCost << "\n";
        return output;
    }
    
    friend istream &operator>>( istream  &input, Card &tempCard ) {
         string cardCost;
         if (getline(input,tempCard.cardName,'\t') && getline(input,tempCard.cardClass,'\t') && getline(input,tempCard.cardRarity,'\t') && getline(input,tempCard.cardSet,'\t') && getline(input,tempCard.cardType,'\t') && getline(input,cardCost,'\n')) {
         tempCard.cardCost = stoi(cardCost);
         }
        return input;
    }
};

#endif /* Card_hpp */
