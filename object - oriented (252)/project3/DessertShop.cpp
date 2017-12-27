//
//  DessertShop.cpp
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

// in order to compile run.sh file can be used
// manual execution: g++ -std=c++11 icecream.cpp candy.cpp cookie.cpp shop.cpp DessertShop.cpp -o test
// ./test

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "shop.h"
#include "candy.h"
#include "cookie.h"
#include "icecream.h"

using namespace std;

int main() {
    Cookie cookie1("Chocolate Chip Cookies",10, 180); //(name, pieces, priceperdozen)
    Cookie cookie2("Cake Mix Cookies", 16, 210);
    
    Shop<Cookie> cookieShop(cookie1);
    
    cookieShop.add(cookie2);
    cout << cookieShop << endl;
    
    //Catch an exception here while trying to access the element at(2)
    try {
        cout << cookieShop[2] << endl;
    } catch (const char* res) {
        cout << res << endl;
    }
    
    Icecream icecream1("Chocolate ice cream",1.5, 170); //(name, litre, priceperlitre)
    Shop<Icecream> icecreamShop(icecream1);
    cout<<icecreamShop<<endl;
    
    
    //Catch an exception here while trying to set the discount to(50)
    try {
        icecreamShop.setDiscount(50);
    } catch (const char* res) {
        cout << res << endl;
    }
    
    Candy candy2("Gummi bears",12,89); //(name, weight, priceperkg)
    Candy candy3("Hanukkah gelt",8,110);
    
    Shop<Candy> candyShop(candy2);
    candyShop.add(candy3);
    
    candyShop.setDiscount(15);
    cout<<candyShop<<endl;
    
    // part for checkout.txt
    string line;
    ifstream orderFile("order.txt");
    ifstream stockFile("stock.txt");
    ofstream checkoutFile;
    
    Shop<Cookie> cookieStock;
    Shop<Candy> candyStock;
    Shop<Icecream> icecreamStock;
    
    Shop<Cookie> cookieOrder;
    Shop<Candy> candyOrder;
    Shop<Icecream> icecreamOrder;
    
    string name;
    int type=0, itemCount=0, price = 0,i=0;
    
    if(stockFile.is_open()) {
        while (getline(stockFile, line)) {
            if (i<1) i++; // in order to ignore first line of stock file
            else {
                // taking string with tab delimeter, and optimization for whether the file is created on mac/windows
                name = line.substr(0,line.find("\t"));
                line.erase(0, name.length()+1);
                type = stoi(line.substr(0,line.find("\t")));
                line.erase(0,to_string(type).length()+1);
                itemCount = stoi(line.substr(0,line.find("\t")));
                line.erase(0,to_string(itemCount).length()+1);
                if (line.compare(line.length()-1,1,"\r") == 0) {
                    price = stoi(line.substr(0,line.find("\r")));
                } else if (line.compare(line.length()-1,1,"\n") == 0) {
                    price = stoi(line.substr(0,line.find("\n")));
                } else if (line.compare(line.length()-2,2,"\r\n") == 0) {
                    price = stoi(line.substr(0,line.find("\r\n")));
                } else if (line.compare(line.length()-1,1,"/n") != 0 && line.compare(line.length()-1,1,"\r") != 0  && line.compare(line.length()-2,2,"\r\n") != 0) {
                    price = stoi(line);
                }
                i++;
                // add types accordoingly to thier containers
                switch (type) {
                    case 1:
                        cookieStock.add(Cookie(name, itemCount, price));
                        break;
                    case 2:
                        candyStock.add(Candy(name, itemCount, price));
                        break;
                    case 3:
                        icecreamStock.add(Icecream(name, itemCount, price));
                        break;
                    default:
                        break;
                }
            }
        }
        stockFile.close();
        i=0;
    }
    
    if(orderFile.is_open()) {
        checkoutFile.open("checkout.txt");
        while (getline(orderFile,line)) {
            // taking string with tab delimeter, and optimization for whether the file is created on mac/windows
            name = line.substr(0,line.find("\t"));
            line.erase(0, name.length()+1);
            type = stoi(line.substr(0,line.find("\t")));
            line.erase(0,to_string(type).length()+1);
            if (line.compare(line.length()-1,1,"\r") == 0) {
                itemCount = stoi(line.substr(0,line.find("\r")));
            } else if (line.compare(line.length()-1,1,"\n") == 0) {
                itemCount = stoi(line.substr(0,line.find("\n")));
            } else if (line.compare(line.length()-2,2,"\r\n") == 0) {
                itemCount = stoi(line.substr(0,line.find("\r\n")));
            } else if (line.compare(line.length()-1,1,"/n") != 0 && line.compare(line.length()-1,1,"\r") != 0  && line.compare(line.length()-2,2,"\r\n") != 0) {
                itemCount = stoi(line);
            }
            // if item's name mathces in the stock and amount is enough, it can be added to order
            if (cookieStock.find(name) != nullptr && cookieStock.find(name)->getAmount()>=itemCount) {
                cookieOrder.add(Cookie(name, itemCount, cookieStock.find(name)->getPrice())),i++;
            } else if (candyStock.find(name) != nullptr && candyStock.find(name)->getAmount()>=itemCount) {
                candyOrder.add(Candy(name, itemCount, candyStock.find(name)->getPrice())),i++;
            } else if (icecreamStock.find(name) != nullptr && icecreamStock.find(name)->getAmount()>=itemCount) {
                icecreamOrder.add(Icecream(name, itemCount, icecreamStock.find(name)->getPrice())),i++;
            }
            else {
                // write to the file
                checkoutFile << "!!! We dont have " << itemCount << "(" << name << ")s.\n";
            }
        }
        // writing orders to the file
        int j = 0;
        checkoutFile << "---------------------\nNumber of items: " << i << "\n";
        if (cookieOrder.getStock() != 0)
            for (; j<cookieOrder.getStock(); j++)
                checkoutFile << j+1 << ": " << cookieOrder.getArr()[j].getName() << " #" <<  cookieOrder.getArr()[j].getAmount() << " Cost: " << cookieOrder.getArr()[j].getCost() <<  "\n";
        if (candyOrder.getStock() != 0)
            for (; j<candyOrder.getStock(); j++)
                checkoutFile << j+1 << ": " << candyOrder.getArr()[j].getName() << " #" <<  candyOrder.getArr()[j].getAmount() << " Cost: " << candyOrder.getArr()[j].getCost() <<  "\n";
        if (icecreamOrder.getStock() != 0)
            for (; j<icecreamOrder.getStock(); j++)
                checkoutFile << j+1 << ": " << icecreamOrder.getArr()[j].getName() << " #" <<  icecreamOrder.getArr()[j].getAmount() << " Cost: " << icecreamOrder.getArr()[j].getCost() <<  "\n";
     
        if (cookieOrder.getStock() != 0 || candyOrder.getStock() != 0 || icecreamOrder.getStock() != 0) checkoutFile << "**********************" << endl << "Total cost: " << cookieOrder.getTotalCost() + candyOrder.getTotalCost() + icecreamOrder.getTotalCost() << "\n";
        cookieOrder.setDiscount(10), candyOrder.setDiscount(10), icecreamOrder.setDiscount(10);
        checkoutFile << "Discount: 10%\n";
        checkoutFile << "Discount amount: " << cookieOrder.getCostWith_D() + candyOrder.getCostWith_D() + icecreamOrder.getCostWith_D() - cookieOrder.getTotalCost() - candyOrder.getTotalCost() - icecreamOrder.getTotalCost() << "\n";
        checkoutFile << "Discounted cost: " << cookieOrder.getCostWith_D() + candyOrder.getCostWith_D() + icecreamOrder.getCostWith_D() << "\n";
        orderFile.close();
    }
}
