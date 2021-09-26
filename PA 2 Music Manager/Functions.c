#include "Header.h"

/* * * * * * * * * * * * * * *
Function Name: printPlaylist
Date Created: 9/13/21
Date Last Modfied: 9/15
Description of Function: Prints the contents of the list
Input parameters: a pointer to a list
Returns: a success variable, 1 for success, 0 for failure
Preconditions: the loadPlaylist function must have already been called, so the list has to be populated with content
Postconditions:
* * * * * * * * * * * * * * */
int printPlaylist(List pList)
{
	Node* pNode = pList.pHead; //makes a node and sets it to the beginning of the list
	int count = 1, success = 0; //this is for printing
	if (pNode == NULL)
	{
		printf("There are no records in this list\n");
	}
	while (pNode != NULL) //while there's content in the list
	{
		printf("%d) %s, %s, %s, %s, %d : %.2d, %d, %d\n", count,
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
		if (pNode->pNext == NULL)
		{
			success = 1;
			return success;
		}
		else
		{
			count++;
			pNode = pNode->pNext;
		}	
	}
	
	return success;
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
	/*The reason I'm using testOutfile.csv instead of the main music.csv is to prove that my code can parse the artists that are indexed "lastname,firstname"*/
	FILE* outfile = fopen("testOutfile.csv", "w"); //opens music.csv for mode write
	Node* pNode = pList.pHead;
	while (pNode != NULL)
	{
		fprintf(outfile, "%s,%s,%s,%s,%d:%.2d,%d,%d\n",
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
		case 1: //load playlist function
			initList(&playlist);
			system("cls");
			if (loadPlaylist(&playlist) == 1)
			{
				printf("Your playlist has successfully been loaded into your CougPod!\n");
			}
			break;
		case 2: //store playlist function
			system("cls");
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
		case 3: //display list
			system("cls");
			if (playlist.pHead == NULL) //if list is empty (usually done by people displaying the list before loading it)
			{
				printf("Oops! Looks like you haven't loaded in your list yet! Go back and try again\n");
				Sleep(2000);
			}
			else
			{
				int playlistChoice = 0, names = 0;
				system("cls");
				printf("Would you like to\n 1)Show the entire playlist?\n 2)Search for an artist\n");
				scanf("%d", &playlistChoice);
				if (playlistChoice == 1)
				{
					system("cls");
					if (printPlaylist(playlist) == 1)
					{
						char buffer[2];
						fgets(buffer, 2, stdin);
						printf("Here's your playlist. Press enter to continue\n");
						fgets(buffer, 2, stdin);
						system("cls");
					}
				}
				else
				{
					names = displaybyName(playlist);
					printf("Found %d records matching your search\n", names);
					Sleep(2000);
					system("cls");
				}	
			}
			break;
		case 4: //add new song
			if (playlist.pHead == NULL)
			{
				printf("Your playlist has not been loaded, try again\n");
			}
			else
			{
				if (addItem(&playlist) == 1)
				{
					system("cls");
					printf("Your song has successfully been added\n");
					Sleep(2000);
				}
			}
			break;
		case 5: //function to delete a song
			if (playlist.pHead == NULL) //if list is empty 
			{				
				printf("Oops! Looks like you haven't loaded in your list yet! Go back and try again\n");
			}
			else
			{
				if (deleteItem(&playlist) == 1);
				{
					system("cls");
					printf("\n");
					printf("Song deleted successfully\n");
					Sleep(2000);
				}
			}
			break;
		case 6: //Edit a song function
			if (playlist.pHead == NULL) //if list is empty 
			{
				printf("Oops! Looks like you haven't loaded in your list yet! Go back and try again\n");
			}
			else
			{
				if (editSong(&playlist) == 1)
				{
					system("cls");
					printf("\n");
					printf("Record edited successfully\n");
				}
			}
			break;
		case 7: //sort list
			if (playlist.pHead == NULL) //if list is empty 
			{
				printf("Oops! Looks like you haven't loaded in your list yet! Go back and try again\n");
			}
			if (sortPlaylist(&playlist) == 1)
			{
				system("cls");
				printf("List sorted successfully");
				Sleep(2000);
			}
			break;
		case 8: //rate song
			if (playlist.pHead == NULL) //if list is empty 
			{
				printf("Oops! Looks like you haven't loaded in your list yet! Go back and try again\n");
			}
			else
			{
				if (rateSong(&playlist) == 1)
				{
					system("cls");
					printf("\n");
					printf("Rating change successfully\n");
				}
			}
			break;
		case 9: //play song function
			if (playlist.pHead == NULL) //if list is empty 
			{
				printf("Oops! Looks like you haven't loaded in your list yet! Go back and try again\n");
			}
			else
			{
				if (playSong(playlist) == 1)
				{
					system("cls");
					printf("\n");
					printf("Reached the end of your playlist\n");
					Sleep(2000);
				}
			}
			break;
		case 10: //Shuffle 
			if (playlist.pHead == NULL) //if list is empty 
			{
				printf("Oops! Looks like you haven't loaded in your list yet! Go back and try again\n");
			}
			else
			{
				if (notScuffedShuffle(playlist) == 1)
				{
					system("cls");
					printf("\n");
					printf("Reached the end of playlist\n");
					Sleep(2000);
				}
			}
			break;
		case 11: //exit the program
			if(storePlaylist(playlist) == 1)
			system("cls");
			//we exit the program
			printf("Playlist Saved. See you next time!\n");
			exit(0);
		default: //case for any invalid input
			system("cls");
			printf("That is an invalid choice, please try again\n");
		}
	}
}

/* * * * * * * * * * * * * * *
Function Name: initList
Date Created:9/12/21
Date Last Modfied: 9.20
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

		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}
	return pMem;
}

/* * * * * * * * * * * * * * *
Function Name: loadPlaylist
Date Created: 9/13/21
Date Last Modfied: 9/16
Description of Function: Reads the playlist data to the linked list, will function like insert at front
Input parameters: the pointer to the infile, and the pointer to the list, as 
Returns: an int for success
Preconditions: list must be initialized
Postconditions:
* * * * * * * * * * * * * * */
int loadPlaylist(List* pList)
{
	printf("Loading your playlist...\n");
	Sleep(3000);
	FILE* infile = fopen("music.csv", "r");
	Temp newArtist = { NULL };
	int success = 0;
	char line[100] = "";
	while (fgets(line, 100, infile) != NULL)
	{
		if (line[0] == '\"')
		{
			line[0] = ' ';
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
		if (newArtist.length.minutes < 0) //protection against invalid values
		{
			newArtist.length.minutes = 0;
		}
		newArtist.length.seconds = atoi(strtok(NULL, ","));
		newArtist.timesPlayed = atoi(strtok(NULL, ","));
		if (newArtist.timesPlayed < 0) //protection against invalid values
		{
			newArtist.timesPlayed = 0;
		}
		newArtist.rating = atoi(strtok(NULL, "\n"));
		if (newArtist.rating < 1) //protection against a rating lower than 1 (invalid value)
		{
			newArtist.rating = 1;
		}
		else if (newArtist.rating > 5) //protection against a rating higher than 5
		{
			newArtist.rating = 5;
		}
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
Date Last Modfied: 9/21
Description of Function: deletes a song from the playlist based on user input
Input parameters: a pointer to the list, and the thing we're trying to delete
Returns: 1 for successful deletion, 0 for unsuccessful
Preconditions: list must be populated
Postconditions:
* * * * * * * * * * * * * * */
int deleteItem(List* pList)
{
	if (pList->pHead != NULL)
	{
		system("cls");
		Node* pCur = pList->pHead, * pPrev = NULL;
		int success = 0, choice = 0, position = 1;
		if (printPlaylist(*pList) == 1)
		{
			printf("Which song would you like to delete? Type a number: ");
			scanf("%d", &choice);
			if (choice > countSongs(*pList))
			{
				printf("invalid choice, try again\n");
				return 0;
			}
			while (pCur != NULL && position < choice)
			{
				pPrev = pCur; //traverse the list in search of the title the user wants to delete
				pCur = pCur->pNext;
				position++;
			}
			if (pCur->pNext == NULL) //if there's only one entry in the list
			{
				free(pCur);
				return 1;
			}
			if (pCur != NULL && position == choice)
			{
				pPrev->pNext = pCur->pNext;
				free(pCur);
				return 1;
			}
		}
	}
	return 0;
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
NOTE: This function is deprecated, but will remain in here instead of being deleted just for records
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
			pMem->pNext = pList->pHead;
			pList->pHead->pPrev = pMem;
			
		}

		pList->pHead = pMem;
	}

/* * * * * * * * * * * * * * *
Function Name: addItem
Date Created: 9/15
Date Last Modfied: 9/15
Description of Function: Asks the user for information and then performs an insertAtFront to add that new information to the list
Input parameters: pointer to the list
Returns: int for success, 1 for success, 0 for failure
Preconditions: list has to already be initialized and populated
Postconditions: list now has a new record inserted at the front
Notes: I looked at geeks4geeks to find out how to read a string with spaces, that's where the strcspn comes from
* * * * * * * * * * * * * * */
int addItem(List* pList)
{
	Temp newRecord = { NULL };
	int success = 0;
	fgets(newRecord.bandName, 100, stdin); //this is for ignoring the previous enter so we can read in the new line
	printf("Enter the name of the artist you would like to add: ");
	fgets(newRecord.bandName, 100, stdin);

	printf("Enter the name of the album: ");
	fgets(newRecord.album, 100, stdin);

	printf("Enter the name of the song: ");
	fgets(newRecord.song, 100, stdin);


	printf("Enter the genre of the song: ");
	fgets(newRecord.genre, 100, stdin);

	printf("Enter how long the song is (minutes): ");
	scanf("%d", &newRecord.length.minutes);

	printf("Enter the seconds of the song: ");
	scanf("%d", &newRecord.length.seconds);

	printf("How many times have you listened to this song?: ");
	scanf("%d", &newRecord.timesPlayed);

	printf("What would you rate this song out of 5: ");
	scanf("%d", &newRecord.rating);

	//this bit eliminates the '\n' that fgets puts on the end of the string, helps with formatting when displaying and storing to the csv
	newRecord.bandName[strcspn(newRecord.bandName, "\n")] = 0;
	newRecord.album[strcspn(newRecord.album, "\n")] = 0;
	newRecord.song[strcspn(newRecord.song, "\n")] = 0;
	newRecord.genre[strcspn(newRecord.genre, "\n")] = 0;

	if (newRecord.length.minutes < 1) //protection against invalid values
	{
		newRecord.length.minutes = 0;
	}
	if (newRecord.length.seconds < 0) //protection against invalid values
	{
		newRecord.length.seconds = 0;
	}
	if (newRecord.timesPlayed < 1) //protection against invalid values
	{
		newRecord.timesPlayed = 0;
	}
	if (newRecord.rating > 5) //protection against a rating higher than 5
	{
		newRecord.rating = 5;
	}
	if (newRecord.rating < 1) //protection against a rating less than 1
	{
		newRecord.rating = 1;
	}

	insertAtFront(pList, newRecord);
	success = 1;
	return success;
}

/* * * * * * * * * * * * * * *
Function Name: playSong
Date Created: 9.15
Date Last Modfied: 9.12
Description of Function: Prompts the user to select a song from the list before printing the name of the song for a short duration
Input parameters: the list
Returns:
Preconditions: list has to be populated
Postconditions:
* * * * * * * * * * * * * * */
int playSong(List pList)
{
	Node* pCur = pList.pHead;
	int choice = 0, count = 0, position = 1;
	if (printPlaylist(pList) == 1) //if the list prints successfully
	{
		printf("Which song would you like to play? Please type a number:\n");
		scanf("%d", &choice);
		if (choice > countSongs(pList)) //if you pick a number that is greater than the number of songs in the list
		{
			system("cls"); //clears the screen
			printf("Invalid Option, try again"); //prints that you picked an invalid option and prompts the user to try again
			return 0;
		}
		//from here this function works like a delete at position n function when it comes to traversal
	}
	while (pCur != NULL && position != choice) //if pCur isn't null and we haven't hit the preferred song
	{
		pCur->pPrev = pCur; //traversal step
		pCur = pCur->pNext;
		++position;
	}
	if (position == choice) //when we reach the position in the list of the choice
	{
		
		while (pCur != NULL) //repeats for every element in the playlist
		{
			printf("Now Playing: %s by %s\n", pCur->data.song, pCur->data.artist); //prints a now playing messages
			Sleep(3000); //waits for 3 seconds
			system("cls"); //before clearing the screen
			pCur = pCur->pNext; //and moving onto the next song
		}
		return 1;
	}
	
}

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
int countSongs(List pList)
{
	Node* pNode = pList.pHead;
	int count = 0;
	if (pNode == NULL)
	{
		return 0;
	}
	while (pNode != NULL)
	{

			++count;
			if (pNode->pNext == NULL)
			{
				return count;
			}
			pNode->pPrev = pNode;
			pNode = pNode->pNext;
	}
	
}

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
NOTE: This function is super scuffed and is not what we want to use, so we're going to keep this here for records and make a new one
* * * * * * * * * * * * * * */
int shuffle(List pList)
{
	int count = countSongs(pList), song = 0;
	while (count > 0) 
	{
		int position = 1;
		Node* pCur = pList.pHead;
		pCur->pPrev = NULL; //this part is for when we reiterate through the function, it resets pCur;
		song = rand() % count; //sets the song position to a random number from 1 - the size of the list
		while (pCur != NULL && position != song) //if pCur isn't null and we haven't hit the shuffled song
		{
			pCur->pPrev = pCur; //traversal step
			pCur = pCur->pNext;
			++position;
		}
		if (position == song)
		{
			system("cls");
			printf("Now Playing: %s by %s\n", pCur->data.song, pCur->data.artist);
			Sleep(3000);
		}
		count--;
	}
	return 1;
}

/* * * * * * * * * * * * * * *
Function Name: notScuffedShuffle
Date Created: 9.23
Date Last Modfied: 9.23
Description of Function: This function, when given a random order, will traverse the list
either forwards or backwards to the given position
Input parameters: The playlist, not a pointer because we're not editing the order
Returns: 1 for success, 0 for failure
Preconditions: list has to be populated with data first
Postconditions: nothing changes as a result of this function running
* * * * * * * * * * * * * * */
int notScuffedShuffle(List pList)
{
	Node* pCur = pList.pHead;
	pCur->pPrev = NULL;
	int position = 1, i = 0, shufflePosition = 0;
	int order[50];
	generateRandomOrder(pList, order); //generates a random order for the size of the list
	while (i <= countSongs(pList) - 1) //the reason we're subtracting 1 from countSongs is because i is the array index
	{
		shufflePosition = order[i];
		while (pCur != NULL)
		{
			if (position == 1)
			{
				pCur->pPrev = NULL;
			}
			if (position < shufflePosition) //if the song is further towards the end of the list
			{
				pCur->pPrev = pCur; //we traverse forwards in the list
				pCur = pCur->pNext;
				++position;
			}
			else if (position > shufflePosition) //if the song is further towards the top of the list
			{
				pCur->pNext = pCur;
				pCur = pCur->pPrev;
				pCur->pPrev = pCur->pPrev->pPrev;
				--position;
			}
			if (position == shufflePosition)
			{
				system("cls");
				printf("Now Playing %s by %s", pCur->data.song, pCur->data.artist);
				Sleep(2000);
				
				break;
			}
		}
			
		i++;
		
	}
	return 1;
}


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
int rateSong(List* pList)
{
	system("cls");
	int choice = 0, position = 1, rating = 0;
	Node* pCur = pList->pHead;
	if (printPlaylist(*pList) == 1)
	{
		printf("Select which song you would like to change the rating of, please type a number: ");
		scanf("%d", &choice);
		if (choice > countSongs(*pList))
		{
			printf("Invalid Choice, please try again\n");
			Sleep(2000);
			system("cls");
			return 0;
		}	
		while (pCur != NULL && position < choice) //while we haven't hit the selected song
		{
			pCur->pPrev = pCur;
			pCur = pCur->pNext;
			position++;
		}
		if (position == choice)
		{
			printf("What would you like to rate this song? Type a number from 1 - 5: ");
			scanf("%d", &rating);
			while (rating) //while the rating has a value (essentially an infinite loop until we hit the return 1
			{
				if (rating >= 1 && rating <= 5) //if the rating is between 1 and 5
				{
				pCur->data.rating = rating;
				return 1;
				}
				else //if we reach here at all that means that the user inputted a bad value
				{
					printf("Try again, your entry isn't acceptable: ");
					scanf("%d", &rating);
				}
			}
			
		}
	}
}

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
int editSong(List* pList)
{
	int choice = 0, position = 1, newMinutes = 0, newSeconds = 0, newTimesPlayed = 0, newRating = 0;
	if (pList->pHead != NULL)
	{
		system("cls");
		Node* pCur = pList->pHead;
		if (printPlaylist(*pList) == 1)
		{
			printf("Select a record you would like to edit, please type a number: ");
			scanf("%d", &choice);
		}
		if (choice > countSongs(*pList) || choice < 0)
		{
			printf("Invalid choice, try again\n");
			Sleep(2000);
			system("cls");
			return 0;
		}
		while (pCur != NULL && position < choice)
		{
			pCur->pPrev = pCur;
			pCur = pCur->pNext;
			++position;
		}
		if (pCur != NULL && position == choice)
		{
			fgets(pCur->data.artist, 100, stdin); //this is to ignore previous enter
			
			printf("Enter the updated artist for the record: ");
			fgets(pCur->data.artist, 100, stdin);
			
			printf("Enter the updated album name: ");
			fgets(pCur->data.album, 100, stdin);

			printf("Enter the updated song title: ");
			fgets(pCur->data.song, 100, stdin);

			printf("Enter the updated genre of the song: ");
			fgets(pCur->data.genre, 100, stdin);

			printf("Enter the updated minute length of the song: ");
			scanf("%d", &newMinutes);
			
			printf("Enter the updated second length of the song: ");
			scanf("%d", &newSeconds);
			
			printf("Enter the new amount of times you've played this song: ");
			scanf("%d", &newTimesPlayed);
			
			printf("Enter the new rating for the song from 1-5: ");
			scanf("%d", &newRating);

			pCur->data.length.minutes = newMinutes;
			pCur->data.length.seconds = newSeconds;
			pCur->data.timesPlayed = newTimesPlayed;
			pCur->data.rating = newRating;
			pCur->data.artist[strcspn(pCur->data.artist, "\n")] = 0;
			pCur->data.album[strcspn(pCur->data.album, "\n")] = 0;
			pCur->data.genre[strcspn(pCur->data.genre, "\n")] = 0;
			pCur->data.song[strcspn(pCur->data.song, "\n")] = 0;
		}
		return 1;
	}
}

/* * * * * * * * * * * * * * *
Function Name: sortPlaylist
Date Created: 9.21
Date Last Modfied: 9.21
Description of Function: Sorts the list given a certain parameter
Input parameters: pointer to a list
Returns: 1 for success, 0 for failure
Preconditions: list has to be populated
Postconditions: list will be sorted by a given parameter specified by the user
NOTE: Connor helped me with the way to sort during office hours, so if it's similar to other people, that's why
* * * * * * * * * * * * * * */
int sortPlaylist(List* pList)
{
	Record temp = { NULL };
	int isSorted = 0;
	int choice;
	system("cls");
	printf("What would you like to sort by?\n 1)Artist\n 2)Album\n 3)Genre\n 4)Song\n 5)Length\n 6)Times Played\n 7)Rating\n");
	scanf("%d", &choice);
	if (choice == 1) //if they want to sort by the artist
	{
		while (!isSorted)
		{
			isSorted = 1;
			Node* pCur = pList->pHead, * pAfter = pCur->pNext;
			while (pAfter != NULL)
			{
				if (strcmp(pCur->data.artist, pAfter->data.artist) > 0)
				{
					temp = pCur->data;
					pCur->data = pAfter->data;
					pAfter->data = temp;
					isSorted = 0;
				}
				pCur = pAfter;
				pAfter = pAfter->pNext;
			}
		}
	}
	if (choice == 2) //if they want to sort by the album
	{
		while (!isSorted)
		{
			isSorted = 1;
			Node* pCur = pList->pHead, * pAfter = pCur->pNext;
			while (pAfter != NULL)
			{
				if (strcmp(pCur->data.album, pAfter->data.album) > 0) 
				{
					temp = pCur->data;
					pCur->data = pAfter->data;
					pAfter->data = temp;
					isSorted = 0;
				}
				pCur = pAfter;
				pAfter = pAfter->pNext;
			}
		}
	}
	if (choice == 3) //if they want to sort by the genre
	{
		while (!isSorted)
		{
			isSorted = 1;
			Node* pCur = pList->pHead, * pAfter = pCur->pNext;
			while (pAfter != NULL)
			{
				if (strcmp(pCur->data.genre, pAfter->data.genre) > 0) 
				{
					temp = pCur->data;
					pCur->data = pAfter->data;
					pAfter->data = temp;
					isSorted = 0;
				}
				pCur = pAfter;
				pAfter = pAfter->pNext;
			}
		}
	}
	if (choice == 4) //if they want to sort by the song title
	{
		while (!isSorted)
		{
			isSorted = 1;
			Node* pCur = pList->pHead, * pAfter = pCur->pNext;
			while (pAfter != NULL)
			{
				if (strcmp(pCur->data.song, pAfter->data.song) > 0)
				{
					temp = pCur->data;
					pCur->data = pAfter->data;
					pAfter->data = temp;
					isSorted = 0;
				}
				pCur = pAfter;
				pAfter = pAfter->pNext;
			}
		}
	}
	if (choice == 5) //if they want to sort by the song length
	{
		while (!isSorted)
		{
			isSorted = 1;
			Node* pCur = pList->pHead, * pAfter = pCur->pNext;
			while (pAfter != NULL)
			{
				if (pCur->data.length.minutes < pAfter->data.length.minutes) //if the mintes values are different we just sort based off of that
				{
					temp = pCur->data;
					pCur->data = pAfter->data;
					pAfter->data = temp;
					isSorted = 0;
				}
				else if (pCur->data.length.minutes == pAfter->data.length.minutes) //but if they have the same minutes value
				{
					if (pCur->data.length.seconds < pAfter->data.length.seconds) //we check the seconds value and then sort based off of that
					{
						temp = pCur->data;
						pCur->data = pAfter->data;
						pAfter->data = temp;
						isSorted = 0;
					}
				}
				pCur = pAfter;
				pAfter = pAfter->pNext;
			}
		}
	}
	if (choice == 6) //if they want to sort by the times a song has been played
	{
		while (!isSorted)
		{
			isSorted = 1;
			Node* pCur = pList->pHead, * pAfter = pCur->pNext;
			while (pAfter != NULL)
			{
				if (pCur->data.timesPlayed < pCur->data.timesPlayed)
				{
					temp = pCur->data;
					pCur->data = pAfter->data;
					pAfter->data = temp;
					isSorted = 0;
				}
				pCur = pAfter;
				pAfter = pAfter->pNext;
			}
		}
	}
	if (choice == 7) //if they want to sort by the record's rating
	{
		while (!isSorted)
		{
			isSorted = 1;
			Node* pCur = pList->pHead, * pAfter = pCur->pNext;
			while (pAfter != NULL)
			{
				if (pCur->data.rating < pCur->data.rating)
				{
					temp = pCur->data;
					pCur->data = pAfter->data;
					pAfter->data = temp;
					isSorted = 0;
				}
				pCur = pAfter;
				pAfter = pAfter->pNext;
			}
		}
	}
	return 1;
}

/* * * * * * * * * * * * * * *
Function Name: displayByName
Date Created: 9.18
Date Last Modfied:
Description of Function: prompts the user for the name of an artist in the list and prints all the records
that have artists that match the user's input
Input parameters: the playlist
Returns: returns how many records matching the given artist are in the list
Preconditions: list has to be populated
Postconditions: nothing changes due to this function
* * * * * * * * * * * * * * */
int displaybyName(List pList)
{
	int count = 0;
	char searchArtist[50] = "";
	Node* pCur = pList.pHead;
	fgets(searchArtist, 50, stdin); //this is to ignore the previous enter character that was entered to get here
	printf("Enter the name of the artist you would like to search for, please be exact: ");
	fgets(searchArtist, 50, stdin);
	searchArtist[strcspn(searchArtist, "\n")] = 0; //gets rid of the "\n" at the end of an fgets
	while (pCur != NULL)
	{
		
		if (strcmp(pCur->data.artist, searchArtist) == 0) //if we find a record matching a given artist
		{
			printf("%s, %s, %s, %s, %d:%.2d, %d, %d\n", pCur->data.artist, pCur->data.album, pCur->data.genre, pCur->data.song, 
				pCur->data.length.minutes, 
				pCur->data.length.seconds, 
				pCur->data.timesPlayed,
				pCur->data.rating); //print the record information
			pCur->pPrev = pCur; //and then traverse to the next node in the list
			pCur = pCur->pNext;
			count++; //and increment the count variable for returning
		}
		if (strcmp(pCur->data.artist, searchArtist) != 0) //if we don't find the matching artist
		{
			pCur->pPrev = pCur; //we just traverse the list
			pCur = pCur->pNext;
		}
		if (pCur == NULL && count == 0)
		{
			printf("No artists found matching that name\n");
		}
	}
	return count;
}

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
void generateRandomOrder(List pList, int array[50])
{
	int i = 0, j = 0, number = 0;
	for (i = 0; i < countSongs(pList); i++) //for loop to generate an order based on the size of the playlist
	{
		array[i] = rand() % countSongs(pList) + 1; //generate a random number
		if (i == 0) //this is to prevent the for loop after this from looping infinitely
		{
			++i;
			array[i] = rand() % countSongs(pList) + 1;
		}
		for (j = 0; j < i; j++)
		{
			if (array[j] == array[i]) //if we find a dupe
			{
				--i; //we decrement i so it overwrites itself
			}
		}

	}
}
	