/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 8.10.2016
 */

#ifndef polyclinic_h
#define polyclinic_h
#include "patient.h"

struct polyclinic_record {
    int polyclinicNumber;
    patient_record patients[10] = {};
};

#endif /* polyclinic_h */
