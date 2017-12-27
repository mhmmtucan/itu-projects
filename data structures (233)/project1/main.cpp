/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 8.10.2016
 */

#include "operations.h"
#include <ctype.h>
#include <stdio.h>
#include <string>

using namespace std;
typedef Data DataStructure;
DataStructure records;

void printMenu();
bool operand(char);
void search_branch();
void search_polyNum();
void add();
void remove();
void exit_program();

int main() {
    records.openDatabase();
    bool go = true;
    char seleciton;
    while(go) {
        printMenu();
        cin >> seleciton;
        go = operand(seleciton);
    }
    return 0;
}

void printMenu() {
    cout << endl << endl <<"Please select the opreation to perform and enter the operaiton code" << endl << endl;
    cout << "(P) Print all of the patient records," << endl;
    cout << "(B) Search the data by the branch name," << endl;
    cout << "(C) Search the data by the polyclinic number," << endl;
    cout << "(I) Insert a new patient record," << endl;
    cout << "(R) Remove the patient record," << endl;
    cout << "(E) Exit the program," << endl;
    cout << "Your selection is:" << endl;
}
bool operand(char execute) {
    bool cont = true;
    switch (execute) {
        case 'P': case 'p':
            records.printData();
            break;
        case 'B': case 'b':
            search_branch();
            break;
        case 'C': case 'c':
            search_polyNum();
            break;
        case 'I': case 'i':
            add();
            break;
        case 'R': case 'r':
            remove();
            break;
        case 'E': case 'e':
            exit_program();
            cont = false;
            break;
        default:
            cout << "Your selection is wrong, please select again:" << endl;
            cin >> execute;
            cont = operand(execute);
            break;
    }
    return cont;
}

void add() {
    patient_record newRecord[1];
    cout << "Name:";
    cin >> newRecord[0].name;
    cout << "Doctor Name:";
    cin >> newRecord[0].doctorName;
    cout << "Diagnosis:";
    cin >> newRecord[0].diagnosis;
    int patientNum;
    cout << "Patinet Number:";
    cin >> patientNum;
    while (999 > patientNum  ||  patientNum > 9999) {
        cout << "Patient number must be 4 digit, enter again:";
        cin >> patientNum;
    }
    newRecord[0].patientNumber = patientNum;
    cout << "Polyclinic Number:";
    cin >> newRecord[0].polyclinicNumber;
    cout << "Branch Name:";
    cin >> newRecord[0].branchName;
    records.insert(newRecord, records.numOfRecords);
}

void remove() {
    int ID;
    cout << "Enter the patient ID to delete:";
    cin >> ID;
    records.remove(ID);
    
}
void search_branch() {
    char branch[15];
    cout << "Enter the branch name:";
    cin.ignore(1000,'\n');
    cin >> branch;
    if(records.searchByBranch(branch) != true) {
        cout << "There is no such branch.";
    }
}

void search_polyNum() {
    int num;
    cout << "Enter the polyclinic number:";
    cin.ignore(1000,'\n');
    cin >> num;
    if(records.searchByPoly(num) != true) {
        cout << "There is no such polyclinic.";
    }
}

void exit_program() {
    records.closeDatabase();
}
