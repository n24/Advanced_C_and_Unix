
/*	Write a program to print a histogram (horizantal) of the frequencies of different characters
	in its input */

# include <stdio.h>
# include <ctype.h>

int main (void) {
	int c, i, j, count[26] = {0};

	printf ("Enter the text (use Ctrl-D to end):\n");
	while ((c = getchar()) != EOF) {	// Accept the input from keyboard.
		if (islower (c))
			count[c - 97]++;		// Increment the count of corresponding character.	
		else if (isupper (c))
			count[c - 65]++;
	}
	
	for (i = 0; i < 26; i++)
		if (count[i]) {
			printf ("%c: ",(i + 97));
			for (j = 0; j < count[i]; j++)
				putchar ('.');
			putchar ('\n');
		}

	return 0;
}
