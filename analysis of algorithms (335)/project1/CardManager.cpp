//
//  CardManager.cpp
//  aoa_hw1
//
//  Muhammet Uçan
//  150140707
//

using namespace std;
#include "CardManager.hpp"

bool compare(const Card&, const Card&, string);

CardManager::CardManager(string filename) {
    cards = readFromFile(filename);
}

vector<Card> CardManager::readFromFile(string filename) {
    ifstream cardFile;
    cardFile.open(filename);
    if (!cardFile.is_open()) {
        return vector<Card>();
    }
    vector<Card> container;
    Card temp;
    while(!cardFile.eof()) {
        cardFile >> temp;
        if (temp.getCardName().find("\n") == string::npos && !temp.getCardName().empty()) container.push_back(temp);
    }
    cardFile.close();
    return container;
}

void CardManager::writeToFile(const vector<Card>& cards, string filename) {
    ofstream cardFile;
    cardFile.open(filename);
    for (int i=0; i<cards.size(); i++) {
        cardFile << cards[i];
    }
    cardFile.close();
}

// if true it means a>b, if false it means a<=b
bool compare(const Card& a, const Card& b, string sortType) {
    
    if (sortType.compare("filter") == 0) {
        // do comparasion for filter type
        if (a.getCardType().compare(b.getCardType()) > 0) {
            return true;
        }
        return false;
    }
    else if (sortType.compare("full") == 0) {
        // do comprasion for full type
        if (a.getCardClass().compare(b.getCardClass()) > 0) {
            return true;
        }
        // if cards has same class name, do compraison for cost and then same for name
        else if (a.getCardClass().compare(b.getCardClass()) == 0) {
            if (a.getCardCost() > b.getCardCost()) {
                return true;
            }
            else if (a.getCardCost() == b.getCardCost()) {
                if (a.getCardName().compare(b.getCardName()) > 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void CardManager::insertionSort(string sortType) {
    int i, j;
    Card key;
    for (i=1; i<cards.size(); i++) {
        key = cards[i];
        j = i-1;
        
        while (j >= 0 && compare(cards[j], key, sortType)) {
            cards[j+1] = cards[j];
            j--;
        }
        cards[j+1] = key;
    }
}

void CardManager::merge(int l, int m, int r, string sortType) {
    int i=0,j=0,k=0;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Card>L;
    vector<Card>R;
    
    for (i=0; i<n1; i++) {
        L.push_back(cards[i+l]);
    }
    for (j=0; j<n2; j++) {
        R.push_back(cards[m + j + 1]);
    }
    
    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (compare(R[j], L[i], sortType)) {
            cards[k] = L[i];
            i++;
        } else {
            cards[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i<n1) {
        cards[k] = L[i];
        i++;
        k++;
    }
    while (j<n2) {
        cards[k] = R[j];
        j++;
        k++;
    }
}

void CardManager::mergeSort(int l, int r, string sortType) {
    if (l < r) {
        int m = l + (r-l) / 2;
        
        mergeSort(l, m, sortType);
        mergeSort(m+1, r, sortType);
        
        merge(l,m,r,sortType);
        
    }
}
