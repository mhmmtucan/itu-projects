/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 21.11.2016 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "operations.h"

using namespace std;

void printAll(song_node *n) { // send head pointer
    song_node *t;
    t = n;
    do {
        printf("%2d.%-40s\t%-15s\t%-5d\t%-15s\n",t->songIndex,t->data->name,t->data->singer,t->data->year,t->data->style);
        t = t->next;
    } while (t != n);
    
}

void list::playSong(song_node *song, playlist * traverse) { // just printing to the screen
    cout << "playing..."<<endl;
    printf("%-40s\t%-15s\t%-5d\t%-15s\n",song->data->name,song->data->singer,song->data->year,song->data->style);
}

string toString(int i) { // own to_string function
    stringstream ss;
    ss << i;
    return ss.str();
}

void list::readFromFile() {
    playlist *node = new playlist;
    playlist *userPl;
    head = node;
    traverse = head;
    strcpy(head->name, "Choronological");
    head->playlistIndex = 1;
    
    node = new playlist;
    strcpy(node->name, "Sorted");
    node->playlistIndex = 2;
    traverse = node;
    head->next = node;
    node->prev = head;
    
    node = new playlist;
    strcpy(node->name, "Random");
    node->playlistIndex = 3;
    traverse->next = node;
    node->prev = traverse;
    node->next = head;
    head->prev = node;
    tail = node;
    
    ifstream myFile("songbook.txt");
    string temp;
    string star = "";
    int index1 = 1,index3 = 1;
    while (getline(myFile,temp)) {
        if (temp.compare(0,5,"*****") == 0)  {
            star = temp.substr(0,5);
            break;
        }
        
        string name,singer,style;
        int year;
        name =  temp.substr(0,temp.find("\t"));
        temp.erase(0,name.length()+1);
        singer = temp.substr(0,temp.find("\t"));
        temp.erase(0,singer.length()+1);
        year = atoi(temp.substr(0,temp.find("\t")).c_str());
        
        temp.erase(0,toString(year).length()+1);
        if (temp.compare(temp.length()-1,1,"\r") == 0) {
            style = temp.substr(0,temp.find("\r"));
        } else if (temp.compare(temp.length()-1,1,"\n") == 0) {
            style = temp.substr(0,temp.find("\n"));
        } else if (temp.compare(temp.length()-2,2,"\r\n") == 0) {
            style = temp.substr(0,temp.find("\r\n"));
        } else if (temp.compare(temp.length()-1,1,"/n") != 0 && temp.compare(temp.length()-1,1,"\r") != 0  && temp.compare(temp.length()-2,2,"\r\n") != 0) {
            style = temp;
        }
        
        song *toAdd = new song;
        strcpy(toAdd->name, name.c_str());
        strcpy(toAdd->singer, singer.c_str());
        toAdd->year = year;
        strcpy(toAdd->style, style.c_str());
        
        song_node *n1 = new song_node;
        song_node *n2 = new song_node;
        song_node *n3 = new song_node;
        n1->data = new song;
        n2->data = new song;
        n3->data = new song;
        t1=h1;
        t2=h2;
        n1->parent = head; // chronological
        n2->parent = head->next; // sorted
        n3->parent = head->next->next ; // head is pointing chronological, so next->next pointing random
        *(n1->data) = *toAdd;
        *(n2->data) = *toAdd;
        *(n3->data) = *toAdd;
        
        if (h1==NULL) {  // chronological list
            h1=n1;
            tail1 = h1;
            head->head = h1;
            t1=h1;
            t1->next = h1;
            t1->prev = h1;
        } else if (h1!=NULL && toAdd->year < h1->data->year) {
            h1=n1;
            h1->next = t1;
            t1->prev = h1;
            h1->prev = tail1;
            tail1->next = h1;
            head->head = h1;
        }
        
        while (toAdd->year > t1->data->year) {
            t1=t1->next;
            if (t1->next == h1) break;
            
        }
        if (t1!=h1) {
            if (h1!=NULL && toAdd->year > h1->data->year && toAdd->year <= t1->data->year) {
                t1->prev->next = n1;
                n1->next = t1;
                n1->prev = t1->prev;
                t1->prev = n1;
            }
        }
        if (h1!=NULL && toAdd->year > h1->data->year && toAdd->year > t1->data->year) {
            t1->next = n1;
            n1->next = h1;
            n1->prev = t1;
            h1->prev = n1;
            tail1=n1;
        }
        head->songnumber++; // chronological ended

        if(h2==NULL) { // sorted list
            h2=n2; // here is initail add
            tail2 = h2;
            head->next->head = h2;
            t2=h2;
            t2->next = h2;
            t2->prev = h2;
        } else if (h2!=NULL && strcmp(toAdd->singer, h2->data->singer) < 0) { // adding to head
            h2=n2;
            h2->next = t2;
            t2->prev = h2;
            h2->prev = tail2;
            tail2->next = h2;
            head->next->head = h2;
        }
        while (strcmp(toAdd->singer, t2->data->singer) > 0) { // traversing
            t2=t2->next;
            if (t2->next == h2) break;
            
        }
        if (t2!=h2) {
            if (h2!=NULL && strcmp(toAdd->singer, h2->data->singer) > 0 && strcmp(toAdd->singer, t2->data->singer) < 0) { // adding between
                t2->prev->next = n2;
                n2->next = t2;
                n2->prev = t2->prev;
                t2->prev = n2;
            }
            else if (h2!=NULL && strcmp(toAdd->singer, h2->data->singer) > 0 && strcmp(toAdd->singer, t2->data->singer) == 0) { // if singer name is equal then song name should be sorted here
                
                if (strcmp(toAdd->name, t2->data->name) < 0) {
                    
                    // add before
                    n2->next = t2;
                    n2->prev = t2->prev;
                    t2->prev->next = n2;
                    t2->prev = n2;
                } else {
                    // add after
                    while (strcmp(toAdd->name, t2->data->name) > 0 && strcmp(toAdd->singer, t2->next->data->singer) == 0) {
                        t2 = t2->next;
                        if (t2->next == h2) break;
                    }
                    if (strcmp(toAdd->name, t2->data->name) < 0) {
                        // add before
                        n2->next = t2;
                        n2->prev = t2->prev;
                        t2->prev->next = n2;
                        t2->prev = n2;
                    } else {
                        // add after
                        n2->next = t2->next;
                        n2->prev = t2;
                        t2->next->prev = n2;
                        t2->next = n2;
                    }
                }
            }
        }
        if (h2!=NULL && strcmp(toAdd->singer, h2->data->singer) > 0 && strcmp(toAdd->singer, t2->data->singer) > 0) { // adding to end
            t2->next = n2;
            n2->next = h2;
            n2->prev = t2;
            h2->prev = n2;
            tail2=n2;
        }
        head->next->songnumber++; // sorted ended
        
        if (h3==NULL) { // random list multi doubly circular list, all data given
            
            h3 = n3;
            t3=h3;
            head->next->next->head = h3; // head is choronological, next next is random, random list's head first song
            h3->songIndex = index3;
        } else {
            t3->next = n3;
            n3->prev = t3;
            t3 = t3->next;
            n3->next = h3;
            h3->prev = n3;
            index3++;
            t3->songIndex = index3;
        }
        head->next->next->songnumber++;  // random ended
    }
    
    while (star.compare(0,5,"*****") == 0) { // if star ***** there is user generated pl
        
        userPl = new playlist;
        tail = userPl;
        playlist_count++;
        int tempIndex = 1;
        getline(myFile,temp);
        strcpy(userPl->name, temp.c_str());
        userPl->playlistIndex = playlist_count;
        userPl->next = head;
        userPl->prev = head->prev;
        head->prev->next = userPl;
        head->prev = userPl;
        star = "";
        song_node *tempHead = new song_node;
        tempHead = NULL;
        song_node *tempT = new song_node;
        
        while (getline(myFile,temp)) {
            if (temp.compare(0,5,"*****") == 0)  { // 5 star is encountered again, break and create new pl
                star = temp.substr(0,5);
                break;
            }
            string name,singer,style;
            int year;
            name =  temp.substr(0,temp.find("\t"));
            temp.erase(0,name.length()+1);
            singer = temp.substr(0,temp.find("\t"));
            temp.erase(0,singer.length()+1);
            year = atoi(temp.substr(0,temp.find("\t")).c_str());
            temp.erase(0,toString(year).length()+1);
            if (temp.compare(temp.length()-1,1,"\r") == 0) {
                style = temp.substr(0,temp.find("\r"));
            } else if (temp.compare(temp.length()-1,1,"\n") == 0) {
                style = temp.substr(0,temp.find("\n"));
            } else if (temp.compare(temp.length()-2,2,"\r\n") == 0) {
                style = temp.substr(0,temp.find("\r\n"));
            } else if (temp.compare(temp.length()-1,1,"/n") != 0 && temp.compare(temp.length()-1,1,"\r") != 0  && temp.compare(temp.length()-2,2,"\r\n") != 0) {
                style = temp;
            }
            
            song_node *n = new song_node;
            
            n->parent = userPl;
            n->data = new song;
            strcpy(n->data->name, name.c_str());
            strcpy(n->data->singer, singer.c_str());
            n->data->year = year;
            strcpy(n->data->style, style.c_str());
            
            if (tempHead==NULL) { // random list multi doubly circular list, all data given
                tempHead = n;
                tempT=tempHead;
                userPl->head = tempHead;
                tempHead->songIndex = tempIndex;
            } else {
                tempT->next = n;
                n->prev = tempT;
                tempT = n;
                n->next = tempHead;
                tempHead->prev = n;
                tempIndex++;
                tempT->songIndex = tempIndex;
            }
            userPl->songnumber++;
        }
    }
    
    // randomize random pl
    srand((unsigned)time(NULL));
    song *tempData = new song;
    int random = rand()%h3->parent->songnumber;
    r3=h3;
    t3=h3;
    for (int i=0; i<10; i++) {
        for (int j=0; j<random; j++) {
            t3=t3->next;
        }
        *tempData = *(t3->data);
        random = rand()%h3->parent->songnumber;
        for (int j=0; j<random; j++) {
            r3 = r3->next;
        }
        *(t3->data) = *(r3->data);
        *(r3->data) = *tempData;
    }
    
    // assigning index to songs
    t1 = h1;
    t2 = h2;
    do {
        t1->songIndex = index1;
        t2->songIndex = index1;
        index1++;
        t1=t1->next;
        t2=t2->next;
    }while (t1!=h1 && t2!=h2);
}

void list::giveSongIndex(playlist* playlist) {
    song_node *temp;
    temp = playlist->head;
    for (int i=1; i<=playlist->songnumber; i++) {
        temp->songIndex = i;
        temp = temp->next;
    }
}

void list::givePlIndex() {
    playlist *temp;
    temp = head;
    for (int i=1; i<=playlist_count; i++) {
        temp->playlistIndex = i;
        temp = temp->next;
    }
}

void list::printList() {
    listAllLists();
    cout << endl;
    traverse = head;
    char operation;
    bool cont = true;
    while (cont) {
        cout << traverse->playlistIndex << ": " << traverse->name << endl;
        cout << "N (NEXT), P (PREVIOUS) , S (SELECT), E (EXIT)" << endl;
        operation = getchar();
        cin.ignore(1000,'\n');
        switch (operation) {
            case 'N': case 'n':
                traverse = traverse->next;
                break;
            case 'P': case 'p':
                traverse = traverse->prev;
                break;
            case 'S': case 's':
                cout << "P (PLAY), A (ADD SONG), R (REMOVE SONG), D (DELETE PLAYLIST)" << endl;
                operation = getchar();
                switch (operation) {
                    case 'P': case 'p': {
                        song_node *temp;
                        temp = traverse->head;
                        char operation;
                        bool cont = true;
                        while (cont) {
                            playSong(temp,traverse);
                            cout << "N(NEXT), P(PREVIOSUS), E(EXIT)" << endl;
                            cin.ignore(1000,'\n');
                            operation = getchar();
                            switch (operation) {
                                case 'N': case 'n':
                                    temp = temp->next;
                                    break;
                                case 'P': case  'p':
                                    temp = temp->prev;
                                    break;
                                case 'E': case 'e':
                                    cont = false;
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                        break;
                    case 'A': case 'a': {
                        addSong(true); // if list already choosen do not ask again which playlist to be added.
                    }
                        break;
                    case 'R': case 'r': { // if list already choosen do not ask again which playlist to be deleted.
                        removeSong(true);
                    }
                        break;
                    case 'D': case 'd': {
                        deleteList(true);
                    }
                        break;
                    default:
                        break;
                }
                break;
            case 'E': case 'e':
                cont = false;
                break;
            default:
                break;
        }
    }
}

void list::play(char c) {
    switch (c) {
        case 'L': case 'l': {
            song_node* temp;
            listAllLists();
            int index;
            cout << "Choose index of playlist to play: ";
            cin >> index;
            
            traverse = head;
            while (index != traverse->playlistIndex) traverse = traverse->next;
            temp = traverse->head;
            char operation;
            bool cont = true;
            while (cont) {
                playSong(temp,traverse);
                cout << "N(NEXT), P(PREVIOSUS), E(EXIT)" << endl;
                cin.ignore(1000,'\n');
                operation = getchar();
                switch (operation) {
                    case 'N': case 'n':
                        temp = temp->next;
                        break;
                    case 'P': case  'p':
                        temp = temp->prev;
                        break;
                    case 'E': case 'e':
                        cont = false;
                        break;
                    default:
                        break;
                }
            }
        }
            break;
        case 'S': case 's':{
            song_node* temp;
            listAllLists();
            int index;
            cout << "Choose index of playlist to play: ";
            cin >> index;
            traverse = head;
            while (index != traverse->playlistIndex) traverse = traverse->next;
            temp = traverse->head;
            printAll(temp);
            cout << "Choose index of song to play: ";
            cin >> index;
            while (index != temp->songIndex) temp = temp->next;
            char operation;
            bool cont = true;
            while (cont) {
                playSong(temp,traverse);
                cout << "N(NEXT), P(PREVIOSUS), E(EXIT)" << endl;
                cin.ignore(1000,'\n');
                operation = getchar();
                switch (operation) {
                    case 'N': case 'n':
                        temp = temp->next;
                        break;
                    case 'P': case  'p':
                        temp = temp->prev;
                        break;
                    case 'E': case 'e':
                        cont = false;
                        break;
                    default:
                        break;
                }
            }
        }
            break;
        case 'P': case 'p':
            printAll(head->next->head);
            song_node *temp;
            int index;
            temp = head->next->head;
            cout << "Choose index of song to play: ";
            cin >> index;
            while (index != temp->songIndex) temp = temp->next;
            playSong(temp,traverse);
            break;
        case 'E': case 'e':
            
            break;
        default:
            break;
    }
}

void list::createList(char c) {
    switch (c) {
        case '1': {
            string style;
            cout << "Choose a specific style for new playlist: ";
            cin.ignore(1000,'\n');
            getline(cin,style);
            
            playlist *node = new playlist;
            node->head = NULL;
            playlist_count++;
            node->playlistIndex = playlist_count;
            node->next = head;
            node->prev = tail;
            tail->next = node;
            head->prev = node;
            tail = node;
            t2 = h2; // sorted playlist head
            song_node *tailNode = new song_node;
            
            strcpy(node->name, style.c_str());
            do {
                if (strcmp(t2->data->style, style.c_str()) == 0) {
                    song_node *n = new song_node;
                    n->parent = node;
                    n->data = t2->data;
                    if (!(node->head)) {
                        node->head = n;
                        tailNode = node->head;
                        node->head->next = n;
                        node->head->prev = n;
                        node->songnumber = 1;
                    } else {
                        node->songnumber++;
                        tailNode->next = n;
                        n->prev = tailNode;
                        node->head->prev = n;
                        n->next = node->head;
                        tailNode = n;
                    }
                    n->songIndex = node->songnumber;
                }
                t2=t2->next;
            } while (t2!=h2);
        }
            break;
        case '2': {
            string singer;
            cout << "Choose a specific singer for new playlist: ";
            cin.ignore(1000,'\n');
            getline(cin,singer);
            
            playlist *node = new playlist;
            node->head = NULL;
            playlist_count++;
            node->playlistIndex = playlist_count;
            node->next = head;
            node->prev = tail;
            tail->next = node;
            head->prev = node;
            tail = node;
            t2 = h2; // sorted playlist head
            song_node *tailNode = new song_node;
            
            strcpy(node->name, singer.c_str());
            do {
                if (strncmp(t2->data->singer,  singer.c_str(), singer.length()) == 0) {
                    song_node *n = new song_node;
                    n->parent = node;
                    n->data = t2->data;
                    if (!(node->head)) {
                        node->head = n;
                        tailNode = node->head;
                        node->head->next = n;
                        node->head->prev = n;
                        node->songnumber = 1;
                    } else {
                        node->songnumber++;
                        tailNode->next = n;
                        n->prev = tailNode;
                        node->head->prev = n;
                        n->next = node->head;
                        tailNode = n;
                    }
                    n->songIndex = node->songnumber;
                }
                t2=t2->next;
            } while (t2!=h2);
        }
            break;
        case '3': {
            listAllLists();
            cout << endl;
            
            playlist *node = new playlist;
            node->head = NULL;
            playlist_count++;
            node->playlistIndex = playlist_count;
            node->next = head;
            node->prev = tail;
            tail->next = node;
            head->prev = node;
            tail = node;
            song_node *tailNode = new song_node;
            
            song_node *temp;
            int index = 0;
            strcpy(node->name, "Concaded Playlist");
            string str = "first";
            for(int i=0; i<2; i++) {
                cout << "Choose "<< str <<" index of playlist to be concated: " << endl;
                cin >> index;
                traverse = head;
                while (index != traverse->playlistIndex) traverse = traverse->next;
                
                temp = traverse->head;
                do {
                    song_node *n = new song_node;
                    n->parent = node;
                    n->data = temp->data;
                    if (!(node->head)) {
                        node->head = n;
                        tailNode = node->head;
                        node->head->next = n;
                        node->head->prev = n;
                        node->songnumber = 1;
                    } else {
                        node->songnumber++;
                        tailNode->next = n;
                        n->prev = tailNode;
                        node->head->prev = n;
                        n->next = node->head;
                        tailNode = n;
                    }
                    n->songIndex = node->songnumber;
                    temp=temp->next;
                } while (temp!=traverse->head);
                str = "second";
            }
        }
            break;
        case '4': {
            
            playlist *node = new playlist;
            node->head = NULL;
            playlist_count++;
            node->playlistIndex = playlist_count;
            node->next = head;
            node->prev = tail;
            tail->next = node;
            head->prev = node;
            tail = node;
            t2 = h2;
            song_node *tailNode = new song_node;
            
            int index = 0;
            bool cont = true;
            strcpy(node->name, "Mix");
            printAll(h2);
            while (cont) {
                cout << "Select index of songs to add Mixed-playlist, to exit enter (-1): ";
                cin >> index;
                if (index == -1) break;

                do {
                    if (t2->songIndex == index) {
                        song_node *n = new song_node;
                        n->parent = node;
                        n->data = t2->data;
                        if (!(node->head)) {
                            node->head = n;
                            tailNode = node->head;
                            node->head->next = n;
                            node->head->prev = n;
                            node->songnumber = 1;
                        } else {
                            node->songnumber++;
                            tailNode->next = n;
                            n->prev = tailNode;
                            node->head->prev = n;
                            n->next = node->head;
                            tailNode = n;
                        }
                        n->songIndex = node->songnumber;
                    }
 
                    t2=t2->next;
                } while (t2!=h2);
            }
        }
            break;
        default:
            break;
    }
}

void list::addSong(bool isChoosed) {
    int index = 0;
    printAll(h2);
    cout << endl << "Choose a song to add a playlist: ";
    cin >> index;
    t2=h2;
    while (index != t2->songIndex) t2=t2->next;
    if(isChoosed == false) {
        listAllLists();
        cout << endl << "Choose playlist: ";
        cin >> index;
        traverse = head;
        while (index != traverse->playlistIndex) traverse = traverse->next;
    }
    song_node * n = new song_node;
    n->parent = traverse;
    n->data = t2->data;
    traverse->head->prev->next = n;
    n->prev = traverse->head->prev;
    n->next = traverse->head;
    traverse->head = n;
    traverse->songnumber++;
    giveSongIndex(traverse);
}

void list::deleteList(bool isChoosed) {
    
    if (isChoosed == false) {
        listAllLists();
        cout << endl << "Choose playlist to be deleted: ";
        int index;
        cin >> index;
        traverse = head;
        while (index != traverse->playlistIndex) traverse = traverse->next;
    }
    song_node * temp;
    traverse->head->prev->next = NULL;
    while (traverse->head->next != NULL) { // song nodes are deleted.
        temp = traverse->head;
        traverse->head = traverse->head->next;
        traverse->head->prev = NULL;
        delete temp;
    }
    delete traverse->head;
    traverse->prev->next = traverse->next;
    traverse->next->prev = traverse->prev;
    delete traverse;
    playlist_count--;
    givePlIndex();
    
}


void list::listAllLists() {
    traverse = head;
    do {
        cout << traverse->playlistIndex << ": " << traverse->name << endl;
        traverse = traverse->next;
    } while(traverse != head);
}

void list::removeSong(bool isChoosed) {
    int index;
    if (isChoosed == false) {
        listAllLists();
        cout << endl << "Choose playlist: ";
        cin >> index;
        traverse = head;
        while (index != traverse->playlistIndex) traverse = traverse->next;
    }
    printAll(traverse->head);
    cout << endl << "Choose song to be deleted: ";
    cin >> index;
    song_node* temp;
    temp = traverse->head;
    while (index != temp->songIndex) temp=temp->next;
    if (temp == traverse->head) traverse->head=temp->next;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    traverse->songnumber--;
    giveSongIndex(traverse);
}

void list::writeToFile() {
    ofstream myFile("songbook.txt");
    song_node * temp ;
    temp = head->head;
    do {
        myFile << temp->data->name << "\t" << temp->data->singer << "\t" << temp->data->year << "\t" << temp->data->style << endl;
        temp = temp->next;
    } while (temp!=head->head);
    
    if (playlist_count>3) {
        for (int i=4; i<=playlist_count; i++) {
            traverse = head;
            while (i != traverse->playlistIndex) traverse = traverse->next;
            myFile << "*****" << endl << traverse->name << endl;
            temp = traverse->head;
            do {
                myFile << temp->data->name << "\t" << temp->data->singer << "\t" << temp->data->year << "\t" << temp->data->style << endl;
                temp = temp->next;
            } while (temp!=traverse->head);
        }
    }
    myFile.close();
}
// Deletes the nodes of playlists and playlist itself
void list::exit() {
    for (int i=playlist_count; i>=1; i--) {
        traverse = head;
        song_node * temp;
        while (i != traverse->playlistIndex) traverse = traverse->next;
        traverse->head->prev->next = NULL;
        while (traverse->head->next != NULL) { // song nodes are deleted.
            temp = traverse->head;
            traverse->head = traverse->head->next;
            traverse->head->prev = NULL;
            delete temp;
        }
        delete traverse->head;
        traverse->prev->next = traverse->next;
        traverse->next->prev = traverse->prev;
        delete traverse;
    }
}
