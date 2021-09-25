#include "Header.h"
#include "TestFunctions.h"

/* * * * * * * * * * * * * * *
Function Name: testCountSongs
Date Created:9/16
Date Last Modfied: 9/15
Description of Function: This function tests that countSongs can return the right amount of elements
Input parameters: the list
Returns: 1 if it successfully counts, 0 if it doesn't
Preconditions: needs a populated list
Postconditions:
* * * * * * * * * * * * * * */
int testCountSongs(void)
{
	List tempList = { NULL }; //creating a temp list and initializing it to empty
	initList(&tempList);
	Temp d1 = { "Jacob", "Collier", "\0", "Djesse Volume 3", "All I Need", "Alt Pop", 3, 23, 5, 5 };
	Temp d2 = { "\0", "\0", "Vulfpeck", "The Beatiful Game", "Animal Sprits", "Funk", 3, 45, 5, 5 };
	insertAtFront(&tempList, d1);
	insertAtFront(&tempList, d2);
	return countSongs(tempList);
	
}

/* * * * * * * * * * * * * * *
Function Name: testInsert
Date Created: 9.22
Date Last Modfied: 9.22
Description of Function: This function takes a sample piece of data from the PA description and tests the loadPlaylist function by inserting
a record with bad data and then printing the node in the list
Input parameters: nothing, it's void
Returns: nothing, it's void
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
void testInsert(void)
{
	List testList = { NULL }; //create temp list for testing
	initList(&testList); //initialize the list
	loadTest(&testList);
	int print = printPlaylist(testList);
}

/* * * * * * * * * * * * * * *
Function Name:loadTest
Date Created: 9.22
Date Last Modfied: 9.22
Description of Function: This has the exact same code as loadPlaylist for my main functions
the only difference is the different infile name
Input parameters: Pointer to a list
Returns: nothing, it's void
Preconditions:
Postconditions: List will be populated
* * * * * * * * * * * * * * */
void loadTest(List* pList)
{
	printf("Loading your playlist...\n");
	Sleep(3000);
	FILE* infile = fopen("testData.csv", "r"); //opening the test data for mode read
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
	return;
}

/* * * * * * * * * * * * * * *
Function Name:testDelete
Date Created:9.22
Date Last Modfied: 9.22
Description of Function: Tests the deleteSong function by making a temp list and then deleting from it
Input parameters: nothing it's void
Returns: nothing it's void
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
void testDelete(void) 
{
	List testList = { NULL };
	initList(&testList);

	/*When testing this function, nothing will come up on the terminal, press enter then it will procede like normal
	This is intended because there's a user input field before the prompts to ignore a previous enter in main*/

	if (addItem(&testList) == 1) //using this function to add the katy perry record to the list
	{
		int success = deleteItem(&testList);
		if (success = 1)
		{
			if (countSongs(testList) == 0)
			{
				printf("Record deleted successfully\n");
			}
		}
	}
}

void testShuffle(void)
{
	List testList = { NULL };
	initList(&testList);
	if (loadPlaylist(&testList) == 1)
	{
		int success = notScuffedShuffle(testList);
	}
}