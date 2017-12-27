//
//  Card.cpp
//  aoa_hw1
//
//  Muhammet Uçan
//  150140707
//

#include "Card.hpp"

Card::Card() {
    string cardName = "";
    string cardClass = "";
    string cardRarity = "";
    string cardSet = "";
    string cardType = "";
    int cardCost = 0;
}

Card::Card(const Card& temp) {
    this->cardName = temp.cardName;
    this->cardClass = temp.cardClass;
    this->cardRarity = temp.cardRarity;
    this->cardSet = temp.cardSet;
    this->cardType = temp.cardType;
    this->cardCost = temp.cardCost;
}

void Card::operator=(const Card& temp) {
    this->cardName = temp.cardName;
    this->cardClass = temp.cardClass;
    this->cardRarity = temp.cardRarity;
    this->cardSet = temp.cardSet;
    this->cardType = temp.cardType;
    this->cardCost = temp.cardCost;
}
