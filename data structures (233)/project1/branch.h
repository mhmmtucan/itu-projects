/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 8.10.2016
 */

#ifndef branch_h
#define branch_h
#include "polyclinic.h"

struct branch_record {
    char branchName[15];
    polyclinic_record polyclinics[2];
};

#endif /* branch_h */
