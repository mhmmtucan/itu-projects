//
//  Residence.cpp
//  aoa_hw2
//
//  Created by Muhammet Uçan on 19.10.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#include "Residence.hpp"

// initilization
Residence::Residence() {
    population = 0;
    maximum_age = "";
    minimum_age = "";
    gender = "";
    zipcode = 0;
    geo_id = "";
}
// copy constructor for Residence class
Residence::Residence(const Residence& temp) {
    this->population = temp.population;
    this->minimum_age = temp.minimum_age;
    this->maximum_age = temp.maximum_age;
    this->zipcode = temp.zipcode;
    this->gender = temp.gender;
    this->geo_id = temp.geo_id;
}
// operator overloading for Residence class
void Residence::operator=(const Residence& temp) {
    this->population = temp.population;
    this->minimum_age = temp.minimum_age;
    this->maximum_age = temp.maximum_age;
    this->zipcode = temp.zipcode;
    this->gender = temp.gender;
    this->geo_id = temp.geo_id;
}
