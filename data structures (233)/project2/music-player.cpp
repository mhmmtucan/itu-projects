/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 21.11.2016 */

#include <iostream>
#include "operations.h"
list player;
using namespace std;

char menu();
bool operation(char);

int main() {
    player.readFromFile();
    while (operation(menu())) {}
    return 0;
}

char menu() {
    cout << endl << "SONG BOX APPLICATON (USING DOUBLY, CIRCULAR LINKED LIST)" << endl;
    cout << "Choose an operation" << endl;
    cout << "P: Play" << endl;
    cout << "L: Show all playlists" << endl;
    cout << "A: Add songs to a playlist" << endl;
    cout << "R: Remove songs from a playlist" << endl;
    cout << "C: Create a new playlist" << endl;
    cout << "D: Delete a playlist" << endl;
    cout << "W: Write to file (SAVE)" << endl;
    cout << "E: Exit" << endl;
    cout << endl << "Enter a choice (P,L,A,R,C,D,W,E): ";
    char c = 0;
    cin >> c;
    cin.ignore(1000,'\n');
    return c;
}

bool operation (char operation) {
    bool cont = true;
    switch (operation) {
        case 'P': case 'p' : {
            cout << "PLAY >" << endl;
            cout << "Chose an option" << endl;
            cout << "L: Play a playlist" << endl;
            cout << "S: Play a playlist starting from a specific  song" << endl;
            cout << "P: Play a sing song" << endl;
            cout << "E: Exit" << endl << endl;
            cout << "Enter a choice (L,S,P,E): ";
            char c = 0;
            cin >> c;
            player.play(c);
        }
            break;
        case 'L': case 'l' :
            player.printList();
            break;
        case 'A': case 'a' :
            player.addSong(false);
            break;
        case 'R': case 'r' :
            player.removeSong(false);
            break;
        case 'C': case 'c' : {
            cout << "1. Songs of a specific style" << endl;
            cout << "2. Songs of a specific singer" << endl;
            cout << "3. Combination of existing playlists" << endl;
            cout << "4. Combination of existing songs" <<endl;
            cout << endl << "Enter the index of operation: ";
            char c = 0;
            cin >> c;
            player.createList(c);
        }
            break;
        case 'D': case 'd' :
            player.deleteList(false);
            break;
        case 'W': case 'w' :
            player.writeToFile();
            break;
        case 'E': case 'e' :
            player.writeToFile();
            player.exit();
            cont = false;
            break;
        default:
            break;
    }
    return cont;
}
