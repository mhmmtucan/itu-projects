//
//  150140707
//  Muhammet Uçan
//  main.cpp
//  homework1
//

#include <iostream>
#include "SmallVector.h"

using namespace std;

void printSmallVector (const char* const message, const SmallVector& object_in) {
    cout << message << ": ";
    for (int i=0; i<object_in.getSize(); i++) {
        cout << object_in[i] << " ";
    }
    cout << endl;
}

int main() {
    
    int temp[35];
    for (int i = 0; i < 35; i++) {
        temp[i] = i;
    }

    SmallVector test(temp, 10);
    SmallVector test2(temp, 35);
    // print test in reverse order
    printSmallVector("Printing test in reverse", test.reverse());
    SmallVector test3; // Empty SmallVector
    SmallVector test6;
    test6 = test3 = test2 + test; // Concatenate two SmallVectors
    printSmallVector("Printing test3", test3);
    test3.push_back(10);
    printSmallVector("Printing test3 with push back",test3);
    printSmallVector("Printing test6", test6);
    cout << "Size of test6: " << test6.getSize() << endl;
    SmallVector test4(test); // Copy SmallVector
    printSmallVector("Printing test4", test4);
    SmallVector test5(temp, 2);
    printSmallVector("Mixing", test.reverse()*2 + test5);
    test5 = test5 * 5; // Replicate elements
    test5.push_back(12); // Add 12 at the end
    test5[0] = 4; // Modify the first element of test5
    std::cout << "Printing test5 in reverse: ";
    for (int i = 1; i < test5.getSize() + 1; i++) {
        // Testing negative numbers as indices
        std::cout << test5[-i] << " ";
    }
    cout << endl;
    return 0;
}
