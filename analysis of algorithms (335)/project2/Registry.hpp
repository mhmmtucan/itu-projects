//
//  Registry.hpp
//  aoa_hw2
//
//  Created by Muhammet Uçan on 19.10.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#ifndef Registry_hpp
#define Registry_hpp

#include "Residence.hpp"

class Registry {
    vector<Residence> container;
public:
    Registry(string,int);
    bool isFileExists;
    void quickSort(int,int);
    int partition(int,int);
    int r_partition(int,int); // randomized partition for quick sort
    void swap(int,int);
    bool compare(Residence&, Residence&);
    bool readFromFile(string,int);
    void writeToFile(string);
    int getContainerSize() {return int(container.size());}
    vector<Residence> getContainer() {return container;}
    vector<Residence>& getContainerReference() {return container;}
public:
    
};

#endif /* Registry_hpp */
