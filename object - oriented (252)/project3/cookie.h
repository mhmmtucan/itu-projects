//
//  cookie.h
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

#ifndef cookie_h
#define cookie_h
#include <string>
using namespace std;
class Cookie {
    string name;
    int pieces;
    int price_per_dozen;
    float cost;
public:
    Cookie(){
        name ="",pieces=0,price_per_dozen=0,cost=0;
    }
    Cookie(string,int,int);
    ~Cookie();
    friend ostream& operator<< (ostream& out, const Cookie&);
    inline float getCost() const {return cost;}
    inline string getName() const {return name;}
    inline int getAmount() const {return pieces;}
    inline int getPrice() const {return price_per_dozen;}
};

#endif /* cookie_h */
