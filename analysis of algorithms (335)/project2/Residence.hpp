//
//  Residence.hpp
//  aoa_hw2
//
//  Created by Muhammet Uçan on 19.10.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//
using namespace std;
#ifndef Residence_hpp
#define Residence_hpp
// neccassary headers
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <cstdlib>

class Residence {
    // minimum_age, maximum_age and gender can be null
    int population,zipcode;
    string gender,geo_id,minimum_age,maximum_age;
public:
    Residence();
    Residence(const Residence&);
    int getPopulation() const {return population;}
    int getZipcode() const {return zipcode;}
    string getMinAge() const {return minimum_age;}
    string getMaxAge() const {return maximum_age;}
    string getGender() const {return gender;}
    string getGeoId() const {return geo_id;}
    void operator=(const Residence&);
    
    // wrting to the file
    friend ostream &operator<<( ostream &output, const Residence &tempResidence ) {
        output << tempResidence.population << "," << tempResidence.minimum_age << "," << tempResidence.maximum_age << "," << tempResidence.gender << "," << tempResidence.zipcode << "," << tempResidence.geo_id << "\n";
        return output;
    }
    // taking from file
    friend istream &operator>>( istream  &input, Residence &tempResidence ) {
        string population,zipcode;
        if (getline(input,population,',') && getline(input,tempResidence.minimum_age,',') && getline(input,tempResidence.maximum_age,',') && getline(input,tempResidence.gender,',') && getline(input,zipcode,',') && getline(input,tempResidence.geo_id,'\n')) {
            
            tempResidence.population = stoi(population);
            tempResidence.zipcode = stoi(zipcode);
        }
        return input;
    }
};

#endif /* Residence_hpp */
