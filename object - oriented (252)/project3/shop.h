//
//  shop.h
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

#ifndef shop_h
#define shop_h
#include <iostream>
#include <type_traits>
#include "cookie.h"
using namespace std;

template <class Type>
class Shop {
    Type* arr;
    int discount,stock;
    float total_cost; // cost with tax included
    float costWith_D; // cost with discount and tax included
public:
    Shop() {discount=0,stock=0,arr = new Type[10],total_cost=0,costWith_D=0;}
    Shop(Type);
    ~Shop();
    void add(const Type&);
    void setDiscount(int);
    const Type& operator[](int) const;
    Type* find(string name) const;
    float setTotalCost();
    void setCostWith_D();
    inline int getStock() const {return stock;}
    inline Type* getArr() const {return arr;}
    inline float getTotalCost() const {return total_cost;}
    inline float getCostWith_D() const {return costWith_D;}
    inline friend ostream& operator<< (ostream& out, const Shop<Type>& s) {
        out << "**********************" << endl << "Number of items: " << s.stock << endl;
        for (int i=0; i < s.stock; i++) {
            out << i+1 << ": " << s.arr[i].getName() << " #" <<  s.arr[i].getAmount() << " Cost: " << s.arr[i].getCost() << endl;
        }
        out << "**********************" << endl << "Total cost: " << s.total_cost;
        if (0 < s.discount && s.discount <= 30) {
            out << "\nDiscount:" << s.discount << "%" << endl;
            out << "Discount amount: " << s.costWith_D - s.total_cost << endl;
            out << "Discounted cost: " << s.costWith_D << endl;
        }
        return out;
    };
};

#endif /* shop_h */
