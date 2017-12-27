//
//  main.cpp
//  aoa_hw2
//
//  Created by Muhammet Uçan on 19.10.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#include <iostream>
#include "Registry.hpp"
using namespace std::chrono;

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        cout << "Enter line count." << "\n";
        return 1;
    }
    
    high_resolution_clock::time_point t1; // start
    high_resolution_clock::time_point t2; // end
    long long duration_micro = 0;
    long long total = 0; // for calculating avarage
    int line = atoi(argv[1]);
    
    Registry registry("population_by_zip_2010.csv",line);
    
    if (!registry.isFileExists) {
        cout << "File is not exists." << "\n";
        return 1;
    }
    
    // copying to a temp container in order to use without reading from file
    vector<Residence> tempContainer = registry.getContainer();
    
    // running 10 times in order to have better results on running time
    for (int i=0; i<10; i++) {
        // copying with reference rather than directly copying
        registry.getContainerReference() = tempContainer;
        
        t1 = high_resolution_clock::now(); // start
        registry.quickSort(0, registry.getContainerSize()-1);
        t2 = high_resolution_clock::now(); // stop
        
        duration_micro = duration_cast<microseconds>( t2 - t1 ).count(); // calculation
        total += duration_micro;
    }
    auto avarage = total / 10;
    
    cout << "Time elapsed: " << avarage << " microseconds\n";
    
    registry.writeToFile("output.csv");
    
    return 0;
}
