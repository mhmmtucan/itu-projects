//
//  TimeCalculator.hpp
//  aoa_hw3
//
//  Created by Muhammet Uçan on 21.11.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#ifndef TimeCalculator_hpp
#define TimeCalculator_hpp

#include <stdio.h>
#include <chrono>
using namespace std::chrono;
class TimeCalculator {
    high_resolution_clock::time_point t1; // start
    high_resolution_clock::time_point t2; // end
    long long duration_micro;
public:
    TimeCalculator(){
        duration_micro=0;
    }
    void start() {
        t1 = high_resolution_clock::now(); // start
    };
    void stop() {
        t2 = high_resolution_clock::now(); // stop
    };
    long long calculate() {
        return duration_micro = duration_cast<microseconds>( t2 - t1 ).count(); // calculation
    };
};

#endif /* TimeCalculator_hpp */
