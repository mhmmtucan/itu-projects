//
//  icecream.cpp
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

#include "icecream.h"
#include <iostream>
//int Icecream::stock = 0;

Icecream::Icecream(string name, float litre, int price_per_litre) {
    this->name = name;
    this->litre = litre;
    this->price_per_litre = price_per_litre;
    cost = litre * price_per_litre;
}
// since container does not contain pointer, no need to delete something in destructor
Icecream::~Icecream() {
}

ostream& operator<< (ostream& out, const Icecream& iceCream) {
    out << iceCream.name << " #" << iceCream.litre << " " << iceCream.price_per_litre;
    return out;
}
