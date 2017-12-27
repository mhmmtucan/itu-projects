/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 21.11.2016 */

#ifndef operations_h
#define operations_h
#include "nodes.h"

struct list {
    int playlist_count = 3 ;
    playlist *head,*traverse,*tail;
    song_node *h1,*h2,*h3,*t1,*t2,*t3,*r3,*tail1,*tail2;  // h=head, t=traverse, n=node
    FILE * file;
    void listAllLists(); // printing all playlists to screen
    void giveSongIndex(playlist*);
    void givePlIndex(); // index for playlists
    void playSong(song_node *song, playlist * traverse);
    void createList(char c);
    void addSong(bool);
    void play(char c);
    void removeSong(bool);
    void deleteList(bool);
    void printList();
    void writeToFile();
    void readFromFile();
    void exit();
};
#endif /* operations_h */
