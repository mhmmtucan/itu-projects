//
//  main.cpp
//  aoa_hw1
//
//  Muhammet Uçan
//  150140707
//
// IMPORTANT: to compile use "g++ -std=c++11 *.cpp -o output"


#include "CardManager.hpp"
#include "Card.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, const char * argv[]) {
    // if not enough argument entered by user, there is a problem
    if (argc != 5) {
        cout << "Please enter parameters correctly!\n";
        return 0;
    }
    // check for sort type, if error prompt
    if (strcmp(argv[1], "-filter") != 0 && strcmp(argv[1], "-full") != 0) {
        cout << "Please enter sort types correctly!\n";
        return 0;
    }
    string sortType(argv[1] + 1, strlen(argv[1]) - 1);
    // check for algoritm name, if error prompt
    if (strcmp(argv[2], "-i") != 0 && strcmp(argv[2], "-m") != 0) {
        cout << "Please enter algoritm parameter correctly!\n";
        return 0;
    }
    // for calculation of time
    high_resolution_clock::time_point t1; // start
    high_resolution_clock::time_point t2; // end
    
    // Creating a manager object which takes file name as paramater,
    // and then reading all the cards from file to the container named cards
    CardManager manager(argv[3]);
    
    // if cards container in Card Manager is zero, that means file is not exist
    if (manager.cards.size() == 0) {
        cout << "No file named " << argv[3] << "\n";
        return 0;
    }
    
    // check for conditions and make sure that correct algorithm is running
    if (strcmp(argv[2], "-i") == 0) {
        t1 = high_resolution_clock::now();
        manager.insertionSort(sortType);
        t2 = high_resolution_clock::now();
    } else if (strcmp(argv[2], "-m") == 0) {
        t1 = high_resolution_clock::now();
        manager.mergeSort(0, int(manager.cards.size()) - 1, sortType);
        t2 = high_resolution_clock::now();
    }
    
    // calculate time with microsecond and second, also print algorithm name for futher info
    auto duration_micro = duration_cast<microseconds>( t2 - t1 ).count(); // calculation
    auto duration_second = duration_cast<seconds>( t2 - t1 ).count();
    cout << "Time elapsed: " << duration_micro << " microseconds / " << duration_second << " seconds\n" ;
    string algrthm = (strcmp(argv[2], "-i") == 0) ? "Insertion" : "Merge";
    cout << "Algorithm used: " << algrthm << " sort - " << sortType << "\n";
    
    // finally, write all sorted cards to the file with given filename
    manager.writeToFile(manager.cards, argv[4]);

    return 0;
}






