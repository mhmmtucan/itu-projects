/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 8.10.2016
 */

#ifndef patient_h
#define patient_h

struct patient_record {
    char name[20], doctorName[20], diagnosis[25];
    int patientNumber, polyclinicNumber;
    char branchName[15];
};

#endif /* patient_h */
