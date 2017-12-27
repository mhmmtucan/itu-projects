/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 8.10.2016
 */

#ifndef operations_h
#define operations_h
#include <stdio.h>
#include <iostream>
#include "patient.h"
#include "branch.h"

struct Data {
    char *fileName;
    FILE *database;
    
    branch_record branchs[10];
    patient_record patients[100];
    patient_record *ptr,*temp;
    
    int numOfRecords,numOfBranchs;
    void openDatabase();
    void closeDatabase();
    void orderArray();
    void printData();
    bool searchByBranch(char[]);
    bool searchByPoly(int);
    void insert(patient_record*, int index);
    void remove(int patientNumber);
    void regulate();
};

#endif /* operations_h */
