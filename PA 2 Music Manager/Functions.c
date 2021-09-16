#include "Header.h"

/* * * * * * * * * * * * * * *
Function Name: printPlaylist
Date Created: 9/13/21
Date Last Modfied:
Description of Function: Prints the contents of the list
Input parameters: a pointer to a node
Returns: nothing, it's void
Preconditions: the loadPlaylist function must have already been called, so the list has to be populated with content
Postconditions:
* * * * * * * * * * * * * * */
void printPlaylist(List pList)
{
	Node* pNode = pList.pHead; //makes a node and sets it to the beginning of the list
	int count = 1; //this is for printing
	while (pNode != NULL) //while there's content in the list
	{
		printf("%d) %s, %s, %s, %s, %d : %d, %d, %d\n", count,
			pNode->data.artist,
			pNode->data.album,
			pNode->data.song,
			pNode->data.genre,
			pNode->data.length.minutes,
			pNode->data.length.seconds,
			pNode->data.timesPlayed,
			pNode->data.rating);
	/*	printf("%s\n", pNode->data.artist);
		printf("%s\n", pNode->data.album);
		printf("\n");*/
		count++;
		pNode = pNode->pNext;
	}

}

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
int storePlaylist(List pList)
{
	int success = 0;
	FILE* outfile = fopen("testOutfile.csv", "w"); //opens music.csv for mode write
	Node* pNode = pList.pHead;
	while (pNode != NULL)
	{
		fprintf(outfile, "%s, %s, %s, %s, %d : %d, %d, %d",
			pNode->data.artist,
			pNode->data.album,
			pNode->data.song,
			pNode->data.genre,
			pNode->data.length.minutes,
			pNode->data.length.seconds,
			pNode->data.timesPlayed,
			pNode->data.rating);
		pNode = pNode->pNext;
		success = 1;
	}
	
	fclose(outfile);
	return success;
}

/* * * * * * * * * * * * * * *
Function Name: printMenu
Date Created: 9/12/21
Date Last Modfied: 9/15
Description of Function: This is the command that most of the program will run through
Input parameters: nothing
Returns: nothing, it's void
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
void printMenu()
{
	List playlist = { NULL };
	int choice = 0, success = 0;
	while (choice != 11) //while the choice does not equal the exit case
	{
		printf("Welcome to your CougPod! What would you like to do?\n");
		printf(" 1) Load Playlist\n 2)Store Playlist\n 3)Display Playlist\n 4)Insert New Song\n 5)Delete a Song\n 6) Edit a song\n 7)Sort\n 8)Rate a song\n 9)Play a Song\n 10)Shuffle\n 11)Exit\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			//load playlist function
			initList(&playlist);
			system("cls");
			if (loadPlaylist(&playlist) == 1)
			{
				printf("Your playlist has successfully been loaded into your CougPod!\n");
			}
			break;
		case 2:
			system("cls");
			//store playlist function
			if (playlist.pHead == NULL)
			{
				printf("There's nothing in your playlist to store, maybe try loading your playlist first\n");
			}
			else 
			{
				if (storePlaylist(playlist) == 1)
				{
					printf("Your playlist has successfully been saved\n");
				}
			}
			break;
		case 3:
			//display list
			system("cls");
			if (playlist.pHead == NULL) //if list is empty (usually done by people displaying the list before loading it)
			{
				printf("Oops! Looks like you haven't loaded in your list yet! Go back and try again\n");
			}
			else
			{
				printPlaylist(playlist);
			}
			break;
		case 4:
			//add a new song function
			if (playlist.pHead == NULL)
			{
				printf("Your playlist has not been loaded, try again\n");
			}
			else
			{
				if (addItem(&playlist) == 1)
				{
					printf("Your song has successfully been added\n");
				}
			}
			break;
		case 5:
			//function to delete a song
			break;
		case 6:
			//Edit a song function
			break;
		case 7:
			//sort list function
		case 8:
			//rate function
			break;
		case 9:
			//play song from top of list/current song
			break;
		case 10:
			//play random song
			break;
		case 11:
			system("cls");
			//we exit the program
			printf("See you next time!\n");
			exit(0);
		default:
			system("cls");
			printf("That is an invalid choice, please try again\n");
		}
	}
}

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
void initList(List* pList)
{
	pList->pHead = NULL; //sets the list to empty
}

/* * * * * * * * * * * * * * *
Function Name: makeNode
Date Created: 9/12/21
Date Last Modfied:9/15
Description of Function: constructs a new node
Input parameters: A pointer to the new node
Returns: The pointer to the new node
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
Node* makeNode(Temp* newRecord)
{
	int i = 0;
	Node* pMem = (Node*)malloc(sizeof(Node));
	if (pMem != NULL)
	{
		//we successfully allocated memory
		if (newRecord->firstName[0] != '\0')
		{
			strcpy(pMem->data.artist, strcat(newRecord->firstName, newRecord->lastName));
		}
		else if (newRecord->firstName[0] == '\0')
		{
			strcpy(pMem->data.artist, newRecord->bandName);
		}
		strcpy(pMem->data.album, newRecord->album);
		strcpy(pMem->data.song, newRecord->song);
		strcpy(pMem->data.genre, newRecord->genre);
		pMem->data.length.minutes = newRecord->length.minutes;
		pMem->data.length.seconds = newRecord->length.seconds;
		pMem->data.timesPlayed = newRecord->timesPlayed;
		pMem->data.rating = newRecord->rating;
	}
	return pMem;
}

/* * * * * * * * * * * * * * *
Function Name: loadPlaylist
Date Created: 9/13/21
Date Last Modfied: 9/13
Description of Function: Reads the playlist data to the linked list, will function like insert at front
Input parameters: the pointer to the infile, and the pointer to the list, as 
Returns: an int for success
Preconditions: list must be initialized
Postconditions:
* * * * * * * * * * * * * * */
int loadPlaylist(List* pList) // remove temp array
{
	printf("Loading your playlist...\n");
	FILE* infile = fopen("music.csv", "r");
	Temp newArtist = { NULL };
	int success = 0;
	//readCsv(infile, array);
	// contents of readCSV goes here
	char line[100] = "";
	while (fgets(line, 100, infile) != NULL)
	{
		if (line[0] == '\"')
		{
			strcpy(newArtist.lastName, strtok(line, ","));
			strcpy(newArtist.firstName, strtok(NULL, "\","));
			strcpy(newArtist.bandName, "\0");
		}
		else if (line[0] != '\"')
		{
			strcpy(newArtist.firstName, "\0");
			strcpy(newArtist.lastName, "\0");
			strcpy(newArtist.bandName, strtok(line, ","));
		}
		strcpy(newArtist.album, strtok(NULL, ","));
		strcpy(newArtist.song, strtok(NULL, ","));
		strcpy(newArtist.genre, strtok(NULL, ","));
		newArtist.length.minutes = atoi(strtok(NULL, ":"));
		newArtist.length.seconds = atoi(strtok(NULL, ","));
		newArtist.timesPlayed = atoi(strtok(NULL, ","));
		newArtist.rating = atoi(strtok(NULL, "\n"));
		insertAtFront(pList, newArtist);

	}
	

	// when new record is populated and you want to insert
	// call insert at front(newRecord, Plist)

	success = 1;
	fclose(infile);
	return success;
}



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
int deleteItem(List* pList, char* searchItem)
{
	Node* pCur = pList->pHead, *pPrev = NULL;
	int success = 0;

	while (pCur != NULL && strcmp(searchItem, pCur->data.song) != 0)
	{
		pPrev = pCur; //traverse the list in search of the title the user wants to delete
		pCur = pCur->pNext;
	}
}

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
void readCsv(FILE* infile, Temp array[])
{
	char line[100] = "";
	int i = 0;
	Temp newArtist = { NULL };


	while (fgets(line, 100, infile) != NULL)
	{
		if (line[0] == '\"') //if the line starts with a double quote, which signifies that it's a name and not a band
		{
			strcpy(array[i].lastName, strtok(line, ",")); //we parse the last name
			strcpy(array[i].firstName, strtok(NULL, "\",")); //then parse the first name
			strcpy(array[i].bandName, "\0"); //and then set the band name to null so there's nothing there when we copy later
		}
		else if (line[0] != '\"') //if the line DOESN'T start with double quotes, which means it's a band
		{
			strcpy(array[i].firstName, "\0");
			strcpy(array[i].lastName, "\0");
			strcpy(array[i].bandName, strtok(line, ","));
		}
		strcpy(array[i].album, strtok(NULL, ","));
		strcpy(array[i].song, strtok(NULL, ","));
		strcpy(array[i].genre, strtok(NULL, ","));
		array[i].length.minutes = atoi(strtok(NULL, ":"));
		array[i].length.seconds = atoi(strtok(NULL, ","));
		array[i].timesPlayed = atoi(strtok(NULL, ","));
		array[i].rating = atoi(strtok(NULL, "\n"));
		
		
	}
}

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
void insertAtFront(List* pList, Temp newRecord)
	{
		Node* pMem = makeNode(&newRecord);
		if (pList->pHead != NULL)
		{
			pMem->pNext = (*pList).pHead;
			(*pList).pHead->pPrev = pMem;
		}
			(*pList).pHead = pMem;
	}

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
int addItem(List* pList)
{
	Temp newRecord = { NULL };
	int success = 0;
	printf("Enter the name of the artist you would like to add: ");
	scanf("%s", &newRecord.bandName);

	printf("Enter the name of the album: ");
	scanf("%s", &newRecord.album);

	printf("Enter the name of the song: ");
	scanf("%s", &newRecord.song);

	printf("Enter the genre of the song: ");
	scanf("%s", &newRecord.genre);

	printf("Enter how long the song is (minutes): ");
	scanf("%d", &newRecord.length.minutes);

	printf("Enter the seconds of the song: ");
	scanf("%d", &newRecord.length.seconds);

	printf("How many times have you listened to this song?: ");
	scanf("%d", &newRecord.timesPlayed);

	printf("What would you rate this song out of 5: ");
	scanf("%d", &newRecord.rating);

	insertAtFront(pList, newRecord);
	success = 1;
	return success;
}

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
void playSong(List pList)
{
	

	int choice = 0, count = 0;
	printPlaylist(pList);
	printf("Which song would you like to play? Please type a number:\n");
	scanf("%d", &choice);

}