/* @Author
 * Student Name: Muhammet Uçan
 * Student ID : 150140707
 * Date: 21.11.2016 */

#ifndef nodes_h
#define nodes_h

#define SNAME_LENGTH 50  
#define LNAME_LENGTH 50 
#define STYLE_LENGTH 30  
#define SINGER_LENGTH 50
struct song {
    char* name = new char[SNAME_LENGTH];
    char* singer = new char[SINGER_LENGTH];
    char* style = new char[STYLE_LENGTH];
    int year;
};
struct playlist;

struct song_node {
    int songIndex;
    song* data;
    song_node* next;
    song_node* prev;
    playlist* parent;
};
struct playlist {
    int songnumber=0;
    int playlistIndex;
    char* name = new char[LNAME_LENGTH];
    song_node* head;
    playlist* next;
    playlist* prev;
};


#endif /* nodes_h */
