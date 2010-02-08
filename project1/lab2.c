#include <stdio.h>

int getint(), isValidInput(int);

int main()
{
	// read integers
	int a, b;
	
	printf("Please enter the first integer between 1 and 100: ");
	if (!isValidInput(a = getint()))
	{
		printf("Invalid Input\n");
		return -1;
	}
		
	printf("Please enter the second integer between 1 and 100: ");	
	if (!isValidInput(b = getint()))
	{
		printf("Invalid Input\n");
		return -1;
	}
	
	// compute greatest common divisor
	//printf("%d, %d\n", a, b);
	int i, gcd = 1;
	for (i = 1; i <= a && i <= b; i++)
	{
		//printf("a mod %d = %d\nb mod %d = %d\n", i, a % i, i, b % i);
		if (a % i == 0 && b % i == 0)
		{
			gcd = i;
		}
	}
	printf("%d\n", gcd);
	
	if (gcd == 1)
	{
		printf("relatively prime\n");
	}
	
	return 0;
}

/* 
 * Gets next int from stdio.
 * Returns -1 if input is invalid.
 */
int getint()
{
	int n = 0, m = 0;
	
	while ((m = getchar()) != '\n')
	{
		/* 
		 * Convert from character to integer by
		 * subtracting 48.
		 */
		m -= '0';
		if (m >= 0 && m <= 9)
		{
			n *= 10;
			n += m;
		}
		else
		{
			return -1;
		}
	}
	
	return n;
}

int isValidInput(int input)
{
	return (input >= 1 && input <= 100);
}
