/* 
 * Project 1
 * by Ben Goosman
 * Section 0101
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int TRUE = 1, 
		  FALSE = 0, 
		  MAX_INPUT_CHARS = 1000,
		  NUM_ASCII_CHARS = 255;
int isValidOption(int);
void clearInputBuffer(), getText(char *, int);

int main()
{
	int keepLooping = TRUE;
	char text[MAX_INPUT_CHARS + 1]; // +1 for \0 character
	text[0] = '\0';
	
	// print menu
	printf("1. Input Text\n2. Text Stats\n3. Find Substring\n4. Reverse Text\n5. Quit\n\n\n\n");
	
	// infinite loop to accept user input
	while (keepLooping)
	{		
		// get user option
		printf("===============Input Option:");
		int option;
		if (isValidOption(option = getMenuOption()))
		{		
			switch (option)
			{
				case 1:
				{
					int keepPrompting = TRUE;
					while (keepPrompting)
					{
						char c;
						int i = 0;
						
						keepPrompting = FALSE;
						while ((c = getchar()) != '\n')
						{
							text[i++] = c;
							if (i > MAX_INPUT_CHARS)
							{
								printf("Text no more than 1000 characters. Please enter again.\n");
								clearInputBuffer();
								keepPrompting = TRUE;
								break;
							}
						}
						
						if (!keepPrompting)
							if (text[i-1] == '\n')
								text[i-1] = '\0';
							else
								text[i] = '\0';
					}
		
					printf("\n\n\n");
						
					break;
				}
				case 2:
				{
					// Text Stats
					int i, inWord = FALSE, wordCount = 0, sentenceCount = 0;
					// index is ascii char; index value is frequency
					int freqChars[NUM_ASCII_CHARS];
					// initialize freqChars to 0's
					for (i = 0; i < NUM_ASCII_CHARS; i++)
						freqChars[i] = 0;
					
					// loop over each character in input
					for (i = 0; i < strlen(text); i++)
					{
						// check if word
						if (isalpha(text[i]) && !inWord)
						{
							inWord = TRUE;
							wordCount++;
						}
						else if (!isalpha(text[i]) && inWord)
						{
							inWord = FALSE;
						}
						
						// check for sentence
						if (i < strlen(text) 
							&& (text[i] == '.' || text[i] == '!' || text[i] == '?') 
							&& (text[i+1] == ' ' || text[i+1] == '\0' || text[i+1] == '\'' || text[i+1] == '"'))
							sentenceCount++;

						// increment character's frequency
						freqChars[text[i]]++;
					}
					
					printf("Character Number: %d\nWord Number: %d\nSentence Number: %d\nMost Frequent Characters:\n",
						strlen(text), wordCount, sentenceCount);
						
					int counter = 0, largest = 0;
					do
					{
						largest = 0;
						
						// find largest
						for (i = 0; i < NUM_ASCII_CHARS; i++)
						{						
							if (freqChars[i] > largest)
								largest = freqChars[i];
						}
						
						if (largest != 0)
						{
							// find and print ties
							for (i = 0; i < NUM_ASCII_CHARS; i++)
							{
								if (freqChars[i] == largest)
								{
									// print value. e.g. 'c':4
									printf("'%c':%d\n", i, freqChars[i]);
									// delete largest values for next iteration
									freqChars[i] = 0;
								}
							}
						}
						else
							break;
					} 
					while (++counter < 3);
		
					printf("\n\n\n");
					
					break;
				}
				case 3:
				{
					// Find Substring
					printf("Please Input Substring\n");
					
					char substring[MAX_INPUT_CHARS+1], c;
					int i = 0;
					
					while ((c = getchar()) != '\n')
					{
						substring[i++] = c;
						if (i > MAX_INPUT_CHARS)
						{
							printf("Text no more than 1000 characters. Substring not found.\n");
							clearInputBuffer();
							break;
						}
					}
					
					if (substring[i-1] == '\n')
						substring[i-1] = '\0';
					else
						substring[i] = '\0';
						
					if (substring[0] != '\0')
					{
						char *pos = text;
						int counter = 0;
						
						// cut off the portion we have already visited by advancing the pos pointer
						while ((pos = strstr(pos, substring)) > 0)
						{
							counter++;
							pos++;
						}
							
						printf("found %d occurrence(s)\n", counter);
					}
		
					printf("\n\n\n");
					
					break;
				}
				case 4:
				{
					// Reverse Text
					
					printf("Reversed Text:\n");
					
					// reverse whole string character by character
					int i, textLength = strlen(text);
					for (i = 0; i < textLength-i-1; i++)
					{
						char temp = text[i];
						text[i] = text[textLength-1-i];
						text[textLength-1-i] = temp;
					}
					
					// reverse characters in each word
					int inWord = FALSE, j, k;
					for (i = 0; i < textLength; i++)
					{
						if (text[i] != '\t' && text[i] != ' ' && !inWord)
						{
							inWord = TRUE;
							int wordLength = 0;
							// find word length
							for (j = i; text[j] != '\t' && text[j] != ' ' && text[j] != '\0'; j++, wordLength++);
							// reverse word
							for (k = 0; k < wordLength-k-1; k++)
							{
								char temp = text[k+i];
								text[k+i] = text[wordLength+i-k-1];
								text[wordLength+i-k-1] = temp;
							}
						}
						else if (!(text[i] != '\t' && text[i] != ' '))
						{
							inWord = FALSE;
						}
						else
						{
							continue;
						}
					}
					
					printf("%s\n", text);
		
					printf("\n\n\n");
					
					break;
				}
				case 5:
					// Quit
					keepLooping = FALSE;
					break;
			} // end switch
		}
		else
		{
			printf("Invalid Input.\n");
		}
	}

	return 0;
}

void getText(char *buffer, int size)
{
   int i = 0;
   for ( ;; )
   {
      int ch = fgetc(stdin);
      if ( ch == '\n' || ch == EOF )
      {
         break;
      }
      if ( i < size - 1 )
      {
         buffer[i++] = ch;
      }
   }
   buffer[i] = '\0';
}

int getMenuOption()
{
	int option;
	scanf("%d", &option); // read integer into option
	clearInputBuffer();
	return option;
}

void clearInputBuffer()
{
	//scanf("%*[^\n]"); // delete remaining characters
	scanf("%*[^\n]"); // delete remaining characters
	(void) fgetc(stdin); // delete \n character
	//char c;
	//while ((c = getchar()) != '\n');
}

int isValidOption(int option)
{
	return (option >= 1 && option <= 5);
}