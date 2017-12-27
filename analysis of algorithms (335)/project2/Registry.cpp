//
//  Registry.cpp
//  aoa_hw2
//
//  Created by Muhammet Uçan on 19.10.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#include "Registry.hpp"

Registry::Registry(string filename,int line) {
    isFileExists = readFromFile(filename,line);
}

bool Registry::readFromFile(string filename, int line) {
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        return false;
    }
    Residence temp = Residence();
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(!file.eof() && line > 0) {
        file >> temp;
        line--;
        container.push_back(temp);
    }
    file.close();
    return true;
}

void Registry::writeToFile(string filename) {
    ofstream file;
    file.open(filename);
    file << "population,minimum_age,maximum_age,gender,zipcode,geo_id" << "\n";
    for (int i=0; i<container.size(); i++) {
        file << container[i];
    }
    file.close();
}

// swaps elements at index a and b
void Registry::swap(int a, int b) {
    iter_swap(container.begin() + a, container.begin() + b);
}

bool Registry::compare(Residence& a, Residence& b) {
    if (a.getPopulation() < b.getPopulation()) {
        return true;
    } else if (a.getPopulation() == b.getPopulation()) {
        // refactored in order not to making comprasion two times for geo code
        int compareGeo = b.getGeoId().compare(a.getGeoId());
        if (compareGeo > 0) {
            return true;
        } else if (compareGeo == 0) {
            // compare other things
            // zipcode would be faster, since compraing int is faster than comparing stirngs
            if (a.getZipcode() < b.getZipcode()) {
                return true;
            }
        }
    }
    return false;
}
/*
/   randomized partition for quick sort
/   If inputs given is in the sorted or reverse sorted order (worst-case), then normal partioning
/   will run with the expected running time Big-Theta(n^2)
/   However if we choose pivot randomly, expected running time will be Big-Theta(nlgn)
*/
int Registry::r_partition(int low, int high) {
    srand((unsigned int)(time(NULL)));
    int randIndex = low + rand()%(high-low+1);
    swap(randIndex, high);
    return partition(low, high);
}

int Registry::partition(int low, int high) {
    Residence pivot = container[high];
    
    int i = low-1;
    
    for (int j = low; j<=high-1; j++) {
        if (compare(container[j], pivot)) {
            i++;
            swap(i, j);
        }
    }
    swap(i+1, high);
    return (i+1);
}

void Registry::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        
        quickSort(low, pi-1);
        quickSort(pi+1, high);
    }
}


