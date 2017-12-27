//
//  candy.h
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

#ifndef candy_h
#define candy_h
#include <string>
using namespace std;
class Candy {
    string name;
    float weight;
    int price_per_kg;
    float cost;
public:
    Candy(){
        name ="",weight=0,price_per_kg=0,cost=0;
    }
    Candy(string,float,int);
    ~Candy();
    friend ostream& operator<< (ostream& out, const Candy&);
    inline float getCost() const {return cost;}
    inline string getName() const {return name;}
    inline float getAmount() const {return weight;}
    inline int getPrice() const {return price_per_kg;}
};

#endif /* candy_h */
