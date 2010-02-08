#include<stdio.h>
#include"mystring.h"

#define TRUE 1
#define FALSE 0
#define MAX_CONTACT 100 // maximum number of contacts
#define MAX_FIELDLEN 50 // maximum length of a field string
#define MAX_LINELEN 250 // maximum length of a user-input line 
#define NUM_FIELDS 7
#define NAME 0
#define TELEPHONE 1
#define ADDRESS 2
#define CITY 3
#define STATE 4
#define ZIPCODE 5
#define EMAIL 6
#define DEBUG 0

void printContacts(char[][NUM_FIELDS][MAX_FIELDLEN], int);
int readContacts(char[][NUM_FIELDS][MAX_FIELDLEN]);
int readContactsStruct(struct contact *);


int main()
{
	printf("Please input the initial data set:\n");
	
	/* Contacts are stored in a multidimensional array where rows
	 * are individual contacts and columns are data fields. */
	//char contacts[MAX_CONTACT][NUM_FIELDS][MAX_FIELDLEN];
	
	struct contact
	{
		char name[MAX_FIELDLEN];
		char telephone[MAX_FIELDLEN];
		char address[MAX_FIELDLEN];
		char city[MAX_FIELDLEN];
		char state[MAX_FIELDLEN];
		char zipcode[MAX_FIELDLEN];
		char email[MAX_FIELDLEN];
	};
	
	/* Store an array of contact structs */
	struct contact contacts[MAX_CONTACT];
	
	// Read contacts from input stream
	int numContacts = readContactsStruct(contacts);
	
	if (DEBUG)
		printContacts(contacts, numContacts);
}

/**
 * Read contacts from stdin line by line.
 * In the contacts array, rows are individual
 * contacts, and columns are each field.  Each
 * field's value is stored as a character array pointer.
 *
 * Returns number of contacts.
 */
int readContactsStruct(struct contact contacts[])
{
	int moreData = TRUE, row = 0, numContacts = 0;

	while (moreData)
	{
		char c, *field, lastChar = '\0';
		int fieldNum = 0, i = 0;
		struct contact con;
		while ((c = getchar()) != '\n')
		{
			switch (field)
			{
				case NAME: field = con.name; break;
				case TELEPHONE: field = con.telephone; break;
				case ADDRESS: field = con.address; break;
				case CITY: field = con.city; break;
				case STATE: field = con.state; break;
				case ZIPCODE: field = con.zipcode; break;
				case EMAIL: field = con.email; break;
			}
			
			if (c == ',')
			{
				// Delete trailing space
				if (*(field-1) == ' '))
					*(field-1) = '\0';
				else
					*field = '\0';
					
				// Increment field counter so we know which 
				// field to save character to.
				fieldNum++;
			}
			else
			{
				if (c == ' ' && !isalnum(lastChar))
					continue;
				lastChar = c;
				*field++ = c;
			}
		}
	}
	
	return numContacts;
}

/**
 * Read contacts from stdin line by line.
 * In the contacts array, rows are individual
 * contacts, and columns are each field.  Each
 * field's value is stored as a character array pointer.
 *
 * Returns number of contacts.
 */
int readContacts(char contacts[][NUM_FIELDS][MAX_FIELDLEN])
{
	int moreData = TRUE, row = 0, column = 0, numContacts = 0;
	while (moreData)
	{
		char c, lastChar = '\0';
		int i = 0;
		while (c = getchar())
		{
			// Skip duplicate spaces
			if (c == ' ' && !isalnum(lastChar))
				continue;
			
			// Save for next time
			lastChar = c;
			
			// If we see a newline with no input on that line, quit.
			// Otherwise, increment the number of contacts.
			if (c == '\n' && column == 0)
			{
				moreData = FALSE;
				break;
			}
			else if (c == '\n' && column > 0)
			{
				numContacts++;
				row++;
				column = 0;
				continue;
			}
			
			// If we find a comma, terminate the current string.
			// Otherwise, append the character to the current string.
			if (c == ',' || (c == '\n' && i > 0))
			{
				if (i > 0 && contacts[row][column][i-1] == ' ')
					contacts[row][column][i-1] = '\0';
				else
				{
					if (DEBUG)
						printf("[i-1]='%c', i=%d, row=%d, column=%d\n", contacts[row][column][i-1], i, row, column);
					contacts[row][column][i] = '\0';
				}
				i = 0;
			}
			else
			{
				contacts[row][column][i++] = c;
			}
			if (c == ',')
				column++;
		}
	}
	
	return numContacts;
}

/**
 * Prints out the list of contacts for debugging
 */
void printContacts(char contacts[][NUM_FIELDS][MAX_FIELDLEN], int numContacts)
{
	int i, j, k;
	for (i = 0; i < numContacts; i++)
	{
		for (j = 0; j < NUM_FIELDS; j++)
		{
			for (k = 0; k < MAX_FIELDLEN && contacts[i][j][k] != '\0'; k++)
			{
				putchar(contacts[i][j][k]);
			}
			if (j != NUM_FIELDS - 1)
				putchar(',');
		}
		putchar('\n');
	}
}