/* * * * * * * * * * * * * * * * * * * * * * *
Name: Zach Fechko
Class: Cpts 122; Lab Section
Programming Assignment: 6
Date Due: Wednesday 9/15/21
Description: Using doubly linked lists to make a playlist manager
* * * * * * * * * * * * * * * * * * * * * * */

#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS

/*Libraries go here*/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct duration
{
	int minutes;
	int seconds;
} Duration;

typedef struct record
{
	char artist[100];
	char album[100];
	char song[100];
	char genre[100];
	Duration length;
	int timesPlayed;
	int rating;
} Record;

typedef struct tempRecord
{
	char firstName[100];
	char lastName[100];
	char bandName[100];
	char album[100];
	char song[100];
	char genre[100];
	Duration length;
	int timesPlayed; 
	int rating;
}Temp;

typedef struct node
{
	Record data;
	struct node* pNext;
	struct node* pPrev;
} Node;

typedef struct list
{
	Node* pHead;
}List;
//copy and paste the following before each function prototype delete before submission
/* * * * * * * * * * * * * * *
Function Name:
Date Created:
Date Last Modfied:
Description of Function:
Input parameters:
Returns:
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * *
Function Name: printMenu
Date Created: 9/12/21
Date Last Modfied:
Description of Function: This is the command that most of the program will run through
Input parameters: nothing
Returns: nothing, it's void
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
void printMenu();

/* * * * * * * * * * * * * * *
Function Name: initList
Date Created:9/12/21
Date Last Modfied:
Description of Function: initializes the list
Input parameters: a pointer to the list
Returns: nothing, it's void
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
void initList(List* pList);

/* * * * * * * * * * * * * * *
Function Name: makeNode
Date Created: 9/12/21
Date Last Modfied:
Description of Function: Allocates memory for a new node
Input parameters: A pointer to the new node
Returns: The pointer to the new node
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
Node* makeNode(Temp* newRecord);

/* * * * * * * * * * * * * * *
Function Name: loadPlaylist
Date Created: 9/13/21
Date Last Modfied:
Description of Function: Reads the playlist data to the linked list
Input parameters: the pointer to the infile, and the pointer to the list
Returns: an int for success
Preconditions: list must be initialized
Postconditions:
* * * * * * * * * * * * * * */
int loadPlaylist(List* pList);

/* * * * * * * * * * * * * * *
Function Name: printPlaylist
Date Created: 9/13/21
Date Last Modfied:
Description of Function: Prints the contents of the playlist
Input parameters: a pointer to a node
Returns: nothing, it's void
Preconditions: the loadPlaylist function must have already been called, so the list has to be populated with content
Postconditions:
* * * * * * * * * * * * * * */
int printPlaylist(List pList);

/* * * * * * * * * * * * * * *
Function Name: deleteItem
Date Created: 9/13/21
Date Last Modfied:
Description of Function: deletes a song from the playlist based on user input
Input parameters: a pointer to the list, and the thing we're trying to delete
Returns: 1 for successful deletion, 0 for unsuccessful
Preconditions: list must be populated
Postconditions:
* * * * * * * * * * * * * * */
int deleteItem(List* pList);

/* * * * * * * * * * * * * * *
Function Name: readCsv
Date Created:9/13
Date Last Modfied:
Description of Function: reads the contents of the musicPlaylist.csv to a temporary array to be copied over
Input parameters: a pointer to the infile, and the temp array 
Returns: nothing, it's void
Preconditions: infile must have been opened
Postconditions:
* * * * * * * * * * * * * * */
void readCsv(FILE* infile, Temp array[]);

/* * * * * * * * * * * * * * *
Function Name: insertAtFront
Date Created: 9/15
Date Last Modfied: 9/15
Description of Function: inserts a node to the beginning of the linked list
Input parameters: pointer to a list, and the new record
Returns: nothing
Preconditions: data must have already been read into the temporary array
Postconditions:
* * * * * * * * * * * * * * */
void insertAtFront(List* pList, Temp newRecord);

/* * * * * * * * * * * * * * *
Function Name: storePlaylist
Date Created:9/15
Date Last Modfied:9/15
Description of Function: writes the playlist to the music.csv
Input parameters: the list, not using the pointer because we're not modifying the list
Returns: a success integer, 1 for success, 0 for failure
Preconditions: list must be populated
Postconditions:
* * * * * * * * * * * * * * */
int storePlaylist(List pList);

/* * * * * * * * * * * * * * *
Function Name: addItem
Date Created: 9/15
Date Last Modfied: 9/15
Description of Function: Asks the user for information and then performs an insertAtFront to add that new information to the list
Input parameters: pointer to the list
Returns: int for success, 1 for success, 0 for failure
Preconditions: list has to already be initialized and populated
Postconditions:
* * * * * * * * * * * * * * */
int addItem(List* pList);

/* * * * * * * * * * * * * * *
Function Name: playSong
Date Created: 9.15
Date Last Modfied: 9.15
Description of Function: Prompts the user to select a song from the list before printing the name of the song for a short duration
Input parameters: the list
Returns:
Preconditions: list has to be populated
Postconditions:
* * * * * * * * * * * * * * */
int playSong(List pList);

/* * * * * * * * * * * * * * *
Function Name: countSongs
Date Created: 9/16
Date Last Modfied: 9/16
Description of Function: Counts the number of songs in the playlist and returns how many there are, this is a helper function for playSong
Input parameters: the list
Returns: the count of how many songs(nodes) are in the list
Preconditions: list has to be populated
Postconditions:
* * * * * * * * * * * * * * */
int countSongs(List pList);

/* * * * * * * * * * * * * * *
Function Name:shuffleSongs
Date Created: 9/16
Date Last Modfied: 9/20
Description of Function: This function functions similar to playSong in the sense it traverses the list and plays a song, but this one
removes the user input and uses rand() to pick a random song in the list, and then decrements the amount of songs that can be chosen from
Input parameters: the list
Returns: 1 for success, 0 for failure
Preconditions: list must have been loaded in, this will not work with an empty list
Postconditions:
* * * * * * * * * * * * * * */
int shuffle(List pList);

/* * * * * * * * * * * * * * *
Function Name: rateSong
Date Created: 9.20
Date Last Modfied: 9.21
Description of Function: Prompts the user for which song they wish to rate, and then overwriting the rating in the list
Input parameters: A pointer to the list because we're editing
Returns: 1 for success, 0 for failure
Preconditions: List has to be populated with data, so loadPlaylist has to be called
Postconditions: A certain song has a different rating than when it was loaded in
* * * * * * * * * * * * * * */
int rateSong(List* pList);

/* * * * * * * * * * * * * * *
Function Name: editSong
Date Created: 9.20
Date Last Modfied: 9.21
Description of Function: This function prompts the user to select a song from the playlist and then prompts them for all the variables
similar to addSong
Input parameters: pointer to the list
Returns: 1 for success, 0 for failure
Preconditions: The list has to be populated, so loadPlaylist has to be called
Postconditions: The record will have different data in the node
* * * * * * * * * * * * * * */
int editSong(List* pList);

/* * * * * * * * * * * * * * *
Function Name: sortPlaylist
Date Created: 9.21
Date Last Modfied:
Description of Function: Sorts the list given a certain parameter
Input parameters: pointer to a list
Returns: 1 for success, 0 for failure
Preconditions: list has to be populated
Postconditions: list will be sorted by a given parameter specified by the user
* * * * * * * * * * * * * * */
int sortPlaylist(List* pList);

/* * * * * * * * * * * * * * *
Function Name: displayByName
Date Created: 9.18
Date Last Modfied:
Description of Function: prompts the user for the name of an artist in the list and prints all the records
that have artists that match the user's input
Input parameters: the playlist
Returns: returns how many records match the given artist
Preconditions: list has to be populated
Postconditions: nothing changes due to this function
* * * * * * * * * * * * * * */
int displaybyName(List pList);

/* * * * * * * * * * * * * * *
Function Name: notScuffedShuffle
Date Created: 9.23
Date Last Modfied: 9.23
Description of Function: This function generates a random order 
Input parameters: The playlist
Returns: 1 for success, 0 for failure
Preconditions: list has to be populated with data first
Postconditions: nothing changes as a result of this function running
* * * * * * * * * * * * * * */
int notScuffedShuffle(List pList);

/* * * * * * * * * * * * * * *
Function Name: generateRandomOrder
Date Created: 9.23
Date Last Modfied: 9.24
Description of Function: This function will populate an array with a sequence of random numbers that are equal to the size of the list
Input parameters: The list in order to make it equal to size
Returns: the pointer to the array of random numbers
Preconditions: this is a helper function to notScuffedShuffle
Postconditions:
* * * * * * * * * * * * * * */
void generateRandomOrder(List pList, int array[]);
#endif
