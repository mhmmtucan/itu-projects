/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 8.10.2016
 */

#include <string>
#include <ctype.h>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include "operations.h"
#define MAX_RECORD 100
using namespace std;


void Data::openDatabase() {
    database = fopen("database.txt", "r");
    char temp[120];
    string temp2;
    string token,tab = "\t",newLine = "\n", eof = "\r";
    int i=0;
    numOfRecords = 0;
    numOfBranchs = 0;
    while (fgets(temp, sizeof(temp), database)) {
        
        if (feof(database)) break;
        
        temp2 = string(temp);
        // takes line finds first tab and then delete the part until first tab
        token = temp2.substr(0,temp2.find(tab));
        strcpy(patients[i].name, token.c_str());
        temp2.erase(0,temp2.find(tab)+1);
        
        token = temp2.substr(0,temp2.find(tab));
        strcpy(patients[i].doctorName, token.c_str());
        temp2.erase(0,temp2.find(tab)+1);
        
        token = temp2.substr(0,temp2.find(tab));
        strcpy(patients[i].diagnosis, token.c_str());
        temp2.erase(0,temp2.find(tab)+1);
        
        token = temp2.substr(0,temp2.find(tab));
        patients[i].patientNumber = atoi(token.c_str());
        temp2.erase(0,temp2.find(tab)+1);
        
        token = temp2.substr(0,temp2.find(tab));
        patients[i].polyclinicNumber = atoi(token.c_str());
        temp2.erase(0,temp2.find(tab)+1);
        
        token = temp2.substr(0,temp2.find(newLine));
        token = token.substr(0,token.find(eof));
        strcpy(patients[i].branchName, token.c_str());
        temp2.erase(0,temp2.find(tab)+1);
        
        i++;

    }
    numOfRecords = i;
    orderArray(); // make array alfabetically ordered
    regulate(); // take one dimension array pass it to new array in order to hold branchNames and polyclinicNumbers
    fclose(database);
}

void Data::closeDatabase() {
    database = fopen("database.txt", "w");
    int i=0;
    ptr = patients;
    while(ptr->polyclinicNumber != 0) {
        fprintf(database,"%s\t%s\t%s\t%d\t%d\t%s\n",ptr->name,ptr->doctorName,ptr->diagnosis,ptr->patientNumber,ptr->polyclinicNumber,ptr->branchName);
        i++;
        if (i==numOfRecords) break;
        ptr++;
    }
}

void Data::printData() {
    int i=0;
    ptr = patients;
    while(true) {
        printf("%d.%-15s\t%-15s\t%-25s\t%-5d\t%-5d\t%s\n",i+1,ptr->name,ptr->doctorName,ptr->diagnosis,ptr->patientNumber,ptr->polyclinicNumber,ptr->branchName);
        i++;
        if (i==numOfRecords) break;
        ptr++;
    }
}

void Data::orderArray() {
    patient_record temp[100],temp2[100];
    for (int i=0; i<(numOfRecords-1); i++) {
        if (patients[i].polyclinicNumber != 0) {
            for (int j=i+1; j<numOfRecords; j++) {
                if (strcmp(patients[i].branchName, patients[j].branchName) > 0) {
                    memcpy(temp, &patients[j], sizeof(patient_record));
                    memcpy(&patients[j], &patients[i], sizeof(patient_record));
                    memcpy(&patients[i], temp, sizeof(patient_record));
                }
            }
        }
    }
    for (int k=0; k<numOfRecords-1; k++) {
        if (patients[k].polyclinicNumber != 0) {
            for (int l=k+1; l<numOfRecords; l++) {
                if (strcmp(patients[k].branchName, patients[l].branchName) == 0 && (patients[k].polyclinicNumber > patients[l].polyclinicNumber)) {
                    memcpy(temp2, &patients[l], sizeof(patient_record));
                    memcpy(&patients[l], &patients[k], sizeof(patient_record));
                    memcpy(&patients[k], temp2, sizeof(patient_record));
                }
            }
        }
    }
}

void Data::insert(patient_record *temp, int index) {
    int i,count1=0,count2=0;
    for (i=0; i<numOfBranchs; i++) {
        // conditions check before 
        if (strcmp(branchs[i].branchName, temp->branchName) == 0) {
            if ((branchs[i].polyclinics[0].polyclinicNumber != temp->polyclinicNumber && branchs[i].polyclinics[1].polyclinicNumber != temp->polyclinicNumber) && (branchs[i].polyclinics[0].polyclinicNumber != 0 || branchs[i].polyclinics[1].polyclinicNumber != 0)) {
                cout << endl << "Each branch can have at most 2 polyclinics!" << endl;
                return;
            }
        }
        if (strcmp(branchs[i].branchName, temp->branchName) != 0) {
            if (branchs[i].polyclinics[0].polyclinicNumber  == temp->polyclinicNumber || branchs[i].polyclinics[1].polyclinicNumber == temp->polyclinicNumber) {
                cout << endl << "Each polyclinic can used for only one branch!" << endl;
                return;
            }
        }
        if (strcmp(branchs[i].branchName, temp->branchName) == 0) {
            if (branchs[i].polyclinics[0].polyclinicNumber == temp->polyclinicNumber) {
                for (int j=0; j<10; j++) {
                    if (branchs[i].polyclinics[0].patients[j].polyclinicNumber != 0) {
                        count1++;
                    }
                }
                if (count1 == 10) {
                    cout << endl << "No more than 10 patients can get examined in one polyclinic" << endl;
                    return;
                }
            } else if (branchs[i].polyclinics[1].polyclinicNumber == temp->polyclinicNumber) {
                for (int j=0; j<10; j++) {
                    if (branchs[i].polyclinics[0].patients[j].polyclinicNumber != 0) {
                        count2++;
                    }
                }
                if (count2 == 10) {
                    cout << endl << "No more than 10 patients can get examined in one polyclinic" << endl;
                    return;
                }
            }
        }
    }
    for (int k=0; k<numOfRecords; k++) {
        if (patients[k].patientNumber == temp->patientNumber) {
            cout << endl << "Patient number can't be same!";
            return;
        }
    }
    memcpy(&patients[index], temp, sizeof(patient_record));
    cout << "Your record has been added.";
    if (strcmp(temp->name, "") != 0) numOfRecords++;
    orderArray();
    regulate();
    
}
void Data::remove(int patientNumber) {
    bool notfound = true;
    for (int i=0; i<numOfRecords; i++) {
        if (patients[i].patientNumber == patientNumber) {
            memcpy(&patients[i], "", sizeof(patient_record));
            for (int j=i; j<numOfRecords; j++) {
                memcpy(&patients[j], &patients[j+1], sizeof(patient_record));
            }
            cout << "Patient record has been deleted.";
            notfound = false;
        }
    }
    if (notfound) cout << "Patient ID is wrong!";
    numOfRecords--;
}

bool Data::searchByBranch(char branch[]) {
    bool found=false;
    for (int i=0; i<numOfRecords; i++) {
        if (patients[i].polyclinicNumber != 0 && strcmp(patients[i].branchName, branch) == 0) {
            printf("%-15s\t%-15s\t%-25s\t%-5d\t%-5d\t%s\n",patients[i].name,patients[i].doctorName,patients[i].diagnosis,patients[i].patientNumber,patients[i].polyclinicNumber,patients[i].branchName);
            found = true;
        }
    }
    return found;
}

bool Data::searchByPoly(int polyNum) {
    bool found = false;
    for (int i=0; i<numOfRecords; i++) {
        if (patients[i].polyclinicNumber == polyNum) {
            printf("%-15s\t%-15s\t%-25s\t%-5d\t%-5d\t%s\n",patients[i].name,patients[i].doctorName,patients[i].diagnosis,patients[i].patientNumber,patients[i].polyclinicNumber,patients[i].branchName);
            found = true;
        }
    }
    return found;
}

void Data::regulate() {
    int i=0,j=0,k=0;
    
    for (int index=0; index<numOfRecords; index++) {
        memcpy(&branchs[i].polyclinics[j].patients[k],&patients[index],sizeof(patient_record));
        
        if ((branchs[i].polyclinics[j].patients[k].polyclinicNumber != patients[index+1].polyclinicNumber) && (strcmp(branchs[i].polyclinics[j].patients[k].branchName, patients[index+1].branchName) == 0)) {
            // poliklinik değişti branş aynı
            branchs[i].polyclinics[j].polyclinicNumber = patients[index].polyclinicNumber;
            strcpy(branchs[i].branchName, patients[index].branchName);
            j++;
            k=-1;
        } else if  ((branchs[i].polyclinics[j].patients[k].polyclinicNumber != patients[index+1].polyclinicNumber) && (strcmp(branchs[i].polyclinics[j].patients[k].branchName, patients[index+1].branchName) != 0)) {
            // poliklinik değişti branş değişti
            branchs[i].polyclinics[j].polyclinicNumber = patients[index].polyclinicNumber;
            strcpy(branchs[i].branchName, patients[index].branchName);
            i++;
            j=0;
            k=-1;
        }
        k++;
    }
    numOfBranchs = i;
}
