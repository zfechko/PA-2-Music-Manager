#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H
#include "Header.h"

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
int testCountSongs(void);


/* * * * * * * * * * * * * * *
Function Name: testInsert
Date Created: 9.22
Date Last Modfied: 9.22
Description of Function: This function takes a sample piece of data from the PA description and tests the loadPlaylist function by inserting
a record with bad data and then printing the node in the list
Input parameters: nothing, it's void
Returns: nothing it's void
Preconditions:
Postconditions:
* * * * * * * * * * * * * * */
void testInsert(void);

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
void loadTest(List* pList);

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
void testDelete(void);

void testShuffle(void);
#endif
