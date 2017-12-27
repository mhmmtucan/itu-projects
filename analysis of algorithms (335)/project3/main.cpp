//
//  main.cpp
//  aoa_hw3
//
//  Created by Muhammet Uçan on 19.11.2017.
//  homework3
//  150140707
//  compile: g++ -std=c++11 *.cpp
//

#include <iostream>
#include "p3list.hpp"
#include "p3dict.hpp"
#include "TimeCalculator.hpp"

int main(int argc, const char * argv[]) {
    // time calculating class
    TimeCalculator timeCalculator;
    long long duration = 0;
    printf("DICTIONARY\n");
    HashMap myHashTable;
    
    timeCalculator.start();
    myHashTable.insertion();
    timeCalculator.stop();
    duration = timeCalculator.calculate();
    printf("Insertion finished after %lld microseconds (%.2fs)\n\n",duration, duration / (1000000.0));
    
    printf("Avarage number of collisions (first 1k)    | %.2f\n", myHashTable.getAverages(1000));
    printf("Avarage number of collisions (first 10k)   | %.2f\n", myHashTable.getAverages(10000));
    printf("Avarage number of collisions (first 100k)  | %.2f\n", myHashTable.getAverages(100000));
    printf("Avarage number of collisions (overall)     | %.2f\n\n", myHashTable.getAverages());
    
    timeCalculator.start();
    myHashTable.lookup();
    timeCalculator.stop();
    duration = timeCalculator.calculate();
    printf("Lookup finished after %lld microseconds (%.2fs)\n\n",duration, duration / (1000000.0));
    
    printf("LIST\n");
    List insertedList;
    
    timeCalculator.start();
    insertedList.insertion();
    timeCalculator.stop();
    duration = timeCalculator.calculate();
    printf("Insertion finished after %lld microseconds (%.2fs)\n",duration, duration / (1000000.0));
    
    
    List listToLookUp;
    listToLookUp.readForlookup();
    
    timeCalculator.start();
    insertedList.lookup(listToLookUp);
    timeCalculator.stop();
    duration = timeCalculator.calculate();
    printf("Lookup finished after %lld microseconds (%.2fs)\n",duration, duration / (1000000.0));
    
    return 0;
}
