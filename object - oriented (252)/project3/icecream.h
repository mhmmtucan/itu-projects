//
//  icecream.h
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

#ifndef icecream_h
#define icecream_h
#include <string>
using namespace std;
class Icecream {
    string name;
    float litre;
    int price_per_litre;
    float cost;
public:
    Icecream(){
        name ="",litre=0,price_per_litre=0,cost=0;
    }
    Icecream(string,float,int);
    ~Icecream();
    friend ostream& operator<< (ostream& out, const Icecream&);
    inline float getCost() const {return cost;}
    inline string getName() const {return name;}
    inline float getAmount() const {return litre;}
    inline int getPrice() const {return price_per_litre;}
};

#endif /* icecream_h */
