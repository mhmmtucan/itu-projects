//
//  shop.cpp
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

#include "shop.h"
#include "candy.h"
#include "icecream.h"

template <class Type>
Shop<Type>::Shop(Type t) {
    arr = new Type[10];
    discount = 0, stock = 0, total_cost = 0;
    arr[stock] = t;
    stock++;
    total_cost = t.getCost()*108/100;
    costWith_D = 0;
}

template <class Type>
Shop<Type>::~Shop() {
    delete [] arr;
}

template <class Type>
void Shop<Type>::add(const Type& t) {
    arr[stock] = t;
    stock++;
    total_cost += t.getCost()*108/100;
}

template <class Type>
void Shop<Type>::setDiscount(int dis) {
    if (dis < 0 || dis > 30) throw "***************\nDiscount rate is out of range!";
    discount = dis;
    costWith_D = total_cost*((100.0-(float)discount)/100.0);
}

template <class Type>
const Type& Shop<Type>::operator[](int i) const{
    if (i>=stock) {
        if (is_same<Type, Cookie>::value) throw "***************\nWe don't have enough cookies!";
        else if (is_same<Type, Icecream>::value) throw "***************\nWe dont have enough ice cream";
        else if (is_same<Type, Candy>::value) throw "***************\nWe dont have enough candy";
    }
    return arr[i];
}

template <class Type>
float Shop<Type>::setTotalCost() {
    for (int i=0; i<stock; i++) {
        total_cost += this->arr[i].getCost()*108/100;
    }
    return total_cost;
}

template <class Type>
Type* Shop<Type>::find(string name) const{
    for (int i=0; i<stock; i++) {
        if (arr[i].getName().compare(name) == 0) return &arr[i];
    }
    return nullptr;
}
// in order to resolve link error, since we have to create separete header and cpp file for template we have to explicitly instantiate it
template class Shop<Cookie>;
template class Shop<Candy>;
template class Shop<Icecream>;
